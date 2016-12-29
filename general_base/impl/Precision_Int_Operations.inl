#include "Precision_Shared_Helpers.h"
#include "Precision_Exception.h"

#include "Type_Traits_Extended/Type_Traits_Ext.h" // For Type_Trait::any_true

#include <utility>  // For std::move and std::swap
#include <iterator> // For std::advance
#include <cmath>    // For std::fmod

namespace Precision{
    namespace Volatile{
        namespace Int_Operations {
            //Arithmetic operators
            template <typename IntType>
            void add(
                typename IntType::diglist_type& diglist1,
                const typename IntType::diglist_type& diglist2,
                typename IntType::sign_type& sign1,
                typename IntType::sign_type sign2,
                typename IntType::digit_type base
            ){
                // Deal with cases where the number is equal to 0
                if(is_zero_list(diglist2)) return;
                if(is_zero_list(diglist1)){
                    diglist1 = std::move(diglist2);
                    sign1 = sign2;
                    return;
                }

                // Determine which number is larger
                //short comp = compare_lists(diglist1, diglist2);
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
                for( size_type i = 0; i < num.count_digits(); ++i){

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
                    lhs.negate();
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
                //  of zeros to append later.
                size_type total_z_count(0), idx = 0;

                // Perform elementary multiplication using additions
                const size_type rhs_z_count = idx;
                Helper::make_zero(lhs);
                for(; idx < rhs.count_digits(); ++idx){
                    IntType addend(big);
                    multiply_diglist(addend, rhs.digit(idx));

                    addend.shift_left(idx-rhs_z_count);

                    lhs += addend;
                }

                // Append the zeros and use the new numeric sign now
                lhs.shift_left(total_z_count);
                lhs.sign(sign_hold);
            }

            template <typename IntType>
            void divide_mod(
                const IntType& lhs, const IntType& rhs,
                IntType* div_req, IntType* mod_req
            ){
                // Deal with easy cases when one number is 0 or 1
                if(Helper::is_zero(rhs)){
                    throw exception(
                        exception::divide_by_zero,
                        "Precision::Volatile::Int_Operations::divide"
                            "(const IntType&, const IntType&, IntType*, IntType*)"
                    );
                }else if(Helper::is_one(rhs)){
                    if(div_req != nullptr)  *div_req = lhs;
                    if(mod_req != nullptr)  Helper::make_zero(*mod_req, lhs);
                    return;
                }else if(lhs == rhs){
                    if(div_req != nullptr)  Helper::make_zero(*div_req, lhs);
                    if(mod_req != nullptr)  Helper::make_zero(*mod_req, lhs);
                    return;
                }else if(compare_lists(lhs.digit_list(), rhs.digit_list()) < 0){
                    if(mod_req != nullptr)  *mod_req = lhs;
                    if(div_req != nullptr)  Helper::make_zero(*div_req, lhs);
                    return;
                }

                IntType quotient(Helper::make_zero_temp(lhs)),
                        remainder(lhs.magnitude()),
                        tens(rhs.magnitude())
                        ;
                typedef typename IntType::size_type size_type;
                size_type t_counter(remainder.count_digits()-tens.count_digits());

                tens.shift_left(t_counter);

                // Perform division by subtracting tens at a time and
                //  counting how many subtractions for performed
                while(tens >= rhs.magnitude()){
                    IntType addend(Helper::make_one_temp(lhs));
                    addend.shift_left(t_counter);
                    while(remainder >= tens){
                        quotient += addend;
                        remainder -= tens;
                    }
                    tens.shift_right(1);
                    --t_counter;
                }

                // Assign the results
                if(div_req != nullptr){
                    quotient.sign(lhs.sign() * rhs.sign());
                    *div_req = std::move(quotient);
                }
                if(mod_req != nullptr)
                    *mod_req = std::move(remainder);
            }

            //Bitwise operators
            template <typename IntType>
            IntType bitwise_complement(const IntType& orig){
                if(Helper::is_zero(orig)){
                    throw exception(
                        exception::insufficient_memory,
                        "Precision::Volatile_::operator~()"
                    );
                }
                IntType toreturn(Helper::make_zero_temp(orig)),
                        reducer(orig.magnitude())
                        ;
                typedef typename IntType::size_type size_type;
                typedef typename IntType::sign_type sign_type;
                size_type i(0);
                sign_type new_s(orig.sign());
                new_s.negate();

                const IntType z_(Helper::make_zero_temp(orig)),
                              two_(Helper::make_two_temp(orig))
                              ;

                while(reducer != z_){
                    if(Helper::is_even(reducer))
                        toreturn += exponentiate(two_, i);
                    ++i;
                    divide_mod( reducer, two_,
                                &reducer, static_cast<IntType*>(nullptr)
                                );
                }
                toreturn.sign(new_s);
                return toreturn;
            }

            template <typename IntType>
            void bitwise_operation(
                IntType& lhs, IntType rhs,
                std::function<bool(bool, bool)>&& condition
            ){
                IntType toreturn(Helper::make_zero_temp(lhs));
                typedef typename IntType::size_type size_type;
                typedef typename IntType::sign_type sign_type;
                size_type i(0);
                sign_type new_s( condition(lhs.is_negative(), rhs.is_negative())
                                 ? -1
                                 : 1
                                 );

                const IntType z_(Helper::make_zero_temp(lhs)),
                              two_(Helper::make_two_temp(lhs))
                              ;

                while(lhs != z_ || rhs != z_){
                    if(condition(lhs.is_odd(), rhs.is_odd()))
                        toreturn += exponentiate(two_, i);
                    ++i;
                    lhs /= two_;
                    rhs /= two_;
                }
                toreturn.sign(new_s);
                lhs = std::move(toreturn);
            }   

            template <typename IntType>
            void bitwise_and_eq(IntType& lhs, const IntType& rhs){
                bitwise_operation(
                    lhs, rhs,
                    [](bool l, bool r){return (l == r && l == true);}
                    );
            }

            template <typename IntType>
            void bitwise_or_eq(IntType& lhs, const IntType& rhs){
                bitwise_operation(
                    lhs, rhs,
                    [](bool l, bool r){return (l == true || r == true);}
                    );
            }

            template <typename IntType>
            void bitwise_xor_eq(IntType& lhs, const IntType& rhs){
                bitwise_operation(
                    lhs, rhs,
                    [](bool l, bool r){return l != r;}
                    );
            }

            template <typename IntType>
            void bitwise_lshift_eq(IntType& lhs, const IntType& rhs)
                {multiply(lhs, exponentiate(Helper::make_two_temp(rhs), rhs));}

            template <typename IntType>
            void bitwise_rshift_eq(IntType& lhs, const IntType& rhs){
                divide_mod( lhs, exponentiate(Helper::make_two_temp(rhs), rhs),
                            &lhs, static_cast<IntType*>(nullptr)
                            );
            }

            //Logical Operators
            template <typename IntType>
            void logical_operation(
                typename IntType::diglist_type& diglist1,
                typename IntType::diglist_type diglist2,
                typename IntType::sign_type& sign1,
                typename IntType::sign_type sign2,
                unsigned short oper, typename IntType::digit_type base
            ){
                using std::swap;
                if(diglist1.size() < diglist2.size()) swap(diglist1, diglist2);
                diglist2.insert( diglist2.end(),
                                 diglist1.size() - diglist2.size(),
                                 0
                                 );
                typedef typename IntType::catalyst_type catalyst_type;
                auto compl_oper = [base](catalyst_type l1)
                    {return std::fmod(base - 1 - l1);};
                auto and_oper = [base](catalyst_type l1, catalyst_type l2)
                    {return std::fmod((l1 * l2), base);};
                auto or_oper = [base, compl_oper, and_oper](catalyst_type l1, catalyst_type l2)
                    {return compl_oper(and_oper(compl_oper(l1), compl_oper(l2)));};
                auto xor_oper = [base](catalyst_type l1, catalyst_type l2)
                    {return std::fmod((l1 + l2), base);};

                for( auto biter(diglist1.begin()), siter(diglist2.begin());
                     siter != diglist2.end();
                     ++biter, ++siter
                ){
                    typename IntType::catalyst_type bld_temp(*biter), sld_temp(*siter);
                    switch(oper){
                        case 1:
                            *biter = and_oper(bld_temp, sld_temp);
                            break;
                        case 2:
                            *biter = or_oper(bld_temp, sld_temp);
                            break;
                        case 3:
                            *biter = xor_oper(bld_temp, sld_temp);
                            break;
                        case 4:
                            *biter = compl_oper(*biter);
                            break;
                        default:
                            throw oper; //Should never happen
                    }
                }
                while(diglist1.size() > 1 && diglist1.back() == 0)
                    diglist1.pop_back();
                switch(oper){
                    case 1:
                        sign1 =
                            1-(sign1.is_negative() & sign2.is_negative())*2;
                        break;
                    case 2:
                        sign1 =
                            1-(sign1.is_negative() | sign2.is_negative())*2;
                        break;
                    case 3:
                        sign1 =
                            1-(sign1.is_negative() ^ sign2.is_negative())*2;
                        break;
                    case 4:
                        sign1.negate();
                        break;
                    default:
                        throw oper; //Should never happen
                }
            }

            template <typename IntType>
            void logical_and(   //res = (a*b)%base
                typename IntType::diglist_type& diglist1,
                typename IntType::diglist_type diglist2,
                typename IntType::sign_type& sign1,
                typename IntType::sign_type sign2,
                typename IntType::digit_type base
            ){
                logical_operation<IntType>( diglist1, diglist2,
                                            sign1, sign2,
                                            1,
                                            base
                                            );
            }

            template <typename IntType>
            void logical_or(    //res = ~(~a & ~b)
                typename IntType::diglist_type& diglist1,
                typename IntType::diglist_type diglist2,
                typename IntType::sign_type& sign1,
                typename IntType::sign_type sign2,
                typename IntType::digit_type base
            ){
                logical_operation<IntType>( diglist1, diglist2,
                                            sign1, sign2,
                                            2,
                                            base
                                            );
            }

            template <typename IntType>
            void logical_xor(   //res = (~((a+b)%base))%base
                typename IntType::diglist_type& diglist1,
                typename IntType::diglist_type diglist2,
                typename IntType::sign_type& sign1,
                typename IntType::sign_type sign2,
                typename IntType::digit_type base
            ){
                logical_operation<IntType>( diglist1, diglist2,
                                            sign1, sign2,
                                            3,
                                            base
                                            );
            }

            template <typename IntType>
            void logical_inversion( //res = Base - 1 - a
                typename IntType::diglist_type& diglist1,
                typename IntType::sign_type& sign1,
                typename IntType::digit_type base
            ){
                logical_operation<IntType>( diglist1, diglist1,
                                            sign1, sign1,
                                            4,
                                            base
                                            );
            }

            template <typename Integer_Type>
            bool is_negative(const Integer_Type& i)
                {return i.is_negative();}

            namespace Exp_Util_{
                template <typename Number_Type, typename Integer_Type>
                Number_Type exponentiate(
                    const Number_Type& base,
                    Integer_Type e,
                    std::true_type
                ){
                    if(Helper::is_zero(e))
                        return Helper::make_one_temp(base);
                    else if(Helper::is_one(e))
                        return base;
                    else if(Helper::is_neg_one(e)){
                        Number_Type toreturn(base);
                        Helper::reciprocate(toreturn);
                        return toreturn;
                    }

                    Number_Type operand(base);
                    if(is_negative(e)){
                        Helper::reciprocate(operand);
                        Helper::negate(e);
                    }
                    //Exponentiation by squaring
                    if(Helper::is_even(e))
                        return exponentiate( (operand * operand),
                            Helper::halve(e), std::true_type() );
                    else
                        return operand * exponentiate( operand,
                            (e - Helper::make_one_temp(e)), std::true_type() );

                }

                template <typename Number_Type, typename Number_Type2>
                Number_Type exponentiate(
                    const Number_Type& base,
                    const Number_Type2& e,
                    std::false_type
                ){
                    throw exception( exception::unsupported,
                                     "Precision::Volatile::Int_Operations::"
                                     "Exp_Util_::exponentiate("
                                        "const Number_Type&,"
                                        "const Number_Type2&,"
                                        "std::false_type"
                                        ")"
                                     );
                }
            }

            template <typename Number_Type, typename Number_Type2>
            Number_Type exponentiate( const Number_Type& base,
                                      const Number_Type2& exp
            ){
                if(Helper::is_zero(exp) && Helper::is_zero(base)){
                    throw exception( exception::indeterminate,
                                     "Precision::Volatile::Int_Operations::"
                                     "exponentiate(const Number_Type&,"
                                                  "const Number_Type2&"
                                                  ")"
                                     );
                }

                // Decide which algorithm to use depending on if the exponent
                //  is an integer or not.
                return Exp_Util_::exponentiate( base, exp,
                    typename Type_Trait::any_true<
                        typename std::is_integral<Number_Type2>::type,
                        typename std::is_base_of<Tag::Integral, Number_Type2>::type
                    >::type());
            }

            //Comparisons
            template <typename IntType>
            short compare(const IntType& lhs, const IntType& rhs){
                if(&lhs == &rhs)                            return 0;
                else if(lhs.sign() < rhs.sign())            return -1;
                else if(lhs.sign() > rhs.sign())            return 1;
                using list_type = typename IntType::diglist_type;
                const list_type& diglist1(lhs.digit_list()),
                                 diglist2(rhs.digit_list())
                                 ;
                if( lhs.is_negative() &&
                    diglist1.size() > diglist2.size()
                    )                                       return -1;
                else if( lhs.is_negative() &&
                         diglist1.size() < diglist2.size()
                         )                                  return 1;
                return lhs.sign().value() * compare_lists(diglist1, diglist2);
            }

            template <typename DigListType>
            short compare_lists (const DigListType& d1, const DigListType& d2){
                //Because this is only the digit list, it is assumed
                //  the magnitudes are being compared.
                if(&d1 == &d2)                  return 0;
                if(d1.size() > d2.size())       return 1;
                if(d1.size() < d2.size())       return -1;
                for(
                    auto titer(d1.crbegin()), siter(d2.crbegin());
                    titer != d1.crend();
                    ++titer, ++siter
                ){
                    if(*titer < *siter)         return -1;
                    else if(*titer > *siter)    return  1;
                }
                return 0;
            }

            template <typename DigListType>
            bool is_zero_list(const DigListType& d)
                {return d.size() == 1u && d.front() == 0;}

            template <typename DigListType, typename SignType>
            bool is_one_list(const DigListType& d, const SignType& s)
                {return d.size() == 1u && d.front() == 1 && s.is_positive();}

            template <typename DigListType, typename SignType>
            bool is_neg_one_list(const DigListType& d, const SignType& s)
                {return d.size() == 1u && d.front() == 1 && s.is_negative();}
        }
    }
}