/** \file Int_Static_Abstract_Base.h
  * 
  * Precision::General_Base::Static::Abstract::Int provides an image-less
  * precision integer with basic integer operations from arithmetic to
  * sign manipulation. This class will also serve as the core to all
  * static (i.e. fixed radix) number types in the Precision namespace.
  */

#ifndef HHH_HHHHHH_H_PRECISION_INT_BASE_IMPO_STATIC_ABSTRACT_BASE_H
#define HHH_HHHHHH_H_PRECISION_INT_BASE_IMPO_STATIC_ABSTRACT_BASE_H

#include "impl/Precision_Signed_Interface.h"
#include "impl/Precision_Digit_Container.h"
#include "impl/Precision_Defaults.h"

namespace Precision{
    namespace General_Base{
        namespace Static{
            namespace Abstract{
                /** A basic integer implementation with a fixed number base
                  * that is specified as a template parameter. This  integer
                  * supports arithmetic to bitwise operations as well direct
                  * digit manipulation.
                  *
                  * \tparam ByteType     - The type used for the computer representation of each
                  *                     digit. This type also sets the maximum base that may
                  *                     be used and affects the dynamic storage size. Defaulted
                  *                     to Precision::byte_type, which is guaranteed to allow a
                  *                     base up to 255 and is guaranteed to be at least
                  *                     one byte in size. It is recommended to use
                  *                     Precision::byte_type for small bases.
                  * \tparam Base         - The base N the class shall represent. Defaulted to 10.
                  * \tparam Container    - The container template used to store indices to the array.
                  *                     Most STL containers will work. This shall be instantiated
                  *                     as Container<digit_type>.
                  *                     * Must support the following:
                  *                         * Container::Container(size_type, digit_type)
                  *                         * Container::Container(const Container&)
                  *                         * Container& Container::operator=(const Container&)
                  *                         * Bidirectional iterators
                  *                         * Container::begin()
                  *                         * Container::end()
                  *                         * Container::crbegin()
                  *                         * Container::crend()
                  *                         * Container::push_back()
                  *                         * Container::size()
                  *                         * Container::insert(iterator, size_type, digit_type)
                  *                         * Container::erase(iterator, size_type)
                  *                         * Container::erase(iterator)
                  *                     Defaulted to Precision::default_container_type.
                  * \tparam SignType     - The type used to represent the sign of the number, i.e.
                  *                     whether it is is_positive or is_negative. Must support the
                  *                     following:
                  *                         * signed_integral_type SignType::value()const
                  *                         * bool SignType::is_positive()const
                  *                         * bool SignType::is_negative()const
                  *                         * void SignType::negate()
                  *                         * void SignType::make_positive()
                  *                         * void SignType::make_negative()
                  *                         * SignType::SignType(sign_integral_type)
                  *                     By convention, all number types in the Precision namespace
                  *                     shall abide by the following rules:
                  *                         * signed short(1) == is_positive
                  *                         * signed short(-1) == is_negative
                  *                     Defaulted to Precision::SignClass.
                  * 
                  * Example Instantiation:
                  *     using Int = Precision::General_Base::Int<int, 25>;
                  */
                template < typename ByteType = Default::byte_type,
                           ByteType Base = 10,
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
                        static constexpr typename dig_container::digit_type base();



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
                          */
                        Int(typename dig_container::signed_size_type val=0);

                        /** Construct the number starting with a string of
                          * digits and a numerical sign.
                          *
                          * \param new_diglist A string of digits to start with.
                          * \param new_sign A numerical sign to start with.
                          */
                        Int( const typename dig_container::diglist_type& new_diglist,
                             typename signed_interface::sign_type new_sign
                             );

                        /** Construct the number using a string of digits pointed
                          * to by iterators.
                          *
                          * \tparam Iterator The iterator type.
                          *
                          * \param pbeg Start of the digit string.
                          * \param pend End of the digit string.
                          * \param new_sign A numerical sign to start with.
                          */
                        template <typename Iterator>
                        Int( const Iterator& pbeg, const Iterator& pend,
                             typename signed_interface::sign_type new_sign
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

                        /** Make sure all the digits in m_number are valid and that
                          * the size is at least one.
                          */
                        void verify_diglist();



                    private:
                        friend void swap(Int& f, Int& s){
                            //Making New Friends idiom thanks to Dan Saks
                            using std::swap;
                            swap(f.m_number, s.m_number);
                            swap(f.m_sign, s.m_sign);
                        }
                };

#define PASTE_TEMPL_ template < typename ByteType, ByteType Base,       \
                                template <typename...> class Container, \
                                typename SignType                       \
                                >
#define PASTE_INST_ Int <ByteType, Base, Container, SignType>

                #include "impl/paste/Precision_Operator.paste"

#undef PASTE_TEMPL_
#undef PASTE_INST_
            }
        }
    }
}

#include "impl/Int_Static_Abstract_Base.inl"

#endif  //Include guard