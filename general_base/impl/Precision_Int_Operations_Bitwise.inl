#include "Precision_Shared_Helpers.h"
#include "Precision_Exception.h"

#include <utility>  // For std::move

#include <type_traits>

#include <fstream>

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

static bool log_open = false;
std::ofstream log("bitwise_log.txt", log_open ? std::ios_base::app : std::ios_base::trunc);
log_open = true;
std::size_t i = 0;
log << (lhs.is_positive() ? '+' : '-');
i = lhs.count_digits();
while(i-- > 0) log << static_cast<int>(lhs.digit(i));
switch(op){
    case 0: // COMPL
        log << " ~ ";
        break;
    case 1: // AND
        log << " & ";
        break;
    case 2: // OR
        log << " | ";
        break;
    case 3: // XOR
        log << " ^ ";
        break;
}
log << (rhs.is_positive() ? '+' : '-');
i = rhs.count_digits();
while(i-- > 0) log << static_cast<int>(rhs.digit(i));
log << '\n';
                // Create a constant for two in radix IntType::base
                // and 
                const IntType two = Helper::make_two_temp(lhs),
                              increment = Helper::make_one_temp(lhs)
                              ;
                IntType counter = Helper::make_zero_temp(lhs),
                        rhs_copy = rhs
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

log << "\t[counter = ";
log << (counter.is_positive() ? '+' : '-');
i = counter.count_digits();
while(i-- > 0) log << static_cast<int>(counter.digit(i));
log << " lhs = ";
log << (lhs.is_positive() ? '+' : '-');
i = lhs.count_digits();
while(i-- > 0) log << static_cast<int>(lhs.digit(i));
log << " rhs_copy = ";
log << (rhs_copy.is_positive() ? '+' : '-');
i = rhs_copy.count_digits();
while(i-- > 0) log << static_cast<int>(rhs_copy.digit(i));
log << "] ";
log << "bit = " << Helper::is_odd(lhs);
switch(op){
    case 0: // COMPL
        log << " ~ ";
        break;
    case 1: // AND
        log << " & ";
        break;
    case 2: // OR
        log << " | ";
        break;
    case 3: // XOR
        log << " ^ ";
        break;
}
log << Helper::is_odd(rhs_copy) << " = " << bit;
                    // Convert the bit to the equivalent number of IntType::base
                    if(bit){
                        IntType bit_int = two;
                        exponentiate(bit_int, counter);
log << " --> Added to bucket: ";
log << (bit_int.is_positive() ? '+' : '-');
i = bit_int.count_digits();
while(i-- > 0) log << static_cast<int>(bit_int.digit(i));

                        bucket.emplace_back(bit_int);
                    }
log << '\n';

                    add(counter, increment);
                    Helper::halve(lhs);
                    Helper::halve(rhs_copy);
                }
                lhs = Helper::make_one_temp(lhs);
                Arith_Helper::accumulate(lhs, bucket);

                lhs.sign(signhold);
log << "Done\n\n";
log.close();
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