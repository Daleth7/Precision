#include "Precision_Float_Operations.h"
#include "Precision_Shared_Helpers.h"

#define FLOAT_TEMP_ template < typename ByteType, ByteType Base,       \
                               template <typename...> class Container, \
                               typename SignType                       \
                               >
#define FLOAT_INST_ Int <ByteType, Base, Container, SignType>

namespace Precision{
    namespace General_Base{
        namespace Static{
            namespace Abstract{
                //Read-only functions

                FLOAT_TEMP_
                bool FLOAT_INST_::is_zero()const
                    {return m_int.is_zero();}

                FLOAT_TEMP_
                bool FLOAT_INST_::is_mag_one()const{
                    return m_int.digit(m_int.size()-1) == 1
                        && this->count_right_digits_no_trail() == 0
                        ;
                }

                FLOAT_TEMP_
                auto FLOAT_INST_::digit_string()const -> const digstr_type&
                    {return m_int.digit_string();}

                FLOAT_TEMP_
                auto FLOAT_INST_::count_digits()const -> size_type{
                    return this->precision() + 1;
                }

                FLOAT_TEMP_
                auto FLOAT_INST_::count_digits_no_trail()const -> size_type
                    {return m_int.count_digits();}

                FLOAT_TEMP_
                auto FLOAT_INST_::count_digits_left()const -> size_type
                    {return (this->power() < 0) ? 0 : this->power() + 1;}

                FLOAT_TEMP_
                auto FLOAT_INST_::count_digits_right()const -> size_type
                    {return this->count_digits() - this->count_digits_left();}

                FLOAT_TEMP_
                auto FLOAT_INST_::count_digits_right_no_trail()const -> size_type
                    {return this->count_digits_no_trail() - this->count_digits_left();}

                FLOAT_TEMP_
                auto FLOAT_INST_::digit(size_type index)const -> digit_type
                    {return Helper::digit_float(*this, m_int, index);}

                FLOAT_TEMP_
                bool FLOAT_INST_::is_positive()const
                    {return m_int.is_positive();}

                FLOAT_TEMP_
                bool FLOAT_INST_::is_negative()const
                    {return m_int.is_negative();}

                FLOAT_TEMP_
                auto FLOAT_INST_::sign()const -> sign_type
                    {return m_int.sign();}

                FLOAT_TEMP_
                FLOAT_INST_ FLOAT_INST_::magnitude()const
                    {return Float(m_int.magnitude(), m_prec, m_pow, m_inf);}

                FLOAT_TEMP_
                short FLOAT_INST_::compare(const Float& rhs)const
                    {return Volatile::Float_Operations::compare(*this, rhs);}

                FLOAT_TEMP_
                FLOAT_INST_ FLOAT_INST_::operator-()const
                    {return Float(-m_int, m_prec, m_pow, m_inf);}

                FLOAT_TEMP_
                bool FLOAT_INST_::is_one()const{
                    return m_int.digit(m_int.size()-1) == 1
                        && this->count_right_digits_no_trail() == 0
                        && this->is_positive()
                        ;
                }

                FLOAT_TEMP_
                bool FLOAT_INST_::is_neg_one()const{
                    return m_int.digit(m_int.size()-1) == 1
                        && this->count_right_digits_no_trail() == 0
                        && this->is_negative()
                        ;
                }

                FLOAT_TEMP_
                integer_type FLOAT_INST_::integer()const{
                    integer_type toreturn(m_int);
                    toreturn.shift(this->power()-m_int.count_digits()+1);
                    return toreturn;
                }

                FLOAT_TEMP_
                integer_type FLOAT_INST_::raw_integer()const{
                    integer_type toreturn(m_int);
                    toreturn.shift_left(m_prec+1-m_int.count_digits());
                    return toreturn;
                }

                FLOAT_TEMP_
                bool FLOAT_INST_::is_integer()const
                    {return this->is_zero() || this->count_digits_right_no_trail() == 0;}

                FLOAT_TEMP_
                auto FLOAT_INST_::precision()const -> size_type
                    {return m_prec;}

                FLOAT_TEMP_
                auto FLOAT_INST_::power()const -> signed_size_type
                    {return m_pow;}

                FLOAT_TEMP_
                bool FLOAT_INST_::has_infinite_precision()const
                    {return m_inf;}



                //Modifiers

                FLOAT_TEMP_
                void FLOAT_INST_::shift_left(size_type e)
                    {m_pow += e;}

