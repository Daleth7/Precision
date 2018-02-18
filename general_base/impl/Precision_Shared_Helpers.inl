//#include "Type_Traits_Extended/Type_Traits_Ext.h"

//#include "Precision_Signed_Interface.h"

//#include "Precision_Tags.h"

//#include "Precision_Precedence_Pack.h"

#include <algorithm> // For std::min

namespace Precision{
    namespace Helper{
/*
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
*/
        template <typename NumType>
        bool is_zero(const NumType& num)
            {return num.is_zero();}

        template <typename NumType>
        bool is_one(const NumType& num)
            {return num.is_one();}

        template <typename NumType>
        bool is_neg_one(const NumType& num)
            {return num.is_neg_one();}

        template <typename NumType>
        bool is_negative(const NumType& num)
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

        template <typename NumType>
        typename NumType::digit_type base(const NumType& num)
            {return num.base();}

        template <typename NumType>
        typename NumType::digit_type digit( const NumType& num,
                                            typename NumType::size_type idx
        ){return num.digit(idx);}

        template <typename NumType>
        void halve(NumType& num)
            {num.halve();}

        template <typename FloatType>
        void reciprocate(FloatType& num)
            {num.reciprocate();}

        template <typename NumType>
        void negate(NumType& num)
            {num.negate();}

        template <typename NumType, typename Number_Type2>
        void match_base(NumType& num, const Number_Type2& ref)
            {num.base(ref.base());}

        template <typename NumType, typename Number_Type2>
        void match_base_raw(NumType& num, const Number_Type2& base)
            {num.base(base);}

        template <typename NumType, typename Number_Type2>
        void copy_image_set(NumType& num, const Number_Type2& ref)
            {num.image_set(ref.image_set());}

        template <typename NumType, typename Number_Type2>
        void make_zero(NumType& num, const Number_Type2& ref){
            match_base(num, ref);
            copy_image_set(num, ref);
            num.make_zero();
        }

        template <typename NumType, typename Number_Type2>
        void make_one(NumType& num, const Number_Type2& ref){
            match_base(num, ref);
            copy_image_set(num, ref);
            num.make_one();
        }

        template <typename NumType, typename Number_Type2>
        void make_two(NumType& num, const Number_Type2& ref){
            match_base(num, ref);
            copy_image_set(num, ref);
            num.make_two();
        }

        template <typename NumType>
        void make_zero(NumType& num)
            {num.make_zero();}

        template <typename NumType>
        void make_one(NumType& num)
            {num.make_one();}

        template <typename NumType>
        void make_two(NumType& num)
            {num.make_two();}

        template <typename NumType>
        NumType make_zero_temp(const NumType& ref){
            NumType toreturn;
            make_zero(toreturn, ref);
            return toreturn;
        }

        template <typename NumType>
        NumType make_one_temp(const NumType& ref){
            NumType toreturn;
            make_one(toreturn, ref);
            return toreturn;
        }

        template <typename NumType>
        NumType make_two_temp(const NumType& ref){
            NumType toreturn;
            make_two(toreturn, ref);
            return toreturn;
        }

        template <typename IntType>
        void remove_excess_zeros(IntType& num){
            while(num.count_digits() > 1 && num.digit(num.count_digits()-1) == 0)
                num.detach();
        }

        template <typename IntType>
        void remove_trailing_zeros(IntType& num){
            using size_type = typename IntType::size_type;
            size_type to_shift = 0;
            for(size_type i=0; i < num.count_digit(); ++i, ++to_shift){
                if(digit(num, i) != 0)
                    return to_shift;
            }
            return to_shift;
        }

        template <typename FloatType>
        void inf_prec(const FloatType& num)
            {return num.has_infinite_precision();}

        template <typename FloatType>
        void prec(const FloatType& num)
            {return num.precision();}

        template <typename FloatType, typename FloatType2>
        typename FloatType::size_type min_precision
            (const FloatType& num, const FloatType2& num2)
        {
            using size_type = typename FloatType::size_type;
            if(inf_prec(num) && inf_prec(num2))
                return static_cast<size_type>(-1);

            if(inf_prec(num))
                return prec(num2);
            else if(inf_prec(num2))
                return prec(num);

            return std::min(prec(num), prec(num2));
        }

        template <typename IntType>
        IntType generate_operand( const IntType& num,
                                  typename IntType::size_type prec
                                  )
        {
            if((prec+1) > int_size(num)){
                IntType toreturn(num);
                toreturn.shift_left(prec+1-int_size(num));
                return toreturn;
            }

            IntType toreturn(num);
            toreturn.shift_right(int_size(num)-prec-1);
            return toreturn;
        }

        template <typename FloatType>
        typename FloatType::digit_type digit_float
            ( const FloatType& num,
              const typename FloatType::integer_type& raw_int,
              typename FloatType::size_type idx
              )
        {
            // Since the number is stored without trailing zeros,
            // calculate the index at which the first digit is stored
            // in raw_int.
            typename FloatType::size_type cross_index = 0;
            if(prec(num)+1 > int_size(raw_int))
                cross_index = prec(num)+1-int_size(raw_int);

            // idx points to a trailing zero.
            if(idx < cross_index)
                return 0;

            // Index points to a digit in raw_int
            return digit(raw_int, idx-cross_index);
        }

        template <typename FloatType>
        typename FloatType::digit_type assign_float
            ( FloatType& num,
              typename FloatType::integer_type& raw_int,
              typename FloatType::size_type idx,
              typename FloatType::digit_type new_dig
              )
        {
            // Since the number is stored without trailing zeros,
            // calculate the index at which the first digit is stored
            // in raw_int.
            typename FloatType::size_type cross_index = 0;
            if(prec(num)+1 > int_size(raw_int))
                cross_index = prec(num)+1-int_size(raw_int);

            // Index points to a trailing zero. Exponent and integer
            // needs to be updated.
            if(idx < cross_index){
                raw_int.shift_left(cross_index-idx);
                raw_int.assign(idx, new_dig);
                num.exponent(num.exponent()-(cross_index-idx));
            }

            // Index points to a digit in raw_int
            return raw_int.assign(idx-cross_index, new_dig);
        }
    }
}

//#undef PRE_CATE_
//#undef PRE_BASE_