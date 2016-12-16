#include "Math_Shared_Functions.h"
#include "Math_Shared_Helpers.h"
#include "Exception.h"

#include <utility>
#include <algorithm>
#include <iterator>

namespace Precision{
    namespace Volatile_{
        namespace Int_Operations {
        //Arithmetic operators
            template <typename IntType>
            void add(
                typename IntType::diglist_type& diglist1,
                typename IntType::diglist_type diglist2,
                typename IntType::sign_type& sign1,
                typename IntType::sign_type sign2,
                typename IntType::digit_type base
            ){
                // No addition to actually perform, so exit function.
                if(is_zero_list(diglist2))  return;

                // First number is 0, so replace digit string and sign.
                if(is_zero_list(diglist1)){
                    diglist1 = std::move(diglist2);
                    sign1 = sign2;
                    return;
                }

                // Make sure both string are the same length.
                using std::swap;
                if(compare_lists(diglist1, diglist2) == -1){
                    swap(diglist1, diglist2);
                    swap(sign1, sign2);
                }
                while(diglist2.size() < diglist1.size())    diglist2.push_back(0);

                if(sign1.is_negative())  sign2.negate();

                // Iterate through each list and perform an addition per digit
                typename IntType::digit_type carry(0);
                auto biter(diglist1.begin()), siter(diglist2.begin());
                for(; siter != diglist2.end(); ++biter, ++siter){
                    typename IntType::ld catalyst
                        (*biter+(*siter)*sign2+carry);
                    //Carry a number
                    carry = (catalyst>=base);
                    catalyst -= base*(catalyst>=base);

                    //Borrow a number
                    auto bcopy(biter);  ++bcopy;
                    if(catalyst < 0 && bcopy != diglist1.end()){
                        --(*bcopy), catalyst += base;
                        auto bcopy2(bcopy), bcopy3(bcopy);
                        while(*bcopy3 < 0 && (++bcopy2) != diglist1.end())
                            *(bcopy3++) += base, --(*bcopy2);
    /*
            //Improper way to handle error: -1 for left-most digit_type
            //  Code still here in case issue props up again
            //  Still need to find out how this situation occurs
                        if(*bcopy3 < 0){
                            *bcopy3 += base;
                            sign1.negate();
                        }
    */
                    }

                    *biter = catalyst;

                    // Account for a carry at the very end
                    if(carry > 0 && bcopy == diglist1.end()){
                        diglist1.push_back(carry);
                        break;
                    }
                }

                // Remove excess 0's, e.g. if sum was 0010, turn into 10.
                while(diglist1.size() > 1 && diglist1.back() == 0)
                    diglist1.pop_back();
            }

            template <typename IntType>
            void multiply(IntType& lhs, const IntType& rhs){
                if(rhs.is_zero()){
                    lhs = Math::Helper::cast(lhs, 0);
                    return;
                }else if(lhs.is_zero() || rhs.is_one()){
                    return;
                }else if(lhs.is_one()){
                    lhs = rhs;
                    return;
                }else if(rhs.is_neg_one()){
                    lhs.negate();
                    return;
                }else if(lhs.is_neg_one()){
                    lhs = rhs;
                    lhs.negate();
                    return;
                }

                typedef typename IntType::sign_type sign_type;
                typedef typename IntType::size_type size_type;
                typedef typename IntType::digit_type digit_type;
                sign_type sign_hold(lhs.sign() * rhs.sign());

                IntType big(lhs);
                using std::swap;

                size_type z_count(0);
                while(big.count_digits() > 0 && big.digit_10(0) == 0)
                    big.shift_right(1), ++z_count;
                size_type i(0);
                for(; i < rhs.count_digits() && rhs.digit_10(i) == 0; ++i)
                    ++z_count;
                const size_type s_count = i;
                if(big.is_zero()){
                    lhs = Math::Helper::cast(lhs, 0);
                    return;
                }

                lhs = Math::Helper::cast(lhs, 0);
                for(; i < rhs.count_digits(); ++i){
                    IntType addend(Math::Helper::cast(lhs, 0));
                    digit_type operand(rhs.digit_10(i));
                    while(operand-- > 0)
                        addend += big;
                    addend.shift_left(i-s_count);
                    lhs += addend;
                }

                lhs.shift_left(z_count);
                lhs.sign(sign_hold);
            }

