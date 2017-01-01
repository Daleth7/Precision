/** \file Precision_Signed_Interface.h
 * This file holds the interface the deals solely
 * with manipulating an integer's numerical sign.
 */

#ifndef S111111IGN335_TYPE_NUMBER_I66NTERFACE__________HHHHHH______
#define S111111IGN335_TYPE_NUMBER_I66NTERFACE__________HHHHHH______

#include "Precision_Defaults.h"

namespace Precision{
    template <typename SignType = Default::sign_type>
    class Signed_Integer{
        public:
            // Type-aliases
            using sign_type = SignType;

            // Read-only
            bool is_positive()const
                {return m_sign.is_positive();}

            bool is_negative()const
                {return m_sign.is_negative();}

            sign_type sign()const
                {return m_sign;}



            // Modifiers
            void negate()
                {m_sign.negate();}

            void sign(sign_type new_sign)
                {m_sign = new_sign;}

        protected:
            sign_type m_sign;
    };

    template <typename SignType = Default::sign_type>
    struct Unsigned_Integer{
        // Type-aliases
        using sign_type = SignType;

        // Read-only
        static constexpr bool is_positive()
            {return true;}

        static constexpr bool is_negative()const
            {return false;}

        static constexpr sign_type sign()const
            {return sign_type(1);}



        // Modifiers
        static constexpr void negate()
            {/* Do nothing */}

        static constexpr void sign(sign_type)
            {/* Do nothing */}
    };
}


#endif