#include "Precision_Shared_Helpers.h"
#include "Precision_Exception.h"

#include <utility>  // For std::move
#include <type_traits>

namespace Precision{
    namespace Volatile{
        namespace Int_Operations {
            namespace Bit_Helpers{
                // Create a mask with a number of ON bits equal to the
                // leading ON bit plus one
                template <typename Digit_Type>
                Digit_Type make_mask(Digit_Type dig){
                    Digit_Type toreturn = 0;
                    while(dig > 0){
                        dig >>= 1;
                        toreturn = (toreturn << 1) | 0x1;
                    }
                    return toreturn;
                }
            }

            //Bitwise operators
            template <typename IntType>
            void bitwise_operation( IntType& lhs, const IntType& rhs,
                                    unsigned short op
            ){
                // Determine the new sign
                typename IntType::sign_type signhold;
                switch(op){
                    case 0: // COMPL
                        signhold = -lhs.sign();
                        break;
                    case 1: // AND
                        signhold =  lhs.sign() + rhs.sign();
                        break;
                    case 2: // OR
                        signhold =  (lhs.sign() * rhs.sign())
                                  + rhs.sign()
                                  + lhs.sign()
                                  ;
                        break;
                    case 3: // XOR
                        signhold =  lhs.sign() * rhs.sign();
                        break;
                    default:
                        signhold = 1;
                        break;
                }

                // Create a constant for two in radix IntType::base
                // and 
                const IntType increment = Helper::make_one_temp(lhs);
                IntType counter = Helper::make_zero_temp(lhs),
                        rhs_copy = rhs,
                        two = Helper::make_one_temp(lhs)
                        ;
                Arith_Helper::bucket_type<IntType> bucket;
                while(!Helper::is_zero(lhs) || !Helper::is_zero(rhs_copy)){
                    // Calculate the bitwise result on the rightmost bit
                    bool bit = false;
                    switch(op){
                        case 0: // COMPL
                            bit = Helper::is_even(lhs);
                            break;
                        case 1: // AND
                            bit = Helper::is_odd(lhs) && Helper::is_odd(rhs_copy);
                            break;
                        case 2: // OR
                            bit = Helper::is_odd(lhs) || Helper::is_odd(rhs_copy);
                            break;
                        case 3: // XOR
                            bit = Helper::is_odd(lhs) != Helper::is_odd(rhs_copy);
                            break;
                        default:
                            bit = false;
                            break;
                    }

                    // Convert the bit to the equivalent number of IntType::base
                    if(bit){
                        bucket.push_back(two);
                    }
                    add(counter, increment);
                    Helper::halve(lhs);
                    Helper::halve(rhs_copy);

                    // Update the binary factor
                    multiply_factor(two, 2);
                }
                lhs = Helper::make_zero_temp(lhs);
                Arith_Helper::accumulate(lhs, bucket);

                lhs.sign(signhold);
            }

            template <typename IntType>
            void bitwise_complement(IntType& orig){
                if(Helper::is_zero(orig)){
                    throw exception(
                        exception::insufficient_memory,
                        "Precision::Volatile::Int_Operations::operator~"
                        "(const IntType&)"
                    );
                }

                bitwise_operation(orig, orig, 0);
            }

            template <typename IntType>
            void bitwise_and_eq(IntType& lhs, const IntType& rhs)
                {bitwise_operation(lhs, rhs, 1);}

            template <typename IntType>
            void bitwise_or_eq(IntType& lhs, const IntType& rhs)
                {bitwise_operation(lhs, rhs, 2);}

            template <typename IntType>
            void bitwise_xor_eq(IntType& lhs, const IntType& rhs)
                {bitwise_operation(lhs, rhs, 3);}

            template <typename IntType>
            void bitwise_lshift_eq(IntType& lhs, const IntType& rhs){
                IntType two_pow = Helper::make_two_temp(rhs);
                exponentiate(two_pow, rhs);
                multiply(lhs, two_pow);
            }

            template <typename IntType>
            void bitwise_rshift_eq(IntType& lhs, const IntType& rhs){
                IntType quo, mod,
                        two = Helper::make_two_temp(lhs)
                        ;
                exponentiate(two, rhs);
                divide_mod( lhs, two, quo, mod );
                lhs = std::move(quo);
            }
        }
    }
}