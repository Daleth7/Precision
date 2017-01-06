/** \file Precision_Signed_Interface.h
 * This file holds the interface that specifies
 * operations related to manipulating numerical
 * signs.
 */

#ifndef S111111IGN335_TYPE_NUMBER_I66NTERFACE__________HHHHHH______
#define S111111IGN335_TYPE_NUMBER_I66NTERFACE__________HHHHHH______

namespace Precision{
    /** Precision::Signed_Integer provides a representation for a number
     *  sign such that all number types can store a number's magnitude
     *  and numerical sign separately. This class also simplifies sign
     *  related operations and follows these rules:
     *      - Negative == -1
     *      - Positive == +1
     *  For purposes of conversion, positive includes [0, inf) and
     *  negative includes (-inf, 0).
     */
    class Signed_Integer{
        public:
            // Type-aliases
            /** signed_type represents the output type that can be +1 or -1 */
            using sign_type = short;

            // Read-only
            /** Return if the sign is positive, or +1.
             *
             * \return Whether the sign is considered positive.
             */
            bool is_positive()const
                {return !m_negative;}

            /** Return if the sign is negative, or -1.
             *
             * \return Whether the sign is considered negative.
             */
            bool is_negative()const
                {return m_negative;}

            /** Return the actual sign value itself.
             *
             * \return -1 for negative and +1 for positive.
             */
            sign_type sign()const
                {return 1 - m_negative * 2;}



            // Modifiers
            /** Change the sign from positive to negative
             *  or vice versa.
             */
            void negate()
                {m_negative = !m_negative;}

            /** Force the sign to be positive. */
            void make_positive()
                {m_negative = false;}

            /** Force the sign to be negative. */
            void make_negative()
                {m_negative = true;}

            /** Change the sign to positive or negative.
             *
             *  \param new_sign The sign to change to.
             *                  (-inf, 0) --> Negative
             *                  [0, inf) --> Positive
             */
            void sign(sign_type new_sign)
                {m_negative = new_sign < 0;}



            //Constructors and Destructor

            /** Construct an object with a specified sign.
             *
             *  \param new_sign The sign to initialize with.
             *                  (-inf, 0) --> Negative
             *                  [0, inf) --> Positive
             */
            Signed_Integer(sign_type new_sign)
                : m_negative(new_sign < 0)
            {}

            /** Compiler generated default constructor. */
            Signed_Integer()                                 = default;
            /** Compiler generated copy constructor. */
            Signed_Integer(const Signed_Integer&)            = default;
            /** Compiler generated copy move constructor. */
            Signed_Integer(Signed_Integer&&)                 = default;
            /** Compiler generated assignment operator. */
            Signed_Integer& operator=(const Signed_Integer&) = default;
            /** Compiler generated move assignment operator. */
            Signed_Integer& operator=(Signed_Integer&&)      = default;
            /** Compiler generated destructor. */
            ~Signed_Integer()                                = default;

        protected:
            bool m_negative;
    };
}


#endif