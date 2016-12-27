/** \file Precision_Int_Operations.h
 * This file centralizes the base algorithms all the number types
 * use. By doing this, the library can be extended more easily.
 * An example of this is the difference between Dynamic and Static
 * number types. Despite sharing the same algorithms, their
 * behaviour for compile-time and run-time is different enough
 * that they cannot share the same inheritance tree or
 * utilize composition.
 * The algorithms are placed under the Volatile namespace since
 * they require the number base to be passed as a parameter to
 * correctly run the algorithm.
 */



#ifndef INTEGRAL_SHARED_ALGORITHMS93000000_HHHH_DETAIL____BASE
#define INTEGRAL_SHARED_ALGORITHMS93000000_HHHH_DETAIL____BASE

#include <functional>

namespace Precision{
    namespace Volatile {
        namespace Int_Operations {
            // Arithmetic operators
            /** A simple add function taking two digit strings
             *  and calculating the sum. Note that the operation
             *  may be slow since the second digit string is copied.
             *  [TODO: Optimize algorithm to not make copies]
             *  [TODO: Optimize algorithm to avoid iterating when borrowing]
             * 
             *  \tparam IntType Number type from which type and base
             *                  information is extracted.
             *
             *  \param diglist1 The digit string of the first number
             *  \param diglist2 The digit string of the second number
             *  \param sign1 The numeric sign of the first number
             *  \param sign2 The numeric sign of the second number
             *  \param base The number base of both numbers
             */
            template <typename IntType>
            void add( typename IntType::diglist_type& diglist1,
                      typename IntType::diglist_type diglist2,
                      typename IntType::sign_type& sign1,
                      typename IntType::sign_type sign2,
                      typename IntType::digit_type base
                      );

            /** A simple multiply function taking two digit strings
             *  and calculating the product. Algorithm does not need
             *  number base information.
             *   [TODO: Optimize algorithm to make less copies]
             * 
             *  \tparam IntType Number type from which type and base
             *                  information is extracted.
             * 
             *  \param lhs The first integer
             *  \param rhs The second integer
             */
            template <typename IntType>
            void multiply(IntType& lhs, const IntType& rhs);

            /** A simple divide function taking two digit strings
             *  and calculating the quotient and modulus. Algorithm
             * does not need number base information.
             * 
             *  \tparam IntType Number type from which type and base
             *                  information is extracted.
             * 
             *  \param lhs The first integer
             *  \param rhs The second integer
             *  \param div_req Pointer to where quotient result is stored
             *  \param mod_req Pointer to where modulus result is stored
             */
            template <typename IntType>
            void divide_mod( const IntType& lhs,
                             const IntType& rhs,
                             IntType* div_req, IntType* mod_req
                             );



            // Bitwise operators

            /** Complement function that calculates the binary,
             *  or bitwise, complement.
             * 
             *  \tparam IntType Number type from which type and base
             *                  information is extracted.
             * 
             *  \param bitstring The original number
             */
            template <typename IntType>
            IntType bitwise_complement(const IntType& bitstring);

            /** Binary base relative function that performs one of
             *  several bitwise operations (AND, OR, XOR) to two
             *  digit strings. The numerical signs are treated
             *  separately. Note that this algorithm may be
             *  slower since the second integer is copied.
             * 
             *  \tparam IntType Number type from which type and base
             *                  information is extracted.
             * 
             *  \param lhs The first integer
             *  \param rhs The second integer
             *  \param oper  A callback function that performs the
             *               bitwise operation on each digit.
             */
            template <typename IntType>
            void bitwise_operation( IntType& lhs, IntType rhs,
                                    std::function<bool(bool, bool)>&& oper
                                    );

            /** Binary AND operation calculated by performing
             *  x & y on each digit.
             * 
             *  \tparam IntType Number type from which type and base
             *                  information is extracted.
             * 
             *  \param lhs The first integer
             *  \param rhs The second integer
             */
            template <typename IntType>
            void bitwise_and_eq(IntType& lhs, const IntType& rhs);

