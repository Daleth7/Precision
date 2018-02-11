/** \file Int_Dynamic_Base.h
  * 
  * Precision::General_Base::Dynamic::Int provides a precision integer
  * with basic integer operations from arithmetic to sign manipulation.
  * This class also supports conversion to a printable string and supports.
  * a runtime mutable base.
  */
#ifndef HHH_HHHHHH_H_PRECISION_INT_BASE_IMPO_DYANMIC03920_BASE_H
#define HHH_HHHHHH_H_PRECISION_INT_BASE_IMPO_DYANMIC03920_BASE_H

#include "Int_Dynamic_Abstract_Base.h"
#include "impl/Precision_Defaults.h"
#include "impl/Precision_Image_Set_Interface.h"
#include "impl/Precision_Int_Operations_Img.h"

namespace Precision{
    namespace General_Base{
        namespace Dynamic{
            /** A basic integer implementation with a mutable number base
              * that is specified as a constructor parameter. This integer
              * supports arithmetic to bitwise operations as well direct
              * digit manipulation.
              *
              * \tparam CharT           The type of character or image used to represent
              *                         each digit in Base N. Must be compatible as a
              *                         template parameter to std::basic_string<T>. The
              *                         string type (str_type) of the class shall be
              *                         instantiated as std::basic_string<CharT>.
              *                         Defaulted to char.
              * \tparam CharIter        Type of iterators pointing to image set.
              *                         Defaulted to char const *.
              * \tparam ByteType        The type used for the computer representation
              *                         of each digit. This type also sets the
              *                         maximum base that may be used and affects the
              *                         dynamic storage size. Defaulted to unsigned
              *                         char, which is guaranteed to allow a base up
              *                         to 255 and is guaranteed to be at least one
              *                         byte in size. It is recommended to use
              *                         unsigned char for small bases.
              * \tparam Container       The container template used to store indices
              *                         to the array.
              *                         Most STL containers will work. This shall be
              *                         instantiated as Container<digit_type>.
              *                         See Digit_Container for more information.
              *                         Defaulted to std::vector.
              * \tparam SignType        The type used to represent the sign of the
              *                         number, i.e. whether it is positive or
              *                         negative. See Signed_Interface for more
              *                         information.
              *                         Defaulted to Precision::SignClass.
              * \tparam SearchPolicy    The search policy for image-based operations.
              * 
              * Example Instantiations:
              * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
              *     using namespace Precision::General_Base;
              *
              *     // Create an integer using int's for digits
              *     // and is base 25.
              *     using Int = Dynamic::Int<int>;
              *
              *     // Create an integer object with base 25 and initialized
              *     // to a value of 420.
              *     Dynamic::Int<> dynamic(420, 25)
              *
              *     // Create an integer with a custom container that
              *     // handles memory differently than std::vector.
              *     // Also create objects with the new instantiation
              *     // of bases 7 and 17.
              *     template <typename value_type>
              *     using my_container = Custom_Container<value_type>;
              *
              *     const char digs* = "0123456789abcdefg";
              *
              *     using MemInt = Dynamic::Int< char, char const *,
              *                                 digs, Precision::Default::syms,
              *                                 int,
              *                                 my_container
              *                                 >;
              *
              *     MemInt num1(12345, 7), num2("-3289ddf2550444ac4444e0g", 31);
              *     MemInt result = num2.logical_xor(num1);
              *
              *     std::cout << result.str() << '\n';
              *
              *     // Create an integer with a custom image representation
              *     // Also construct objects of base 10 and 4.
              *     const char digs* = ")!@#$%^&*(", *syms = "=_>3\t?1";
              *
              *     using ShiftInt = Dynamic::Int<char, char const *>;
              *
              *     ShiftInt num1(12345, 10, digs, syms),
              *              num2("-@#$(&)@#*$#@&%", 4, digs, syms)
              *              ;
              *     ShiftInt result = num2 * num1;
              *
              *     std::cout << result.str() << '\n';
              *     
              * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
              */
            template < typename CharT = Default::image_type,
                       typename CharIter = CharT const *,
                       typename ByteType = Default::byte_type,
                       template <typename...>
                           class Container = Default::container_type,
                       typename SignType = Default::sign_type,
                       typename SearchPolicy = ImgSearchPolicy::Binary
                       >
            class Int : public Abstract::Int<ByteType, Container, SignType> {
                public:
                    //Type aliases

