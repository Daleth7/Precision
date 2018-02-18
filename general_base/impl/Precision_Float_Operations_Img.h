/** \file Precision_Float_Operations_Img.h
 *  This file centralizes the conversion algorithms to convert
 *  a floating point number to an "image" and vice versa.
 *  The algorithms are placed under the Volatile namespace since
 *  they require the number base to be passed as a parameter to
 *  correctly run the algorithm.
 */

#ifndef VOLATILE_H34_HHHH_PRECISION_FLOAT_BASE_IMPL_VOLATILE_DETAIL_BASE_H
#define VOLATILE_H34_HHHH_PRECISION_FLOAT_BASE_IMPL_VOLATILE_DETAIL_BASE_H

#include "Precision_Image_Set_Interface.h"

namespace Precision{
    namespace Volatile{
        namespace Float_Operations {
            namespace Img{
                /** Convert a floating point number to a string of glyphs/symbols.
                 *
                 *  \tparam FloatType Type of the number to convert. Refer to
                 *                    sci_note() for more details.
                 *  \tparam ISIType Image Set Interface Type containing
                 *                  the set of images to use during conversion.
                 *
                 *  \param ref The floating point number to convert.
                 *  \param prec The number of digits to show after
                 *              the point symbol. 
                 *  \param img_set Interface with digit to glyph information.
                 *
                 *  \return The converted string of glyphs, or the "image." 
                 */
                template <typename FloatType, typename ISIType>
                typename ISIType::str_type
                    str( const FloatType& ref, typename FloatType::size_type prec,
                         const ISIType& img_set
                         );

                /** Convert a floating point number to a string of glyphs/symbols
                 *  in scientific notation, e.g. "+1.23e16."
                 *
                 *  \tparam FloatType Type of the number to convert. Refer to
                 *                    str() for more details. FloatType must
                 *                    have the following public members:
                 *                        * Type FloatType::str_type
                 *                        * Type FloatType::size_type
                 *                        * Method bool FloatType::is_zero()
                 *                        * Method bool FloatType::is_positive()
                 *                        * Method size_type FloatType::count_digits()
                 *                        * Method digit_type FloatType::digit(size_type)
                 *                        * Method digit_type FloatType::base()
                 *  \tparam ISIType Image Set Interface Type containing
                 *                  the set of images to use during conversion.
                 *
                 *  \param ref The floating point number to convert.
                 *  \param prec The number of digits to show after
                 *              the point symbol. 
                 *  \param img_set Interface with digit to glyph information.
                 *
                 *  \return The converted string of glyphs, or the "image." 
                 */
                template <typename FloatType, typename ISIType>
                typename ISIType::str_type
                    sci_note( const FloatType& ref, typename FloatType::size_type prec,
                              const ISIType& img_set
                              );

                /** Convert a floating point number to a string of glyphs/symbols
                 *  in scientific notation, e.g. "+ 1.23 e 16."
                 *
                 *  \tparam FloatType Type of the number to convert. Refer to
                 *                    str() for more details.
                 *  \tparam ISIType Image Set Interface Type containing
                 *                  the set of images to use during conversion.
                 *
                 *
                 *  \param ref The floating point number to convert.
                 *  \param prec The number of digits to show after
                 *              the point symbol. 
                 *  \param img_set Interface with digit to glyph information.
                 *
                 *  \return The converted string of glyphs, or the "image." 
                 */
                template <typename FloatType, typename ISIType>
                typename ISIType::str_type
                    sci_note_w_spaces( const FloatType& ref,
                                       typename FloatType::size_type prec,
                                       const ISIType& img_set
                                       );

                /** Convert a string of glyphs to a floating point number.
                 *
                 *  \tparam FloatType Type of the number to convert. Refer to
                 *                    str() for more details. In addition to
                 *                    the requirements for str(), FloatType must
                 *                    also have the following public members:
                 *                        * Type FloatType::digstr_type
                 *                        * Type FloatType::digstr_type::insert
                 *                        * Type FloatType::digit_type
                 *                        * Type FloatType::sign_type::assign
                 *  \tparam ISIType Image Set Interface Type containing
                 *                  the set of images to use during conversion.
                 *  \tparam SearchPolicy Determines which algorithm to use
                 *                       when searching for matching glyphs.
                 *                       See Precision::Image_Set_Interface for
                 *                       more information.
                 *
                 *
                 *  \param src The original image to convert
                 *  \param dest The integer in which to store the parsed digits.
                 *  \param dest_prec The variable in which to store the extracted
                 *                   precision.
                 *  \param dest_pow The variable in which to store the extracted
                 *                  power.
                 *  \param base The number base to interpret the string as.
                 *  \param img_set Interface with digit to glyph information.
                 */
                template < typename FloatType,
                           typename ISIType,
                           typename SearchPolicy = ImgSearchPolicy::Binary
                           >
                void parse( const typename ISIType::str_type& src,
                            typename FloatType::integer_type& dest,
                            typename FloatType::size_type& dest_prec,
                            typename FloatType::signed_size_type& dest_pow,
                            typename FloatType::digit_type base,
                            const ISIType& img_set
                            );
            }
        }
    }
}

#include "Precision_Float_Operations_Img.inl"

#endif  //Include guard