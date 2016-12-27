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
                 *  \tparam IntType Type of the number to convert. It must
                 *                  have these public members:
                 *                      * Type IntType::str_type
                 *                      * Type IntType::size_type
                 *                      * Method bool IntType::is_zero()
                 *                      * Method bool IntType::is_positive()
                 *                      * Method size_type IntType::count_digits()
                 *                      * Method digit_type IntType::digit(size_type)
                 *  \tparam CharTIterator Random Access Iterator pointing to
                 *                        glyphs representing digits or symbols.
                 *
                 *  \param ref The integer to convert.
                 *  \param dig_glyphs Iterator to a set of digit glyphs. 
                 *  \param sym_glyphs Iterator to a set of symbol
                 *                    (e.g. "+") glyphs. 
                 *  \return The converted string of glyphs, or the "image." 
                 */
                template <typename IntType, typename CharTIterator>
                typename IntType::str_type str( const IntType& ref,
                                                CharTIterator dig_glyphs,
                                                CharTIterator sym_glyphs
                                                );

                /** Convert an integer to a string of glyphs/symbols
                 *  in scientific notation, e.g. "+1.23e16."
                 *
                 *  \tparam IntType Type of the number to convert. Refer to
                 *                  str() for more details. In addition to
                 *                  the requirements for str(), IntType must
                 *                  also have the following public members:
                 *                      * Method digit_type IntType::base()
                 *  \tparam CharTIterator Random Access Iterator pointing to
                 *                        glyphs representing digits or symbols.
                 *
                 *  \param ref The integer to convert.
                 *  \param prec The number of digits to show after
                 *              the point symbol. 
                 *  \param dig_glyphs Iterator to a set of digit glyphs. 
                 *  \param sym_glyphs Iterator to a set of symbol
                 *                    (e.g. "+") glyphs. 
                 *  \return The converted string of glyphs, or the "image." 
                 */
                template <typename IntType, typename CharTIterator>
                typename IntType::str_type
                    sci_note( const IntType& ref,
                              typename IntType::size_type prec,
                              CharTIterator dig_glyphs, CharTIterator sym_glyphs
                              );

                /** Convert an integer to a string of glyphs/symbols
                 *  in scientific notation, e.g. "+ 1.23 e 16."
                 *
                 *  \tparam IntType Type of the number to convert. Refer to
                 *                  str() for more details.
                 *  \tparam CharTIterator Random Access Iterator pointing to
                 *                        glyphs representing digits or symbols.
                 *
                 *
                 *  \param ref The integer to convert.
                 *  \param prec The number of digits to show after
                 *              the point symbol. 
                 *  \param dig_glyphs Iterator to a set of digit glyphs. 
                 *  \param sym_glyphs Iterator to a set of symbol
                 *                    (e.g. "+") glyphs. 
                 *  \return The converted string of glyphs, or the "image." 
                 */
                template <typename IntType, typename CharTIterator>
                typename IntType::str_type
                    sci_note_w_spaces( const IntType& ref,
                                       typename IntType::size_type prec,
                                       CharTIterator dig_glyphs,
                                       CharTIterator sym_glyphs
                                       );

                /** Convert a string of glyphs to an integer. Notice that this
                 *  function does not take an iterator for the symbols because
                 *  this function does not deal with numbers in scientific
                 *  notation or signed numbers.
                 *
                 *  \tparam IntType Type of the number to convert. Refer to
                 *                  str() for more details. In addition to
                 *                  the requirements for str(), IntType must
                 *                  also have the following public members:
                 *                      * Type IntType::diglist_type
                 *                      * Type IntType::digit_type
                 *  \tparam CharTIterator Random Access Iterator pointing to
                 *                        glyphs representing digits or symbols.
                 *
                 *
                 *  \param src The original image to convert 
                 *  \param dest The container in which to store
                 *              the converted integer.  
                 *  \param base The number base to interpret the image. 
                 *  \param dig_glyphs Iterator to a set of digit glyphs. 
                 */
                template <typename IntType, typename CharTIterator>
                void parse( const typename IntType::str_type& src,
                            typename IntType::diglist_type& dest,
                            typename IntType::digit_type base,
                            const CharTIterator dig_glyphs
                            );
            }
        }
    }
}

#include "Precision_Int_Operations_Img.inl"

#endif  //Include guard