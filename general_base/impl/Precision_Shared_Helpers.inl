#include "Type_Traits_Extended/Type_Traits_Ext.h"

//#include "Precision_Signed_Interface.h"

#include "Precision_Tags.h"

#include "Precision_Precedence_Pack.h"

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
        bool is_negative(const Number_Type& num)
            {return num.is_negative();}

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
        Number_Type make_zero_temp(const Number_Type& ref){
            Number_Type toreturn;
            make_zero(toreturn, ref);
            return toreturn;
        }

        template <typename Number_Type>
        Number_Type make_one_temp(const Number_Type& ref){
            Number_Type toreturn;
            make_one(toreturn, ref);
            return toreturn;
        }

        template <typename Number_Type>
        Number_Type make_two_temp(const Number_Type& ref){
            Number_Type toreturn;
            make_two(toreturn, ref);
            return toreturn;
        }




        template <typename DigList>
        bool is_zero_diglist(const DigList& num)
            {return (num.size() == 1) && (num.front() == 0);}

        template <typename DigList, typename Sign>
        bool is_one_diglist(const DigList& num, const Sign& sign)
            {return (sign > 0) && (num.size() == 1) && (num.front() == 1);}

        template <typename DigList, typename Sign>
        bool is_neg_one_diglist(const DigList& num, const Sign& sign)
            {return (sign < 0) && (num.size() == 1) && (num.front() == 1);}

        template <typename DigList>
        bool is_odd_diglist(const DigList& num)
            {return !is_even_diglist(num);}

        template <typename DigList>
        bool is_even_diglist(const DigList& num)
            {return (num.size() > 0) && (num.front() % 2 == 0);}

        template <typename DigList>
        typename DigList::size_type size_diglist(const DigList& num)
            {return num.size();}

        template <typename DigList, typename IndexType>
        typename DigList::digit_type& digit( const DigList& num,
                                                   IndexType idx
        ){
            auto it = num.begin();
            std::advance(it, idx);
            return *it;
        }

        template <typename DigList, typename IndexType>
        void digit( const DigList& num,
                    IndexType idx,
                    typename DigList::digit_type val,
                    typename DigList::digit_type base
        ){
            auto it = num.begin();
            std::advance(it, idx);
            *it = val % base;
        }

        template <typename DigList>
        void make_zero_diglist(DigList& num)
            {num = DigList(1, 0);}

        template <typename DigList, typename BaseType, typename Sign>
        void make_one_diglist( DigList& num, const BaseType& base,
                               Sign& sign
        ){
            num = DigList(1, 1);
            sign = 1;
        }

        template <typename DigList, typename BaseType, typename Sign>
        void make_two_diglist( DigList& num, const BaseType& base,
                               Sign& sign
        ){
            if(base == 2){
                num = DigList({0, 1});
            } else {
                num = DigList(1, 2);
            }
            sign = 1;
        }

        template <typename DigList, typename Sign>
        void make_one_diglist(DigList& num, Sign& sign){
            num.erase(num.begin()+1, num.end());
            num.front() = 1;
            sign = 1;
        }

        template <typename DigList, typename Sign>
        void make_two_diglist(DigList& num, Sign& sign){
            num.erase(num.begin()+1, num.end());
            num.front() = 2;
            sign = 1;
        }

        template <typename DigList, typename Base_Type>
        DigList make_zero_temp_diglist(const Base_Type& base){
            DigList toreturn;
            make_zero_diglist(toreturn, base);
            return toreturn;
        }

        template <typename DigList, typename Base_Type>
        DigList make_one_temp_diglist(const Base_Type& base){
            DigList toreturn;
            short fake_sign;
            make_one_diglist(toreturn, fake_sign, base);
            return toreturn;
        }

        template <typename DigList, typename Base_Type>
        DigList make_two_temp_diglist(const Base_Type& base){
            DigList toreturn;
            short fake_sign;
            make_two_diglist(toreturn, fake_sign, base);
            return toreturn;
        }

        template <typename DigList, typename DigitType>
        void append_diglist(DigList& num, const DigitType& dig)
            {num.push_back(dig);}

        template <typename DigList>
        void detach_diglist(DigList& num)
            {num.pop_back();}

        template <typename DigList>
        void remove_excess_zeros_diglist(DigList& num){
            while(size_diglist(num) > 1 && num.back() == 0)
                detach_diglist(num);
        }

        template <typename DigList, typename SizeType>
        void shift_left_diglist(DigList& num, SizeType sz){
            if(is_zero(num)) return;
            else             num.insert(num.begin(), sz, 0);
        }

        template <typename DigList, typename SizeType>
        void shift_right_diglist(DigList& num, SizeType sz){
            if(num.size() <= sz) num = DigList(1, 0);
            else                 num.erase(num.begin(), num.begin() + sz);
        }
    }
}

#undef PRE_CATE_
#undef PRE_BASE_