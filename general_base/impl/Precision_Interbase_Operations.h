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
     *  \tparam IntType Number type from which type and base
     *                  information is extracted. This function
     *                  assumes IntType has the public members:
     *                  * Type IntType::diglist_type
     *                  * Type IntType::sign_type
     *                  * Type IntType::size_type
     *                  * Type IntType::digit_type
     *                  * Type IntType::catalyst_type
     *                  * Method bool IntType::is_zero()
     *                  * Method digit_type IntType::digit(size_type)
     *                  * Method diglist_type IntType::digit_list()
     *                  * Method size_type IntType::count_digits()
     *                  * Method sign_type IntType::sign()
     *                  * Method digit_type IntType::base()
     *                  * Method void IntType::append()
     *                  * Method void IntType::detach(digit_type)
     *                  * Method void IntType::digit(size_type, digit_type)
     *                  * Method sign_type IntType::sign(sign_type)
     *
     *  \param lhs The number to convert
     *  \param rhs The second number to extract type information from
     */
    template <typename IntType1, typename IntType2>
    IntType2 convert_base(const IntType1& lhs, const IntType2& rhs);
}

#include "Precision_Interbase_Operations.inl"

#endif  //Include guard