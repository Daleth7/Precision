/** \file Int_Static_Base.h
  * 
  * Precision::General_Base::Static::Int provides a precision integer
  * with basic integer operations from arithmetic to sign manipulation.
  * This class also supports conversion to a printable string.
  */

#ifndef HHH_HHHHHH_H_PRECISION_INT_BASE_IMPO_STATIC_ABSTRACT_BASE_H
#define HHH_HHHHHH_H_PRECISION_INT_BASE_IMPO_STATIC_ABSTRACT_BASE_H

#include "Int_Static_Abstract_Base.h"
#include "impl/Precision_Defaults.h"

namespace Precision{
    namespace General_Base{
        namespace Static{
            /** A basic integer implementation with a fixed number base
              * that is specified as a template parameter. This  integer
              * supports arithmetic to bitwise operations as well direct
              * digit manipulation.
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
              * \tparam CharT     The type of character or image used to represent
              *                   each digit in Base N. Must be compatible as a
              *                   template parameter to std::basic_string<T>. The
              *                   string type (str_type) of the class shall be
              *                   instantiated as std::basic_string<CharT>.
              * \tparam _digs     A pointer to the first digit in an array
              *                   containing the images of each digit. The array
              *                   must have external linkage.
              *                   Important note: It is the responsibility of the
              *                   instantiator to ensure this is a valid parameter
              *                   and that the array pointed to contains the
              *                   appropriate images.
              *                   _digs is defaulted to Constant::symbols which
              *                   points to an array containing images of type
              *                   const char:
              *                   "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ".
              * \tparam _syms     A pointer to the first symbol in an array with
              *                   external linkage and that contains the images
              *                   of each symbol.
              *                   Each symbol is further defined below in the
              *                   order it should appear in the array.
              *                   * plus      An image depicting the plus sign to
              *                               indicate a positive number as in
              *                               "+123".
              *                   * minus     An image depicting the minus sign to
              *                               indicate a negative number as in
              *                               "-123".
              *                   * point     An image depicting the decimal point
              *                               to indicate a separation between a
              *                               number's whole part and decimal part
              *                               as in "123.456".
              *                   * exponent  An image depicting the exponential
              *                               sign to represent a power of Base
              *                               as in "1.23 e 456" which is
              *                               equivalent to writing "1.23 x 10^456".
              *                   * space     An image depicting an empty space
              *                               between two other images as in
              *                               "+ 1234".
              *                   The above five symbols are the minimum.
              *                   Depending on what the number type is, there may
              *                   be additional symbols needed:
              *                   * slash     An image depicting the slash sign to
              *                               indicate a fractional number as in
              *                               "12/345". Required for Fraction
              *                               number types.
              *                   * imaginary An image depicting the imaginary
              *                               number to indicate a complex number
              *                               as in "a + bi". Required for Complex
              *                               number types.
              *                   Important note: It is the responsibility of the
              *                   instantiator to ensure this is a valid parameter
              *                   and that the array pointed to contains the
              *                   appropriate symbols.
              *                   _syms is defaulted to Constant::symbols which
              *                   points to an array containing images of type
              *                   const char:
              *                       * plus symbol:      '+'
              *                       * minus symbol:     '-'
              *                       * point symbol:     '.'
              *                       * exponent symbol:  'e'
              *                       * space symbol:     ' '
              *                       * slash symbol:     '/'
              *                       * imaginary symbol: 'i'
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
              *     // Create an integer using int's for digits
              *     // and is base 25.
              *     using Int = Static::Abstract::Int<int, 25>;
              *
              *     // Create an integer with a custom container that
              *     // handles memory differently than std::vector.
              *     template <typename value_type>
              *     using my_container = Custom_Container<value_type>;
              *
              *     char digs* = "0123456789abcdefg";
              *
              *     using MemInt = Static::Abstract::Int< int, 17,
              *                                           char, digs,
              *                                           Precision::Default::syms, 
              *                                           my_container
              *                                           >;
              *
              *     MemInt num1(12345), num2("-3289ddf2550444ac4444e0g");
              *     MemInt result = num2.logical_xor(num1);
              *
              *     std::cout << result.str() << '\n';
              *     
              * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
              */
            template < typename ByteType = Default::byte_type, ByteType Base = 10,
                       typename CharT = Default::image_type,
                       CharT const * const _digs = Default::digs,
                       CharT const * const _syms = Default::syms,
                       template <typename...>
                           class Container = Default::container_type,
                       typename SignType = Default::sign_type
                       >
            class Int : public Abstract::Int<ByteType, Base, Container, SignType> {
                public:
                    //Type aliases

                    /* Inherited from Abstract::Int

                    using catalyst_type;
                    using dig_container;
                    using signed_interface;

                    using digit_type;
                    using diglist_type;
                    using size_type;
                    using signed_size_type;

                    using sign_type;

                    */

                    /** The type of the glyph to represent digits and symbols. */
                    using image_type    = CharT;
        
