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
                size_type dend1 = Helper::int_size(lhs),
                          dend2 = Helper::int_size(rhs)
                          ;
                bool borrowed = false;
                ld carry = 0;
                for( size_type fit(0), sit(0)
                     ; !( (fend = (fit >= dend1)) && (sit >= dend2) )
                     ;
                ){
                    // Determine each digit to add based on if the end of
                    //  the digit list is reached
                    ld operand1 = lhs.sign() * (fend ? 0 : Helper::digit(lhs, fit)),
                       operand2 = rhs_sign * ((sit < dend2) ? Helper::digit(rhs, sit) : 0)
                       ;

                    // Deal with borrowing when there is a 0-x case
                    if(sign_neq){
                        // -operand1 + 0
                        if( comp < 0
                            && Helper::digit(lhs, fit) != 0
                            && Helper::digit(rhs, sit) == 0
                            && rhs_sign < 0
                            ){
                            operand2 -= Helper::base(lhs);
                            borrowed = true;
                        }
                        // 0 - operand2
                        if( comp > 0
                            && Helper::digit(lhs, fit) == 0
                            && Helper::digit(rhs, sit) != 0
                            && lhs.sign() < 0
                            ){
                            operand1 -= Helper::base(lhs);
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
                    if(Helper::base(lhs) <= catalyst){
                        // Both signs must be equal for catalyst > base
                        catalyst -= Helper::base(lhs);
                        carry = lhs.sign();
                    } else if(catalyst < 0){
                        catalyst += Helper::base(lhs);
                        carry = -1;
                    } else if(!borrowed){
                        carry = 0;
                    }

                    // Store calculated sum into first digit list
                    lhs.force_assign(fit, catalyst);
                    /*
                    if(fend) lhs.append(catalyst);
                    else     lhs.assign(fit, catalyst);
                    */

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

                Helper::remove_excess_zeros(lhs);
            }

            template <typename IntType>
            void multiply_factor(IntType& num, typename IntType::digit_type fac){
                // Deal with trivial multiplications if fac is 0 or 1
                if(fac == 0){
                    Helper::make_zero(num);
                    return;
                } else if(fac == 1){
                    return;
                }

                const typename IntType::digit_type base = Helper::base(num);

                fac %= base; // Make sure factor is limited

                using ld_type = typename IntType::catalyst_type;
                using size_type = typename IntType::size_type;

                // Iterate through each digit and add and carry
                ld_type carry = 0;
                for(size_type i = 0; i < Helper::int_size(num); ++i){

                    // Perform main addition
                    ld_type dig = Helper::digit(num, i);
                    ld_type catalyst = carry + fac * dig;

                    // Deal with carrying
                    if(base <= catalyst){
                        carry = catalyst / base;
                        catalyst = std::fmod(catalyst, base);
                    } else {
                        carry = 0;
                    }

                    // Store calculated product into number
                    num.assign(i, catalyst);
                }

                // Deal with overflow
                typename IntType::digit_type carry_int = carry;
                while(carry_int > 0){
                    num.append(carry_int % base);
                    carry_int /= base;
                }

                Helper::remove_excess_zeros(num);
            }

            namespace Arith_Helper{
                // Specify the minimum number of digits before the
                // multiplication function switches algorithms
                static constexpr std::size_t acc_sw_min = 100000;
                template <typename IntType>
                using bucket_type = std::vector<IntType>;

                template<typename IntType>
                void accumulate(IntType& dest, const bucket_type<IntType>& bucket){
                    using ld_type = typename IntType::catalyst_type;
                    using size_type = typename IntType::size_type;

                    // Find the length of the longest integer
                    size_type max_len = Helper::int_size(bucket.back());
                    for(const auto& num : bucket){
                        if(Helper::int_size(num) > max_len)
                            max_len = Helper::int_size(num);
                    }

                    // Take the sum of each digit place
                    ld_type carry = 0;
                    Helper::make_zero(dest);
                    for(size_type i = 0; i < max_len; ++i){

                        // Perform main addition
                        ld_type catalyst = carry;
                        for(const auto& num : bucket){
                            if(i < Helper::int_size(num))
                                catalyst += Helper::digit(num, i);
                        }

                        // Deal with carrying
                        if(Helper::base(dest) <= catalyst){
                            carry = catalyst / Helper::base(dest);
                            catalyst = std::fmod(catalyst, Helper::base(dest));
                        } else {
                            carry = 0;
                        }

                        // Store calculated sum into number
                        dest.force_assign(i, catalyst);
                    }

                    // Deal with overflow
                    while(carry > 0){
                        dest.append(std::fmod(carry, Helper::base(dest)));
                        carry /= Helper::base(dest);
                    }

                    Helper::remove_excess_zeros(dest);
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
                    for(; idx < Helper::int_size(rhs); ++idx){
                        IntType addend(base_adder);
                        multiply_factor(addend, Helper::digit(rhs, idx));

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
                    IntType product = Helper::make_zero_temp(lhs);
                    for(; idx < Helper::int_size(rhs); ++idx){
                        IntType addend(base_adder);
                        multiply_factor(addend, Helper::digit(rhs, idx));

                        addend.shift_left(idx-zeros);

                        add(product, addend);
                    }
                    lhs = std::move(product);
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
                while(Helper::digit(big, total_z_count) == 0)  ++total_z_count;
                big.shift_right(total_z_count);
                // Tally the zeros from rhs
                while(Helper::digit(rhs, idx) == 0){
                    ++total_z_count;
                    ++idx;
                }

                //  Choose which multiplication algorithm to use based on
                // the number of digits.
                //  multiply_accumulation() is faster, but it stores many
                // integers, which can take up a lot of space.
                //  multiply_gathering() does not store more than one extra
                // number at a time but is slower.
                if(Helper::int_size(rhs) < Arith_Helper::acc_sw_min)
                    Arith_Helper::multiply_accumulation(lhs, rhs, big, idx);
                else
                    Arith_Helper::multiply_gathering(lhs, rhs, big, idx);

                // Attach the zeros and use the new numeric sign
                lhs.shift_left(total_z_count);
                lhs.sign(sign_hold);
            }

            namespace Arith_Helper{
                template <typename Size, typename Catalyst, typename IntType>
                Size fast_div_count( Size start_idx,
                                     const IntType& mod, const IntType& rhs
                ){
                    Catalyst rhs_lead = 0, mod_lead = 0;

                    // Calculate leading digits for rhs and mod
                    Catalyst ten_mult = 1;
                    for( Size i = start_idx;
                         i < Helper::int_size(mod);
                         ++i, ten_mult *= Helper::base(mod)
                    ){
                        if(i < Helper::int_size(rhs))
                            rhs_lead += ten_mult * Helper::digit(rhs, i);
                        mod_lead += ten_mult * Helper::digit(mod, i);
                    }

                    Catalyst rhs_lead_copy = rhs_lead;

                    Size toreturn = 0;
                    while(!(mod_lead < rhs_lead)){
                        ++toreturn;
                        rhs_lead += rhs_lead_copy;
                    }
                    return toreturn;
                }

                template <typename Size, typename IntType>
                Size slow_div_count( Size start_idx,
                                     const IntType& mod, const IntType& rhs
                ){
                    IntType rhs_lead(Helper::make_zero_temp(mod)),
                            mod_lead(Helper::make_zero_temp(mod))
                            ;

                    // Calculate leading digits for rhs and mod
                    for(Size i = start_idx; i < Helper::int_size(mod); ++i){
                        if(i < Helper::int_size(rhs))
                            rhs_lead.append(Helper::digit(rhs, i));
                        mod_lead.append(Helper::digit(mod, i));
                    }

                    IntType rhs_lead_copy = rhs_lead;

                    Size toreturn = 0;
                    while( !(compare_lists( mod_lead.digit_list(),
                                            rhs_lead.digit_list()
                                            ) < 0)
                    ){
                        ++toreturn;
                        add(rhs_lead, rhs_lead_copy);
                    }
                    return toreturn;
                }

                template <typename IntType>
                typename IntType::size_type div_core( IntType& mod,
                                                      const IntType& rhs
                ){
                    // Look at the leading base or more digits to determine
                    // how many subtractions are needed to make rhs >= mod.
                    // It is assumed that rhs has the same or less digits
                    // than mod.

                    // rhs is already larger --> no subtract needed
                    if(Helper::int_size(rhs) > Helper::int_size(mod)) return 0;

                    using size_type = typename IntType::size_type;

                    // Max propogation refers to the maximum number of
                    // digits the act of carrying can propogate when one
                    // number is multiplied by a single digit number,
                    // as is the case with multiply_factor(). Take the
                    // worst case scenario: 1234567890123456789 * 9
                    //                      [base 10]
                    // Notice that carrying propogates until 0 is reached,
                    // when it is impossible to have another carry.
                    // Therefore, the maximum propogation is equal to base.
                    const size_type max_prop = Helper::base(mod);
                    size_type min_idx = (Helper::int_size(rhs) > max_prop)
                                      ? (Helper::int_size(rhs)-max_prop-1)
                                      : 0
                                      ;

                    size_type sub_count = 0;

                #ifndef USE_SLOW_DIV_CORE
                    //Algorithm depending on the precision of IntType::catalyst_type
                    sub_count = fast_div_count
                        <size_type, typename IntType::catalyst_type>
                        (min_idx, mod, rhs);
                #else
                    sub_count = slow_div_count<size_type>(min_idx, mod, rhs);
                #endif

                    // Update modulus
                    IntType rhs_mult(rhs);
                    multiply_factor(rhs_mult, sub_count);
                    rhs_mult.sign(-1);
                    add(mod, rhs_mult);

                    return sub_count;
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

                        size_type sub_count = div_core(modulus, shifter);

                        // Leverage multiply_factor() to avoid
                        // reduce number of additions.
                        multiply_factor(addend, sub_count);
                        if(acc) bucket.emplace_back(addend);
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

                size_type t_counter(Helper::int_size(modulus)-Helper::int_size(rhs));

                // Perform division by subtracting rhs_shift at a time and
                //  counting how many subtractions were performed
                t_counter += 1; // Increase counter by 1 after shifting rhs_shift,
                                // because in elementary division, we need to
                                // account for subtraction at the one's place.
                                // This, there are always (# of divisor digits) + 1
                                // subtractons that happen.
                Arith_Helper::div_acc_gath( rhs, quotient, modulus,
                                            t_counter,
                                            Helper::int_size(modulus)
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