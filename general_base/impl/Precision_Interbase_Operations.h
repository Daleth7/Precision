/** \file Precision_Interbase_Operations.h
 * This file centralizes the algorithms for operating
 * with numbers of differing number bases.
 */



#ifndef INTE29ER__ASBSEAR123399__OEPRAT0303OIP____NS____
#define INTE29ER__ASBSEAR123399__OEPRAT0303OIP____NS____

#include <functional>
#include <type_traits>

namespace Precision{
    /** A simple number conversion function to convert among bases.
     *
     *  \tparam IntType1 The type of the original number.
     *  \tparam IntType1 The type of the number to convert to.
     *  \tparam Digit_Type The type of the number base.
     *
     *  \param orig The number to convert
     *  \param base The number base to convert to.
     */
    template <typename IntType2, typename IntType1, typename Digit_Type>
    IntType2 convert_base(const IntType1& orig, Digit_Type base);

    /** A simple number conversion function to convert among bases.
     *  This function also copies over attributes based on the
     *  reference number given.
     * 
     *  \tparam IntType1 The type of the original number.
     *  \tparam IntType1 The type of the number to convert to.
     *
     *  \param orig The number to convert
     *  \param ref The second number to extract type information from
     */
    template <typename IntType1, typename IntType2>
    IntType2 convert_base_copy(const IntType1& orig, const IntType2& ref);
}

#include "Precision_Interbase_Operations.inl"

#endif  //Include guard