                FLOAT_TEMP_
                void FLOAT_INST_::shift(signed_size_type sz)
                    {m_pow += sz;}

                FLOAT_TEMP_
                void FLOAT_INST_::shift_right(size_type e)
                    {m_pow -= e;}

                FLOAT_TEMP_
                void FLOAT_INST_::append(digit_type new_dig){
                    m_int.append(new_dig);
                    // Update power and precision since the
                    // number is stored in scientific notation.
                    ++m_prec;
                    ++m_pow;
                }

                FLOAT_TEMP_
                void FLOAT_INST_::detach(){
                    m_int.detach();
                    // Update power and precision since the
                    // number is stored in scientific notation.
                    --m_prec;
                    --m_pow;
                }

                FLOAT_TEMP_
                void FLOAT_INST_::negate()
                    {m_int.negate();}

                FLOAT_TEMP_
                void FLOAT_INST_::make_positive()
                    {m_int.make_positive();}

                FLOAT_TEMP_
                void FLOAT_INST_::make_negative()
                    {m_int.make_negative();}

                FLOAT_TEMP_
                void FLOAT_INST_::sign(sign_type new_sign)
                    {m_int.sign(new_sign);}

                FLOAT_TEMP_
                void FLOAT_INST_::make_zero(){
                    m_int.make_zero();
                    m_pow = 0;
                }

                FLOAT_TEMP_
                void FLOAT_INST_::make_one(){
                    m_int.make_one();
                    m_pow = 0;
                }

                FLOAT_TEMP_
                void FLOAT_INST_::make_neg_one(){
                    m_int.make_neg_one();
                    m_pow = 0;
                }

                FLOAT_TEMP_
                void FLOAT_INST_::make_two(){
                    m_int.make_two();
                    m_pow = 0;
                }

                FLOAT_TEMP_
                void FLOAT_INST_::halve(){
                    // The number of digits might decrease from halving.
                    // Update power if that happens.
                    size_type old_count = m_int.count_digits();
                    m_int.halve();
                    if(m_int.count_digits() < old_count)
                        --m_pow;
                }

                FLOAT_TEMP_
                void FLOAT_INST_::assign(size_type index, digit_type new_dig)
                    {Helper::assign_float(*this, m_int, index, new_dig);}

                void FLOAT_INST_::precision(size_type new_prec){
                    // Remove "invalidated" digits if precision is reduced.
                    if((new_prec+1) < m_int.count_digits())
                        m_int.shift_right(m_int.count_digits() - new_prec - 1);
                    m_prec = new_prec;
                }

                FLOAT_TEMP_
                void FLOAT_INST_::power(signed_size_type new_exp)
                    {m_pow = new_exp;}

                FLOAT_TEMP_
                void FLOAT_INST_::infinite_precision(bool has_inf_prec)
                    {m_inf = has_inf_prec;}



                //Arithmetic operators

                /** Arithmetic addition operator.
                  * 
                  * \param rhs Right hand side number to add from.
                  * 
                  * \return A reference to this object.
                  */
                FLOAT_TEMP_
                FLOAT_INST_& FLOAT_INST_::operator+=(const Float& rhs);  

                /** Arithmetic subtraction operator.
                  * 
                  * \param rhs Right hand side number to subtract.
                  * 
                  * \return A reference to this object.
                  */
                FLOAT_TEMP_
                FLOAT_INST_& FLOAT_INST_::operator-=(const Float& rhs);  

                /** Arithmetic mutiplication operator.
                  * 
                  * \param rhs Right hand side number to multiply with.
                  * 
                  * \return A reference to this object.
                  */
                FLOAT_TEMP_
                FLOAT_INST_& FLOAT_INST_::operator*=(const Float& rhs);  

                /** Arithmetic division operator.
                  * 
                  * \param rhs Denominator.
                  * 
                  * \return A reference to this object.
                  */
                FLOAT_TEMP_
                FLOAT_INST_& FLOAT_INST_::operator/=(const Float& rhs);

                /** Arithmetic pre-decrement operator.
                  * 
                  * \return A reference to this object.
                  */
                FLOAT_TEMP_
                FLOAT_INST_& FLOAT_INST_::operator--();

                /** Arithmetic post-decrement operator.
                  * 
                  * \return A reference to this object.
                  */
                FLOAT_TEMP_
                FLOAT_INST_ FLOAT_INST_::operator--(int);

