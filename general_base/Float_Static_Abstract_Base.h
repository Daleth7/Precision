/** \file FLOAT_Static_Abstract_Base.h
  * 
  * Precision::General_Base::Static::Abstract::Float provides an image-less
  * precision floating point number supporting operations from arithmetic to
  * sign manipulation.
  */

#ifndef HHH_HHHHHH_H_PRECISION_FLOAT_BASE_IMPO_STATIC_ABSTRACT_BASE_H
#define HHH_HHHHHH_H_PRECISION_FLOAT_BASE_IMPO_STATIC_ABSTRACT_BASE_H

#include "impl/Int_Static_Abstract_Base.h"

namespace Precision{
    namespace General_Base{
        namespace Static{
            namespace Abstract{
                /** A basic floating point implementation with a fixed number base
                  * that is specified as a template parameter. This class supports
                  * the ability to track precision defined as the number of digits
                  * past the decimal point in a number represented in scientific
                  * notation.
                  * Numbers can also be marked to have infinite precisions if they
                  * represent exact or defined numbers. For example, "2" in "There
                  * are 2 objects," can be represented as an exact number. Or
                  * "299,792,458" in "Speed of light = 299,792,458 m/s" can be
                  * represented as a defined value with infinite precision.
                  * This implementation supports a dynamic precision. It can be set
                  * but it can also automatically shrink. For example, after the
                  * following operation:
                  *     1.234 + 6.7
                  * The sum result has a precision of 1.
                  *
                  * \tparam ByteType  The type used for the computer representation
                  *                   of each digit. This type also sets the
                  *                   maximum base that may be used and affects the
                  *                   dynamic storage size. Defaulted to unsigned
                  *                   char, which is guaranteed to allow a base up
                  *                   to 255 and is guaranteed to be at least one
                  *                   byte in size. It is recommended to use
                  *                   unsigned char for small bases.
                  * \tparam Base      The base N the class shall represent.
                  *                   Defaulted to 10.
                  * \tparam Container The container template used to store indices
                  *                   to the array.
                  *                   Most STL containers will work. This shall be
                  *                   instantiated as Container<digit_type>.
                  *                   See Digit_Container for more information.
                  *                   Defaulted to std::vector.
                  * \tparam SignType  The type used to represent the sign of the
                  *                   number, i.e. whether it is positive or
                  *                   negative. See Signed_Interface for more
                  *                   information.
                  *                   Defaulted to Precision::SignClass.
                  * 
                  * Example Instantiations:
                  * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                  *     using namespace Precision::General_Base;
                  *
                  *     // Create a floating point type using int's for digits
                  *     // and is base 25.
                  *     using Float = Static::Abstract::Float<int, 25>;
                  *
                  *     // Create a floating point with a custom container that
                  *     // handles memory differently than std::vector.
                  *     template <typename value_type>
                  *     using my_container = Custom_Container<value_type>;
                  *     using MemFloat = Static::Abstract::Float
                  *                      <int, 10, my_container>;
                  *
                  *     MemFloat::integer int_parm({3, 4}, -1);
                  *     MemFloat num1(123.456),
                  *              num2(int_parm),         // Infinite precision since
                  *                                      // it is an integer
                  *              num3(int_parm, 3),      // Alternatively, specify a precision
                  *              num4(41.35, 5),         // Mark to have 5 digits of precision,
                  *                                      // i.e. num4 == 4.13500 * 10^1
                  *              num5(3.14, 0, 0, true), // Mark to have infinite precision
                  *              num6(3.14, 2, -2, true) // Mark to have an power, i.e.
                  *                                      // num6 == 3.14e-2 == 0.0314
                  *              ;
                  *     MemFloat result1 = num1+num4; // result has a precision of 3
                  *     MemFloat result2 = num1*num4; // result has a precision of 3
                  *     
                  * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                  */
                template < typename ByteType = Default::byte_type,
                           ByteType Base = 10,
                           template <typename...>
                               class Container = Default::container_type,
                           typename SignType = Default::sign_type
                           >
                class Float {
                    public:
                        //Type aliases

                        /** Integer type used by this class. */
                        using integer_type = Int<Bytetype, Base, Container, SignType>;

                        /** A primitive type representing a floating point number. */
                        using raw_float_type = typename integer_type::catalyst_type;

                        /** Digit Container type used by integer_type */
                        using dig_container = typename integer_type::dig_container;

