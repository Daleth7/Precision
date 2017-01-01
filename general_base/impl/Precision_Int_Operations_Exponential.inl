#include "Precision_Shared_Helpers.h"
#include "Precision_Exception.h"

#include "Type_Traits_Extended/Type_Traits_Ext.h" // For Type_Trait::any_true

namespace Precision{
    namespace Volatile{
        namespace Int_Operations {
            namespace Exp_Helper{
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
                                     "Exp_Helper::exponentiate("
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
                return Exp_Helper::exponentiate( base, exp,
                    typename Type_Trait::any_true<
                        typename std::is_integral<Number_Type2>::type,
                        typename std::is_base_of<Tag::Integral, Number_Type2>::type
                    >::type());
            }
        }
    }
}