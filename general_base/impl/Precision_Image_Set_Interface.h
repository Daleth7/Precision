/** \file Precision_Image_Set_Interface.h
  * This file contains the image interface that deals with
  * converting an "abstract" integer to a printable string.
  * This interface is designed to make child number classes
  * easier and faster to implement.
  */

#ifndef PRECISION_IMAGE_INTERFACE_INGHERITABBBL5
#define PRECISION_IMAGE_INTERFACE_INGHERITABBBL5

#include <string>
#include <iterator> // For std::advance()
#include <algorithm> // For std::lower_bound()

namespace Precision {
    namespace ImgSearchPolicy{
        /** Used as a tag to inform an algorithm to search for an
          * image by iterating normally.
          */
        class Normal{};

        /** Used as a tag to inform an algorithm to search for an
          * image using a binary search algorithm.
          */
        class Binary{};
    }

    /** This is an interface that provides a set of functions
      * to help convert a given "abstract" integer to a printable
      * string.
      *
      * \tparam CharT Type of the printable glyphs.
      * \tparam CharTIterator Type of iterators pointing to image set.
      * \tparam ByteType Type of the "abstract" digits to convert.
      */
    template <typename CharT, typename CharTIterator, typename ByteType>
    class Image_Set_Interface {
        public:
            //Type aliases

            /** Alias for the printable glyph type */
            using image_type      = CharT;

            /** Alias for a reference to the constant glyph type */
            using const_reference = const image_type&;

            /** Alias for the string of printable glyphs */
            using str_type        = std::basic_string<image_type>;

            /** Alias for the iterators pointing to printable glyphs */
            using iterator_type   = CharTIterator;

            /** Alias for size representation */
            using size_type       = typename str_type::size_type;

            /** Alias for abstract digits to convert to printable glyphs */
            using digit_type      = ByteType;



            //Read only

            /** Test if a given image can be found in the image set this
              * interface is using.
              *
              * \tparam SearchPolicy The type of search algorithm to use
              *
              * \param img The image to test.
              * \param base The number base to expect the image to be
              *             confined within.
              *
              * \return Whether or not the image was found in the image set.
              */
            template <typename SearchPolicy = ImgSearchPolicy::Binary>
            bool is_valid(const_reference img, digit_type base)const
                {return base != this->img_to_dig<SearchPolicy>(img, base);}

            /** Convert a given image to its associated digit.
              *
              * \tparam SearchPolicy The type of search algorithm to use
              *
              * \param img The image to look for.
              * \param base The number base to expect the image to be
              *             confined within.
              *
              * \return The corresponding, "abstract" digit. If the returned
              *         value is equal to base, no match was found.
              */
            template <typename SearchPolicy = ImgSearchPolicy::Binary>
            digit_type get_index(const_reference img, digit_type base)const
                {return this->img_to_dig<SearchPolicy>(img, base);}

            /** Convert a given image to its associated digit using the
              * normal search algorithm.
              *
              * \param img The image to look for.
              * \param base The number base to expect the image to be
              *             confined within.
              *
              * \return The corresponding, "abstract" digit. If the returned
              *         value is equal to base, no match was found.
              */
            digit_type get_index_norm(const_reference img, digit_type base)const
                {return this->img_to_dig<ImgSearchPolicy::Normal>(img, base);}

            /** Convert a given image to its associated digit using the
              * binary search algorithm.
              *
              * \param img The image to look for.
              * \param base The number base to expect the image to be
              *             confined within.
              *
              * \return The corresponding, "abstract" digit. If the returned
              *         value is equal to base, no match was found.
              */
            digit_type get_index_bin(const_reference img, digit_type base)const
                {return this->img_to_dig<ImgSearchPolicy::Binary>(img, base);}

            /** Convert an abstract digit to its associated glyph.
              *
              * \param dig Digit to convert.
              *
              * \return The corresponding, printable glyph.
              *
              */
            const_reference digit(digit_type dig)const
                {return retrieve_glyph(m_0, dig);}

