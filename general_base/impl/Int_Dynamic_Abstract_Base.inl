#include "Precision_Int_Operations.h"
#include "Precision_Shared_Helpers.h"
#include "Precision_Interbase_Operations.h"

#define INT_TEMP_ template < typename ByteType,                      \
                             template <typename...> class Container, \
                             typename SignType                       \
                             >
#define INT_INST_ Int <ByteType, Container, SignType>

namespace Precision{
    namespace General_Base{
        namespace Dynamic{
            namespace Abstract{
                //Read-only functions

                INT_TEMP_
                INT_INST_ INT_INST_::magnitude()const
                    {return Int(this->digit_list(), 1, this->base());}

                INT_TEMP_
                short INT_INST_::compare(const INT_INST_& rhs)const
                    {return Volatile::Int_Operations::compare(*this, rhs);}

                INT_TEMP_
                INT_INST_ INT_INST_::operator-()const
                    {return Int(this->digit_list(), -this->sign(), this->base());}

                INT_TEMP_
                bool INT_INST_::is_one()const
                    {return this->is_positive() && this->is_mag_one();}

                INT_TEMP_
                bool INT_INST_::is_neg_one()const
                    {return this->is_negative() && this->is_mag_one();}

                INT_TEMP_
                typename INT_INST_::dig_container::digit_type
                    INT_INST_::base()const
                {return m_base;}



                //Modifiers

                INT_TEMP_
                void INT_INST_::make_zero(){
                    this->force_single_digit(0);
                    this->make_positive();
                }

                INT_TEMP_
                void INT_INST_::make_one(){
                    this->force_single_digit(1);
                    this->make_positive();
                }

                INT_TEMP_
                void INT_INST_::make_neg_one(){
                    this->force_single_digit(1);
                    this->make_negative();
                }

                INT_TEMP_
                void INT_INST_::make_two(){
                    if(this->base() > 2) this->force_single_digit(2);
                    else{
                        this->make_zero();
                        this->append(1);
                    }
                    this->make_positive();
                }

                INT_TEMP_
                void INT_INST_::halve(){
                    Int temp(0, this->base());
                    temp.make_two();
                    *this /= temp;
                }

                INT_TEMP_
                void INT_INST_::assign( typename dig_container::size_type index,
                                        typename dig_container::digit_type new_dig
                ){this->assign_digit(index, new_dig, this->base());}

                INT_TEMP_
                void INT_INST_::force_assign( typename dig_container::size_type
                                                index,
                                              typename dig_container::digit_type
                                                new_dig
                ){this->force_assign_digit(index, new_dig, this->base());}

                INT_TEMP_
                void INT_INST_::base(typename dig_container::digit_type new_base){
                    if(this->base() == new_base) return;

                    if(this->count_digits() < 2){
                        // Deal with trivial conversion of one digit long numbers
                        using dtype = typename dig_container::digit_type;
                        using stype = typename signed_interface::sign_type;

                        dtype fac = this->digit(0);
                        stype sig = signed_interface::m_sign;

                        this->make_one();
                        Volatile::Int_Operations::multiply_factor(*this, fac);
                        signed_interface::m_sign = sig;
                        m_base = new_base;

                        return;
                    }

                    *this = convert_base<Int>(*this, new_base);
                }



                //Arithmetic operators
                INT_TEMP_
                INT_INST_& INT_INST_::operator+=(const INT_INST_& rhs){
                    Int conv(rhs);
                    conv.base(this->base());

                    Volatile::Int_Operations::add(*this, conv);

                    return *this;
                }

                INT_TEMP_
                INT_INST_& INT_INST_::operator-=(const INT_INST_& rhs){
                    Int conv(rhs);
                    conv.base(this->base());

                    Volatile::Int_Operations::add(*this, conv, -1);

                    return *this;
                }

                INT_TEMP_
                INT_INST_& INT_INST_::operator*=(const INT_INST_& rhs){
                    Int conv(rhs);
                    conv.base(this->base());

                    Volatile::Int_Operations::multiply(*this, conv);

                    return *this;
                }

                INT_TEMP_
                INT_INST_& INT_INST_::operator/=(const INT_INST_& rhs){
                    Int quo, mod;
                    Int conv(rhs);
                    conv.base(this->base());

                    Volatile::Int_Operations::divide_mod(*this, conv, quo, mod);
                    *this = std::move(quo);

                    return *this;
                } 

                INT_TEMP_
                INT_INST_& INT_INST_::operator%=(const INT_INST_& rhs){
                    Int quo, mod;
                    Int conv(rhs);
                    conv.base(this->base());

                    Volatile::Int_Operations::divide_mod(*this, conv, quo, mod);
                    *this = std::move(mod);

                    return *this;
                } 

                INT_TEMP_
                INT_INST_& INT_INST_::operator--(){
                    Int decrement(-1, this->base());
                    *this += decrement;

                    return *this;
                }

                INT_TEMP_
                INT_INST_ INT_INST_::operator--(int){
                    Int toreturn(*this);
                    --(*this);
                    return toreturn;
                }

