#include "Type_Traits_Extended/Type_Traits_Ext.h"

//#include "Precision_Signed_Interface.h"

#include "Precision_Tags.h"

#include "Precision_Precedence_Pack.h"

namespace Precision{
    namespace Helper{
        template <typename IntType>
        bool are_equal(
            const IntType& f, const IntType& s,
            Tag::Fraction
        ){return f.decimal() == s.decimal();}

        template <typename IntType>
        bool are_equal_float_fund(
            const IntType& f, const IntType& s,
            std::true_type
        ){return ( (f < s+1e-7) && (s-1e-7 < f) );}

        template <typename IntType>
        bool are_equal_float_fund(
            const IntType& f, const IntType& s,
            std::false_type
        ){return f == s;}

        template <typename IntType, typename U>
        bool are_equal(const IntType& f, const IntType& s, U){
            return are_equal_float_fund(
                f, s,
                typename std::is_floating_point<IntType>::type()
            );
        }

        template <typename IntType>
        bool are_equal(const IntType& f, const IntType& s){
            return are_equal(
                f, s,
                typename Type_Trait::find_base<IntType, PRE_CATE_>::type()
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

        template <typename IntType>
        bool is_zero(const IntType& num)
            {return num.is_zero();}

        template <typename IntType>
        bool is_one(const IntType& num)
            {return num.is_one();}

        template <typename IntType>
        bool is_neg_one(const IntType& num)
            {return num.is_neg_one();}

        template <typename IntType>
        bool is_negative(const IntType& num)
            {return num.is_negative();}

        template <typename IntType>
        bool is_odd(const IntType& num)
            {return num.is_odd();}

        template <typename IntType>
        bool is_even(const IntType& num)
            {return num.is_even();}

        template <typename IntType>
        typename IntType::size_type int_size(const IntType& num)
            {return num.count_digits();}

        template <typename IntType>
        typename IntType::digit_type base(const IntType& num)
            {return num.base();}

        template <typename IntType>
        typename IntType::digit_type digit( const IntType& num,
                                            typename IntType::size_type idx
        ){return num.digit(idx);}

        template <typename IntType>
        void halve(IntType& num)
            {num.halve();}

        template <typename IntType>
        void reciprocate(IntType& num)
            {num.reciprocate();}

        template <typename IntType>
        void negate(IntType& num)
            {num.negate();}

        template <typename IntType, typename Number_Type2>
        void match_base(IntType& num, const Number_Type2& ref)
            {num.base(ref.base());}

        template <typename IntType, typename Number_Type2>
        void copy_image_set(IntType& num, const Number_Type2& ref)
            {num.image_set(ref.image_set());}

        template <typename IntType, typename Number_Type2>
        void make_zero(IntType& num, const Number_Type2& ref){
            match_base(num, ref);
            copy_image_set(num, ref);
            num.make_zero();
        }

        template <typename IntType, typename Number_Type2>
        void make_one(IntType& num, const Number_Type2& ref){
            match_base(num, ref);
            copy_image_set(num, ref);
            num.make_one();
        }

        template <typename IntType, typename Number_Type2>
        void make_two(IntType& num, const Number_Type2& ref){
            match_base(num, ref);
            copy_image_set(num, ref);
            num.make_two();
        }

        template <typename IntType>
        void make_zero(IntType& num)
            {num.make_zero();}

        template <typename IntType>
        void make_one(IntType& num)
            {num.make_one();}

        template <typename IntType>
        void make_two(IntType& num)
            {num.make_two();}

        template <typename IntType>
        IntType make_zero_temp(const IntType& ref){
            IntType toreturn;
            make_zero(toreturn, ref);
            return toreturn;
        }

        template <typename IntType>
        IntType make_one_temp(const IntType& ref){
            IntType toreturn;
            make_one(toreturn, ref);
            return toreturn;
        }

        template <typename IntType>
        IntType make_two_temp(const IntType& ref){
            IntType toreturn;
            make_two(toreturn, ref);
            return toreturn;
        }

        template <typename IntType>
        void remove_excess_zeros(IntType& num){
            while(num.count_digits() > 1 && num.digit(num.count_digits()-1) == 0)
                num.detach();
        }
    }
}

#undef PRE_CATE_
#undef PRE_BASE_