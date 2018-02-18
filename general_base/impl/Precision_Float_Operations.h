/** \file Precision_Float_Operations.h
 * This file centralizes the base algorithms for all floating
 * number types.
 */



#ifndef FLOAT__ION__SHARED_ALGORITHMS92390735_HHHH_DETAIL____BASE
#define FLOAT__ION__SHARED_ALGORITHMS92390735_HHHH_DETAIL____BASE

namespace Precision{
    namespace Volatile {
        namespace Float_Operations {
            // Comparisons

            /** Comparison function that determines which number is
             *  greater than the other.
             * 
             *  \tparam FloatType Number type from which type and base
             *                    information is extracted. It is assumed
             *                    that this type supports the following:
             *                        * Type FloatType::diglist_type
             *                        * Method sign_type FloatType::sign()
             * 
             *  \param lhs The first number
             *  \param rhs The second number
             *  \return  Representation of which number is greater:
             *           * -1 : lhs < rhs (less than)
             *           *  0 : rhs == lhs (equivalent)
             *           * +1 : lhs > rhs (greater than)
             */
            template <typename FloatType>
            short compare(const FloatType& lhs, const FloatType& rhs);



            // Arithmetic operators

            /** A simple add function taking two floating point
             *  numbers and calculating the sum.
             *  The precision of the result will be equal to the
             *  minimum precision between the two operands.
             * 
             *  \tparam FloatType Number type from which type and base
             *                    information is extracted. This function
             *                    assumes FloatType has the public members:
             *                    * Type FloatType::diglist_type
             *                    * Method digit_type FloatType::digit(size_type)
             *
             *  \param lhs The first number to add and in which to store the sum
             *  \param lhs_int The underlying integer of the first number.
             *  \param rhs The second number to add
             *  \param rhs_int The underlying integer of the second number.
             *  \param add_sign An optional specification of whether to perform a
             *                  subtraction (-1) or addition (1)
             */
            template <typename FloatType>
            void add( FloatType& lhs, typename FloatType::integer_type& lhs_int,
                      const FloatType& rhs, const FloatType::integer_type& rhs_int,
                      short add_sign=1
                      );

            /** A simple multiply function taking two digit strings
             *  and calculating the product. Algorithm does not need
             *  number base information.
             *  The precision of the result will be equal to the
             *  minimum precision between the two operands.
             * 
             *  \tparam FloatType Number type from which type and base
             *                  information is extracted. In addition
             *                  to the requirements as detailed by add(),
             *                  FloatType is assumed to support:
             *                  * Type FloatType::size_type
             *                  * Method bool FloatType::is_zero()
             * 
             *  \param lhs The first number
             *  \param lhs_int The underlying integer of the first number.
             *  \param rhs The second number
             *  \param rhs_int The underlying integer of the second number.
             */
            template <typename FloatType>
            void multiply( FloatType& lhs, typename FloatType::integer_type& lhs_int,
                           const FloatType& rhs, const FloatType::integer_type& rhs_int
                           );

            /** A simple divide function taking two digit strings
             *  and calculating the quotient and modulus. Algorithm
             *  does not need number base information.
             *  The division and modulus are defined as follows:
             *      Numerator / Denominator = Quotient + Modulus / Denominator
             *  This is important because the sign of the modulus will
             *  match the sign of the quotient.
             * 
             *  \tparam FloatType Number type from which type and base
             *                  information is extracted. In addition
             *                  to the requirements as detailed by multiply(),
             *                  FloatType is assumed to support:
             *                  * Method diglist_type FloatType::digit_list()
             *                  
             * 
             *  \param lhs The first number
             *  \param lhs_int The underlying integer of the first number.
             *  \param rhs The second number
             *  \param rhs_int The underlying integer of the second number.
             *  \param quotient Reference to where quotient result is stored
             *  \param modulus Reference to where modulus result is stored
             */
            template <typename FloatType>
            void divide_mod( FloatType& lhs, typename FloatType::integer_type& lhs_int,
                             const FloatType& rhs, const FloatType::integer_type& rhs_int,
                             typename FloatType::integer_type& quotient,
                             typename FloatType::integer_type& modulus
                             );

            /** Calculate the reciprocal of a floating point number.
             * 
             *  \tparam FloatType Number type from which type and base
             *                  information is extracted.
             * 
             *  \param orig The number to invert
             */
            template <typename FloatType>
            void invert(FloatType& orig);

            /** Floating point exponentiation function.
             * 
             *  \tparam FloatType Number type from which type and base
             *                  information is extracted.
             * 
             *  \param base The number to exponentiate
             *  \param exp The integer exponent
             */
            template <typename FloatType>
            void exponentiate(FloatType& base, const typename FloatType::integer_type& exp);

            /** Floating point exponentiation function.
             * 
             *  \tparam FloatType Number type from which type and base
             *                  information is extracted.
             * 
             *  \param base The number to exponentiate
             *  \param exp The floating point exponent
             */
            template <typename FloatType>
            inline void exponentiate(FloatType& base, const FloatType& exp);
        }
    }
}

#include "Precision_Float_Operations.inl"

#endif  //Include guard