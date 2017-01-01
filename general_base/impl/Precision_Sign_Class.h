/** \file Precision_Sign_Class.h
 *  Precision::SignClass provides a representation for a number
 *  sign such that all number types can store a number's magnitude
 *  and numerical sign separately. This class also simplifies sign
 *  related operations and follows these rules:
 *      - Negative == -1
 *      - Positive == +1
 *  For purposes of conversion, positive also includes [0, inf).
 */

#ifndef SIGN_CLASS_DEFINITION_H___
#define SIGN_CLASS_DEFINITION_H___

namespace Precision{
    /** Precision::SignClass provides a representation for a number
     *  sign such that all number types can store a number's magnitude
     *  and numerical sign separately. This class also simplifies sign
     *  related operations and follows these rules:
     *      - Negative == -1
     *      - Positive == +1
     *  For purposes of conversion, positive also includes [0, inf).
     */
    class SignClass{
        public:
            //Type Aliases

            /** signed_type represents the output type that can be +1 or -1 */
            using signed_type = signed short;



            //Read-only

            /** Return the actual sign value itself.
             *
             * \return -1 for negative and +1 for positive.
             */
            signed_type value()const;

            /** Return if the sign is positive, or +1.
             *
             * \return Whether the sign is considered positive.
             */
            bool is_positive()const;

            /** Return if the sign is negative, or -1.
             *
             * \return Whether the sign is considered negative.
             */
            bool is_negative()const;

            /** Cast the object to the sign value itself.
             *  Similar to value().
             *
             * \return -1 for negative and +1 for positive.
             */
            operator signed_type()const;


            //Modifiers

            /** Change the sign from positive to negative
             *  or vice versa.
             */
            void flip();

            /** Change the sign from positive to negative
             *  or vice versa. Operates the same as flip().
             */
            void negate();

            /** Change the sign to positive or negative.
             *
             *  \param new_sign The sign to change to.
             *                  (-inf, 0) --> Negative
             *                  [0, inf) --> Positive
             */
            void assign(signed_type new_sign);

            /** Force the sign to be positive. */
            void make_positive();

            /** Force the sign to be negative. */
            void make_negative();



            //Constructors and Destructor

            /** Construct an object with a specified sign.
             *
             *  \param new_sign The sign to initialize with.
             *                  (-inf, 0) --> Negative
             *                  [0, inf) --> Positive
             */
            SignClass(signed_type new_sign);

            /** Compiler generated default constructor. */
            SignClass()                             = default;
            /** Compiler generated copy constructor. */
            SignClass(const SignClass&)             = default;
            /** Compiler generated copy move constructor. */
            SignClass(SignClass&&)                  = default;
            /** Compiler generated assignment operator. */
            SignClass& operator=(const SignClass&)  = default;
            /** Compiler generated move assignment operator. */
            SignClass& operator=(SignClass&&)       = default;
            /** Compiler generated destructor. */
            ~SignClass()                            = default;

        private:
            bool m_positive;
    };
}

#endif