                        /** Signed integer interface used by integer_type */
                        using signed_interface = typename integer_type::signed_interface;

                        /** The raw primitive representing the digit. */
                        using digit_type = typename integer_type::digit_type;

                        /** The underlying container storing the string of digits.
                          * Refer to Precision::Digit_Container for more information.
                          */
                        using digstr_type = typename integer_type::digstr_type;

                        /** The primitive representing size in digstr_type. */
                        using size_type = typename integer_type::size_type;

                        /** A primitive type used for dealing with size related
                          * operations that need the negative range.
                          */
                        using signed_size_type = typename integer_type::signed_size_type;

                        /** sign_type represents the underlying sign class used for
                         *  composition. The class is assumed to be a lightweight POD.
                         */
                        using sign_type = typename integer_type::sign_type;



                        //Read-only functions

                        /** Check if the number is equivalent to 0.
                          *
                          * \return True if the number is 0. False otherwise.
                          */
                        bool is_zero()const;

                        /** Check if the number is equivalent to 1, regardless
                          * of sign.
                          *
                          * \return True if the number is 1. False otherwise.
                          */
                        bool is_mag_one()const;

                        /** Return a reference to the underlying container.
                          *
                          * \return a read-only reference to the underlying container.
                          */
                        const digstr_type& digit_string()const;

                        /** Count the number of digits in the number.
                          * To count the number of digits excluding trailing zeros,
                          * call count_digits_no_trail().
                          *
                          * For example, for a number 12.3560000, this function would
                          * return 9.
                          * Or, for a number 0.00345, this function would
                          * return 3.
                          *
                          * \return The number of digits in the number.
                          */
                        size_type count_digits()const;

                        /** Count the number of digits in the number excluding trailing
                          * zeros.
                          *
                          * For example, for a number 12.3560000, this function would
                          * return 5.
                          * Or, for a number 120.000, this function would
                          * return 2.
                          *
                          * \return The number of digits in the number excluding trailing
                          *         zeros.
                          */
                        size_type count_digits_no_trail()const;

                        /** Count the number of digits to the left of the decimal point
                          * of the number represented normally, i.e. the number of digits
                          * in the integer portion of this number.
                          *
                          * For example, for a number 12.3560000, this function would
                          * return 2.
                          *
                          * \return The number of digits in the number's integer portion.
                          */
                        size_type count_digits_left()const;

                        /** Count the number of digits to the right of the decimal point
                          * of the number represented normally, i.e. the number of digits
                          * in the fraction portion of this number.
                          * To count the number of digits excluding trailing zeros,
                          * call count_digits_right_no_trail().
                          *
                          * For example, for a number 12.3560000, this function would
                          * return 7.
                          *
                          * \return The number of digits in the number's fraction portion.
                          */
                        size_type count_digits_right()const;

                        /** Count the number of digits to the right of the decimal point
                          * of the number represented normally, i.e. the number of digits
                          * in the fraction portion of this number. Trailing zeros are
                          * excluded from the count.
                          *
                          * For example, for a number 12.3560000, this function would
                          * return 3.
                          *
                          * \return The number of digits in the number's fraction portion,
                          *         excluding trailing zeros.
                          */
                        size_type count_digits_right_no_trail()const;

                        /** Get a copy of a specific digit in the number. Note that the
                          * index does not have to be bound to the actual digit count
                          * of the number since any digit beyond is essentially 0.
                          *
                          * \param index The position of a digit to retrieve.
                          *
                          * \return The requested digit at position index.
                          */
                        digit_type digit(size_type index)const;

                        /** Return if the sign is positive, or +1.
                         *
                         * \return Whether the sign is considered positive.
                         */
                        bool is_positive()const;

                        /** Return if the sign is negative, or -1.
                         *
                         * \return Whether the sign is considered negative.
                         */
                        bool is_negative()const;

                        /** Return the actual sign value itself.
                         *
                         * \return The sign object representing the value
                         *         (-1 for negative and +1 for positive).
                         */
                        sign_type sign()const;

                        /** Generate the positive version of this number.
                          *
                          * \return The magnitude of this number.
                          */
                        Float magnitude()const;

                        /** Compare two number to determine if the left
                          * hand side is less than, greater than, or equal
                          * to the right hand side.
                          *
                          * \param rhs The number to compare against
                          *
                          * \return The result of the comparison:
                          *         * -1 - this < rhs
                          *         *  0 - this == rhs
                          *         * +1 - this > rhs
                          */
                        short compare(const Float& rhs)const;

