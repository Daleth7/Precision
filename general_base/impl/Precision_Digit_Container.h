/** \file Precision_Digit_Container.h
 * This file holds the parent class that deals solely
 * with storing digits and their manipulation.
 */

#ifndef CONTAIN23ER_NUMBER_HOL978DING_DIGIT22222____HHHH
#define CONTAIN23ER_NUMBER_HOL978DING_DIGIT22222____HHHH

#include "Precision_Defaults.h"

namespace Precision{
    template < typename ByteType = Default::byte_type,
               template <typename...> class Container = Default::container_type
               >
    class DigitContainer{
        public:
            // Type-aliases
            using digit_type   = ByteType;
            using diglist_type = Container<digit_type>;
            using size_type    = default_size_type;

            // Read-only
            bool is_zero()const
                {return m_number.size() == 1 && m_number.front() == 0;}
            bool is_one()const
                {return m_number.size() == 1 && m_number.front() == 1;}
            bool is_even()const
                {return (m_number.front() % 2) == 0;}

            const diglist_type& digit_list()const
                {return m_number;}

            size_type count_digits()const
                {return m_number.size();}

            digit_type digit(size_type index)const{
                if(index >= this->count_digits()) return 0;
                return m_number[index];
            }



            // Modifiers

            void make_zero()
                {m_number = diglist_type(1, 0);}

            void make_one()
                {m_number = diglist_type(1, 1);}

            void make_two()
                {m_number = diglist_type(1, 2);}

            void shift_left(size_type e){
                if(this->is_zero()) return;
                else                m_number.insert(m_number.begin(), e, 0);
            }

            void shift_right(size_type e){
                if(m_number.size() <= e)
                    m_number = diglist_type(1, 0);
                else{
                    auto end(m_number.begin());
                    std::advance(end, e);
                    m_number.erase(m_number.begin(), end);
                }   
            }

            void digit(size_type index, digit_type new_digit){
                if(index >= m_number.size()) return;

                auto it = m_number.begin();
                std::advance(it, index);
                *it = new_digit % this->base();
            }

            void append(digit_type new_digit)
                {m_number.push_back(new_digit % this->base());}

            void detach()
                {m_number.pop_back();}

        protected:
            diglist_type m_number;
    };
}


#endif