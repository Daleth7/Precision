/** \file Precision_Signed_Interface.h
 * This file holds the interface that specifies
 * operations related to manipulating numerical
 * signs.
 */

#ifndef S111111IGN335_TYPE_NUMBER_I66NTERFACE__________HHHHHH______
#define S111111IGN335_TYPE_NUMBER_I66NTERFACE__________HHHHHH______

#include "Precision_Sign_Class.h"

namespace Precision{
    /** Precision::Signed_Interface provides a set of functions for
     *  manipulating the numerical sign that can be inherited, rather than
     *  having the client classes redefine the same functions over and over
     *  again. This class also serves as a thin layer over
     *  Precision::SignClass such that child classes still follow a
     *  composition structure and can pass a sign object to functions
     *  without having to pass a reference to the whole class, which would
     *  not make sense in situations where only a sign is required.
     *  
     *  This class obeys the same rules as Precision::SignClass as follows:
     *      - Negative == -1
     *      - Positive == +1
     *  For purposes of conversion, positive includes [0, inf) and
     *  negative includes (-inf, 0).
     */
    class Signed_Interface{
        public:
            // Type-aliases
            /** sign_type represents the underlying sign class used for
             *  composition. The class is assumed to be a lightweight POD.
             */
            using sign_type = Precision::SignClass;

            // Read-only
            /** Return if the sign is positive, or +1.
             *
             * \return Whether the sign is considered positive.
             */
            bool is_positive()const
                {return m_sign.is_positive();}

            /** Return if the sign is negative, or -1.
             *
             * \return Whether the sign is considered negative.
             */
            bool is_negative()const
                {return m_sign.is_negative();}

            /** Return the actual sign value itself.
             *
             * \return The sign object representing the value
             *         (-1 for negative and +1 for positive).
             */
            sign_type sign()const
                {return m_sign;}



            // Modifiers
            /** Change the sign from positive to negative
             *  or vice versa.
             */
            void negate()
                {m_sign.negate();}

            /** Force the sign to be positive. */
            void make_positive()
                {m_sign.make_positive();}

            /** Force the sign to be negative. */
            void make_negative()
                {m_sign.make_negative();}

            /** Change the sign to positive or negative.
             *
             *  \param new_sign The sign to change to.
             *                  (-inf, 0) --> Negative
             *                  [0, inf) --> Positive
             */
            void sign(sign_type new_sign)
                {m_sign.assign(new_sign);}



            //Constructors and Destructor

            /** Construct an object with a specified sign.
             *
             *  \param new_sign The sign to initialize with.
             *                  (-inf, 0) --> Negative
             *                  [0, inf) --> Positive
             */
            Signed_Interface(sign_type new_sign)
                : m_sign(new_sign)
            {}

            /** Compiler generated default constructor. */
            Signed_Interface()                                   = default;
            /** Compiler generated copy constructor. */
            Signed_Interface(const Signed_Interface&)            = default;
            /** Compiler generated copy move constructor. */
            Signed_Interface(Signed_Interface&&)                 = default;
            /** Compiler generated assignment operator. */
            Signed_Interface& operator=(const Signed_Interface&) = default;
            /** Compiler generated move assignment operator. */
            Signed_Interface& operator=(Signed_Interface&&)      = default;
            /** Compiler generated destructor. */
            ~Signed_Interface()                                  = default;

        protected:
            sign_type m_sign;
    };
}


#endif