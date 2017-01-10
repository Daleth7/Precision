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
         * \tparam Number_Type Type of the numbers passed as arguments 
         *
         * \param f The first number to compare against 
         * \param s The second number to compare against 
         *
         * \return Whether or not the arguments f and s are equivalent.
         */
        template <typename Number_Type>
        bool are_equal(const Number_Type& f, const Number_Type& s);

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
         * \tparam Number_Type The type of the number under test 
         *
         * \param num Number to test. 
         *
         * \return Whether or not num == 0. 
         */
        template <typename Number_Type>
        inline bool is_zero(const Number_Type& num);

        /** Decoupled check if the number is equivalent to 1.
         *
         * \tparam Number_Type The type of the number under test 
         *
         * \param num Number to test. 
         *
         * \return Whether or not num == 1. 
         */
        template <typename Number_Type>
        inline bool is_one(const Number_Type& num);

        /** Decoupled check if the number is equivalent to -1.
         *
         * \tparam Number_Type The type of the number under test 
         *
         * \param num Number to test. 
         *
         * \return Whether or not num == -1. 
         */
        template <typename Number_Type>
        inline bool is_neg_one(const Number_Type& num);

        /** Decoupled check if the number sign is negative.
         *
         * \tparam Number_Type The type of the number under test 
         *
         * \param num Number to test. 
         *
         * \return Whether or not num < 0. 
         */
        template <typename Number_Type>
        inline bool is_negative(const Number_Type& num);

        /** Decoupled check if the number is odd.
         *
         * \tparam Number_Type The type of the number under test 
         *
         * \param num Number to test. 
         *
         * \return Whether or not num is odd. 
         */
        template <typename Number_Type>
        inline bool is_odd(const Number_Type& num);

        /** Decoupled check if the number is even.
         *
         * \tparam Number_Type The type of the number under test 
         *
         * \param num Number to test. 
         *
         * \return Whether or not num is even. 
         */
        template <typename Number_Type>
        inline bool is_even(const Number_Type& num);

        /** Decoupled modifier to divide a number by 2.
         *
         * \tparam Number_Type The type of the number being changed 
         *
         * \param num Number to change. 
         */
        template <typename Number_Type>
        inline void halve(Number_Type& num);

        /** Decoupled modifier to find a 1/num.
         *
         * \tparam Number_Type The type of the number being changed 
         *
         * \param num Number to change. 
         */
        template <typename Number_Type>
        inline void reciprocate(Number_Type& num);

        /** Decoupled modifier to flip a number's numerical sign.
         *
         * \tparam Number_Type The type of the number being changed 
         *
         * \param num Number to change. 
         */
        template <typename Number_Type>
        inline void negate(Number_Type& num);

        /** Modifier to change the number base of a Number_Type
         *  object to the number base of a Number_Type2 object.
         *  Whether or not the base is actually changed depends
         *  on Number_Type.
         *
         * \tparam Number_Type The type of the number being changed 
         * \tparam Number_Type2 The type of the reference number 
         *
         * \param num Number to change the base of.  
         * \param ref Number to extract base information from. 
         */
        template <typename Number_Type, typename Number_Type2>
        inline void match_base(Number_Type& num, const Number_Type2& ref);

        /** Decoupled modifier to assign 0 to a number.
         *
         * \tparam Number_Type The type of the number being changed 
         * \tparam Number_Type2 The type of the reference number 
         *
         * \param num Number to change.  
         * \param ref Number to extract base information from. 
         */
        template <typename Number_Type, typename Number_Type2>
        inline void make_zero(Number_Type& num, const Number_Type2& ref);

        /** Decoupled modifier to assign 1 to a number.
         *
         * \tparam Number_Type The type of the number being changed 
         * \tparam Number_Type2 The type of the reference number 
         *
         * \param num Number to change.  
         * \param ref Number to extract base information from. 
         */
        template <typename Number_Type, typename Number_Type2>
        inline void make_one(Number_Type& num, const Number_Type2& ref);

        /** Decoupled modifier to assign 2 to a number.
         *
         * \tparam Number_Type The type of the number being changed 
         * \tparam Number_Type2 The type of the reference number 
         *
         * \param num Number to change.  
         * \param ref Number to extract base information from. 
         */
        template <typename Number_Type, typename Number_Type2>
        inline void make_two(Number_Type& num, const Number_Type2& ref);

        /** Decoupled modifier to assign 0 to a number.
         *
         * \tparam Number_Type The type of the number being changed 
         *
         * \param num Number to change.  
         */
        template <typename Number_Type>
        inline void make_zero(Number_Type& num);

        /** Decoupled modifier to assign 1 to a number.
         *
         * \tparam Number_Type The type of the number being changed 
         *
         * \param num Number to change.  
         */
        template <typename Number_Type>
        inline void make_one(Number_Type& num);

        /** Decoupled modifier to assign 2 to a number.
         *
         * \tparam Number_Type The type of the number being changed 
         *
         * \param num Number to change.  
         */
        template <typename Number_Type>
        inline void make_two(Number_Type& num);

        /** Decoupled modifier to make a temporary number with value 0.
         *
         * \tparam Number_Type The type of the reference number 
         *
         * \param ref Number to extract base information from.  
         */
        template <typename Number_Type>
        inline Number_Type make_zero_temp(const Number_Type& ref);

        /** Decoupled modifier to make a temporary number with value 1.
         *
         * \tparam Number_Type The type of the reference number 
         *
         * \param ref Number to extract base information from.  
         */
        template <typename Number_Type>
        inline Number_Type make_one_temp(const Number_Type& ref);

        /** Decoupled modifier to make a temporary number with value 2.
         *
         * \tparam Number_Type The type of the reference number 
         *
         * \param ref Number to extract base information from.  
         */
        template <typename Number_Type>
        inline Number_Type make_two_temp(const Number_Type& ref);

        /** Decoupled modifier to make a temporary number with value 2.
         *
         * \tparam Base_Type The type of the reference number 
         *
         * \param ref Number to extract base information from.  
         */
        template <typename Number_Type>
        inline Number_Type make_two_temp(const Number_Type& ref);

        /** Helper to remove extra leading zeros.
         *
         * \tparam Number_Type The type of the number to change
         *
         * \param num Number to change.
         */
        template <typename Number_Type>
        inline void remove_excess_zeros(Number_Type& num);
    }
}

#include "Precision_Shared_Helpers.inl"

#endif