                    /** The type of the image set interface used internally. */
                    using image_set_type    = Image_Set_Interface< CharT,
                                                                   CharIter,
                                                                   ByteType
                                                                   >;

                    /** The type of the glyph to represent digits and symbols. */
                    using image_type        = typename image_set_type::image_type;

                    /** The type of the iterator for glyphs. */
                    using image_iter_type   = typename image_set_type::iterator_type;
        
                    /** The type of a string of images. */
                    using str_type          = typename image_set_type::str_type;
        
                    /** The type of the abstract type. */
                    using abstract_type     = Abstract::Int< ByteType,
                                                             Container, SignType
                                                             >;

                    /** A primitive type used for dealing with intentional
                      * overflow in certain calculations.
                      */
                    using catalyst_type     = typename abstract_type::catalyst_type;

                    /** The raw primitive representing the digit. */
                    using digit_type        = typename abstract_type::digit_type;

                    /** The underlying container storing the string of digits.
                      * See Precision::Digit_Container for more details.
                      */
                    using digstr_type      = typename abstract_type::digstr_type;

                    /** The primitive representing size in digstr_type. */
                    using size_type         = typename abstract_type::size_type;

                    /** A primitive type used for dealing with size related
                      * operations that still need the negative range.
                      */
                    using signed_size_type  = typename abstract_type::signed_size_type;

                    /** sign_type represents the underlying sign class used for
                     *  composition. The class is assumed to be a lightweight POD.
                     */
                    using sign_type         = typename abstract_type::sign_type;



                    //Read-only functions

                    /** Check if the digit string is equivalent to 0.
                      *
                      * \return True if the string is 0. False otherwise.
                      */
                    bool is_zero()const
                        {return m_abs.is_zero();}

                    /** Check if the digit string is equivalent to 1, regardless
                      * of sign.
                      *
                      * \return True if the string is 1. False otherwise.
                      */
                    bool is_mag_one()const
                        {return m_abs.is_mag_one();}

                    /** Check if the rightmost (first) digit of the string is
                      * even.
                      *
                      * \return True if the string is even. False otherwise.
                      */
                    bool is_even()const
                        {return m_abs.is_even();}

                    /** Check if the rightmost (first) digit of the string is
                      * odd.
                      *
                      * \return True if the string is odd. False otherwise.
                      */
                    bool is_odd()const
                        {return m_abs.is_odd();}

                    /** Return a reference to the underlying container.
                      *
                      * \return a read-only reference to the underlying container.
                      */
                    const digstr_type& digit_string()const
                        {return m_abs.digit_string();}

                    /** Count the number of digits in the string. The value returned
                      * should always be at least one.
                      *
                      * \return The number of digits in the string.
                      */
                    size_type count_digits()const
                        {return m_abs.count_digits();}

                    /** Get a copy of a specific digit in the string. Note that the
                      * index does not have to be bound to the actual size of the
                      * string since any digit beyond is essentially 0.
                      *
                      * \param index The position of a digit to retrieve.
                      *
                      * \return The requested digit at position index.
                      */
                    digit_type digit(size_type index)const
                        {return m_abs.digit(index);}

                    /** Return if the sign is positive, or +1.
                     *
                     * \return Whether the sign is considered positive.
                     */
                    bool is_positive()const
                        {return m_abs.is_positive();}

                    /** Return if the sign is negative, or -1.
                     *
                     * \return Whether the sign is considered negative.
                     */
                    bool is_negative()const
                        {return m_abs.is_negative();}

                    /** Return the actual sign value itself.
                     *
                     * \return The sign object representing the value
                     *         (-1 for negative and +1 for positive).
                     */
                    sign_type sign()const
                        {return m_abs.sign();}


                    /** Generate the positive version of this number.
                      *
                      * \return The magnitude of this number.
                      */
                    Int magnitude()const
                        {return Int(m_abs.magnitude(), m_img_set.digit_set(), m_img_set.symbol_set());}

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
                    short compare(const Int& rhs)const
                        {return m_abs.compare(rhs.m_abs);}

