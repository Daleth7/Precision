#ifndef CORE_INT_THEFASKSE__INTHEAD
#define CORE_INT_THEFASKSE__INTHEAD

#include "general_base/impl/Precision_Int_Operations.h"
#include "general_base/impl/Precision_Sign_Class.h"
//#include "general_base/impl/Precision_Signed_Interface.h"

#include <vector>

/*
struct Core_Int : public Precision::Signed_Integer {
    using str_type      = std::string;
    using size_type     = std::size_t;
    using digit_type    = std::uint_fast8_t;
    using diglist_type  = std::vector<digit_type>;
    using catalyst_type = long double;

    bool is_zero()const
        {return Precision::Volatile::Int_Operations::is_zero_list(m_number);}

    bool is_one()const{
        return Precision::Volatile::Int_Operations
               ::is_one_list(m_number, this->is_negative());
    }

    bool is_neg_one()const{
        return Precision::Volatile::Int_Operations
               ::is_neg_one_list(m_number, this->is_negative());
    }

    const diglist_type& digit_list()const
        {return m_number;}

    Core_Int magnitude()const{
        Core_Int toreturn(*this);
        toreturn.make_positive();
        return toreturn;
    }

    size_type count_digits()const
        {return m_number.size();}

    digit_type digit(size_type index)const{
        if(index >= this->count_digits()) return 0;
        return m_number[index];
    }

    static size_type base()
        {return 10;}



    void set_base(digit_type)
        { }

    void make_zero()
        {m_number = diglist_type(1, 0); this->make_positive();}

    void make_one()
        {m_number = diglist_type(1, 1); this->make_positive();}

    void make_neg_one()
        {m_number = diglist_type(1, 1); this->make_negative();}

    void make_two()
        {m_number = diglist_type(1, 2); this->make_positive();}

    void shift_left(size_type e){
        if(this->is_zero()) return;
        else                m_number.insert(m_number.begin(), e, 0);
    }

    void shift_right(size_type e){
        if(m_number.size() <= e)
            m_number = diglist_type(1, 0);
        else
            m_number.erase(m_number.begin(), m_number.begin() + e);
    }

    void digit(size_type index, digit_type new_digit){
        if(index >= m_number.size()) return;

        m_number[index] = new_digit;
    }

    void append(digit_type new_digit)
        {m_number.push_back(new_digit % this->base());}

    void detach()
        {m_number.pop_back();}


    diglist_type m_number;
};
/*/
struct Core_Int {
    using str_type      = std::string;
    using size_type     = std::size_t;
    using sign_type     = Precision::SignClass;
    using digit_type    = std::uint_fast8_t;
    using diglist_type  = std::vector<digit_type>;
    using catalyst_type = long double;

    bool is_zero()const
        {return Precision::Volatile::Int_Operations::is_zero_list(m_number);}

    bool is_one()const{
        return Precision::Volatile::Int_Operations
               ::is_one_list(m_number, this->is_negative());
    }

    bool is_neg_one()const{
        return Precision::Volatile::Int_Operations
               ::is_neg_one_list(m_number, this->is_negative());
    }

    bool is_even()const{
        return (m_number.front() % 2) == 0;
    }

    bool is_odd()const{
        return (m_number.front() % 2) == 1;
    }

    const diglist_type& digit_list()const
        {return m_number;}

    Core_Int magnitude()const{
        Core_Int toreturn(*this);
        toreturn.make_positive();
        return toreturn;
    }

    size_type count_digits()const
        {return m_number.size();}

    digit_type digit(size_type index)const{
        if(index >= this->count_digits()) return 0;
        return m_number[index];
    }

    bool is_positive()const
        {return m_sign.is_positive();}

    bool is_negative()const
        {return m_sign.is_negative();}

    sign_type sign()const
        {return m_sign;}

    static digit_type base()
        {return 10;}



    void set_base(digit_type)
        {/* Do nothing */}

    void make_zero()
        {m_number = diglist_type(1, 0); this->make_positive();}

    void make_one()
        {m_number = diglist_type(1, 1); this->make_positive();}

    void make_neg_one()
        {m_number = diglist_type(1, 1); this->make_negative();}

    void make_two()
        {m_number = diglist_type(1, 2); this->make_positive();}

    void halve(){
        Core_Int two, quo_res, mod_res;
        two.m_number.push_back(2);
        two.make_positive();
        Precision::Volatile::Int_Operations::divide_mod(*this, two, quo_res, mod_res);

        *this = std::move(quo_res);
    }

    void shift_left(size_type e){
        if(this->is_zero()) return;
        else                m_number.insert(m_number.begin(), e, 0);
    }

    void shift_right(size_type e){
        if(m_number.size() <= e)
            m_number = diglist_type(1, 0);
        else
            m_number.erase(m_number.begin(), m_number.begin() + e);
    }

    void digit(size_type index, digit_type new_digit){
        if(index >= m_number.size()) return;

        m_number[index] = new_digit;
    }

    void force_digit(size_type index, digit_type new_digit){
        if(index < m_number.size()){
            m_number[index] = new_digit;
            return;
        }

        m_number.insert(m_number.end(), index - m_number.size(), 0);
        m_number.push_back(new_digit);
    }

    void append(digit_type new_digit)
        {m_number.push_back(new_digit % this->base());}

    void detach()
        {m_number.pop_back();}

    void negate()
        {m_sign.negate();}

    void make_positive()
        {m_sign.make_positive();}

    void make_negative()
        {m_sign.make_negative();}

    void sign(sign_type new_sign)
        {m_sign.assign(new_sign);}


    diglist_type m_number;
    sign_type    m_sign;
};
//*/

#include "Test_Shared_Utilities.h"
// For converting results to comparable strings
#include "general_base/impl/Precision_Int_Operations_Img.h"

template <typename IntType>
test_and_log_util::str_type to_str(const IntType& num){
    static char const *const digs = "0123456789";
    static char const *const syms = "+-.e /i";

    return Precision::Volatile::Int_Operations::Img::str<IntType>(num, digs, syms);
}

template <typename IntType>
test_and_log_util::str_type to_sci_note_str(const IntType& num, std::size_t prec){
    static char const *const digs = "0123456789";
    static char const *const syms = "+-.e /i";

    return Precision::Volatile::Int_Operations::Img::sci_note<IntType>
                                                    (num, prec, digs, syms);
}

#endif