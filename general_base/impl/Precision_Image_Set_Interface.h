/** \file Precision_Image_Set_Interface.h
  * This file contains the image interface that deals with
  * converting an "abstract" integer to a printable string.
  * This interface is designed to be inerited to make child
  * number classes easier and faster to implement.
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
            using size_type       = typename str_type::size_type

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



        protected:
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
            digit_type img_to_dig(const_reference img, digit_type base)const;

            /** Retrieve a glyph from an image set.
              *
              * \param beg The pointer to the image set to retrieve from.
              * \param pos The position of the glyph to retrieve.
              *
              * \return The corresponding, printable glyph.
              *
              */
            const_reference retrieve_img(iterator_type beg, size_type pos)const{
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

namespace Precision {
#define IMG_TEMP_ template < typename CharT,         \
                             typename CharTIterator, \
                             typename ByteType       \
                             >
#define IMG_INST_ Image_Set_Interface<CharT, CharTIterator, ByteType>

    IMG_TEMP_
    template <>
    auto IMG_INST_::img_to_dig<ImgSearchPolicy::Normal>
        (const_reference img, digit_type base)
    const -> digit_type {
        digit_type i = base;
        while(i-- > 0)
            if(img == this->digit(i)) return i;
        return base;
    }

    IMG_TEMP_
    template <>
    auto IMG_INST_::img_to_dig<ImgSearchPolicy::Binary>
        (const_reference img, digit_type base)
    const -> digit_type {
        iterator_type end = m_0;
        std::advance(end, base);

        // This algorithm assumes the glyphs of type
        //  CharT are continuous and consecutive
        return std::lower_bound(m_0, end, img) - m_0;
    }

#undef IMG_TEMP_
#undef IMG_INST_
}

#endif