                    /** Generate the opposite sign version of this number.
                      *
                      * \return The negated version of this number.
                      */
                    Int operator-()const
                        {return Int(-m_abs, m_img_set.digit_set(), m_img_set.symbol_set());}

                    /** Determine if this number is equal to positive one.
                      *
                      * \return Whether or not this == +1.
                      */
                    bool is_one()const
                        {return m_abs.is_one();}

                    /** Determine if this number is equal to negative one.
                      *
                      * \return Whether or not this == -1.
                      */
                    bool is_neg_one()const
                        {return m_abs.is_neg_one();}

                    /** Return the number base of this number.
                      *
                      * \return The number base.
                      */
                    digit_type base()const
                        {return m_abs.base();}

                    /** Return the image set.
                      *
                      * \return The image set.
                      */
                    const image_set_type& image_set()const
                        {return m_img_set;}

                    /** Convert this integer to a string of glyphs/symbols.
                      *
                      *  \return The converted string of glyphs, or the "image." 
                      */
                    str_type str()const{
                        return Volatile::Int_Operations::Img::str
                                   <Int, image_set_type>( *this, m_img_set );
                    }

                    /** Convert an integer to a string of glyphs/symbols
                      *  in scientific notation, e.g. "+1.23e16."
                      *
                      *  \param prec The number of digits to show after
                      *              the point symbol. 
                      *
                      *  \return The converted string of glyphs, or the "image." 
                      */
                    str_type sci_note(size_type prec=Default::display_prec)const{
                        return Volatile::Int_Operations::Img::sci_note
                                   <Int, image_set_type>( *this, prec, this->m_img_set );
                    }

                    /** Convert an integer to a string of glyphs/symbols
                      *  in scientific notation, e.g. "+ 1.23 e 16."
                      *
                      *  \param prec The number of digits to show after
                      *              the point symbol. 
                      *
                      *  \return The converted string of glyphs, or the "image." 
                      */
                    str_type sci_note_w_spaces(size_type prec=Default::display_prec)const{
                        return Volatile::Int_Operations::Img::sci_note_w_spaces
                                   <Int, image_set_type>( *this, prec, this->m_img_set );
                    }

                    /** Return the abstract version of this integer, i.e. one with
                      * no image representation. 
                      *
                      *  \return Return the abstract version of this integer. 
                      */
                    abstract_type abstract()const{
                        return abstract_type( m_abs.digit_string(), m_abs.sign(),
                                              this->base()
                                              );
                    }



                    //Modifiers

                    /** Extend the digit string. This is equivalent to multiplying
                      * the number by a power of its number base.
                      *
                      * \param e The number of digit places to shift to the left by.
                      */
                    void shift_left(size_type e)
                        {m_abs.shift_left(e);}

                    /** Extend or shrink the digit string by inserting 0's at the
                      * beginning or removing digits from the beginning.
                      *
                      * \param sz The number of digit places to shift by.
                      */
                    void shift(signed_size_type sz)
                        {m_abs.shift(sz);}

                    /** Extend the digit string. This is equivalent to dividing
                      * the number by a power of its number base.
                      *
                      * \param e The number of digit places to shift to the right by.
                      */
                    void shift_right(size_type e)
                        {m_abs.shift_right(e);}

                    /** Insert a new digit at the end of the string. */
                    void append(digit_type new_dig)
                        {m_abs.append(new_dig);}

                    /** Remove the leftmost (last) digit in the string. */
                    void detach()
                        {m_abs.detach();}

                    /** Change the sign from positive to negative
                     *  or vice versa.
                     */
                    void negate()
                        {m_abs.negate();}

                    /** Force the sign to be positive. */
                    void make_positive()
                        {m_abs.make_positive();}

                    /** Force the sign to be negative. */
                    void make_negative()
                        {m_abs.make_negative();}

                    /** Change the sign to positive or negative.
                     *
                     *  \param new_sign The sign to change to.
                     *                  (-inf, 0) --> Negative
                     *                  [0, inf) --> Positive
                     */
                    void sign(sign_type new_sign)
                        {m_abs.sign(new_sign);}

                    /** Force the number to be 0 */
                    void make_zero()
                        {m_abs.make_zero();}

