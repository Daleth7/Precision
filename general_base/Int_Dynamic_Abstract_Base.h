/** \file Int_Dynamic_Abstract_Base.h
  * 
  * Precision::General_Base::Dynamic::Abstract::Int provides an image-less
  * precision integer with basic integer operations from arithmetic to
  * sign manipulation. This class will also serve as the core to all
  * dynamic (i.e. mutable radix) number types in the Precision namespace.
  * Results of operations involving multiple integers will share the base
  * of the left hand side value.
  */

#ifndef HHH_HHHHHH_H_PRECISION_INT_BASE_IMPO_DYN77_NAMEIC_ABSTRACT_BASE_H
#define HHH_HHHHHH_H_PRECISION_INT_BASE_IMPO_DYN77_NAMEIC_ABSTRACT_BASE_H

#include "impl/Precision_Signed_Interface.h"
#include "impl/Precision_Digit_Container.h"
#include "impl/Precision_Defaults.h"

namespace Precision{
    namespace General_Base{
        namespace Dynamic{
            namespace Abstract{
                /** A basic integer implementation with a mutable number base
                  * that is specified as a constructor parameter. This integer
                  * supports arithmetic to bitwise operations as well direct
                  * digit manipulation.
                  * Results of operations involving multiple integers will
                  * share the base of the left hand side value.
                  *
                  * \tparam ByteType  The type used for the computer representation
                  *                   of each digit. This type also sets the
                  *                   maximum base that may be used and affects the
                  *                   dynamic storage size. Defaulted to unsigned
                  *                   char, which is guaranteed to allow a base up
                  *                   to 255 and is guaranteed to be at least one
                  *                   byte in size. It is recommended to use
                  *                   unsigned char for small bases.
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
                  *     // Create an integer type using int's for digits.
                  *     using Int = Dynamic::Abstract::Int<int>;
                  *
                  *     // Create an integer object with base 25 and initialized
                  *     // to a value of 420.
                  *     Dynamic::Abstract::Int<> dynamic(420, 25);
                  *
                  *     // Create an integer with a custom container that
                  *     // handles memory differently than std::vector. Also
                  *     // create objects of bases 17 and 33.
                  *     template <typename value_type>
                  *     using my_container = Custom_Container<value_type>;
                  *     using MemInt = Dynamic::Abstract::Int<int, my_container>;
                  *
                  *     MemInt num1(12345, 17),
                  *            num2({9, 0, 1, 1, 16, 14, 10}, -1, 33)
                  *            ;
                  *     MemInt result = num2 % num1; // result is base 33
                  *                                  // (left hand side)
                  *     
                  * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                  */
                template < typename ByteType = Default::byte_type,
                           template <typename...>
                               class Container = Default::container_type,
                           typename SignType = Default::sign_type
                           >
                class Int : public Digit_Container<ByteType, Container>,
                            public Signed_Interface<SignClass>
                {
                    public:
                        //Type aliases

                        /** A primitive type used for dealing with intentional
                          * overflow in certain calculations.
                          */
                        using catalyst_type = long double;

                        /** Parent class with the digit container */
                        using dig_container = Digit_Container<ByteType, Container>;

                        /** Parent class with the signed interface */
                        using signed_interface = Signed_Interface<SignClass>;

                        /* Inherited from Digit_Container

                        using digit_type;
                        using diglist_type;
                        using size_type;
                        using signed_size_type;

                        */

                        /* Inherited from Signed_Interface

                        using sign_type = SignType;

                        */



                        //Read-only functions

                        /* Inherited from Digit_Container

                        bool is_zero()const;
                        bool is_mag_one()const;
                        bool is_even()const;
                        bool is_odd()const;
                        const diglist_type& digit_list()const;
                        size_type count_digits()const;
                        digit_type digit(size_type index)const;

                        */

                        /* Inherited from Sign_Interface

                        bool is_positive()const;
                        bool is_negative()const;
                        sign_type sign()const;

                        */

                        /** Generate the positive version of this number.
                          *
                          * \return The magnitude of this number.
                          */
                        Int magnitude()const;

                        /** Compare two integers to determine if the left
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
                        short compare(const Int& rhs)const;

                        /** Generate the opposite sign version of this number.
                          *
                          * \return The negated version of this number.
                          */
                        Int operator-()const;

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
                        typename dig_container::digit_type base()const;

                        /** Return the image set. Since this number type is abstract,
                          * i.e. has no visual representation, this function always
                          * returns a 0. This function is needed for certain algorithms.
                          *
                          * \return The image set.
                          */
                        static constexpr int image_set(){return 0;}



                        //Modifiers

                        /* Inherited from Digit_Container

                        void shift(signed_size_type);
                        void shift_left(size_type e);
                        void shift_right(size_type e);
                        void detach();

                        */

                        /* Inherited from Sign_Interface

                        void negate();
                        void make_positive();
                        void make_negative();
                        void sign(sign_type new_sign);

                        */

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
                        void assign( typename dig_container::size_type index,
                                     typename dig_container::digit_type new_dig
                                     );

                        /** Force a single digit to a specified value.
                          *
                          * \param index Position of the digit to change.
                          * \param new_dig The new digit to assign.
                          *
                          */
                        void force_assign( typename dig_container::size_type index,
                                           typename dig_container::digit_type new_dig
                                           );

                        /** Change the base.
                          *
                          * \param new_base The base to change to.
                          *
                          */
                        void base(typename dig_container::digit_type new_base);

                        /** Change the image set. Since this is an abstract number, i.e.
                          * has no visual representation, this function does nothing. This
                          * is required for certain algorithms.
                          *
                          * \param new_set The new image set to use.
                          *
                          */
                        template <typename Dummy>
                        void image_set(const Dummy& new_set){}



                        //Arithmetic operators

                        /** Arithmetic addition operator.
                          * 
                          * \param rhs Right hand side number to add from.
                          * 
                          * \return A reference to this object.
                          */
                        Int& operator+=(const Int& rhs);  

                        /** Arithmetic subtraction operator.
                          * 
                          * \param rhs Right hand side number to subtract.
                          * 
                          * \return A reference to this object.
                          */
                        Int& operator-=(const Int& rhs);  

                        /** Arithmetic mutiplication operator.
                          * 
                          * \param rhs Right hand side number to multiply with.
                          * 
                          * \return A reference to this object.
                          */
                        Int& operator*=(const Int& rhs);  

                        /** Arithmetic division operator.
                          * 
                          * \param rhs Denominator.
                          * 
                          * \return A reference to this object.
                          */
                        Int& operator/=(const Int& rhs);  

                        /** Arithmetic modulus operator.
                          * 
                          * \param rhs Denominator.
                          * 
                          * \return A reference to this object.
                          */
                        Int& operator%=(const Int& rhs);

                        /** Arithmetic pre-decrement operator.
                          * 
                          * \return A reference to this object.
                          */
                        Int& operator--();

                        /** Arithmetic post-decrement operator.
                          * 
                          * \return A reference to this object.
                          */
                        Int operator--(int);

                        /** Arithmetic pre-increment operator.
                          * 
                          * \return A reference to this object.
                          */
                        Int& operator++();

                        /** Arithmetic post-increment operator.
                          * 
                          * \return A reference to this object.
                          */
                        Int operator++(int);



                        //Bitwise operators

                        /** Bitwise AND operator.
                          * 
                          * \param rhs Right hand side number.
                          * 
                          * \return A reference to this object.
                          */
                        Int& operator&=(const Int& rhs);  

                        /** Bitwise OR operator.
                          * 
                          * \param rhs Right hand side number.
                          * 
                          * \return A reference to this object.
                          */
                        Int& operator|=(const Int& rhs);  

                        /** Bitwise XOR operator.
                          * 
                          * \param rhs Right hand side number.
                          * 
                          * \return A reference to this object.
                          */
                        Int& operator^=(const Int& rhs);  

                        /** Bitwise COMPLEMENT operator
                          * Note that since there is no set limit to the number
                          * of digits, ~Int(0) shall throw an exception due to
                          * insufficient memory for allocation. Also note that
                          * because of the internal representation of the
                          * number, the number of bits flipped is equivalent to
                          * static_cast<Int>(log(Int, 2)) and is not guaranteed
                          * to be a multiple of eight. The sign is guaranteed
                          * to be negated.
                          *
                          * \return The bitwise complement of this number.
                          */
                        Int operator~()const;

                        /** Bitwise LEFT SHIFT operator.
                          * 
                          * \param rhs Right hand side number.
                          * 
                          * \return A reference to this object.
                          */
                        Int& operator<<=(const Int& rhs);

                        /** Bitwise RIGHT SHIFT operator.
                          * 
                          * \param rhs Right hand side number.
                          * 
                          * \return A reference to this object.
                          */
                        Int& operator>>=(const Int& rhs);



                        //Logical Operators

                        /** Logical, base dependent AND operator.
                          * 
                          * \param rhs Right hand side number.
                          * 
                          * \return The result of the logical operation.
                          */
                        Int logical_and(const Int& rhs)const;

                        /** Logical, base dependent OR operator.
                          * 
                          * \param rhs Right hand side number.
                          * 
                          * \return The result of the logical operation.
                          */
                        Int logical_or(const Int& rhs)const;

                        /** Logical, base dependent XOR operator.
                          * 
                          * \param rhs Right hand side number.
                          * 
                          * \return The result of the logical operation.
                          */
                        Int logical_xor(const Int& rhs)const;

                        /** Logical, base dependent reverse XOR operator.
                          * Unlike with a binary base, performing an XOR
                          * operation twice does not return a previous key.
                          * This function will return a previous key if this
                          * object was the result of a prior XOR operation.
                          * 
                          * \param rhs Right hand side number.
                          * 
                          * \return The result of the logical operation.
                          */
                        Int logical_rev_xor(const Int& rhs)const;

                        /** Logical, base dependent COMPLEMENT operator
                          *
                          * \return The logical complement of this number.
                          */
                        Int logical_complement()const;

                        /** Logical, base dependent SHIFT operator. The
                          * operation is equivalent to multiplying  or dividing
                          * this number by a power of base.
                          *
                          * \param sz The number of digit places to shift by.
                          *
                          * \return The logical shift of this number.
                          */
                        Int logical_shift
                            (typename dig_container::signed_size_type sz)const;

                        /** Logical, base dependent LEFT SHIFT operator. The
                          * operation is equivalent to multiplying this number
                          * by a power of base.
                          *
                          * \param sz The number of digit places to shift by.
                          *
                          * \return The logical shift of this number.
                          */
                        Int logical_shift_left
                            (typename dig_container::size_type sz)const;

                        /** Logical, base dependent RIGHT SHIFT operator. The
                          * operation is equivalent to dividing this number
                          * by a power of base.
                          *
                          * \param sz The number of digit places to shift by.
                          *
                          * \return The logical shift of this number.
                          */
                        Int logical_shift_right
                            (typename dig_container::size_type sz)const;



                        //Constructors and destructor

                        /** Construct the number starting with a signed
                          * integer value.
                          *
                          * \param val The signed integer number to start with.
                          * \param new_base The number base this number is
                          *                 represented as.
                          */
                        Int( typename dig_container::signed_size_type val=0,
                             typename dig_container::digit_type new_base=10
                             );

                        /** Construct the number starting with a string of
                          * digits and a numerical sign.
                          *
                          * \param new_diglist A string of digits to start with.
                          * \param new_sign A numerical sign to start with.
                          * \param new_base The number base this number is
                          *                 represented as.
                          */
                        Int( const typename dig_container::diglist_type& new_diglist,
                             typename signed_interface::sign_type new_sign,
                             typename dig_container::digit_type new_base = 10
                             );

                        /** Construct the number using a string of digits pointed
                          * to by iterators.
                          *
                          * \tparam Iterator The iterator type.
                          *
                          * \param pbeg Start of the digit string.
                          * \param pend End of the digit string.
                          * \param new_sign A numerical sign to start with.
                          * \param new_base The number base this number is
                          *                 represented as.
                          */
                        template <typename Iterator>
                        Int( const Iterator& pbeg, const Iterator& pend,
                             typename signed_interface::sign_type new_sign,
                             typename dig_container::digit_type new_base = 10
                             );

                        /** Compiler generated copy constructor. */
                        Int(const Int&)             = default;
                        /** Compiler generated copy move constructor. */
                        Int(Int&&)                  = default;
                        /** Compiler generated assignment operator. */
                        Int& operator=(const Int&)  = default;
                        /** Compiler generated move assignment operator. */
                        Int& operator=(Int&&)       = default;
                        /** Compiler generated destructor. */
                        ~Int()                      = default;



                    protected:
                        /* Inherited from Digit_Container

                        diglist_type m_number;

                        */

                        /* Inherited from Signed_Interface

                        sign_type m_sign;

                        */

                        typename dig_container::digit_type m_base;



                    private:
                        friend void swap(Int& f, Int& s){
                            //Making New Friends idiom thanks to Dan Saks
                            using std::swap;
                            swap(f.m_number, s.m_number);
                            swap(f.m_sign, s.m_sign);
                            swap(f.m_base, s.m_base);
                        }
                };

#define PASTE_TEMPL_ template < typename ByteType,                      \
                                template <typename...> class Container, \
                                typename SignType                       \
                                >
#define PASTE_INST_ Int <ByteType, Container, SignType>

                #include "impl/paste/Precision_Operator.paste"

#undef PASTE_TEMPL_
#undef PASTE_INST_
            }
        }
    }
}

#include "impl/Int_Dynamic_Abstract_Base.inl"

#endif  //Include guard