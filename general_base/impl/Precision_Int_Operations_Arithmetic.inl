#include "Precision_Shared_Helpers.h"
#include "Precision_Exception.h"

#include <cmath>    // For std::fmod
#include <vector>   // For custom bucket type

// Undefine this switch to have the divide_mod algorithm use IntType
// for the subtractions in the faster algorithm. This will slow down
// the algorithm but will remove dependency on the precision of
// IntType::catalyst_type
//#define USE_SLOW_DIV_CORE

namespace Precision{
    namespace Volatile{
        namespace Int_Operations {
            //Arithmetic operators
            template <typename IntType>
            void add_diglist(
                typename IntType::diglist_type& diglist1,
                const typename IntType::diglist_type& diglist2,
                typename IntType::sign_type& sign1,
                typename IntType::sign_type sign2,
                typename IntType::digit_type base
            ){
                // Deal with cases where the number is equal to 0
                if(is_zero_list(diglist2)) return;
                if(is_zero_list(diglist1)){
                    diglist1 = diglist2;
                    sign1 = sign2;
                    return;
                }

                // Determine which number is larger
                short comp = compare_lists(diglist1, diglist2);
                bool sign_neq = sign1.value() != sign2.value();

                using ld_type = typename IntType::catalyst_type;

                // Iterate through each digit and add, carry, and borrow as needed
                bool fend(false);// Track when iterator reach the end
                auto dend1 = diglist1.end(), dend2 = diglist2.end();
                bool borrowed = false;
                ld_type carry = 0;
                for( auto fit(diglist1.begin()), sit(diglist2.begin())
                     ; !( (fend = (fit == dend1)) && (sit == dend2) )
                     ;
                ){
                    // Determine each digit to add based on if the end of
                    //  the digit list is reached
                    ld_type operand1 = sign1 * (fend ? 0 : *fit),
                            operand2 = sign2 * ((sit != dend2) ? *sit : 0)
                            ;

                    // Deal with borrowing when there is a 0-x case
                    if(sign_neq){
                        // -operand1 + 0
                        if( comp < 0
                            && *fit != 0 && *sit == 0
                            && sign2.is_negative()
                            ){
                            operand2 -= base;
                            borrowed = true;
                        }
                        // 0 - operand2
                        if( comp > 0
                            && *fit == 0 && *sit != 0
                            && sign1.is_negative()
                            ){
                            operand1 -= base;
                            borrowed = true;
                        }
                    }

                    // Perform the main addition between two digits
                    ld_type catalyst = operand1
                                     + operand2
                                     + carry
                                     ;

                    if(borrowed){
                        catalyst *= -1;
                        carry = 1;
                    }

                    if(!sign_neq){
                        catalyst *= sign1;
                    }

                    // Deal with carrying and borrowing
                    if(base <= catalyst){
                        // Both signs must be equal for catalyst > base
                        catalyst -= base;
                        carry = sign1.value();
                    } else if(catalyst < 0){
                        catalyst += base;
                        carry = -1;
                    } else if(!borrowed){
                        carry = 0;
                    }

                    // Store calculated sum into first digit list
                    if(fend) diglist1.push_back(catalyst);
                    else     *fit = catalyst;

                    // Update iterators as needed
                    if(!fend) ++fit;
                    if(sit != dend2) ++sit;
                } // End for loop

                // Deal with over and underflow
                if((carry > 0 || carry < 0) && !borrowed){
                    diglist1.push_back(1);
                }

                // Store the final numerical sign
                if(comp < 0) sign1 = sign2;

                // Remove excess 0's
                while(diglist1.size() > 1 && diglist1.back() == 0)
                    diglist1.pop_back();
            }