                INT_TEMP_
                INT_INST_& INT_INST_::operator++(){
                    Int increment(1, this->base());
                    *this += increment;

                    return *this;
                }

                INT_TEMP_
                INT_INST_ INT_INST_::operator++(int){
                    Int toreturn(*this);
                    ++(*this);
                    return toreturn;
                }



                //Bitwise operators

                INT_TEMP_
                INT_INST_& INT_INST_::operator&=(const INT_INST_& rhs){
                    Int conv(rhs);
                    conv.base(this->base());

                    Volatile::Int_Operations::bitwise_and_eq(*this, conv);

                    return *this;
                }

                INT_TEMP_
                INT_INST_& INT_INST_::operator|=(const INT_INST_& rhs){
                    Int conv(rhs);
                    conv.base(this->base());

                    Volatile::Int_Operations::bitwise_or_eq(*this, conv);

                    return *this;
                }

                INT_TEMP_
                INT_INST_& INT_INST_::operator^=(const INT_INST_& rhs){
                    Int conv(rhs);
                    conv.base(this->base());

                    Volatile::Int_Operations::bitwise_xor_eq(*this, conv);

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
                    Int conv(rhs);
                    conv.base(this->base());

                    Volatile::Int_Operations::bitwise_lshift_eq(*this, conv);

                    return *this;
                }

                INT_TEMP_
                INT_INST_& INT_INST_::operator>>=(const INT_INST_& rhs){
                    Int conv(rhs);
                    conv.base(this->base());

                    Volatile::Int_Operations::bitwise_rshift_eq(*this, conv);

                    return *this;
                }



                //Logical Operators

                INT_TEMP_
                INT_INST_ INT_INST_::logical_and(const INT_INST_& rhs)const{
                    Int toreturn(*this);
                    Int conv(rhs);
                    conv.base(this->base());

                    Volatile::Int_Operations::logical_and_eq(toreturn, conv);

                    return toreturn;
                }

                INT_TEMP_
                INT_INST_ INT_INST_::logical_or(const INT_INST_& rhs)const{
                    Int toreturn(*this);
                    Int conv(rhs);
                    conv.base(this->base());

                    Volatile::Int_Operations::logical_or_eq(toreturn, conv);

                    return toreturn;
                }

                INT_TEMP_
                INT_INST_ INT_INST_::logical_xor(const INT_INST_& rhs)const{
                    Int toreturn(*this);
                    Int conv(rhs);
                    conv.base(this->base());

                    Volatile::Int_Operations::logical_xor_eq(toreturn, conv);

                    return toreturn;
                }

                INT_TEMP_
                INT_INST_ INT_INST_::logical_rev_xor(const INT_INST_& rhs)const{
                    Int toreturn(*this);
                    Int conv(rhs);
                    conv.base(this->base());

                    Volatile::Int_Operations::logical_rev_xor_eq(toreturn, conv);

                    return toreturn;
                }

                INT_TEMP_
                INT_INST_ INT_INST_::logical_complement()const{
                    Int toreturn(*this);

                    Volatile::Int_Operations::logical_complement_eq(toreturn);

                    return toreturn;
                }

                INT_TEMP_
                INT_INST_ INT_INST_::logical_shift
                    (typename dig_container::signed_size_type sz)const
                {
                    Int toreturn(*this);

                    toreturn.shift(sz);

                    return toreturn;
                }

                INT_TEMP_
                INT_INST_ INT_INST_::logical_shift_left
                    (typename dig_container::size_type sz)const
                {
                    Int toreturn(*this);

                    toreturn.shift_left(sz);

                    return toreturn;
                }

                INT_TEMP_
                INT_INST_ INT_INST_::logical_shift_right
                    (typename dig_container::size_type sz)const
                {
                    Int toreturn(*this);

                    toreturn.shift_right(sz);

                    return toreturn;
                }



                //Constructors and destructor

                INT_TEMP_
                INT_INST_::Int( typename dig_container::signed_size_type val,
                                typename dig_container::digit_type new_base
                )
                    : dig_container(0)
                    , Signed_Interface((val < 0) * -1)
                    , m_base(new_base)
                {
                    this->split_number_store(val * this->sign(), this->base());
                }

                INT_TEMP_
                INT_INST_::Int( const typename dig_container::diglist_type& new_str,
                                typename signed_interface::sign_type new_sign,
                                typename dig_container::digit_type new_base
                )
                    : dig_container(new_str)
                    , Signed_Interface(new_sign)
                    , m_base(new_base)
                {
                    this->verify_diglist(this->base());
                }

                INT_TEMP_
                template <typename Iterator>
                INT_INST_::Int( const Iterator& pbeg, const Iterator& pend,
                                typename signed_interface::sign_type new_sign,
                                typename dig_container::digit_type new_base
                )
                    : dig_container(pbeg, pend)
                    , Signed_Interface(new_sign)
                    , m_base(new_base)
                {
                    this->verify_diglist(this->base());
                }
            }
        }
    }
}


#undef INT_TEMP_
#undef INT_INST_