            /** Binary OR operation calculated by performing
             *  x | y on each digit.
             * 
             *  \tparam IntType Number type from which type and base
             *                  information is extracted.
             * 
             *  \param lhs The first integer
             *  \param rhs The second integer
             */
            template <typename IntType>
            void bitwise_or_eq(IntType& lhs, const IntType& rhs);

            /** Binary XOR operation calculated by performing
             *  x ^ y on each digit.
             * 
             *  \tparam IntType Number type from which type and base
             *                  information is extracted.
             * 
             *  \param lhs The first integer
             *  \param rhs The second integer
             */
            template <typename IntType>
            void bitwise_xor_eq(IntType& lhs, const IntType& rhs);

            /** Binary left shift operation that is equivalent to
             *  performing x *= 2 by y times.
             * 
             *  \tparam IntType Number type from which type and base
             *                  information is extracted.
             * 
             *  \param lhs The first integer
             *  \param rhs The second integer
             */
            template <typename IntType>
            void bitwise_lshift_eq(IntType& lhs, const IntType& rhs);

            /** Binary right shift operation that is equivalent to
             *  performing x /= 2 by y times.
             * 
             *  \tparam IntType Number type from which type and base
             *                  information is extracted.
             * 
             *  \param lhs The first integer
             *  \param rhs The second integer
             */
            template <typename IntType>
            void bitwise_rshift_eq(IntType& lhs, const IntType& rhs);



            // Logical Operators

            /** Number base relative function that performs one of
             *  several logical operations (AND, OR, XOR, COMPL)
             *  to two digit strings. The numerical signs are treated
             *  separately and go through the respective bitwise
             *  operation.
             * 
             *  \tparam IntType Number type from which type and base
             *                  information is extracted.
             * 
             *  \param diglist1 The digit string of the first number
             *  \param diglist2 The digit string of the second number
             *  \param sign1 The numeric sign of the first number
             *  \param sign2 The numeric sign of the second number
             *  \param oper Determines which operation to perform
             *           1. AND
             *           2. OR
             *           3. XOR
             *           4. COMPLEMENT
             *  \param base The number base of both numbers
             */
            template <typename IntType>
            void logical_operation( typename IntType::diglist_type& diglist1,
                                    typename IntType::diglist_type diglist2,
                                    typename IntType::sign_type& sign1,
                                    typename IntType::sign_type sign2,
                                    unsigned short oper,
                                    typename IntType::digit_type base
                                    );

            /** Logical base AND operation calculated by performing
             *  x * y on each digit.
             * 
             *  \tparam IntType Number type from which type and base
             *                  information is extracted.
             * 
             *  \param diglist1 The digit string of the first number
             *  \param diglist2 The digit string of the second number
             *  \param sign1 The numeric sign of the first number
             *  \param sign2 The numeric sign of the second number
             *  \param base The number base of both numbers
             */
            template <typename IntType>
            void logical_and(   typename IntType::diglist_type& diglist1,
                                typename IntType::diglist_type diglist2,
                                typename IntType::sign_type& sign1,
                                typename IntType::sign_type sign2,
                                typename IntType::digit_type base
                                );

            /** Logical base OR operation that is equivalent to
             *  COMPL( AND( COMPL(x), COMPL(y) ) )
             * 
             *  \tparam IntType Number type from which type and base
             *                  information is extracted.
             * 
             *  \param diglist1 The digit string of the first number
             *  \param diglist2 The digit string of the second number
             *  \param sign1 The numeric sign of the first number
             *  \param sign2 The numeric sign of the second number
             *  \param base The number base of both numbers
             */
            template <typename IntType>
            void logical_or(    typename IntType::diglist_type& diglist1,
                                typename IntType::diglist_type diglist2,
                                typename IntType::sign_type& sign1,
                                typename IntType::sign_type sign2,
                                typename IntType::digit_type base
                                );

