/** \file Precision_Shared_Helpers.h
 *  This file centralizes trivial and common utility functions for
 *  use among all number types. These functions can also serve to
 *  decouple algorithms for possible future improvement.
 */

#ifndef PR777ECISON_OPERATIONS_SHARED_HELPERS__H__
#define PR777ECISON_OPERATIONS_SHARED_HELPERS__H__

#include <type_traits>

namespace Precision{
    namespace Helper{
        /** <I>are_equal</I> is used in the case when the comparison MUST
         *  be by precision. This is especially important in the case
         *  of Fraction types, to avoid infinite loops or recursions.
         *
         * \tparam IntType Type of the numbers passed as arguments 
         *
         * \param f The first number to compare against 
         * \param s The second number to compare against 
         *
         * \return Whether or not the arguments f and s are equivalent.
         */
        template <typename IntType>
        bool are_equal(const IntType& f, const IntType& s);

        /** <I>cast</I> shall be used to safely convert among Precision
         *  types, mainly to ensure any cast to Fract or Float will also
         *  carry the precision. This helps ensure no loss in precision
         *  while not requiring the number type to declare a precision()
         *  function. Needs another object from which to extract the
         *  precision.
         *
         * \tparam Number_Type1 The type of the sample number  
         * \tparam Number_Type2 The type of the number to cast   
         *
         * \param sample Number from which precision or number base
         *               can be extracted.
         * \param orig The number to cast from Number_Type2 to
         *             Number_Type1
         *
         * \return The result of casting orig to Number_Type1 
         */
        template <typename Number_Type1, typename Number_Type2>
        Number_Type1 cast(const Number_Type1& sample, const Number_Type2& orig);

        /** <I>is_integer</I> and <I>integer</I> are used to relax the
         *  requirement for a number type to declare and define is_integer
         *  and integer members.
         *
         * \tparam T The type of the number under test 
         *
         * \param testee Number to test. May be fundamental. 
         *
         * \return Whether or not testee is an integer. 
         */
        template <typename T>
        bool is_integer(const T& testee);

        // Decouple certain functions even though one could just call
        //  the respective member functions. This is so that the algorithm
        //  can be expanded in the future to be more number type generic.

        /** Decoupled check if the number is equivalent to 0.
         *
         * \tparam IntType The type of the number under test 
         *
         * \param num Number to test. 
         *
         * \return Whether or not num == 0. 
         */
        template <typename IntType>
        inline bool is_zero(const IntType& num);

        /** Decoupled check if the number is equivalent to 1.
         *
         * \tparam IntType The type of the number under test 
         *
         * \param num Number to test. 
         *
         * \return Whether or not num == 1. 
         */
        template <typename IntType>
        inline bool is_one(const IntType& num);

        /** Decoupled check if the number is equivalent to -1.
         *
         * \tparam IntType The type of the number under test 
         *
         * \param num Number to test. 
         *
         * \return Whether or not num == -1. 
         */
        template <typename IntType>
        inline bool is_neg_one(const IntType& num);

        /** Decoupled check if the number sign is negative.
         *
         * \tparam IntType The type of the number under test 
         *
         * \param num Number to test. 
         *
         * \return Whether or not num < 0. 
         */
        template <typename IntType>
        inline bool is_negative(const IntType& num);

        /** Decoupled check if the number is odd.
         *
         * \tparam IntType The type of the number under test 
         *
         * \param num Number to test. 
         *
         * \return Whether or not num is odd. 
         */
        template <typename IntType>
        inline bool is_odd(const IntType& num);

        /** Decoupled check if the number is even.
         *
         * \tparam IntType The type of the number under test 
         *
         * \param num Number to test. 
         *
         * \return Whether or not num is even. 
         */
        template <typename IntType>
        inline bool is_even(const IntType& num);

        /** Decoupled check to return the number of digits
         *
         * \tparam IntType The type of the number under test 
         *
         * \param num Number to test. 
         *
         * \return The number of digits in num.
         */
        template <typename IntType>
        inline typename IntType::size_type int_size(const IntType& num);

        /** Decoupled check to return the number base
         *
         * \tparam IntType The type of the number under test 
         *
         * \param num Number to test. 
         *
         * \return The number base
         */
        template <typename IntType>
        inline typename IntType::digit_type base(const IntType& num);

