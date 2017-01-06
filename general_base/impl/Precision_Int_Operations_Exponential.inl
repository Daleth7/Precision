#include "Precision_Shared_Helpers.h"
#include "Precision_Exception.h"

namespace Precision{
    namespace Volatile{
        namespace Int_Operations {
            template <typename IntType>
            void exponentiate(IntType& base, const IntType& exp){
                if(Helper::is_zero(exp) && Helper::is_zero(base)){
                    throw exception( exception::indeterminate,
                                     "Precision::Volatile::Int_Operations::"
                                     "exponentiate(const IntType&, const IntType&)"
                                     );
                } else if(Helper::is_zero(exp)){
                    base = Helper::make_one_temp(base);
                    return;
                } else if(Helper::is_one(exp)){
                    return;
                } else if(Helper::is_negative(exp) || Helper::is_zero(base)){
                    base = Helper::make_zero_temp(base);
                    return;
                }

                //Exponentiation by squaring
                if(Helper::is_even(exp)){
                    multiply(base, base);

                    // Divide exponent by 2
                    IntType half_exp, two_temp = Helper::make_two_temp(base), mod;
                    divide_mod(exp, two_temp, half_exp, mod);

                    exponentiate(base, half_exp);

                    return;
                }

                // Decrement exponent
                IntType dec_exp = exp;
                add(dec_exp, Helper::make_one_temp(exp), -1);

                IntType base_copy = base;
                exponentiate(base_copy, dec_exp);

                multiply(base, base_copy);
            }
        }
    }
}