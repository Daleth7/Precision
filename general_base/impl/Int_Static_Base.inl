#include "Precision_Int_Operations_Img.h"

#define INT_TEMP_ template < typename ByteType, ByteType Base, typename CharT,     \
                             CharT const * const _digs, CharT const * const _syms, \
                             template <typename...> class Container,               \
                             typename SignType                                     \
                             >
#define INT_INST_ Int <ByteType, Base, CharT, _digs, _syms, Container, SignType>

namespace Precision{
    namespace General_Base{
        namespace Static{
            //Read-only functions

            INT_TEMP_
            auto INT_INST_::str()const -> str_type{
                return Volatile::Int_Operations::Img::str
                           <str_type, INT_INST_, CharT const * const>
                           ( *this, _digs, _syms );
            }

            INT_TEMP_
            auto INT_INST_::sci_note(size_type prec)const -> str_type{
                return Volatile::Int_Operations::Img::sci_note
                           <str_type, INT_INST_, CharT const * const>
                           ( *this, prec, _digs, _syms );
            }

            INT_TEMP_
            auto INT_INST_::sci_note_w_spaces(size_type prec)const -> str_type{
                return Volatile::Int_Operations::Img::sci_note_w_spaces
                           <str_type, INT_INST_, CharT const * const>
                           ( *this, prec, _digs, _syms );
            }



            //Constructors and destructor

            INT_TEMP_
            INT_INST_::Int(typename abstract_type::signed_size_type val)
                : abstract_type(val)
            {}

            INT_TEMP_
            INT_INST_::Int(const str_type& img_str)
                : abstract_type(0)
            {
                // Determine the sign, if any
                if(img_str.size() > 0){
                    // Check for plus sign or minus sign
                    if(img_str.front() == _syms[0] || img_str.front() == _syms[1]){
                        abstract_type::m_sign.assign(-(img_str.front() == _syms[1]));

                        Volatile::Int_Operations::Img::parse
                          <str_type, INT_INST_, CharT const * const>
                          ( img_str.substr(1, img_str.size()-1),
                            abstract_type::m_number, this->base(), _digs
                            );
                    } else {
                        Volatile::Int_Operations::Img::parse
                          <str_type, INT_INST_, CharT const * const>
                          ( img_str, abstract_type::m_number, this->base(), _digs );
                    }
                }
            }

            INT_TEMP_
            INT_INST_::Int( const typename abstract_type::diglist_type& new_diglist,
                            typename abstract_type::sign_type new_sign
            )
                : abstract_type(new_diglist, new_sign)
            {}

            INT_TEMP_
            template <typename Iterator>
            INT_INST_::Int( const Iterator& pbeg, const Iterator& pend,
                            typename abstract_type::sign_type new_sign
            )
                : abstract_type(pbeg, pend, new_sign)
            {}
        }
    }
}

#undef INT_TEMP_
#undef INT_INST_