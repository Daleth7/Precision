#include "Precision_Int_Operations.h"
#include "Precision_Shared_Helpers.h"

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
                    {return Int(this->digit_list(), 1);}

                INT_TEMP_
                short INT_INST_::compare(const INT_INST_& rhs)const
                    {return Volatile::Int_Operations::compare(*this, rhs);}

                INT_TEMP_
                INT_INST_ INT_INST_::operator-()const
                    {return Int(this->digit_list(), -this->sign());}

                INT_TEMP_
                bool INT_INST_::is_one()const
                    {return this->is_positive() && this->is_mag_one();}

                INT_TEMP_
                bool INT_INST_::is_neg_one()const
                    {return this->is_negative() && this->is_mag_one();}

                INT_TEMP_
                constexpr typename INT_INST_::dig_container::digit_type
                    INT_INST_::base()
                {return Base;}



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
                    if(Int::base() > 2) this->force_single_digit(2);
                    else{
                        this->make_zero();
                        this->append(1);
                    }
                    this->make_positive();
                }

                INT_TEMP_
                void INT_INST_::halve()
                    {*this /= Int(2);}

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
                    --(*this);
                    return toreturn;
                }

                INT_TEMP_
                INT_INST_& INT_INST_::operator++(){
                    Int increment(1);
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
                    Volatile::Int_Operations::bitwise_and_eq(*this, rhs);

                    return *this;
                }

                INT_TEMP_
                INT_INST_& INT_INST_::operator|=(const INT_INST_& rhs){
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
                    Int toreturn(*this);

                    Volatile::Int_Operations::logical_and_eq(toreturn, rhs);

                    return toreturn;
                }

                INT_TEMP_
                INT_INST_ INT_INST_::logical_or(const INT_INST_& rhs)const{
                    Int toreturn(*this);

                    Volatile::Int_Operations::logical_or_eq(toreturn, rhs);

                    return toreturn;
                }

                INT_TEMP_
                INT_INST_ INT_INST_::logical_xor(const INT_INST_& rhs)const{
                    Int toreturn(*this);

                    Volatile::Int_Operations::logical_xor_eq(toreturn, rhs);

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
                INT_INST_::Int(typename dig_container::signed_size_type val)
                    : dig_container(0)
                    , Signed_Interface((val < 0) * -1)
                {
                    val *= this->sign();
                    dig_container::m_number.front() = val % this->base();
                    val /= this->base();

                    while(val > 0){
                        this->append(val % this->base());
                        val /= this->base();
                    }

                    if(this->count_digits() == 0)
                        dig_container::m_number.push_back(0);
                }

                INT_TEMP_
                INT_INST_::Int( const typename dig_container::diglist_type& new_str,
                                typename signed_interface::sign_type new_sign
                )
                    : dig_container(new_str)
                    , Signed_Interface(new_sign)
                {
                    this->verify_diglist();
                }

                INT_TEMP_
                template <typename Iterator>
                INT_INST_::Int( const Iterator& pbeg, const Iterator& pend,
                                typename signed_interface::sign_type new_sign
                )
                    : dig_container(pbeg, pend)
                    , Signed_Interface(new_sign)
                {
                    this->verify_diglist();
                }

                INT_TEMP_
                void INT_INST_::verify_diglist(){
                    if(dig_container::m_number.size() == 0)
                        dig_container::m_number.push_back(0);
                    for( auto it = dig_container::m_number.begin();
                         it != dig_container::m_number.end();
                         ++it
                    ){
                        if(*it >= this->base() || *it < 0) *it = 0;
                    }
                    Helper::remove_excess_zeros(*this);
                }
            }
        }
    }
}


#undef INT_TEMP_
#undef INT_INST_