            template <typename IntType>
            void add(IntType& lhs, const IntType& rhs, short add_sign){
                // Deal with cases where the number is equal to 0
                if(Helper::is_zero(rhs)) return;
                if(Helper::is_zero(lhs)){
                    lhs = rhs;
                    return;
                }

                // Determine sign of rhs based on addition or subtraction
                typename IntType::sign_type rhs_sign(rhs.sign() * add_sign);

                // Determine which number is larger
                short comp = compare_lists(lhs.digit_list(), rhs.digit_list());
                bool sign_neq = lhs.sign() != rhs.sign();

                using ld = typename IntType::catalyst_type;
                using size_type = typename IntType::size_type;

                // Iterate through each digit and add, carry, and borrow as needed
                bool fend(false);// Track when iterator reach the end
                size_type dend1 = lhs.count_digits(), dend2 = rhs.count_digits();
                bool borrowed = false;
                ld carry = 0;
                for( size_type fit(0), sit(0)
                     ; !( (fend = (fit >= dend1)) && (sit >= dend2) )
                     ;
                ){
                    // Determine each digit to add based on if the end of
                    //  the digit list is reached
                    ld operand1 = lhs.sign() * (fend ? 0 : lhs.digit(fit)),
                       operand2 = rhs_sign * ((sit < dend2) ? rhs.digit(sit) : 0)
                       ;

                    // Deal with borrowing when there is a 0-x case
                    if(sign_neq){
                        // -operand1 + 0
                        if( comp < 0
                            && lhs.digit(fit) != 0 && rhs.digit(sit) == 0
                            && rhs_sign.is_negative()
                            ){
                            operand2 -= lhs.base();
                            borrowed = true;
                        }
                        // 0 - operand2
                        if( comp > 0
                            && lhs.digit(fit) == 0 && rhs.digit(sit) != 0
                            && lhs.sign().is_negative()
                            ){
                            operand1 -= lhs.base();
                            borrowed = true;
                        }
                    }

                    // Perform the main addition between two digits
                    ld catalyst = operand1
                                  + operand2
                                  + carry
                                  ;

                    if(borrowed){
                        catalyst *= -1;
                        carry = 1;
                    }

                    if(!sign_neq){
                        catalyst *= lhs.sign();
                    }

                    // Deal with carrying and borrowing
                    if(lhs.base() <= catalyst){
                        // Both signs must be equal for catalyst > base
                        catalyst -= lhs.base();
                        carry = lhs.sign().value();
                    } else if(catalyst < 0){
                        catalyst += lhs.base();
                        carry = -1;
                    } else if(!borrowed){
                        carry = 0;
                    }

                    // Store calculated sum into first digit list
                    if(fend) lhs.append(catalyst);
                    else     lhs.digit(fit, catalyst);

                    // Update iterators as needed
                    if(!fend) ++fit;
                    if(sit < dend2) ++sit;
                } // End for loop

                // Deal with over and underflow
                if((carry > 0 || carry < 0) && !borrowed){
                    lhs.append(1);
                }

                // Store the final numerical sign
                if(comp < 0) lhs.sign(rhs.sign());

                // Remove excess 0's
                while(lhs.count_digits() > 1 && lhs.digit(lhs.count_digits()-1) == 0)
                    lhs.detach();
            }

            template <typename IntType>
            void multiply_diglist(IntType& num, typename IntType::digit_type fac){
                // Deal with trivial multiplications if fac is 0 or 1
                if(fac == 0){
                    Helper::make_zero(num);
                    return;
                } else if(fac == 1){
                    return;
                }

                const typename IntType::digit_type base = num.base();

                fac %= base; // Make sure factor is limited

                using ld_type = typename IntType::catalyst_type;
                using size_type = typename IntType::size_type;

                // Iterate through each digit and add and carry
                ld_type carry = 0;
                for(size_type i = 0; i < num.count_digits(); ++i){

                    // Perform main addition
                    ld_type dig = num.digit(i);
                    ld_type catalyst = carry + fac * dig;

                    // Deal with carrying
                    if(base <= catalyst){
                        carry = catalyst / base;
                        catalyst = std::fmod(catalyst, base);
                    } else {
                        carry = 0;
                    }

                    // Store calculated product into number
                    num.digit(i, catalyst);
                }

                // Deal with overflow
                typename IntType::digit_type carry_int = carry;
                while(carry_int > 0){
                    num.append(carry_int % base);
                    carry_int /= base;
                }

                // Remove excess 0's
                while(num.count_digits() > 1 && num.digit(num.count_digits()-1) == 0)
                    num.detach();
            }

            namespace Arith_Helper{
                // Specify the minimum number of digits before the
                // multiplication function switches algorithms
                static constexpr std::size_t acc_sw_min = 1000;
                template <typename IntType>
                using bucket_type = std::vector<IntType>;

                template<typename IntType>
                void accumulate(IntType& dest, const bucket_type<IntType>& bucket){
                    using ld_type = typename IntType::catalyst_type;
                    using size_type = typename IntType::size_type;

                    // Find the length of the longest integer
                    size_type max_len = bucket.back().count_digits();
                    for(const auto& num : bucket){
                        if(num.count_digits() > max_len)
                            max_len = num.count_digits();
                    }

                    // Take the sum of each digit place
                    ld_type carry = 0;
                    Helper::make_zero(dest);
                    for(size_type i = 0; i < max_len; ++i){

                        // Perform main addition
                        ld_type catalyst = carry;
                        for(const auto& num : bucket){
                            if(i < num.count_digits()) catalyst += num.digit(i);
                        }

                        // Deal with carrying
                        if(dest.base() <= catalyst){
                            carry = catalyst / dest.base();
                            catalyst = std::fmod(catalyst, dest.base());
                        } else {
                            carry = 0;
                        }

                        // Store calculated sum into number
                        if(i >= dest.count_digits()) dest.append(catalyst);
                        else                         dest.digit(i, catalyst);
                    }

                    // Deal with overflow
                    while(carry > 0){
                        dest.append(std::fmod(carry, dest.base()));
                        carry /= dest.base();
                    }
                }