                    /** Force the number to be +1 */
                    void make_one()
                        {m_abs.make_one();}

                    /** Force the number to be -1 */
                    void make_neg_one()
                        {m_abs.make_neg_one();}

                    /** Force the number to be +2 */
                    void make_two()
                        {m_abs.make_two();}

                    /** Divide this number by two */
                    void halve()
                        {m_abs.halve();}

                    /** Change a single digit to a specified value.
                      *
                      * \param index Position of the digit to change.
                      * \param new_dig The new digit to assign.
                      *
                      */
                    void assign(size_type index, digit_type new_dig)
                        {m_abs.assign(index, new_dig);}

                    /** Force a single digit to a specified value.
                      *
                      * \param index Position of the digit to change.
                      * \param new_dig The new digit to assign.
                      *
                      */
                    void force_assign(size_type index, digit_type new_dig)
                        {m_abs.force_assign(index, new_dig);}

                    /** Change the base.
                      *
                      * \param new_base The base to change to.
                      *
                      */
                    void base(digit_type new_base)
                        {m_abs.base(new_base);}

                    /** Set a new image set.
                      *
                      * \param new_set The new image set to use.
                      *
                      */
                    void image_set(const image_set_type& new_set)
                        {m_img_set = new_set;}



                    //Arithmetic operators

                    /** Arithmetic addition operator.
                      * 
                      * \param rhs Right hand side number to add from.
                      * 
                      * \return A reference to this object.
                      */
                    Int& operator+=(const Int& rhs)
                        {m_abs += rhs.m_abs; return *this;}

                    /** Arithmetic subtraction operator.
                      * 
                      * \param rhs Right hand side number to subtract.
                      * 
                      * \return A reference to this object.
                      */
                    Int& operator-=(const Int& rhs)
                        {m_abs -= rhs.m_abs; return *this;}  

                    /** Arithmetic mutiplication operator.
                      * 
                      * \param rhs Right hand side number to multiply with.
                      * 
                      * \return A reference to this object.
                      */
                    Int& operator*=(const Int& rhs)
                        {m_abs *= rhs.m_abs; return *this;}  

                    /** Arithmetic division operator.
                      * 
                      * \param rhs Denominator.
                      * 
                      * \return A reference to this object.
                      */
                    Int& operator/=(const Int& rhs)
                        {m_abs /= rhs.m_abs; return *this;}  

                    /** Arithmetic modulus operator.
                      * 
                      * \param rhs Denominator.
                      * 
                      * \return A reference to this object.
                      */
                    Int& operator%=(const Int& rhs)
                        {m_abs %= rhs.m_abs; return *this;}

                    /** Arithmetic pre-decrement operator.
                      * 
                      * \return A reference to this object.
                      */
                    Int& operator--()
                        {--m_abs; return *this;}

                    /** Arithmetic post-decrement operator.
                      * 
                      * \return A reference to this object.
                      */
                    Int operator--(int)
                        {return Int(m_abs--, m_img_set.digit_set(), m_img_set.symbol_set());}

                    /** Arithmetic pre-increment operator.
                      * 
                      * \return A reference to this object.
                      */
                    Int& operator++()
                        {++m_abs; return *this;}

                    /** Arithmetic post-increment operator.
                      * 
                      * \return A reference to this object.
                      */
                    Int operator++(int)
                        {return Int(m_abs++, m_img_set.digit_set(), m_img_set.symbol_set());}



                    //Bitwise operators

                    /** Bitwise AND operator.
                      * 
                      * \param rhs Right hand side number.
                      * 
                      * \return A reference to this object.
                      */
                    Int& operator&=(const Int& rhs)
                        {m_abs &= rhs.m_abs; return *this;}  

                    /** Bitwise OR operator.
                      * 
                      * \param rhs Right hand side number.
                      * 
                      * \return A reference to this object.
                      */
                    Int& operator|=(const Int& rhs)
                        {m_abs |= rhs.m_abs; return *this;}

                    /** Bitwise XOR operator.
                      * 
                      * \param rhs Right hand side number.
                      * 
                      * \return A reference to this object.
                      */
                    Int& operator^=(const Int& rhs)
                        {m_abs ^= rhs.m_abs; return *this;}

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
                    Int operator~()const
                        {return Int(~m_abs, m_img_set.digit_set(), m_img_set.symbol_set());}