        /** Decoupled check to retrieve a specific digit
         *
         * \tparam IntType The type of the number under test 
         *
         * \param num Number to test. 
         * \param idx Position of the digit to retrieve
         *
         * \return The specified digit
         */
        template <typename IntType>
        inline typename IntType::digit_type digit( const IntType& num,
                                                   typename IntType::size_type idx
                                                   );

        /** Decoupled modifier to divide a number by 2.
         *
         * \tparam IntType The type of the number being changed 
         *
         * \param num Number to change. 
         */
        template <typename IntType>
        inline void halve(IntType& num);

        /** Decoupled modifier to find a 1/num.
         *
         * \tparam IntType The type of the number being changed 
         *
         * \param num Number to change. 
         */
        template <typename IntType>
        inline void reciprocate(IntType& num);

        /** Decoupled modifier to flip a number's numerical sign.
         *
         * \tparam IntType The type of the number being changed 
         *
         * \param num Number to change. 
         */
        template <typename IntType>
        inline void negate(IntType& num);

        /** Modifier to change the number base of a IntType
         *  object to the number base of a Number_Type2 object.
         *  Whether or not the base is actually changed depends
         *  on IntType.
         *
         * \tparam IntType The type of the number being changed 
         * \tparam Number_Type2 The type of the reference number 
         *
         * \param num Number to change the base of.  
         * \param ref Number to extract base information from. 
         */
        template <typename IntType, typename Number_Type2>
        inline void match_base(IntType& num, const Number_Type2& ref);

        /** Decoupled modifier to assign 0 to a number.
         *
         * \tparam IntType The type of the number being changed 
         * \tparam Number_Type2 The type of the reference number 
         *
         * \param num Number to change.  
         * \param ref Number to extract base information from. 
         */
        template <typename IntType, typename Number_Type2>
        inline void make_zero(IntType& num, const Number_Type2& ref);

        /** Decoupled modifier to assign 1 to a number.
         *
         * \tparam IntType The type of the number being changed 
         * \tparam Number_Type2 The type of the reference number 
         *
         * \param num Number to change.  
         * \param ref Number to extract base information from. 
         */
        template <typename IntType, typename Number_Type2>
        inline void make_one(IntType& num, const Number_Type2& ref);

        /** Decoupled modifier to assign 2 to a number.
         *
         * \tparam IntType The type of the number being changed 
         * \tparam Number_Type2 The type of the reference number 
         *
         * \param num Number to change.  
         * \param ref Number to extract base information from. 
         */
        template <typename IntType, typename Number_Type2>
        inline void make_two(IntType& num, const Number_Type2& ref);

        /** Decoupled modifier to assign 0 to a number.
         *
         * \tparam IntType The type of the number being changed 
         *
         * \param num Number to change.  
         */
        template <typename IntType>
        inline void make_zero(IntType& num);

        /** Decoupled modifier to assign 1 to a number.
         *
         * \tparam IntType The type of the number being changed 
         *
         * \param num Number to change.  
         */
        template <typename IntType>
        inline void make_one(IntType& num);

        /** Decoupled modifier to assign 2 to a number.
         *
         * \tparam IntType The type of the number being changed 
         *
         * \param num Number to change.  
         */
        template <typename IntType>
        inline void make_two(IntType& num);

        /** Decoupled modifier to make a temporary number with value 0.
         *
         * \tparam IntType The type of the reference number 
         *
         * \param ref Number to extract base information from.  
         */
        template <typename IntType>
        inline IntType make_zero_temp(const IntType& ref);

        /** Decoupled modifier to make a temporary number with value 1.
         *
         * \tparam IntType The type of the reference number 
         *
         * \param ref Number to extract base information from.  
         */
        template <typename IntType>
        inline IntType make_one_temp(const IntType& ref);

        /** Decoupled modifier to make a temporary number with value 2.
         *
         * \tparam IntType The type of the reference number 
         *
         * \param ref Number to extract base information from.  
         */
        template <typename IntType>
        inline IntType make_two_temp(const IntType& ref);

        /** Decoupled modifier to make a temporary number with value 2.
         *
         * \tparam Base_Type The type of the reference number 
         *
         * \param ref Number to extract base information from.  
         */
        template <typename IntType>
        inline IntType make_two_temp(const IntType& ref);

        /** Helper to remove extra leading zeros.
         *
         * \tparam IntType The type of the number to change
         *
         * \param num Number to change.
         */
        template <typename IntType>
        inline void remove_excess_zeros(IntType& num);
    }
}

#include "Precision_Shared_Helpers.inl"

#endif