                        /** Generate the opposite sign version of this number.
                          *
                          * \return The negated version of this number.
                          */
                        Float operator-()const;

                        /** Determine if this number is equal to positive one.
                          *
                          * \return Whether or not this == +1.
                          */
                        bool is_one()const;

                        /** Determine if this number is equal to negative one.
                          *
                          * \return Whether or not this == -1.
                          */
                        bool is_neg_one()const;

                        /** Return the number base of this number.
                          *
                          * \return The number base.
                          */
                        static constexpr typename dig_container::digit_type base();

                        /** Return the image set. Since this number type is abstract,
                          * i.e. has no visual representation, this function always
                          * returns a 0. This function is needed for certain algorithms.
                          *
                          * \return The image set.
                          */
                        static constexpr int image_set(){return 0;}

                        /** Return this number converted to an integer, i.e. the
                          * fraction portion of this number is truncated.
                          *
                          * \return This number's integer portion.
                          */
                        integer_type integer()const;

                        /** Return the underlying integer this object uses with the
                          * full precision.
                          *
                          * \return The underlying integer with full precision.
                          */
                        integer_type raw_integer()const;

                        /** Check if this number is essentially an integer. For
                          * this number to be equivalent to an integer, all digits
                          * to the right of the point (after accounting for power)
                          * must be zero.
                          *
                          * \return Whether this number is equivalent to an integer.
                          */
                        bool is_integer()const;

                        /** Return this number's precision, or the number of valid
                          * digits after the point when this number is in scientific
                          * notation.
                          * For example, for the number 1.234 * 10^7, this function
                          * would return 3.
                          *
                          * \return This number's precision.
                          */
                        size_type precision()const;

                        /** Return this number's power when this number is in
                          * scientific notation.
                          * For example, for the number 1.234 * 10^7, this function
                          * would return 7.
                          *
                          * \return This number's power.
                          */
                        signed_size_type power()const;

                        /** Check if this number has infinite precision.
                          *
                          * \return Whether this number has infinite precision.
                          */
                        bool has_infinite_precision()const;



                        //Modifiers

                        /** Extend the digit string. This is equivalent to multiplying
                          * the number by a power of its number base.
                          *
                          * \param e The number of digit places to shift to the left by.
                          */
                        void shift_left(size_type e);

                        /** Extend or shrink the digit string by inserting 0's at the
                          * beginning or removing digits from the beginning.
                          *
                          * \param sz The number of digit places to shift by.
                          */
                        void shift(signed_size_type sz);

                        /** Extend the digit string. This is equivalent to dividing
                          * the number by a power of its number base.
                          *
                          * \param e The number of digit places to shift to the right by.
                          */
                        void shift_right(size_type e);

                        /** Insert a new digit at the end of the string. */
                        void append(digit_type new_dig);

                        /** Remove the leftmost (last) digit in the string. */
                        void detach();

                        /** Change the sign from positive to negative
                         *  or vice versa.
                         */
                        void negate();

                        /** Force the sign to be positive. */
                        void make_positive();

                        /** Force the sign to be negative. */
                        void make_negative();

                        /** Change the sign to positive or negative.
                         *
                         *  \param new_sign The sign to change to.
                         *                  (-inf, 0) --> Negative
                         *                  [0, inf) --> Positive
                         */
                        void sign(sign_type new_sign);

                        /** Force the number to be 0 */
                        void make_zero();

                        /** Force the number to be +1 */
                        void make_one();

                        /** Force the number to be -1 */
                        void make_neg_one();

                        /** Force the number to be +2 */
                        void make_two();

                        /** Divide this number by two */
                        void halve();

                        /** Change a single digit to a specified value.
                          *
                          * \param index Position of the digit to change.
                          * \param new_dig The new digit to assign.
                          *
                          */
                        void assign(size_type index, digit_type new_dig);

                        /** Change the base. Since this is a static number, i.e.
                          * has a fixed base, this function does nothing. This
                          * is required for certain algorithms.
                          *
                          * \param new_base The base to change to.
                          *
                          */
                        void base(typename dig_container::digit_type new_base){}

                        /** Change the image set. Since this is an abstract number, i.e.
                          * has no visual representation, this function does nothing. This
                          * is required for certain algorithms.
                          *
                          * \param new_set The new image set to use.
                          *
                          */
                        template <typename Dummy>
                        void image_set(const Dummy& new_set){}