                    /** Bitwise LEFT SHIFT operator.
                      * 
                      * \param rhs Right hand side number.
                      * 
                      * \return A reference to this object.
                      */
                    Int& operator<<=(const Int& rhs)
                        {m_abs <<= rhs.m_abs; return *this;}

                    /** Bitwise RIGHT SHIFT operator.
                      * 
                      * \param rhs Right hand side number.
                      * 
                      * \return A reference to this object.
                      */
                    Int& operator>>=(const Int& rhs)
                        {m_abs >>= rhs.m_abs; return *this;}



                    //Logical Operators

                    /** Logical, base dependent AND operator.
                      * 
                      * \param rhs Right hand side number.
                      * 
                      * \return The result of the logical operation.
                      */
                    Int logical_and(const Int& rhs)const
                        {return Int(m_abs.logical_and(rhs.m_abs), m_img_set.digit_set(), m_img_set.symbol_set());}

                    /** Logical, base dependent OR operator.
                      * 
                      * \param rhs Right hand side number.
                      * 
                      * \return The result of the logical operation.
                      */
                    Int logical_or(const Int& rhs)const
                        {return Int(m_abs.logical_or(rhs.m_abs), m_img_set.digit_set(), m_img_set.symbol_set());}

                    /** Logical, base dependent XOR operator.
                      * 
                      * \param rhs Right hand side number.
                      * 
                      * \return The result of the logical operation.
                      */
                    Int logical_xor(const Int& rhs)const
                        {return Int(m_abs.logical_xor(rhs.m_abs), m_img_set.digit_set(), m_img_set.symbol_set());}

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
                    Int logical_rev_xor(const Int& rhs)const
                        {return Int(m_abs.logical_rev_xor(rhs.m_abs), m_img_set.digit_set(), m_img_set.symbol_set());}

                    /** Logical, base dependent COMPLEMENT operator
                      *
                      * \return The logical complement of this number.
                      */
                    Int logical_complement()const
                        {return Int(m_abs.logical_complement(), m_img_set.digit_set(), m_img_set.symbol_set());}

                    /** Logical, base dependent SHIFT operator. The
                      * operation is equivalent to multiplying  or dividing
                      * this number by a power of base.
                      *
                      * \param sz The number of digit places to shift by.
                      *
                      * \return The logical shift of this number.
                      */
                    Int logical_shift(signed_size_type sz)const
                        {return Int(m_abs.logical_shift(sz), m_img_set.digit_set(), m_img_set.symbol_set());}

                    /** Logical, base dependent LEFT SHIFT operator. The
                      * operation is equivalent to multiplying this number
                      * by a power of base.
                      *
                      * \param sz The number of digit places to shift by.
                      *
                      * \return The logical shift of this number.
                      */
                    Int logical_shift_left(size_type sz)const
                        {return Int(m_abs.logical_shift_left(sz), m_img_set.digit_set(), m_img_set.symbol_set());}

                    /** Logical, base dependent RIGHT SHIFT operator. The
                      * operation is equivalent to dividing this number
                      * by a power of base.
                      *
                      * \param sz The number of digit places to shift by.
                      *
                      * \return The logical shift of this number.
                      */
                    Int logical_shift_right(size_type sz)const
                        {return Int(m_abs.logical_shift_right(sz), m_img_set.digit_set(), m_img_set.symbol_set());}



                    //Constructors and destructor

                    /** Construct the number starting with a signed
                      * integer value.
                      *
                      * \param val The signed integer number to start with.
                      * \param new_base The number base this number is
                      *                 represented as.
                      * \param new_dig_img_set Iterator to the start
                      *                        of the digit image set.
                      * \param new_sym_img_set Iterator to the start
                      *                        of the symbol image set.
                      */
                    Int( typename abstract_type::signed_size_type val=0,
                         typename abstract_type::digit_type new_base=10,
                         image_iter_type new_dig_img_set = Default::digs,
                         image_iter_type new_sym_img_set = Default::syms
                         )
                        : m_abs(val, new_base)
                        , m_img_set(new_dig_img_set, new_sym_img_set)
                    {}

