#include "Precision_Shared_Helpers.h"

#include <utility> // For std::pair

namespace Precision{
    namespace Volatile {
        namespace Float_Operations {
            // Comparisons

            template <typename FloatType>
            short compare(const FloatType& lhs, const FloatType& rhs){
                if(lhs.power() < rhs.power())         return -1;
                else if(lhs.power() > rhs.power())    return 1;

                using size_type = typename FloatType::size_type;
                size_type min_prec = Helper::min_precision(lhs, rhs);

                return Helper::generate_operand(lhs, min_prec)
                     . compare(Helper::generate_operand(rhs, min_prec));
            }



            // Arithmetic operators

            namespace Arith_Helper{
                template <typename FloatType>
                using opp_type = std::pair
                    <typename FloatType::integer_type, typename FloatType::integer_type>;

                // Generate operands with matching precision and orders of magnitude
                // and return: the smaller precision and difference in order of magnitude
                typename <typename FloatType>
                opp_type<FloatType> gen_op(
                    FloatType& ref1, typename FloatType::integer_type& lhs_int,
                    const FloatType& ref2, const FloatType::integer_type& rhs_int,
                    typename FloatType::size_type& min_prec,
                    typename FloatType::signed_size_type& del_pow
                    )
                {
                    // First, generate operands based on precision
                    using size_type = typename FloatType::size_type;
                    min_prec = Helper::min_precision(ref1, ref2);

                    using int_type = typename FloatType::integer_type;
                    int_type op1(Helper::generate_operand(lhs_int, min_prec)),
                             op2(Helper::generate_operand(rhs_int, min_prec))
                             ;

                    // Next, modify operands to match order of magnitude
                    using ss_type = typename FloatType::signed_size_type;
                    ss_type del_pow=0;
                    if(ref1.power() > ref2.power())
                        op1.shift_left(del_pow=ref1.power()-ref2.power());
                    else if(ref1.power() < ref2.power())
                        op2.shift_left(del_pow=ref2.power()-ref1.power());

                    return std::make_pair(op1, op2);
                }
            }

            template <typename FloatType>
            void add( FloatType& lhs, typename FloatType::integer_type& lhs_int,
                      const FloatType& rhs, const FloatType::integer_type& rhs_int,
                      short add_sign
                      )
            {
                using size_type = typename FloatType::size_type;
                using ss_type = typename FloatType::signed_size_type;

                // Generate a pair of operands based on precision and power
                // such that they match.
                size_type min_prec = 0;
                ss_type del_pow = 0;
                Arith_Helper::opp_type = Arith_Helper::gen_op( lhs, lhs_int,
                                                               rhs, rhs_int,
                                                               min_prec, del_pow
                                                               );

                Int_Operations::add(opp_type.first, opp_type.second, add_sign);

                // Store the sum
                lhs_int = std::move(opp_type.first);

                // Update the power and precision
                lhs.shift(del_pow);
                lhs.precision(min_prec);
            }

            template <typename FloatType>
            void multiply( FloatType& lhs, typename FloatType::integer_type& lhs_int,
                           const FloatType& rhs, const FloatType::integer_type& rhs_int
                           )
            {
                using size_type = typename FloatType::size_type;
                using ss_type = typename FloatType::signed_size_type;

                // Generate a pair of operands based on precision and power
                // such that they match.
                size_type min_prec = 0;
                ss_type del_pow = 0;
                Arith_Helper::opp_type = Arith_Helper::gen_op( lhs, lhs_int,
                                                               rhs, rhs_int,
                                                               min_prec, del_pow
                                                               );

                Int_Operations::multiply(opp_type.first, opp_type.second);

                // Store the sum
                lhs_int = std::move(opp_type.first);

                // Update the power and precision
                lhs.shift(del_pow);
                lhs.precision(min_prec);
            }

            template <typename FloatType>
            void divide_mod( FloatType& lhs, typename FloatType::integer_type& lhs_int,
                             const FloatType& rhs, const FloatType::integer_type& rhs_int,
                             typename FloatType::integer_type& quotient,
                             typename FloatType::integer_type& modulus
                             )
            {
                using size_type = typename FloatType::size_type;
                using ss_type = typename FloatType::signed_size_type;

                // Generate a pair of operands based on precision and power
                // such that they match.
                size_type min_prec = 0;
                ss_type del_pow = 0;
                Arith_Helper::opp_type = Arith_Helper::gen_op( lhs, lhs_int,
                                                               rhs, rhs_int,
                                                               min_prec, del_pow
                                                               );

                Int_Operations::divide_mod(opp_type.first, opp_type.second, quotient, modulus);

                // Update the power and precision
                lhs.shift(del_pow);
                lhs.precision(min_prec);
            }

            template <typename FloatType>
            void invert(FloatType& orig){
                FloatType numer( typename FloatType::raw_float_type(1),
                                 0, orig.power()+1, true
                                 );
                numer.operator/=(orig);
                orig = std::move(numer);
            }

            template <typename FloatType>
            void exponentiate(FloatType& base, const typename FloatType::integer_type& exp)
                {Int_Operations::exponentiate(base, exp);}

            template <typename FloatType>
            void exponentiate(FloatType& base, const FloatType& exp){
                exponentiate(base, exp.integer());

                //TODO: Implement exponentiation with floating point powers
            }
        }
    }
}