                        /** Specify a new precision for this number. */
                        void precision(size_type new_prec);

                        /** Specify a new power for this number as if
                          * this number was in scientific notation.
                          */
                        void power(signed_size_type new_exp);

                        /** Set this number to have or not have infinite precision. */
                        void infinite_precision(bool has_inf_prec);



                        //Arithmetic operators

                        /** Arithmetic addition operator.
                          * 
                          * \param rhs Right hand side number to add from.
                          * 
                          * \return A reference to this object.
                          */
                        Float& operator+=(const Float& rhs);  

                        /** Arithmetic subtraction operator.
                          * 
                          * \param rhs Right hand side number to subtract.
                          * 
                          * \return A reference to this object.
                          */
                        Float& operator-=(const Float& rhs);  

                        /** Arithmetic mutiplication operator.
                          * 
                          * \param rhs Right hand side number to multiply with.
                          * 
                          * \return A reference to this object.
                          */
                        Float& operator*=(const Float& rhs);  

                        /** Arithmetic division operator.
                          * 
                          * \param rhs Denominator.
                          * 
                          * \return A reference to this object.
                          */
                        Float& operator/=(const Float& rhs);

                        /** Arithmetic pre-decrement operator.
                          * 
                          * \return A reference to this object.
                          */
                        Float& operator--();

                        /** Arithmetic post-decrement operator.
                          * 
                          * \return A reference to this object.
                          */
                        Float operator--(int);

                        /** Arithmetic pre-increment operator.
                          * 
                          * \return A reference to this object.
                          */
                        Float& operator++();

                        /** Arithmetic post-increment operator.
                          * 
                          * \return A reference to this object.
                          */
                        Float operator++(int);



                        //Special operators

                        /** Remainder operator.
                          * 
                          * \param rhs Denominator.
                          * 
                          * \return The remainder of this number
                          *         divided by rhs.
                          */
                        Float& remainder(const Float& rhs);

                        /** Inverse operator.
                          * 
                          * \return The inverse value of this number.
                          */
                        Float inverse()const;

                        /** Inverse operator. Invert this number and
                          * return it.
                          * 
                          * \return The inverse value of this number.
                          */
                        Float& invert();

                        /** Exponentiation operator with an integer.
                          * 
                          * \param rhs Exponent.
                          * 
                          * \return This number raised to the power of rhs.
                          */
                        Float& exponentiate(const integer_type& rhs);

                        /** Exponentiation operator with a floating point.
                          *
                          * Exponentiation with floating point powers is
                          * not supported yet.
                          * 
                          * \param rhs Exponent.
                          * 
                          * \return This number raised to the power of rhs.
                          */
                        Float& exponentiate(const Float& rhs);

                        /** Remainder operator. The equivalent
                          * of calling remainder().
                          * 
                          * \param rhs Denominator.
                          * 
                          * \return The remainder of this number
                          *         divided by rhs.
                          */
                        Float& operator%=(const Float& rhs);

                        /** Inverse operator. The equivalent
                          * of calling inverse().
                          * 
                          * \return The inverse value of this number.
                          */
                        Float operator~()const;

                        /** Exponentiation operator with an integer.
                          * The equivalent of calling exponentiate().
                          * 
                          * \param rhs Exponent.
                          * 
                          * \return This number raised to the power of rhs.
                          */
                        Float& operator^=(const integer_type& rhs);

                        /** Exponentiation operator with a floating point.
                          * The equivalent of calling exponentiate().
                          *
                          * Exponentiation with floating point powers is
                          * not supported yet.
                          * 
                          * \param rhs Exponent.
                          * 
                          * \return This number raised to the power of rhs.
                          */
                        Float& operator^=(const Float& rhs); 



                        //Constructors and destructor

                        /** Construct the number starting with a signed
                          * floating point value.
                          *
                          * \param val The signed floating point number to start with.
                          *            If val is 0, and no precision (0) is specified, the
                          *            number is assumed to have infinite precision.
                          * \param prec The initial precision. If a precision of 0 is
                          *             specified, the precision is equal to the number of
                          *             digits in the fraction portion of val without
                          *             trailing zeros.
                          *             Note that this parameter refers to the precision of
                          *             val, i.e. the numbers of digits to the right of the 
                          *             point in val. This is different than the precision
                          *             of this class, which is the number of digits to the
                          *             right of the point if the number was written in
                          *             scientific notation.
                          * \param exp An additional power of Base to multiply the number
                          *            by. For example, Float(23.5, 2, -5) == 23.5*10^-5
                          *            == 2.35*10^-4 == 0.000235
                          * \param inf_prec Whether the number will have infinite precision
                          *                 or not. If this is true, prec is ignored.
                          */
                        Float( raw_float_type val=0.0,
                               size_type prec=0, signed_size_type exp=0,
                               bool inf_prec=false
                               );

