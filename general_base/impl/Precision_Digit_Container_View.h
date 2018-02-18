/** \file Precision_Digit_Container_View.h
 * This file holds a digit container class that
 * handles sub-digit strings from an existing
 * container that actually stores the digits.
 * This is analogous to std::basic_string_view
 */

#ifndef CONTAIN77ER_NUMBER_VIWE32889IEWER____HHHH
#define CONTAIN77ER_NUMBER_VIWE32889IEWER____HHHH

#include "Precision_Defaults.h"

#include <iterator>
#include <cstdint>

namespace Precision{
    /** Precision::Digit_Container_View provides a set of functions for
     *  viewing the digit string, to avoid creating copies of a digit
     *  string when there will be no manipulation.
     *
     *  Note that while this class provides a view-only interface
     *  to an existing digits string, this class has no knowledge
     *  of any changes to the existing string. This means that,
     *  for example, if the size of the original string falls below
     *  the size this class expects, calling Digit_Container_View::digit_count()
     *  can return an incorrect size. Also be aware of insertions or
     *  erasing in the original string that may invalidate the underlying
     *  raw_iterator this class uses.
     *
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
     *  \tparam Container The underlying container to store a string of digits.
     */
    template < class Container = Default::container_type<Default::byte_type> >
    class Digit_Container_View{
        public:
            // Type-aliases

            /** The container type from which to extract type information.
              */
            using digstr_type           = Container;

            /** The raw primitive representing the digit. */
            using digit_type            = typename digstr_type::value_type;

            /** The raw_iterator type of the container */
            using raw_iterator          = typename digstr_type::const_iterator;

            /** The raw_iterator type of the container */
            using reverse_raw_iterator  = std::reverse_iterator<raw_iterator>;

            /** The primitive representing size in digstr_type. */
            using size_type             = typename digstr_type::size_type;

            /** A primitive type used for dealing with size related
              * operations that still need the negative range.
              */
            using signed_size_type      = std::int_least32_t;



            // Read-only

            /** Check if the digit string is equivalent to 0.
              *
              * \return True if the string is 0. False otherwise.
              */
            bool is_zero()const
                {return m_sz == 1 && *m_beg == 0;}

            /** Check if the digit string is equivalent to 1, regardless
              * of sign.
              *
              * \return True if the string is 1. False otherwise.
              */
            bool is_mag_one()const
                {return m_sz == 1 && *m_beg == 1;}

            /** Check if the rightmost (first) digit of the string is
              * even.
              *
              * \return True if the string is even. False otherwise.
              */
            bool is_even()const
                {return (*m_beg % 2) == 0;}

            /** Check if the rightmost (first) digit of the string is
              * odd.
              *
              * \return True if the string is odd. False otherwise.
              */
            bool is_odd()const
                {return !(this->is_even());}

            /** Return the underlying iterator.
              *
              * \return a copy of the underlying raw_iterator.
              */
            const raw_iterator& raw_begin()const
                {return m_beg;}

            /** Return an iterator to the end of the string.
              *
              * \return a the end raw_iterator.
              */
            raw_iterator raw_end()const{
                raw_iterator cpy = m_beg;
                std::advance(cpy, m_sz);
                return cpy;
            }

            /** Return an iterator to the beginning of the digit
              * string as if the number was reversed.
              *
              * \return a copy of the underlying raw_iterator.
              */
            reverse_raw_iterator raw_rbegin()const
                {return reverse_raw_iterator(this->raw_end());}

            /** Return an iterator to the end of the digit
              * string as if the number was reversed.
              *
              * \return a the end raw_iterator.
              */
            reverse_raw_iterator raw_rend()const
                {return reverse_raw_iterator(this->raw_begin());}

            /** Count the number of digits in the string. The value returned
              * should always be at least one.
              *
              * \return The number of digits in the string.
              */
            size_type count_digits()const
                {return m_sz;}

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
                raw_iterator cpy = m_beg;
                std::advance(cpy, index);
                return *cpy;
            }


            // Constructors and destructor

            /** Construct a string view from a pair of iterators
              *
              * \param new_beg An raw_iterator to the beginning of the digit string.
              * \param new_end An raw_iterator to the end of the digit string.
              */
            Digit_Container_View(const raw_iterator& new_beg, const raw_iterator& new_end)
                : m_beg(new_beg)
                , m_sz(std::distance(new_beg, new_end))
            {}

            /** Construct a string view from an raw_iterator to the beginning of a digit
              * string and the string size.
              *
              * \param new_beg An raw_iterator to the beginning of the digit string.
              * \param new_sz The size of the digit string to view.
              */
            Digit_Container_View(const raw_iterator& new_beg, size_type new_sz)
                : m_beg(new_beg)
                , m_sz(new_sz)
            {}


            /** Construct a string view from an already existing digit string
              * starting with an offset and size.
              *
              * \param new_num The digit string to view
              * \param offset The offset or index to start the string view.
              * \param new_sz The size of the digit string to view.
              */
            Digit_Container_View( const digstr_type& new_num,
                                  size_type offset = 0, size_type new_sz = -1
                                  )
                : m_beg(new_num.cbegin())
                , m_sz(new_num.size() < new_sz ? (new_num.size()-offset) : new_sz)
            {
                std::advance(m_beg, offset);
            }

            /** Compiler generated copy constructor. */
            Digit_Container_View(const Digit_Container_View&)               = default;
            /** Compiler generated copy move constructor. */
            Digit_Container_View(Digit_Container_View&&)                    = default;
            /** Compiler generated assignment operator. */
            Digit_Container_View& operator=(const Digit_Container_View&)    = default;
            /** Compiler generated move assignment operator. */
            Digit_Container_View& operator=(Digit_Container_View&&)         = default;
            /** Compiler generated destructor. */
            ~Digit_Container_View()                                         = default;

        protected:

            raw_iterator  m_beg;
            size_type m_sz;
    };
}


#endif