                /** Arithmetic pre-increment operator.
                  * 
                  * \return A reference to this object.
                  */
                FLOAT_TEMP_
                FLOAT_INST_& FLOAT_INST_::operator++();

                /** Arithmetic post-increment operator.
                  * 
                  * \return A reference to this object.
                  */
                FLOAT_TEMP_
                FLOAT_INST_ FLOAT_INST_::operator++(int);



                //Special operators

                /** Remainder operator.
                  * 
                  * \param rhs Denominator.
                  * 
                  * \return The remainder of this number
                  *         divided by rhs.
                  */
                FLOAT_TEMP_
                FLOAT_INST_& FLOAT_INST_::remainder(const Float& rhs);

                FLOAT_TEMP_
                FLOAT_INST_ FLOAT_INST_::inverse()const{
                    Float toreturn(*this);
                    toreturn.invert();
                    return toreturn;
                }

                /** Inverse operator.
                  * 
                  * \return The inverse value of this number.
                  */
                FLOAT_TEMP_
                FLOAT_INST_& FLOAT_INST_::invert();

                /** Exponentiation operator with an integer.
                  * 
                  * \param rhs Exponent.
                  * 
                  * \return This number raised to the power of rhs.
                  */
                FLOAT_TEMP_
                FLOAT_INST_& FLOAT_INST_::exponentiate(const integer_type& rhs);

                FLOAT_TEMP_
                FLOAT_INST_& FLOAT_INST_::exponentiate(const Float& rhs)
                {return *this; /* TODO: Implement exponentiation with decimal powers */}

                FLOAT_TEMP_
                FLOAT_INST_&FLOAT_INST_:: operator%=(const Float& rhs)
                    {return this->remainder(rhs);}

                FLOAT_TEMP_
                FLOAT_INST_ FLOAT_INST_::operator~()const
                    {return this->inverse();}

                FLOAT_TEMP_
                FLOAT_INST_& FLOAT_INST_::operator^=(const integer_type& rhs)
                    {return this->exponentiate(rhs);}

                FLOAT_TEMP_
                FLOAT_INST_& FLOAT_INST_::operator^=(const Float& rhs)
                    {return this->exponentiate(rhs);} 



                //Constructors and destructor

                FLOAT_TEMP_
                FLOAT_INST_::Float( raw_float_type val,
                                    size_type prec, signed_size_type exp,
                                    bool inf_prec
                                    )
                    : m_int()
                    , m_prec(prec)
                    , m_pow(exp)
                    , m_inf(inf_prec)
                {
                    // Shift the raw value to convert an integer value
                    signed_size_type shift_factor = 1;
                    while(prec-- > 0)
                        shift_factor *= this->base();
                    m_int = integer_type(static_cast<signed_size_type>(val*shift_factor));

                    // Now update precision and power if val > Base
                    size_type val_count_left = 0;
                    while(val > this->base()){
                        ++val_count_left;
                        val /= this->base();
                    }
                    m_prec += val_count_left;
                    m_pow += val_count_left;

                    Helper::remove_trailing_zeros(m_int);
                }

                FLOAT_TEMP_
                FLOAT_INST_::Float( const digstr_type& new_diglist, sign_type new_sign,
                                    size_type prec, signed_size_type exp,
                                    bool inf_prec
                                    )
                    : m_int(new_diglist, new_sign)
                    , m_prec(prec)
                    , m_pow(exp)
                    , m_inf(inf_prec)
                {Helper::remove_trailing_zeros(m_int);}

                FLOAT_TEMP_
                template <typename Iterator>
                FLOAT_INST_::Float( const Iterator& pbeg, const Iterator& pend,
                                    sign_type new_sign,
                                    size_type prec, signed_size_type exp,
                                    bool inf_prec
                                    )
                    : m_int(pbeg, pend, new_sign)
                    , m_prec(prec)
                    , m_pow(exp)
                    , m_inf(inf_prec)
                {Helper::remove_trailing_zeros(m_int);}

                FLOAT_TEMP_
                FLOAT_INST_::Float( const integer_type& new_int,
                                    size_type prec, signed_size_type exp,
                                    bool inf_prec
                                    )
                    : m_int(new_int)
                    , m_prec(prec)
                    , m_pow(exp)
                    , m_inf(inf_prec)
                {Helper::remove_trailing_zeros(m_int);}
            }
        }
    }
}