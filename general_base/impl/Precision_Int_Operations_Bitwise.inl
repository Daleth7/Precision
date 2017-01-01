#include "Precision_Shared_Helpers.h"
#include "Precision_Exception.h"

#include <utility>  // For std::move

namespace Precision{
    namespace Volatile{
        namespace Int_Operations {
            //Bitwise operators
            template <typename IntType>
            IntType bitwise_complement(const IntType& orig){
                if(Helper::is_zero(orig)){
                    throw exception(
                        exception::insufficient_memory,
                        "Precision::Volatile::Int_Operations::operator~"
                        "(const IntType&)"
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
        }
    }
}