#include "Precision_Int_Operations.h"

#define INT_TEMP_ template < typename ByteType, ByteType Base,       \
                             template <typename...> class Container, \
                             typename SignType                       \
                             >
#define INT_INST_ Int <ByteType, Base, Container, SignType>

namespace Precision{
    namespace General_Base{
        namespace Static{
            namespace Abstract{
                //Read-only functions

                INT_TEMP_
                INT_INST_ INT_INST_::magnitude()const
                    {return Int(this->diglist(), 1);}

                INT_TEMP_
                short INT_INST_::compare(const INT_INST_& rhs)const
                    {return Volatile::Int_Operations::compare(*this, rhs);}

                INT_TEMP_
                INT_INST_ INT_INST_::operator-()const
                    {return Int(this->diglist(), -this->sign());}

                INT_TEMP_
                bool INT_INST_::is_one()const
                    {return this->is_positive() && this->is_mag_one();}

                INT_TEMP_
                bool INT_INST_::is_neg_one()const
                    {return this->is_negative() && this->is_mag_one();}

                INT_TEMP_
                auto INT_INST_::base() -> digit_type
                    {return Base;}



                //Modifiers

                INT_TEMP_
                void INT_INST_::make_zero(){
                    m_number.front() = 0;
                    m_number.erase(m_number.begin() + 1, m_number.end());
                    this->make_positive();
                }

                INT_TEMP_
                void INT_INST_::make_one(){
                    m_number.front() = 1;
                    m_number.erase(m_number.begin() + 1, m_number.end());
                    this->make_positive();
                }

                INT_TEMP_
                void INT_INST_::make_neg_one(){
                    m_number.front() = 1;
                    m_number.erase(m_number.begin() + 1, m_number.end());
                    this->make_negative();
                }

                INT_TEMP_
                void INT_INST_::make_two(){
                    m_number.front() = 2;
                    m_number.erase(m_number.begin() + 1, m_number.end());
                    this->make_positive();
                }



                //Arithmetic operators
                INT_TEMP_
                INT_INST_& INT_INST_::operator+=(const INT_INST_& rhs){
                    Volatile::Int_Operations::add(*this, rhs);

                    return *this;
                }

                INT_TEMP_
                INT_INST_& INT_INST_::operator-=(const INT_INST_& rhs){
                    Volatile::Int_Operations::add(*this, rhs, -1);

                    return *this;
                }

                INT_TEMP_
                INT_INST_& INT_INST_::operator*=(const INT_INST_& rhs){
                    Volatile::Int_Operations::multiply(*this, rhs);

                    return *this;
                }

                INT_TEMP_
                INT_INST_& INT_INST_::operator/=(const INT_INST_& rhs){
                    Int quo, mod;

                    Volatile::Int_Operations::divide_mod(*this, rhs, quo, mod);
                    *this = std::move(quo);

                    return *this;
                } 

                INT_TEMP_
                INT_INST_& INT_INST_::operator%=(const INT_INST_& rhs){
                    Int quo, mod;

                    Volatile::Int_Operations::divide_mod(*this, rhs, quo, mod);
                    *this = std::move(mod);

                    return *this;
                } 

                INT_TEMP_
                INT_INST_& INT_INST_::operator--(){
                    Int decrement(-1);
                    *this += decrement;

                    return *this;
                }

                INT_TEMP_
                INT_INST_ INT_INST_::operator--(int){
                    Int toreturn(*this);
                    return --(*this);
                }

                INT_TEMP_
                INT_INST_& INT_INST_::operator++(){
                    Int increment(1);
                    *this += decrement;

                    return *this;
                }

                INT_TEMP_
                INT_INST_ INT_INST_::operator++(int){
                    Int toreturn(*this);
                    return ++(*this);
                }



                //Bitwise operators

                INT_TEMP_
                INT_INST_& INT_INST_::operator&=(const INT_INST_& rhs){
                    Volatile::Int_Operations::bitwise_and_eq(*this, rhs);

                    return *this;
                }

                INT_TEMP_
                INT_INST_& INT_INST_::operator|=(const INT_INST_& rhs); {
                    Volatile::Int_Operations::bitwise_or_eq(*this, rhs);

                    return *this;
                }

                INT_TEMP_
                INT_INST_& INT_INST_::operator^=(const INT_INST_& rhs){
                    Volatile::Int_Operations::bitwise_xor_eq(*this, rhs);

                    return *this;
                }

                INT_TEMP_
                INT_INST_ INT_INST_::operator~()const{
                    Int toreturn(*this);

                    Volatile::Int_Operations::bitwise_complement(toreturn);

                    return toreturn;
                }

                INT_TEMP_
                INT_INST_& INT_INST_::operator<<=(const INT_INST_& rhs){
                    Volatile::Int_Operations::bitwise_lshift_eq(*this, rhs);

                    return *this;
                }

                INT_TEMP_
                INT_INST_& INT_INST_::operator>>=(const INT_INST_& rhs){
                    Volatile::Int_Operations::bitwise_rshift_eq(*this, rhs);

                    return *this;
                }



                //Logical Operators

                INT_TEMP_
                INT_INST_ INT_INST_::logical_and(const INT_INST_& rhs)const{
                    Volatile::Int_Operations::logical_and_eq(*this, rhs);

                    return *this;
                }

                INT_TEMP_
                INT_INST_ INT_INST_::logical_or(const INT_INST_& rhs)const{
                    Volatile::Int_Operations::logical_or_eq(*this, rhs);

                    return *this;
                }

                INT_TEMP_
                INT_INST_ INT_INST_::logical_xor(const INT_INST_& rhs)const{
                    Volatile::Int_Operations::logical_xor_eq(*this, rhs);

                    return *this;
                }

                INT_TEMP_
                INT_INST_ INT_INST_::logical_complement()const{
                    Int toreturn(*this);

                    Volatile::Int_Operations::logical_complement_eq(toreturn);

                    return toreturn;
                }

                INT_TEMP_
                INT_INST_ INT_INST_::logical_shift(signed_size_type sz)const{
                    Int toreturn(*this);

                    toreturn.shift(sz);

                    return toreturn;
                }

                INT_TEMP_
                INT_INST_ INT_INST_::logical_shift_left(size_type sz)const{
                    Int toreturn(*this);

                    toreturn.logical_shift_left(sz);

                    return toreturn;
                }

                INT_TEMP_
                INT_INST_ INT_INST_::logical_shift_right(size_type sz)const{
                    Int toreturn(*this);

                    toreturn.logical_shift_right(sz);

                    return toreturn;
                }



                //Constructors and destructor

                INT_TEMP_
                INT_INST_::INT_INST_(signed_size_type val)
                    : Digit_Container({{}})
                    , Signed_Interface((val < 0) * -1)
                {
                    val *= this->sign();

                    while(val > 0){
                        this->append(val % this->base());
                        val /= this->base();
                    }
                }

                INT_TEMP_
                INT_INST_::INT_INST_( const diglist_type& new_str,
                                      sign_type new_sign
                )
                    : Digit_Container(new_str)
                    , Signed_Interface(new_sign)
                {}

                INT_TEMP_
                template <typename Iterator>
                INT_INST_::INT_INST_( const Iterator& pbeg, const Iterator& pend,
                                      sign_type new_sign
                )
                    : Digit_Container(pbeg, pend)
                    , Signed_Interface(new_sign)
                {}
            }
        }
    }
}


#undef INT_TEMP_
#undef INT_INST_