            template <typename IntType>
            void divide_mod(
                const IntType& lhs, const IntType& rhs,
                IntType* div_req, IntType* mod_req
            ){
                if(rhs.is_zero()){
                    throw exception(
                        exception::divide_by_zero,
                        "Precision::Volatile_::divide"
                            "(const IntType&, const IntType&, IntType*, IntType*)"
                    );
                }else if(rhs.is_one()){
                    if(div_req != nullptr)  *div_req = lhs;
                    if(mod_req != nullptr)  *mod_req = Math::Helper::cast(lhs, 0);
                    return;
                }else if(lhs == rhs){
                    if(div_req != nullptr)  *div_req = Math::Helper::cast(lhs, 1);
                    if(mod_req != nullptr)  *mod_req = Math::Helper::cast(lhs, 0);
                    return;
                }else if(compare_lists(lhs.digit_list(), rhs.digit_list()) < 0){
                    if(mod_req != nullptr)  *mod_req = lhs;
                    if(div_req != nullptr)  *div_req = Math::Helper::cast(lhs, 0);
                    return;
                }

                IntType
                    quotient(Math::Helper::cast(lhs, 0)),
                    remainder(lhs.magnitude()),
                    tens(rhs.magnitude())
                ;
                typedef typename IntType::size_type size_type;
                size_type t_counter(remainder.count_digits()-tens.count_digits());

                tens.shift_left(t_counter);

                while(tens >= rhs.magnitude()){
                    IntType addend(Math::Helper::cast(lhs, 1));
                    addend.shift_left(t_counter);
                    while(remainder >= tens){
                        quotient += addend;
                        remainder -= tens;
                    }
                    tens.shift_right(1);
                    --t_counter;
                }
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
                if(orig.is_zero()){
                    throw exception(
                        exception::insufficient_memory,
                        "Precision::Volatile_::operator~()"
                    );
                }
                IntType
                    toreturn(Math::Helper::cast(orig, 0)),
                    reducer(orig.magnitude())
                ;
                typedef typename IntType::size_type size_type;
                typedef typename IntType::sign_type sign_type;
                size_type i(0);
                sign_type new_s(orig.sign());
                new_s.negate();
                const IntType
                    z_(Math::Helper::cast(orig, 0)),
                    two_(Math::Helper::cast(orig, 2))
                ;
                while(reducer != z_){
                    toreturn += reducer.is_odd()
                                ? Math::Helper::cast(orig, 0)
                                : Math::exponentiate(two_, i);
                    ++i;
                    divide_mod(
                        reducer, two_,
                        &reducer, static_cast<IntType*>(nullptr)
                        );
                }
                toreturn.sign(new_s);
                return toreturn;
            }