            /** Retrieve a glyph for special symbols such as the plus sign.
              *
              * \param pos The position of the symbol to retrieve.
              *            0) plus      "+"
              *            1) minus     "-"
              *            2) point     "."
              *            3) exponent  "e"
              *            4) space     " "
              *            5) slash     "/"
              *            6) imaginary "i"
              *
              * \return The corresponding, printable glyph.
              *
              */
            const_reference symbol(size_type pos)const
                {return retrieve_glyph(m_syms, pos);}

            /** Retrieve a glyph for the special symbol plus.
              *
              * \return The corresponding, printable glyph.
              *
              */
            const_reference plus()const
                {return retrieve_glyph(m_syms, 0);}

            /** Retrieve a glyph for the special symbol minus.
              *
              * \return The corresponding, printable glyph.
              *
              */
            const_reference minus()const
                {return retrieve_glyph(m_syms, 1);}

            /** Retrieve a glyph for the special symbol point.
              *
              * \return The corresponding, printable glyph.
              *
              */
            const_reference point()const
                {return retrieve_glyph(m_syms, 2);}

            /** Retrieve a glyph for the special symbol exponent.
              *
              * \return The corresponding, printable glyph.
              *
              */
            const_reference exponent()const
                {return retrieve_glyph(m_syms, 3);}

            /** Retrieve a glyph for the special symbol space.
              *
              * \return The corresponding, printable glyph.
              *
              */
            const_reference space()const
                {return retrieve_glyph(m_syms, 4);}

            /** Retrieve a glyph for the special symbol slash.
              *
              * \return The corresponding, printable glyph.
              *
              */
            const_reference slash()const
                {return retrieve_glyph(m_syms, 5);}

            /** Retrieve a glyph for the special symbol imaginary.
              *
              * \return The corresponding, printable glyph.
              *
              */
            const_reference imaginary()const
                {return retrieve_glyph(m_syms, 6);}

            /** Retrieve the pointer to the digit image set
              *
              * \return The iterator that points to the digit image set.
              *
              */
            const iterator_type& digit_set()const
                {return m_0;}

            /** Retrieve the pointer to the symbol image set
              *
              * \return The iterator that points to the symbol image set.
              *
              */
            const iterator_type& symbol_set()const
                {return m_syms;}



            //Modifiers

            /** Change the image set used by this interface when converting
              * an abstract number to a printable string.
              *
              * \param new_set The new set of digit glyphs.
              *
              */
            void digit_set(const iterator_type& new_set)
                {m_0 = new_set;}

            /** Change the image set used by this interface when converting
              * an abstract number to a printable string.
              *
              * \param new_set The new set of symbol glyphs.
              *
              */
            void symbol_set(const iterator_type& new_set)
                {m_syms = new_set;}



            //Constructors and destructor
            /**
              * \param dig_set A pointer to the first digit in an array
              *                containing the images of each digit. The array
              *                must have external linkage.
              *                Important note: It is the responsibility of the
              *                instantiator to ensure this is a valid parameter
              *                and that the array pointed to contains the
              *                appropriate images.
              *                dig_set is defaulted to Constant::symbols which
              *                points to an array containing images of type
              *                const char:
              *                "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ".
              * \param sym_set A pointer to the first symbol in an array with
              *                external linkage and that contains the images
              *                of each symbol.
              *                Each symbol is further defined below in the
              *                order it should appear in the array.
              *                * plus      An image depicting the plus sign to
              *                            indicate a positive number as in
              *                            "+123".
              *                * minus     An image depicting the minus sign to
              *                            indicate a negative number as in
              *                            "-123".
              *                * point     An image depicting the decimal point
              *                            to indicate a separation between a
              *                            number's whole part and decimal part
              *                            as in "123.456".
              *                * exponent  An image depicting the exponential
              *                            sign to represent a power of Base
              *                            as in "1.23 e 456" which is
              *                            equivalent to writing "1.23 x 10^456".
              *                * space     An image depicting an empty space
              *                            between two other images as in
              *                            "+ 1234".
              *                The above five symbols are the minimum.
              *                Depending on what the number type is, there may
              *                be additional symbols needed:
              *                * slash     An image depicting the slash sign to
              *                            indicate a fractional number as in
              *                            "12/345". Required for Fraction
              *                            number types.
              *                * imaginary An image depicting the imaginary
              *                            number to indicate a complex number
              *                            as in "a + bi". Required for Complex
              *                            number types.
              *                Important note: It is the responsibility of the
              *                instantiator to ensure this is a valid parameter
              *                and that the array pointed to contains the
              *                appropriate symbols.
              *                sym_set is defaulted to Constant::symbols which
              *                points to an array containing images of type
              *                const char:
              *                    * plus symbol:      '+'
              *                    * minus symbol:     '-'
              *                    * point symbol:     '.'
              *                    * exponent symbol:  'e'
              *                    * space symbol:     ' '
              *                    * slash symbol:     '/'
              *                    * imaginary symbol: 'i'
              */
            Image_Set_Interface(iterator_type dig_set, iterator_type sym_set)
                : m_0(dig_set)
                , m_syms(sym_set)
            {}