                        /** Construct the number starting with a string of
                          * digits and a numerical sign.
                          *
                          * \param new_diglist A string of digits to start with.
                          * \param new_sign A numerical sign to start with.
                          * \param prec The initial precision.
                          * \param exp An additional power of Base to multiply the number
                          *            by. For example, Float(23.5, 2, -5) == 23.5*10^-5
                          *            == 2.35*10^-4 == 0.000235
                          * \param inf_prec Whether the number will have infinite precision
                          *                 or not. If this is true, prec is ignored.
                          */
                        Float( const digstr_type& new_diglist, sign_type new_sign,
                               size_type prec=0, signed_size_type exp=0,
                               bool inf_prec=false
                               );

                        /** Construct the number using a string of digits pointed
                          * to by iterators.
                          *
                          * \tparam Iterator The iterator type.
                          *
                          * \param pbeg Start of the digit string.
                          * \param pend End of the digit string.
                          * \param new_sign A numerical sign to start with.
                          * \param prec The initial precision.
                          * \param exp An additional power of Base to multiply the number
                          *            by. For example, Float(23.5, 2, -5) == 23.5*10^-5
                          *            == 2.35*10^-4 == 0.000235
                          * \param inf_prec Whether the number will have infinite precision
                          *                 or not. If this is true, prec is ignored.
                          */
                        template <typename Iterator>
                        Float( const Iterator& pbeg, const Iterator& pend,
                               sign_type new_sign,
                               size_type prec=0, signed_size_type exp=0,
                               bool inf_prec=false
                               );

                        /** Construct the number using an integer_type object.
                          *
                          * \param new_int The integer value to initialize with.
                          * \param prec The initial precision.
                          * \param exp An additional power of Base to multiply the number
                          *            by. For example, Float(23.5, 2, -5) == 23.5*10^-5
                          *            == 2.35*10^-4 == 0.000235
                          * \param inf_prec Whether the number will have infinite precision
                          *                 or not. If this is true, prec is ignored.
                          */
                        Float( const integer_type& new_int,
                               size_type prec=0, signed_size_type exp=0,
                               bool inf_prec=false
                               );

                        /** Compiler generated copy constructor. */
                        Float(const Float&)             = default;
                        /** Compiler generated copy move constructor. */
                        Float(Float&&)                  = default;
                        /** Compiler generated assignment operator. */
                        Float& operator=(const Float&)  = default;
                        /** Compiler generated move assignment operator. */
                        Float& operator=(Float&&)       = default;
                        /** Compiler generated destructor. */
                        ~Float()                        = default;



                    protected:

                        // Treat the number in scientific notation with
                        // m_pow storing the power.
                        // Store the number as an integer consisting
                        // of all sig. figs. without trailing zeros. m_prec
                        // tracks the number of digits to the right of the
                        // point as if this number was in scientific notation.
                        // For exact and defined numbers, m_inf can be used to
                        // mark infinite precision.
                        integer_type        m_int;
                        size_type           m_prec;
                        signed_size_type    m_pow;
                        bool                m_inf;



                    private:
                        friend void swap(Float& f, Float& s){
                            //Making New Friends idiom thanks to Dan Saks
                            using std::swap;
                            swap(f.m_int,  s.m_int);
                            swap(f.m_prec, s.m_prec);
                            swap(f.m_pow,  s.m_pow);
                            swap(f.m_inf,  s.m_inf);
                        }
                };

#define PASTE_TEMPL_ template < typename ByteType, ByteType Base,       \
                                template <typename...> class Container, \
                                typename SignType                       \
                                >
#define PASTE_INST_ Float <ByteType, Base, Container, SignType>

                #include "impl/paste/Precision_Operator_No_Bit.paste"

#undef PASTE_TEMPL_
#undef PASTE_INST_
            }
        }
    }
}

#include "impl/Float_Static_Abstract_Base.inl"

#endif  //Include guard