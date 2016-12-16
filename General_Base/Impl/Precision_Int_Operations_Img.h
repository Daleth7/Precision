#ifndef IMG_REALATED_UTILSSSS_HHH23823828982888888____7
#define IMG_REALATED_UTILSSSS_HHH23823828982888888____7

    /*  Centralize the more complex algorithms
        under a set of helpers. This eases
        extensions to the library.
    */

namespace Precision{
    namespace Volatile {
        namespace Int_Operations {
            namespace Img{
                template <typename IntType, typename CharTIterator>
                typename IntType::str_type str(
                    const IntType&,
                    CharTIterator dig_glyphs, CharTIterator sym_glyphs
                );

                //Set the precision through parameter
                template <typename IntType, typename CharTIterator>
                typename IntType::str_type sci_note(
                    const IntType&, typename IntType::size_type,
                    CharTIterator dig_glyphs, CharTIterator sym_glyphs
                );

                template <typename IntType, typename CharTIterator>
                typename IntType::str_type sci_note_w_spaces(
                    const IntType&, typename IntType::size_type,
                    CharTIterator dig_glyphs, CharTIterator sym_glyphs
                );

                template <typename IntType, typename CharTIterator>
                void parse(
                    const typename IntType::str_type& src,
                    typename IntType::diglist_type& dest,
                    typename IntType::sign_type& new_sign,
                    typename IntType::digit_type base,
                    const CharTIterator digs
                );
            }
        }
    }
}

#include "Precision_Int_Operations_Img.inl"

#endif  //Include guard