                template <typename IntType>
                void multiply_accumulation( IntType& lhs,
                                            const IntType& rhs,
                                            const IntType& base_adder,
                                            typename IntType::size_type idx
                ){
                    // Perform elementary multiplication using additions
                    // Instead of adding whole integers two at a time,
                    // store all addends in a bucket and sum all the
                    // digits one by one at the end.
                    const typename IntType::size_type zeros = idx;
                    bucket_type<IntType> bucket;
                    for(; idx < rhs.count_digits(); ++idx){
                        IntType addend(base_adder);
                        multiply_diglist(addend, rhs.digit(idx));

                        addend.shift_left(idx-zeros);

                        bucket.emplace_back(addend);
                    }

                    accumulate(lhs, bucket);
                }

                template <typename IntType>
                void multiply_gathering( IntType& lhs,
                                         const IntType& rhs,
                                         const IntType& base_adder,
                                         typename IntType::size_type idx
                ){
                    using size_type = typename IntType::size_type;

                    // Perform elementary multiplication using additions
                    const size_type zeros = idx;
                    Helper::make_zero(lhs);
                    for(; idx < rhs.count_digits(); ++idx){
                        IntType addend(base_adder);
                        multiply_diglist(addend, rhs.digit(idx));

                        addend.shift_left(idx-zeros);

                        add(lhs, addend);
                    }
                }
            }

            template <typename IntType>
            void multiply(IntType& lhs, const IntType& rhs){
                // Deal with easy cases when a number is -1, 0, or 1
                if(Helper::is_zero(rhs)){
                    Helper::make_zero(lhs);
                    return;
                }else if(Helper::is_zero(lhs) || Helper::is_one(rhs)){
                    return;
                }else if(Helper::is_one(lhs)){
                    lhs = rhs;
                    return;
                }else if(Helper::is_neg_one(rhs)){
                    Helper::negate(lhs);
                    return;
                }else if(Helper::is_neg_one(lhs)){
                    lhs = rhs;
                    Helper::negate(lhs);
                    return;
                }

                typedef typename IntType::sign_type sign_type;
                typedef typename IntType::size_type size_type;

                // Determine final numeric sign first
                sign_type sign_hold(lhs.sign() * rhs.sign());

                // Make a copy of the original number since original will
                //  be cleared later on.
                IntType big(lhs);

                // To reduce number of additions, tally the number
                //  of zeros to attach later.
                size_type total_z_count(0), idx = 0;
                // Tally the zeros from lhs
                while(big.digit(total_z_count) == 0)  ++total_z_count;
                big.shift_right(total_z_count);
                // Tally the zeros from rhs
                while(rhs.digit(idx) == 0){
                    ++total_z_count;
                    ++idx;
                }

                //  Choose which multiplication algorithm to use based on
                // the number of digits.
                //  multiply_accumulation() is faster, but it stores many
                // integers, which can take up a lot of space.
                //  multiply_gathering() does not store more than one extra
                // number at a time but is slower.
                if(rhs.count_digits() < Arith_Helper::acc_sw_min)
                    Arith_Helper::multiply_accumulation(lhs, rhs, big, idx);
                else
                    Arith_Helper::multiply_gathering(lhs, rhs, big, idx);

                // Attach the zeros and use the new numeric sign
                lhs.shift_left(total_z_count);
                lhs.sign(sign_hold);
            }