            /** Logical base XOR operation calculated by performing
             *  x + y on each digit.
             * 
             *  \tparam IntType Number type from which type and base
             *                  information is extracted.
             * 
             *  \param diglist1 The digit string of the first number
             *  \param diglist2 The digit string of the second number
             *  \param sign1 The numeric sign of the first number
             *  \param sign2 The numeric sign of the second number
             *  \param base The number base of both numbers
             */
            template <typename IntType>
            void logical_xor(   typename IntType::diglist_type& diglist1,
                                typename IntType::diglist_type diglist2,
                                typename IntType::sign_type& sign1,
                                typename IntType::sign_type sign2,
                                typename IntType::digit_type base
                                );

            /** Complement function that is relative to the
             *  number base of the IntType object.
             * 
             *  \tparam IntType Number type from which type and base
             *                  information is extracted.
             * 
             *  \param diglist The digit string of the integer
             *  \param int_sign The numerical sign of the integer
             *  \param base The number base of the integer
             */
            template <typename IntType>
            void logical_complement( typename IntType::diglist_type& diglist,
                                     typename IntType::sign_type& int_sign,
                                     typename IntType::digit_type base
                                     );

            /** Integer exponentiation function that employs
             *  the exponentiation by squaring algorithm. This
             *  function does not support floating point
             *  exponents.
             * 
             *  \tparam Number_Type Type of the first number
             *  \tparam Number_Type2 Type of the second number
             * 
             *  \param base The number to exponentiate
             *  \param exp The exponent integer
             *  \return The result of POWER(base, exp)
             */
            template <typename Number_Type, typename Number_Type2>
            Number_Type exponentiate( const Number_Type& base,
                                      const Number_Type2& exp
                                      );



            // Comparisons

            /** Comparison function that determines which integer is
             *  greater than the other.
             * 
             *  \tparam IntType Number type from which type and base
             *                  information is extracted. It is assumed
             *                  that this type supports the following:
             *                      * Type IntType::diglist_type
             *                      * Method sign_type IntType::sign()
             *                      * Method diglist_type IntType::digit_list()
             *                      * Method size_type DigListType::size()
             *                      * Method const_iterator diglist_type::crbegin()
             *                      * Method const_iterator diglist_type::crend()
             *                      * Method bool IntType::is_negative()
             *                      * Method bool sign_type::value()
             * 
             *  \param lhs The first integer
             *  \param rhs The second integer
             *  \return  Representation of which number is greater:
             *           * -1 : lhs < rhs (less than)
             *           *  0 : rhs == lhs (equivalent)
             *           * +1 : lhs > rhs (greater than)
             */
            template <typename IntType>
            short compare(const IntType& lhs, const IntType& rhs);

            /** More basic function that only compares two digit lists.
             *  Because there is no numerical sign information, this
             *  is a comparison of the numbers' magnitudes.
             * 
             *  \tparam DigListType Type of the STL compliant container
             *                      holding the digits of a number. It
             *                      is assumed that this type supports
             *                      the following:
             *                      * Method size_type DigListType::size()
             *                      * Method const_iterator DigListType::crbegin()
             *                      * Method const_iterator DigListType::crend()
             * 
             *  \param diglist1 The digit string of the first number
             *  \param diglist2 The digit string of the second number
             *  \return  Representation of which number is greater:
             *           * -1 : lhs < rhs (less than)
             *           *  0 : rhs == lhs (equivalent)
             *           * +1 : lhs > rhs (greater than)
             */
            template <typename DigListType>
            short compare_lists( const DigListType& diglist1,
                                 const DigListType& diglist2
                                 );

            /** Helper function to tell if a number is basically 0.
             * 
             *  \tparam DigListType Type of the STL compliant container
             *                      holding the digits of a number. It
             *                      is assumed that this type supports
             *                      the following:
             *                          * Method size_type DigListType::size()
             *                          * Method digit_type DigListType::front()
             * 
             *  \param diglist The digit string of the number
             *  \return  Whether or not the list contains only {0}.
             *           Note that an empty list or a list with more
             *           than one 0's do not count.
             */
            template <typename DigListType>
            bool is_zero_list(const DigListType& diglist);
        }
    }
}

#include "Precision_Int_Operations.inl"

#endif  //Include guard