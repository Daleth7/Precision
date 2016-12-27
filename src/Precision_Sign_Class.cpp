#include "general_base/Precision_Sign_Class.h"

namespace Precision{
    //Read-only

    SignClass::signed_type SignClass::value()const{
        return
            static_cast<signed_type>(m_positive)
            * static_cast<signed_type>(2)
            - static_cast<signed_type>(1)
        ;
    }

    bool SignClass::is_positive()const
        {return m_positive;}

    bool SignClass::is_negative()const
        {return !m_positive;}

    SignClass::operator signed_type()const
        {return this->value();}



    //Modifiers

    void SignClass::flip()
        {m_positive = !m_positive;}

    void SignClass::negate()
        {this->flip();}

    void SignClass::assign(signed_type n)
        {m_positive = !(n < 0);}

    void SignClass::make_positive()
        {m_positive = true;}

    void SignClass::make_negative()
        {m_positive = false;}



    //Constructors and Destructor

    SignClass::SignClass(signed_type n)
        : m_positive(!(n < 0))
    {}
}