            /** Compiler generated default constructor */
            Image_Set_Interface()                                      = default;

            /** Compiler generated copy constructor */
            Image_Set_Interface(const Image_Set_Interface&)            = default;

            /** Compiler generated copy assignment operator */
            Image_Set_Interface& operator=(const Image_Set_Interface&) = default;

            /** Compiler generated move constructor */
            Image_Set_Interface(Image_Set_Interface&&)                 = default;

            /** Compiler generated move assignment operator */
            Image_Set_Interface& operator=(Image_Set_Interface&&)      = default;

            /** Compiler generated destructor */
            ~Image_Set_Interface()                                     = default;



        protected:
            /** Helper structure for template specialization */
            template <typename SearchPolicyType>
            struct spt_type {};

            /** Helper function to convert a given image to its associated digit.
              *
              * \tparam SearchPolicy The type of search algorithm to use
              *
              * \param img The image to look for.
              * \param base The number base to expect the image to be
              *             confined within.
              *
              * \return The corresponding, "abstract" digit.
              */
            template <typename SearchPolicy>
            digit_type img_to_dig(const_reference img, digit_type base)const
                {return this->img_to_dig(img, base, spt_type<SearchPolicy>());}

            /** Helper function to convert a given image to its associated digit.
              *
              * \tparam SearchPolicy The type of search algorithm to use
              *
              * \param img The image to look for.
              * \param base The number base to expect the image to be
              *             confined within.
              *
              * \return The corresponding, "abstract" digit.
              */
            template <typename SearchPolicy>
            digit_type img_to_dig(  const_reference img,
                                    digit_type base,
                                    spt_type<SearchPolicy>
                                    )const;

            digit_type img_to_dig(  const_reference img,
                                    digit_type base,
                                    spt_type<ImgSearchPolicy::Normal>
                                    )const
            {
                digit_type i = base;
                while(i-- > 0)
                    if(img == this->digit(i)) return i;
                return base;
            }


            digit_type img_to_dig(  const_reference img,
                                    digit_type base,
                                    spt_type<ImgSearchPolicy::Binary>
                                    )const
            {
                iterator_type end = m_0;
                std::advance(end, base-1);

                // Check if the image belongs in the image set.
                // This can be done since it is assumed the image set
                // is ordered. This does, however, not help for invalid
                // images whose value falls within the range.
                if(img < *m_0 || img > *(end)) return base;

                std::advance(end, 1);

                // This algorithm assumes the glyphs of type
                //  CharT are continuous and consecutive
                return std::distance(m_0, std::lower_bound(m_0, end, img));
                
            }


            /** Retrieve a glyph from an image set.
              *
              * \param beg The pointer to the image set to retrieve from.
              * \param pos The position of the glyph to retrieve.
              *
              * \return The corresponding, printable glyph.
              *
              */
            const_reference retrieve_glyph(iterator_type beg, size_type pos)const{
                iterator_type it = beg;
                std::advance(it, pos);
                return *it;
            }

            /** Pointer to the beginning of the set of images
              * representating digits.
              */
            iterator_type m_0;

            /** Pointer to the beginning of the set of images
              * representating special symbols such as the
              * plus sign.
              */
            iterator_type m_syms;
    };
}


#endif