/** \file Precision_Int_Operations_Img.h
 *  This file centralizes the conversion algorithms to convert
 *  an integer to an "image" and vice versa.
 *  The algorithms are placed under the Volatile namespace since
 *  they require the number base to be passed as a parameter to
 *  correctly run the algorithm.
 */

#ifndef VOLATILE_H34_HHHH_PRECISION_INT_BASE_IMPL_VOLATILE_DETAIL_BASE_H
#define VOLATILE_H34_HHHH_PRECISION_INT_BASE_IMPL_VOLATILE_DETAIL_BASE_H

#include <functional>

namespace Precision{
    namespace Volatile{
        namespace Int_Operations {
            namespace Img{
                /** Convert an integer to a string of glyphs/symbols.
                 *
                 * \param ref The integer to convert.
                 * \param dig_glyphs Iterator to a set of digit glyphs. 
                 * \param sym_glyphs Iterator to a set of symbol
                 *                   (e.g. "+") glyphs. 
                 * \return The converted string of glyphs, or the "image." 
                 */
                template <typename IntType, typename CharTIterator>
                typename IntType::str_type str( const IntType& ref,
                                                CharTIterator dig_glyphs,
                                                CharTIterator sym_glyphs
                                                );

                /** Convert an integer to a string of glyphs/symbols
                 *  in scientific notation, e.g. "+1.23e16."
                 *
                 * \param ref The integer to convert.
                 * \param prec The number of digits to show after
                 *             the point symbol. 
                 * \param dig_glyphs Iterator to a set of digit glyphs. 
                 * \param sym_glyphs Iterator to a set of symbol
                 *                   (e.g. "+") glyphs. 
                 * \return The converted string of glyphs, or the "image." 
                 */
                template <typename IntType, typename CharTIterator>
                typename IntType::str_type sci_note(
                    const IntType&, typename IntType::size_type,
                    CharTIterator dig_glyphs, CharTIterator sym_glyphs
                );

                /** Convert an integer to a string of glyphs/symbols
                 *  in scientific notation, e.g. "+ 1.23 e 16."
                 *
                 * \param ref The integer to convert.
                 * \param prec The number of digits to show after
                 *             the point symbol. 
                 * \param dig_glyphs Iterator to a set of digit glyphs. 
                 * \param sym_glyphs Iterator to a set of symbol
                 *                   (e.g. "+") glyphs. 
                 * \return The converted string of glyphs, or the "image." 
                 */
                template <typename IntType, typename CharTIterator>
                typename IntType::str_type sci_note_w_spaces(
                    const IntType&, typename IntType::size_type,
                    CharTIterator dig_glyphs, CharTIterator sym_glyphs
                );

                /** Convert a string of glyphs to an integer.
                 *
                 * \param src The original image to convert 
                 * \param dest The container in which to store
                 *             the converted integer. 
                 * \param new_sign The numerical sign to give
                 *                 the converted number. 
                 * \param base The number base to interpret the image. 
                 * \param dig_glyphs Iterator to a set of digit glyphs. 
                 */
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