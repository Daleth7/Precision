/** \file Precision_Digit_Container.h
 * This file holds the parent class that deals solely
 * with storing digits and their manipulation.
 */

#ifndef CONTAIN23ER_NUMBER_HOL978DING_DIGIT22222____HHHH
#define CONTAIN23ER_NUMBER_HOL978DING_DIGIT22222____HHHH

#include "Precision_Defaults.h"
#include "Precision_Shared_Helpers.h"

#include <initializer_list>

namespace Precision{
    /** Precision::Digit_Container provides a set of functions for
     *  manipulating the digit string that can be inherited, to ease
     *  the implementation of child classes.
     *  This class also serves as a thin layer over the underlying
     *  container type, such that child classes still follow a
     *  composition structure and can pass a reference to or copy of
     *  the digit string itself when needed.
     *  Note that this class is blind to the actual number base, so
     *  this class does not provide digit changing/adding functions.
     *  The child class is expected to provide these and to ensure
     *  all digits in the container are valid according to the number
     *  base. This class will not store base information to avoid
     *  forcing child classes to treat the number base a certain way.
     *  This class also assumes that, no matter the number base, that
     *  the associated digits are consecutive integers starting at 0.
     *
     *  Digits are stored in reverse. For example, the number 1234 will
     *  be stored as {4, 3, 2, 1}.
     *
     *  \tparam ByteType The primitive used to store a digit.
     *  \tparam Container The underlying container to store a string of digits.
     */
    template < typename ByteType = Default::byte_type,
               template <typename...> class Container = Default::container_type
               >
    class Digit_Container{
        public:
            // Type-aliases

            /** The raw primitive representing the digit. */
            using digit_type   = ByteType;

            /** The underlying container storing the string of digits.
              * The container is assumed to support:
              *     * Random access iterators
              *     * Type Container<digit_type>::size_type
              *     * Method size_type Container<digit_type>::size()
              *     * Method digit_type Container<digit_type>::front()
              *     * Method iterator Container<digit_type>::begin()
              *     * Method void Container<digit_type>::insert
              *                   (iterator, size_type, digit_type)
              *     * Method void Container<digit_type>::erase(iterator, iterator)
              *     * Method void Container<digit_type>::push_back()
              *     * Method void Container<digit_type>::pop_back()
              *     * Method Container<digit_type>::Container(size_type, digit_type)
              *     * Method Container<digit_type>::Container
              *              (const std::initializer_list<digit_type>&)
              *     * Method Container<digit_type>::Container(iterator, iterator)
              */
            using diglist_type = Container<digit_type>;

            /** The primitive representing size in diglist_type.
              */
            using size_type    = typename diglist_type::size_type;

            /** A primitive type used for dealing with size related
              * operations that still need the negative range.
              */
            using signed_size_type = std::int_least32_t;



            // Read-only

            /** Check if the digit string is equivalent to 0.
              *
              * \return True if the string is 0. False otherwise.
              */
            bool is_zero()const
                {return m_number.size() == 1 && m_number.front() == 0;}

            /** Check if the digit string is equivalent to 1, regardless
              * of sign.
              *
              * \return True if the string is 1. False otherwise.
              */
            bool is_mag_one()const
                {return m_number.size() == 1 && m_number.front() == 1;}

            /** Check if the rightmost (first) digit of the string is
              * even.
              *
              * \return True if the string is even. False otherwise.
              */
            bool is_even()const
                {return (m_number.front() % 2) == 0;}

            /** Check if the rightmost (first) digit of the string is
              * odd.
              *
              * \return True if the string is odd. False otherwise.
              */
            bool is_odd()const
                {return !(this->is_even());}

            /** Return a reference to the underlying container.
              *
              * \return a read-only reference to the underlying container.
              */
            const diglist_type& digit_list()const
                {return m_number;}

            /** Count the number of digits in the string. The value returned
              * should always be at least one.
              *
              * \return The number of digits in the string.
              */
            size_type count_digits()const
                {return m_number.size();}

            /** Get a copy of a specific digit in the string. Note that the
              * index does not have to be bound to the actual size of the
              * string since any digit beyond is essentially 0.
              *
              * \param index The position of a digit to retrieve.
              *
              * \return The requested digit at position index.
              */
            digit_type digit(size_type index)const{
                if(index >= this->count_digits()) return 0;
                return m_number[index];
            }



            // Modifiers

            /** Extend the digit string. This is equivalent to multiplying
              * the number by a power of its number base.
              *
              * \param e The number of digit places to shift to the left by.
              */
            void shift_left(size_type e){
                if(this->is_zero()) return;
                else                m_number.insert(m_number.begin(), e, 0);
            }

            /** Extend or shrink the digit string by inserting 0's at the
              * beginning or removing digits from the beginning.
              *
              * \param sz The number of digit places to shift by.
              */
            void shift(signed_size_type sz){
                if(sz < 0) this->shift_right(-sz);
                else       this->shift_left(sz);
            }

            /** Extend the digit string. This is equivalent to dividing
              * the number by a power of its number base.
              *
              * \param e The number of digit places to shift to the right by.
              */
            void shift_right(size_type e){
                if(m_number.size() <= e)
                    m_number = diglist_type(1, 0);
                else{
                    auto erase_end(m_number.begin());
                    std::advance(erase_end, e);
                    m_number.erase(m_number.begin(), erase_end);
                }   
            }

            /** Remove the leftmost (last) digit in the string. */
            void detach()
                {m_number.pop_back();}


            // Constructors and destructor

            /** Construct a string from a specified set.
              *
              * \param str The string of digits to start with.
              */
            Digit_Container(const std::initializer_list<digit_type>& str)
                : m_number(str)
            {
                this->verify_diglist();
            }


            /** Construct a string from an already existing digit string.
              *
              * \param new_num The digit string to copy
              */
            template <typename Iterator>
            Digit_Container(const diglist_type& new_num)
                : m_number(new_num)
            {
                this->verify_diglist();
            }


            /** Construct a string from a specified set.
              *
              * \param pbeg Iterator pointing to the beginning of the set.
              * \param pend Iterator pointing to the ending of the set.
              */
            template <typename Iterator>
            Digit_Container(const Iterator& pbeg, const Iterator& pend)
                : m_number(pbeg, pend)
            {
                this->verify_diglist();
            }

            /** Construct a string with one digit.
              *
              * \param num The digit value to start with.
              */
            Digit_Container(digit_type num = 0)
                : m_number(1, num)
            {}

            /** Compiler generated copy constructor. */
            Digit_Container(const Digit_Container&)            = default;
            /** Compiler generated copy move constructor. */
            Digit_Container(Digit_Container&&)                 = default;
            /** Compiler generated assignment operator. */
            Digit_Container& operator=(const Digit_Container&) = default;
            /** Compiler generated move assignment operator. */
            Digit_Container& operator=(Digit_Container&&)      = default;
            /** Compiler generated destructor. */
            ~Digit_Container()                                 = default;

        protected:

            /** Make sure all the digits in m_number are valid and that
              * the size is at least one.
              */
            void verify_diglist(){
                if(m_number.size() == 0) m_number.push_back(0);
                for(auto it = m_number.begin(); it != m_number.end(); ++it){
                    if(*it >= this->base()) *it = 0;
                }
                Helper::remove_excess_zeros(m_number);
            }

            diglist_type m_number;
    };
}


#endif