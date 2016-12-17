#include "Type_Traits_Extended/Type_Traits_Ext.h"

#include "Precision_Tags.h"

#include "Precision_Precedence_Pack.h"

#include <utility> // For std::move()

namespace Precision{
    namespace Helper{
        template <typename Number_Type>
        bool are_equal(
            const Number_Type& f, const Number_Type& s,
            Tag::Fraction
        ){return f.decimal() == s.decimal();}

        template <typename Number_Type>
        bool are_equal_float_fund(
            const Number_Type& f, const Number_Type& s,
            std::true_type
        ){return ( (f < s+1e-7) && (s-1e-7 < f) );}

        template <typename Number_Type>
        bool are_equal_float_fund(
            const Number_Type& f, const Number_Type& s,
            std::false_type
        ){return f == s;}

        template <typename Number_Type, typename U>
        bool are_equal(const Number_Type& f, const Number_Type& s, U){
            return are_equal_float_fund(
                f, s,
                typename std::is_floating_point<Number_Type>::type()
            );
        }

        template <typename Number_Type>
        bool are_equal(const Number_Type& f, const Number_Type& s){
            return are_equal(
                f, s,
                typename Type_Trait::find_base<Number_Type, PRE_CATE_>::type()
            );
        }

        #include "Cast_System.inl"

        template <typename T>
        bool is_integer_prec(const T&, std::true_type)
            {return true;}

        template <typename T>
        bool is_integer_prec(const T& val, std::false_type)
            {return val.is_integer();}

        template <typename T>
        bool is_integer(const T&, std::true_type)
            {return typename std::is_integral<T>::type();}

        template <typename T>
        bool is_integer(const T& val, std::false_type){
            return is_integer_prec(
                val,
                typename std::is_base_of<Tag::Integral, T>::type()
            );
        }

        template <typename T>
        bool is_integer(const T& val)
            {return is_integer(val, typename std::is_fundamental<T>::type());}

        template <typename Number_Type>
        bool is_zero(const Number_Type& num)
            {return num.is_zero();}

        template <typename Number_Type>
        bool is_one(const Number_Type& num)
            {return num.is_one();}

        template <typename Number_Type>
        bool is_neg_one(const Number_Type& num)
            {return num.is_neg_one();}

        template <typename Number_Type>
        bool is_odd(const Number_Type& num)
            {return num.is_odd();}

        template <typename Number_Type>
        bool is_even(const Number_Type& num)
            {return num.is_even();}

        template <typename Number_Type>
        void halve(Number_Type& num)
            {num.halve();}

        template <typename Number_Type>
        void reciprocate(Number_Type& num)
            {num.reciprocate();}

        template <typename Number_Type>
        void negate(Number_Type& num)
            {num.negate();}

        template <typename Number_Type, typename Number_Type2>
        void match_base(Number_Type& num, const Number_Type2& ref)
            {num.set_base(ref.base());}

        template <typename Number_Type, typename Number_Type2>
        void make_zero(Number_Type& num, const Number_Type2& ref){
            match_base(num, ref);
            num.make_zero();
        }

        template <typename Number_Type, typename Number_Type2>
        void make_one(Number_Type& num, const Number_Type2& ref){
            match_base(num, ref);
            num.make_one();
        }

        template <typename Number_Type, typename Number_Type2>
        void make_two(Number_Type& num, const Number_Type2& ref){
            match_base(num, ref);
            num.make_two();
        }

        template <typename Number_Type>
        void make_zero(Number_Type& num)
            {num.make_zero();}

        template <typename Number_Type>
        void make_one(Number_Type& num)
            {num.make_one();}

        template <typename Number_Type>
        void make_two(Number_Type& num)
            {num.make_two();}

        template <typename Number_Type>
        Number_Type&& make_zero_temp(const Number_Type& ref){
            Number_Type toreturn;
            make_zero(toreturn, ref);
            return std::move(toreturn);
        }

        template <typename Number_Type>
        Number_Type&& make_one_temp(const Number_Type& ref){
            Number_Type toreturn;
            make_one(toreturn, ref);
            return std::move(toreturn);
        }

        template <typename Number_Type>
        Number_Type&& make_two_temp(const Number_Type& ref){
            Number_Type toreturn;
            make_two(toreturn, ref);
            return std::move(toreturn);
        }
    }
}

#undef PRE_CATE_
#undef PRE_BASE_