            template <typename IntType>
            void bitwise_operation(
                IntType& f, IntType s,
                std::function<bool(bool, bool)>&& condition
            ){
                IntType toreturn(0);
                typedef typename IntType::size_type size_type;
                typedef typename IntType::sign_type sign_type;
                size_type i(0);
                sign_type new_s(condition(f.is_negative(), s.is_negative()) ? -1 : 1);
                const IntType z_(0), two_(2);
                while(f != z_ || s != z_){
                    toreturn += condition(f.is_odd(), s.is_odd())
                        ? Math::exponentiate(two_, i) : 0;
                    ++i, f /= two_, s /= two_;
                }
                toreturn.sign(new_s);
                f = std::move(toreturn);
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
                {multiply(lhs, Math::exponentiate(Math::Helper::cast(rhs, 2), rhs));}

            template <typename IntType>
            void bitwise_rshift_eq(IntType& lhs, const IntType& rhs){
                divide_mod(
                    lhs, Math::exponentiate(Math::Helper::cast(rhs, 2), rhs),
                    &lhs, static_cast<IntType*>(nullptr)
                    );
            }

        //Logical Operators
            template <typename IntType>
            void logical_operation(
                typename IntType::diglist_type& diglist1,
                typename IntType::diglist_type diglist2,
                typename IntType::sign_type& new_sign,
                typename IntType::sign_type sign2,
                unsigned short oper, typename IntType::digit_type base
            ){
                using std::swap;
                if(diglist1.size() < diglist2.size())   swap(diglist1, diglist2);
                diglist2.insert(diglist2.end(), diglist1.size() - diglist2.size(), 0);
                for(
                    auto biter(diglist1.begin()), siter(diglist2.begin());
                    siter != diglist2.end();
                    ++biter, ++siter
                ){
                    typename IntType::ld bld_temp(*biter), sld_temp(*siter);
                    switch(oper){
                        case 1:
                            *biter = std::fmod((bld_temp * sld_temp), base);
                            break;
                        case 2:
                            *biter = std::fmod(
                                base - 1
                                - std::fmod(
                                    std::fmod(base-1-bld_temp, base)
                                    * std::fmod(base-1-sld_temp, base),
                                    base),
                                base
                                );
                            break;
                        case 3:
                            *biter = std::fmod(
                                std::fmod(base-(bld_temp + sld_temp), base)
                                , base
                                );
                            break;
                        case 4:
                            *biter = base - 1 - *biter;
                            break;
                        default:
                            throw oper; //Should never happen
                    }
                }
                while(diglist1.size() > 1 && diglist1.back() == 0)
                    diglist1.pop_back();
                switch(oper){
                    case 1:
                        new_sign =
                            1-(new_sign.is_negative() & sign2.is_negative())*2;
                        break;
                    case 2:
                        new_sign =
                            1-(new_sign.is_negative() | sign2.is_negative())*2;
                        break;
                    case 3:
                        new_sign =
                            1-(new_sign.is_negative() ^ sign2.is_negative())*2;
                        break;
                    case 4:
                        new_sign.negate();
                        break;
                    default:
                        throw oper; //Should never happen
                }
            }

            template <typename IntType>
            void logical_and(   //res = (a*b)%base
                typename IntType::diglist_type& diglist1,
                typename IntType::diglist_type diglist2,
                typename IntType::sign_type& new_sign,
                typename IntType::sign_type sign2,
                typename IntType::digit_type base
            ){logical_operation<IntType>(diglist1, diglist2, new_sign, sign2, 1, base);}

            template <typename IntType>
            void logical_or(    //res = ~(~a & ~b)
                typename IntType::diglist_type& diglist1,
                typename IntType::diglist_type diglist2,
                typename IntType::sign_type& new_sign,
                typename IntType::sign_type sign2,
                typename IntType::digit_type base
            ){logical_operation<IntType>(diglist1, diglist2, new_sign, sign2, 2, base);}

            template <typename IntType>
            void logical_xor(   //res = (~((a+b)%base))%base
                typename IntType::diglist_type& diglist1,
                typename IntType::diglist_type diglist2,
                typename IntType::sign_type& new_sign,
                typename IntType::sign_type sign2,
                typename IntType::digit_type base
            ){logical_operation<IntType>(diglist1, diglist2, new_sign, sign2, 3, base);}

            template <typename IntType>
            void logical_inversion( //res = Base - 1 - a
                typename IntType::diglist_type& diglist1,
                typename IntType::sign_type& new_sign,
                typename IntType::digit_type base
            ){logical_operation<IntType>(diglist1, diglist1, new_sign, new_sign, 4, base);}

        //Read-only functions
            template <typename IntType>
            short compare(const IntType& f, const IntType& s){
                if(&f == &s)                            return 0;
                else if(f.sign() < s.sign())            return -1;
                else if(f.sign() > s.sign())            return 1;
                const typename IntType::diglist_type
                    f_digs(f.digit_list()),
                    diglist2(s.digit_list())
                ;
                if(f_digs == diglist2)                    return 0;
                else if(
                    f.is_negative() &&
                    f_digs.size() > diglist2.size()
                )                                       return -1;
                else if(
                    f.is_negative() &&
                    f_digs.size() < diglist2.size()
                )                                       return 1;
                else if(f_digs.size() < diglist2.size())  return -1;
                else if(f_digs.size() > diglist2.size())  return 1;
                for(
                    auto titer(f_digs.crbegin()), siter(diglist2.crbegin());
                    titer != f_digs.crend();
                    ++titer, ++siter
                ){
                    if(*titer < *siter)         return -f.sign().value();
                    else if(*titer > *siter)    return  f.sign().value();
                }
                                                        return 0;
            }

            template <typename DigListType>
            short compare_lists
                (const DigListType& d1, const DigListType& d2)
            {
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

        }
    }
}