                    /** Convert a string of glyphs to an integer.
                      *
                      * \param img_str The original image to convert.
                      * \param new_base The number base this number is
                      *                 represented as.
                      * \param new_dig_img_set Iterator to the start
                      *                        of the digit image set.
                      * \param new_sym_img_set Iterator to the start
                      *                        of the symbol image set.
                      */
                    Int( const str_type& img_str,
                         typename abstract_type::digit_type new_base=10,
                         image_iter_type new_dig_img_set = Default::digs,
                         image_iter_type new_sym_img_set = Default::syms
                         )
                        : m_abs(0, new_base)
                        , m_img_set(new_dig_img_set, new_sym_img_set)
                    {
                        digstr_type new_num(1, 0);
                        sign_type new_sign;
                        Volatile::Int_Operations::Img::parse
                              <Int, image_set_type, SearchPolicy>
                              ( img_str, new_num, new_sign,
                                this->base(), m_img_set
                                );
                        m_abs = abstract_type(new_num, new_sign, new_base);
                    }

                    /** Construct the number starting with a string of
                      * digits and a numerical sign.
                      *
                      * \param new_diglist A string of digits to start with.
                      * \param new_sign A numerical sign to start with.
                      * \param new_base The number base this number is
                      *                 represented as.
                      * \param new_dig_img_set Iterator to the start
                      *                        of the digit image set.
                      * \param new_sym_img_set Iterator to the start
                      *                        of the symbol image set.
                      */
                    Int( const typename abstract_type::digstr_type& new_diglist,
                         typename abstract_type::sign_type new_sign,
                         typename abstract_type::digit_type new_base=10,
                         image_iter_type new_dig_img_set = Default::digs,
                         image_iter_type new_sym_img_set = Default::syms
                         )
                        : m_abs(new_diglist, new_sign, new_base)
                        , m_img_set(new_dig_img_set, new_sym_img_set)
                    {}

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
                      * \param new_dig_img_set Iterator to the start
                      *                        of the digit image set.
                      * \param new_sym_img_set Iterator to the start
                      *                        of the symbol image set.
                      */
                    template <typename Iterator>
                    Int( const Iterator& pbeg, const Iterator& pend,
                         typename abstract_type::sign_type new_sign,
                         typename abstract_type::digit_type new_base=10,
                         image_iter_type new_dig_img_set = Default::digs,
                         image_iter_type new_sym_img_set = Default::syms
                         )
                        : m_abs(pbeg, pend, new_sign, new_base)
                        , m_img_set(new_dig_img_set, new_sym_img_set)
                    {}

                    /** Construct the number using an abstract integer.
                      *
                      * \tparam Iterator The iterator type.
                      *
                      * \param abs The abstract number.
                      * \param new_dig_img_set Iterator to the start
                      *                        of the digit image set.
                      * \param new_sym_img_set Iterator to the start
                      *                        of the symbol image set.
                      */
                    Int( const abstract_type& abs,
                         image_iter_type new_dig_img_set = Default::digs,
                         image_iter_type new_sym_img_set = Default::syms
                         )
                        : m_abs(abs)
                        , m_img_set(new_dig_img_set, new_sym_img_set)
                    {}

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
                    // Use composition instead of inheritance to make sure
                    // any construction is type consistent, e.g. due to
                    // "x [op] y" or x.magnitude() expressions.
                    abstract_type m_abs;
                    image_set_type m_img_set;



                private:
                    friend void swap(Int& f, Int& s){
                        //Making New Friends idiom thanks to Dan Saks
                        std::swap(f.m_abs, s.m_abs);
                        std::swap(f.m_img_set, s.m_img_set);
                    }
            };

#define PASTE_TEMPL_ template < typename CharT, typename CharIter,      \
                                typename ByteType,                      \
                                template <typename...> class Container, \
                                typename SignType, typename SearchPolicy\
                                >
#define PASTE_INST_ Int <CharT, CharIter, ByteType, Container, SignType, SearchPolicy>

                #include "impl/paste/Precision_Operator.paste"

#undef PASTE_TEMPL_
#undef PASTE_INST_
        }
    }
}

#endif  //Include guard