            namespace Arith_Helper{
                template <typename IntType>
                typename IntType::size_type div_core( IntType& mod,
                                                      const IntType& rhs
                ){
                    // Look at the leading base or more digits to determine
                    // how many subtractions are needed to make rhs >= mod.
                    // It is assumed that rhs has the same or less digits
                    // than mod.

                    // rhs is already larger --> no subtract needed
                    if(rhs.count_digits() > mod.count_digits()) return 0;

                    using size_type = typename IntType::size_type;

                    size_type subtraction_count = 0;

                    // Max propogation refers to the maximum number of
                    // digits the act of carrying can propogate when one
                    // number is multiplied by a single digit number,
                    // as is the case with multiply_diglist(). Take the
                    // worst case scenario: 1234567890123456789 * 9
                    //                      [base 10]
                    // Notice that carrying propogates until 0 is reached,
                    // when it is impossible to have another carry.
                    size_type max_propogation = mod.base();
                    size_type min_index = (rhs.count_digits() > max_propogation)
                                        ? (rhs.count_digits()-max_propogation-1)
                                        : 0
                                        ;

                #ifndef USE_SLOW_DIV_CORE
                    //Algorithm depending on the precision of IntType::catalyst_type
                    using ld = typename IntType::catalyst_type;

                    ld rhs_lead = 0, mod_lead = 0;

                    // Calculate leading digits for rhs and mod
                    ld ten_mult = 1;
                    for( size_type i = min_index;
                         i < mod.count_digits();
                         ++i, ten_mult *= mod.base()
                    ){
                        if(i < rhs.count_digits())
                            rhs_lead += ten_mult * rhs.digit(i);
                        mod_lead += ten_mult * mod.digit(i);
                    }

                    ld rhs_lead_copy = rhs_lead;

                    while(rhs_lead < mod_lead){
                        ++subtraction_count;
                        rhs_lead += rhs_lead_copy;
                    }
                #else
                    IntType rhs_lead(Helper::make_zero_temp(mod)),
                            mod_lead(Helper::make_zero_temp(mod))
                            ;

                    // Calculate leading digits for rhs and mod
                    for(size_type i = min_index; i < mod.count_digits(); ++i){
                        if(i < rhs.count_digits())
                            rhs_lead.append(rhs.digit(i));
                        mod_lead.append(mod.digit(i));
                    }

                    IntType rhs_lead_copy = rhs_lead;

                    while( compare_lists( rhs_lead.digit_list(),
                                          mod_lead.digit_list()
                                          ) < 0
                    ){
                        ++subtraction_count;
                        add(rhs_lead, rhs_lead_copy);
                    }
                #endif

                    // Update modulus
                    IntType rhs_mult(rhs);
                    multiply_diglist(rhs_mult, subtraction_count);
                    rhs_mult.sign(-1);
                    add(mod, rhs_mult);

                    return subtraction_count;
                }

                // Accumulate or gather
                template <typename IntType>
                void div_acc_gath( const IntType& rhs,
                                   IntType& quotient, IntType& modulus,
                                   typename IntType::size_type counter,
                                   bool acc
                ){
                    using size_type = typename IntType::size_type;

                    // shifter will be used to count the number of subtractions
                    // and will start as the largest possible such that lhs
                    // and rhs have the same number of digits.
                    IntType shifter(rhs.magnitude());
                    shifter.shift_left(counter-1);

                    bucket_type<IntType> bucket;
                    while(counter-- > 0){
                        IntType addend(Helper::make_one_temp(modulus));
                        addend.shift_left(counter);

                        size_type subtraction_count = div_core(modulus, shifter);

                        // Leverage multiply_diglist() to avoid
                        // reduce number of additions.
                        multiply_diglist(addend, subtraction_count);
                        if(acc) bucket.push_back(addend);
                        else    add(quotient, addend);

                        shifter.shift_right(1);
                    }
                    if(acc) accumulate(quotient, bucket);
                }
            }

            template <typename IntType>
            void divide_mod(
                const IntType& lhs, const IntType& rhs,
                IntType& quotient, IntType& modulus
            ){
                // Deal with easy cases when one number is 0 or 1.
                // Also deal with cases when the denominator > numerator
                if(Helper::is_zero(rhs)){
                    throw exception( exception::divide_by_zero,
                                     "Precision::Volatile::Int_Operations"
                                     "::divide_mod"
                                     "(const IntType&, const IntType&,"
                                     " IntType&, IntType&)"
                                     );
                }else if(Helper::is_one(rhs)){
                    quotient = lhs;
                    Helper::make_zero(modulus, lhs);
                    return;
                }else if(compare_lists(lhs.digit_list(), rhs.digit_list()) == 0){
                    Helper::make_one(quotient, lhs);
                    Helper::make_zero(modulus, lhs);

                    quotient.sign(lhs.sign() * rhs.sign());
                    return;
                }else if(compare_lists(lhs.digit_list(), rhs.digit_list()) < 0){
                    modulus = lhs;
                    Helper::make_zero(quotient, lhs);
                    return;
                }

                // Prepare variables used to store the results
                Helper::make_zero(quotient, lhs);
                modulus = lhs.magnitude();

                typedef typename IntType::size_type size_type;

                size_type t_counter(modulus.count_digits()-rhs.count_digits());

                // Perform division by subtracting rhs_shift at a time and
                //  counting how many subtractions were performed
                t_counter += 1; // Increase counter by 1 after shifting rhs_shift,
                                // because in elementary division, we need to
                                // account for subtraction at the one's place.
                                // This, there are always (# of divisor digits) + 1
                                // subtractons that happen.
                Arith_Helper::div_acc_gath( rhs, quotient, modulus,
                                            t_counter,
                                            modulus.count_digits()
                                                < Arith_Helper::acc_sw_min
                                            );

                // Determine final numerical sign
                typename IntType::sign_type new_sign(lhs.sign() * rhs.sign());
                quotient.sign(new_sign);
                modulus.sign(new_sign);
            }
        }
    }
}