                    /** The type of a string of images. */
                    using str_type      = std::basic_string<image_type>;
        
                    /** The type of the abstract type. */
                    using abstract_type = Abstract::Int< ByteType, Base,
                                                         Container, SignType
                                                         >;



                    //Read-only functions

                    /* Inherited from Abstract::Int

                    bool is_zero()const;
                    bool is_mag_one()const;
                    bool is_even()const;
                    bool is_odd()const;
                    const diglist_type& digit_list()const;
                    size_type count_digits()const;
                    digit_type digit(size_type index)const;

                    bool is_positive()const;
                    bool is_negative()const;
                    sign_type sign()const;

                    Int magnitude()const;
                    short compare(const Int& rhs)const;
                    Int operator-()const;

                    bool is_one()const;
                    bool is_neg_one()const;

                    static constexpr typename abstract_type::digit_type base();

                    */

                    /** Convert this integer to a string of glyphs/symbols.
                      *
                      *  \return The converted string of glyphs, or the "image." 
                      */
                    str_type str()const;

                    /** Convert an integer to a string of glyphs/symbols
                      *  in scientific notation, e.g. "+1.23e16."
                      *
                      *  \param prec The number of digits to show after
                      *              the point symbol. 
                      *
                      *  \return The converted string of glyphs, or the "image." 
                      */
                    str_type sci_note(size_type prec=display_prec)const;

                    /** Convert an integer to a string of glyphs/symbols
                      *  in scientific notation, e.g. "+ 1.23 e 16."
                      *
                      *  \param prec The number of digits to show after
                      *              the point symbol. 
                      *
                      *  \return The converted string of glyphs, or the "image." 
                      */
                    str_type sci_note_w_spaces(size_type prec=display_prec)const;



                    //Modifiers

                    /* Inherited from Abstract::Int

                    void shift(signed_size_type);
                    void shift_left(size_type e);
                    void shift_right(size_type e);
                    void detach();

                    void negate();
                    void make_positive();
                    void make_negative();
                    void sign(sign_type new_sign);

                    void make_zero();
                    void make_one();
                    void make_neg_one();
                    void make_two();
                    void halve();

                    void assign( typename abstract_type::size_type index,
                                 typename abstract_type::digit_type new_dig
                                 );
                    void force_assign( typename abstract_type::size_type index,
                                       typename abstract_type::digit_type new_dig
                                       );

                    void set_base(typename abstract_type::digit_type new_base){}

                    */



                    //Arithmetic operators

                    /* Inherited from Abstract::Int

                    Int& operator+=(const Int& rhs);
                    Int& operator-=(const Int& rhs);
                    Int& operator*=(const Int& rhs);
                    Int& operator/=(const Int& rhs);
                    Int& operator%=(const Int& rhs);
                    Int& operator--();
                    Int operator--(int);
                    Int& operator++();
                    Int operator++(int);

                    */



                    //Bitwise operators

                    /* Inherited from Abstract::Int

                    Int& operator&=(const Int& rhs); 
                    Int& operator|=(const Int& rhs);
                    Int& operator^=(const Int& rhs);
                    Int operator~()const;
                    Int& operator<<=(const Int& rhs);
                    Int& operator>>=(const Int& rhs);

                    */



                    //Logical Operators

                    /* Inherited from Abstract::Int

                    Int logical_and(const Int& rhs)const;
                    Int logical_or(const Int& rhs)const;
                    Int logical_xor(const Int& rhs)const;
                    Int logical_rev_xor(const Int& rhs)const;
                    Int logical_complement()const;
                    Int logical_shift
                        (typename abstract_type::signed_size_type sz)const;
                    Int logical_shift_left
                        (typename abstract_type::size_type sz)const;
                    Int logical_shift_right
                        (typename abstract_type::size_type sz)const;

                    */



                    //Constructors and destructor

                    /** Construct the number starting with a signed
                      * integer value.
                      *
                      * \param val The signed integer number to start with.
                      */
                    Int(typename abstract_type::signed_size_type val=0);

                    /** Convert a string of glyphs to an integer.
                      *
                      * \param img_str The original image to convert.
                      */
                    Int(const str_type& img_str);

                    /** Construct the number starting with a string of
                      * digits and a numerical sign.
                      *
                      * \param new_diglist A string of digits to start with.
                      * \param new_sign A numerical sign to start with.
                      */
                    Int( const typename abstract_type::diglist_type& new_diglist,
                         typename abstract_type::sign_type new_sign
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
                         typename abstract_type::sign_type new_sign
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
                    /* Inherited from Abstract::Int

                    diglist_type m_number;
                    sign_type m_sign;

                    void verify_diglist();

                    */



                private:
                    friend void swap(Int& f, Int& s){
                        //Making New Friends idiom thanks to Dan Saks
                        Abstract::Int::swap(f, s);
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

#include "impl/Int_Static_Base.inl"

#endif  //Include guard