#include "Test_Shared_Utilities.h"

#include "general_base/impl/Precision_Int_Operations.h"
#include "general_base/Precision_Sign_Class.h"

// For converting results to comparable strings
#include "general_base/impl/Precision_Int_Operations_Img.h"

#include <vector>

struct Core_Int{
    using str_type      = std::string;
    using size_type     = std::size_t;
    using digit_type    = std::uint_fast8_t;
    using diglist_type  = std::vector<digit_type>;
    using sign_type     = Precision::SignClass;
    using catalyst_type = long double;

    bool is_zero()const
        {return Precision::Volatile::Int_Operations::is_zero_list(m_number);}

    bool is_one()const
        {return Precision::Volatile::Int_Operations::is_one_list(m_number, m_sign);}

    bool is_neg_one()const{
        return Precision::Volatile::Int_Operations
               ::is_neg_one_list(m_number, m_sign);
    }

    bool is_positive()const
        {return m_sign.is_positive();}

    bool is_negative()const
        {return m_sign.is_negative();}

    sign_type sign()const
        {return m_sign;}

    diglist_type digit_list()const
        {return m_number;}

    size_type count_digits()const
        {return m_number.size();}

    digit_type digit(size_type index)const
        {return m_number[index];}

    static size_type base()
        {return 10;}



    void set_base(digit_type)
        {/* Do nothing */}

    void make_zero()
        {m_number = diglist_type(1, 0); m_sign.make_positive();}

    void make_one()
        {m_number = diglist_type(1, 1); m_sign.make_positive();}

    void make_neg_one()
        {m_number = diglist_type(1, 1); m_sign.make_negative();}

    void make_two()
        {m_number = diglist_type(1, 2); m_sign.make_positive();}

    void negate()
        {m_sign.negate();}

    void shift_left(size_type e){
        if(m_number.size() == 1 && m_number.front() == 0)
            return;
        else
            m_number.insert(m_number.begin(), e, 0);
    }

    void shift_right(size_type e){
        if(m_number.size() <= e)
            m_number = diglist_type(1, 0);
        else{
            auto end(m_number.begin());
            std::advance(end, e);
            m_number.erase(m_number.begin(), end);
        }   
    }

    void sign(sign_type new_sign)
        {m_sign = new_sign;}

    void digit(size_type index, digit_type new_digit){
        if(index >= m_number.size()) return;

        auto it = m_number.begin();
        std::advance(it, index);
        *it = new_digit % this->base();
    }

    void append(digit_type new_digit)
        {m_number.push_back(new_digit % this->base());}

    Core_Int& operator+=(const Core_Int& rhs){
        Precision::Volatile::Int_Operations::add<Core_Int>( m_number, rhs.m_number,
                                                            m_sign, rhs.m_sign,
                                                            this->base()
                                                            );
        return *this;
    }



    diglist_type m_number;
    sign_type m_sign;
};

                // Variables for testing comparisons
static Core_Int func_variable,
                func_gr_variable, func_le_variable,
                func_dig_gr_variable, func_dig_le_variable,
                func_dig_eq_variable,

                // Variables for testing arithmetic
                zero_list_int, one_list_int, neg_one_int,
                all_digs_int, less_digs_int, sub_int,
                sub_le_int, sub_add_digs,
                mult_fac1, mult_fac2
                ;

                // Variables for testing comparisons
static Core_Int speed_variable, speed_eq_variable,

                // Variables for testing arithmetic
                speed_add_var1, speed_add_var2,
                speed_sub_var,
                speed_mult_var1, speed_mult_var2
                ;

template <typename IntType>
test_and_log_util::str_type to_str(const IntType& num);

// Comparison tests
void setup_comparison_variables();
test_and_log_util::result_type test_complists_eq(test_and_log_util::out_type&);
test_and_log_util::result_type test_complists_gr(test_and_log_util::out_type&);
test_and_log_util::result_type test_complists_le(test_and_log_util::out_type&);
test_and_log_util::result_type test_complists_dig_gr(test_and_log_util::out_type&);
test_and_log_util::result_type test_complists_dig_le(test_and_log_util::out_type&);
test_and_log_util::result_type test_complists_eq2(test_and_log_util::out_type&);
test_and_log_util::result_type test_compare_eq(test_and_log_util::out_type&);
test_and_log_util::result_type test_compare_sign_gr(test_and_log_util::out_type&);
test_and_log_util::result_type test_compare_sign_le(test_and_log_util::out_type&);
test_and_log_util::result_type test_compare_gr(test_and_log_util::out_type&);
test_and_log_util::result_type test_compare_le(test_and_log_util::out_type&);
test_and_log_util::result_type test_compare_eq2(test_and_log_util::out_type&);
void test_compare_speed(test_and_log_util::out_type&);

// Addition tests
void setup_arithmetic_variables();
test_and_log_util::result_type test_add_list2_eq0(test_and_log_util::out_type&);
test_and_log_util::result_type test_add_list1_eq0(test_and_log_util::out_type&);
test_and_log_util::result_type test_add_le(test_and_log_util::out_type&);
test_and_log_util::result_type test_add_le2(test_and_log_util::out_type&);
test_and_log_util::result_type test_add(test_and_log_util::out_type&);
void test_add_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_sub_gr(test_and_log_util::out_type&);
test_and_log_util::result_type test_sub_neg(test_and_log_util::out_type&);
test_and_log_util::result_type test_sub_neg2(test_and_log_util::out_type&);
test_and_log_util::result_type test_sub(test_and_log_util::out_type&);
void test_sub_speed(test_and_log_util::out_type&);

// Multiplication tests
test_and_log_util::result_type test_mult_list_1(test_and_log_util::out_type&);
test_and_log_util::result_type test_mult_list_3(test_and_log_util::out_type&);
test_and_log_util::result_type test_mult_list_7(test_and_log_util::out_type&);
void test_mult_list_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_mult_list2_eq0(test_and_log_util::out_type&);
test_and_log_util::result_type test_mult_list1_eq0(test_and_log_util::out_type&);
test_and_log_util::result_type test_mult_list2_eq1(test_and_log_util::out_type&);
test_and_log_util::result_type test_mult_list1_eq1(test_and_log_util::out_type&);
test_and_log_util::result_type test_mult_list2_eqN1(test_and_log_util::out_type&);
test_and_log_util::result_type test_mult_list1_eqN1(test_and_log_util::out_type&);
test_and_log_util::result_type test_mult_zeros(test_and_log_util::out_type&);
test_and_log_util::result_type test_mult(test_and_log_util::out_type&);
void test_mult_speed(test_and_log_util::out_type&);

// Cleanup function to free memory
void cleanup();

void int_operations_test(){
    test_and_log_util test_list("Precision::Volatile::Int_Operations", __FILE__);
        test_list.set_log_output(test_log);
        test_list.set_console_output(test_console);
        test_list.set_assert(false);

    // Comparison tests
    ADD_TEST(test_list, test_complists_eq);
    ADD_TEST(test_list, test_complists_gr);
    ADD_TEST(test_list, test_complists_le);
    ADD_TEST(test_list, test_complists_dig_gr);
    ADD_TEST(test_list, test_complists_dig_le);
    ADD_TEST(test_list, test_complists_eq2);

    ADD_TEST(test_list, test_compare_eq);
    ADD_TEST(test_list, test_compare_sign_gr);
    ADD_TEST(test_list, test_compare_sign_le);
    ADD_TEST(test_list, test_compare_gr);
    ADD_TEST(test_list, test_compare_le);
    ADD_TEST(test_list, test_compare_eq2);
    ADD_TEST_BOTH( test_list,
                   test_compare_eq2, test_compare_speed,
                   1000000
                   );

    // Addition tests
    ADD_TEST(test_list, test_add_list2_eq0);
    ADD_TEST(test_list, test_add_list1_eq0);
    ADD_TEST(test_list, test_add_le);
    ADD_TEST(test_list, test_add_le2);
    ADD_TEST_BOTH( test_list,
                   test_add, test_add_speed,
                   1000000
                   );
    ADD_TEST(test_list, test_sub_gr);
    ADD_TEST(test_list, test_sub_neg);
    ADD_TEST(test_list, test_sub_neg2);
    ADD_TEST_BOTH( test_list,
                   test_sub, test_sub_speed,
                   1000000
                   );

    // Multiplication tests
    ADD_TEST(test_list, test_mult_list_1);
    ADD_TEST(test_list, test_mult_list_3);
    ADD_TEST_BOTH( test_list,
                   test_mult_list_7, test_mult_list_speed,
                   1000000
                   );
    ADD_TEST(test_list, test_mult_list2_eq0);
    ADD_TEST(test_list, test_mult_list1_eq0);
    ADD_TEST(test_list, test_mult_list2_eq1);
    ADD_TEST(test_list, test_mult_list1_eq1);
    ADD_TEST(test_list, test_mult_list2_eqN1);
    ADD_TEST(test_list, test_mult_list1_eqN1);
    ADD_TEST(test_list, test_mult_zeros);
    ADD_TEST_BOTH( test_list,
                   test_mult, test_mult_speed,
                   1000
                   );

    setup_comparison_variables();
    setup_arithmetic_variables();

    test_list.execute_tests();
}

void setup_comparison_variables(){
    func_variable.m_sign.assign(1);
    func_dig_gr_variable.m_sign.assign(-1);
    func_dig_le_variable.m_sign.assign(1);
    func_dig_eq_variable.m_sign.assign(1);
    for(unsigned i = 0; i < 20; ++i){
        func_variable.m_number.push_back(i % 10);
        func_dig_gr_variable.m_number.push_back(i % 10);
        func_dig_le_variable.m_number.push_back(i % 10);
        func_dig_eq_variable.m_number.push_back(i % 10);
    }
    func_dig_gr_variable.m_number.front() = 1;
    func_dig_le_variable.m_number.back() = 8;

    func_gr_variable.m_sign.assign(-1);
    for(unsigned i = 0; i < 22; ++i)
        func_gr_variable.m_number.push_back(i % 10);

    func_le_variable.m_sign.assign(1);
    for(unsigned i = 0; i < 18; ++i)
        func_le_variable.m_number.push_back(i % 10);

    speed_variable.m_sign.assign(-1);
    speed_eq_variable.m_sign.assign(-1);
    for(unsigned i = 0; i < 100; ++i){
        speed_variable.m_number.push_back(i % 10);
        speed_eq_variable.m_number.push_back(i % 10);
    }
}

void setup_arithmetic_variables(){
    all_digs_int.m_sign.make_positive();
    sub_int.m_sign.make_negative();
    for(unsigned i = 0; i < 10; ++i){
        all_digs_int.m_number.push_back(i % 10);
        sub_int.m_number.push_back(0);
    }
    sub_int.m_number.push_back(1);

    less_digs_int.m_sign.make_positive();
    for(unsigned i = 0; i < 5; ++i){
        less_digs_int.m_number.push_back(i % 10);
    }

    sub_le_int.m_number.push_back(0);
    sub_le_int.m_number.push_back(0);
    sub_le_int.m_number.push_back(0);
    sub_le_int.m_number.push_back(1);

    sub_add_digs = all_digs_int;
    sub_add_digs.m_sign.make_negative();

    zero_list_int.m_number.push_back(0);
    zero_list_int.m_sign.make_positive();
    one_list_int.m_number.push_back(1);
    one_list_int.m_sign.make_positive();
    neg_one_int.m_number.push_back(1);
    neg_one_int.m_sign.make_negative();

    mult_fac1.m_sign.make_positive();
    mult_fac1.m_number.push_back(0);
    mult_fac1.m_number.push_back(8);
    mult_fac1.m_number.push_back(6);
    mult_fac1.m_number.push_back(5);
    mult_fac1.m_number.push_back(4);
    mult_fac1.m_number.push_back(3);
    mult_fac1.m_number.push_back(2);
    mult_fac1.m_number.push_back(1);
    mult_fac1.m_number.push_back(0);
    mult_fac1.m_number.push_back(9);
    mult_fac1.m_number.push_back(7);
    mult_fac2.m_sign.make_positive();
    mult_fac2.m_number.push_back(0);
    mult_fac2.m_number.push_back(0);
    mult_fac2.m_number.push_back(9);
    mult_fac2.m_number.push_back(8);
    mult_fac2.m_number.push_back(8);
    mult_fac2.m_number.push_back(8);
    mult_fac2.m_number.push_back(8);
    mult_fac2.m_number.push_back(8);
    mult_fac2.m_number.push_back(8);
    mult_fac2.m_number.push_back(8);
    mult_fac2.m_number.push_back(8);
    mult_fac2.m_number.push_back(8);



    speed_add_var1.m_sign.make_positive();
    speed_add_var2.m_sign.make_positive();
    speed_sub_var.m_sign.make_negative();
    for(unsigned i = 0; i < 100; ++i){
        speed_add_var1.m_number.push_back(i % 10);
        speed_add_var2.m_number.push_back((i*2) % 10);
        speed_sub_var.m_number.push_back((i*3) % 10);
    }

    speed_mult_var1.m_number = Core_Int::diglist_type(5, 0);
    speed_mult_var2.m_number = Core_Int::diglist_type(5, 0);
    for(unsigned i = 0; i < 95; ++i){
        speed_mult_var1.m_number.push_back((i*4) % 10);
        speed_mult_var2.m_number.push_back((i*4) % 10);
    }
}


void cleanup(){
    // Variables for testing comparisons
    func_gr_variable.m_number.clear();
    func_le_variable.m_number.clear();
    func_dig_gr_variable.m_number.clear();
    func_dig_le_variable.m_number.clear();
    func_dig_eq_variable.m_number.clear();
    speed_add_var1.m_number.clear();
    speed_add_var2.m_number.clear();
    speed_sub_var.m_number.clear();

    // Variables for testing arithmetic
    zero_list_int.m_number.clear();
    one_list_int.m_number.clear();
    neg_one_int.m_number.clear();
    all_digs_int.m_number.clear();
    less_digs_int.m_number.clear();
    sub_int.m_number.clear();
    sub_le_int.m_number.clear();
    sub_add_digs.m_number.clear();
    mult_fac1.m_number.clear();
    mult_fac2.m_number.clear();
    speed_variable.m_number.clear();
    speed_eq_variable.m_number.clear();
}

template <typename IntType>
test_and_log_util::str_type to_str(const IntType& num){
    static char const *const digs = "0123456789";
    static char const *const syms = "+-.e /i";

    return Precision::Volatile::Int_Operations::Img::str<IntType>(num, digs, syms);
}

test_and_log_util::str_type comparison_to_string(short res){
    switch(res){
        case -1: return "<";
        case  0: return "==";
        case  1: return ">";
    }
    return "err";
}

test_and_log_util::result_type test_complists_eq(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = comparison_to_string(0);
    res.actual = comparison_to_string(
                     Precision::Volatile::Int_Operations::compare_lists
                     (func_variable.m_number, func_variable.m_number)
                 );

    return res;
}

test_and_log_util::result_type test_complists_gr(test_and_log_util::out_type& o){
    test_and_log_util::result_type res;
    res.expected = comparison_to_string(1);
    res.actual = comparison_to_string(
                     Precision::Volatile::Int_Operations::compare_lists
                     (func_variable.m_number, func_le_variable.m_number)
                 );

    return res;
}

test_and_log_util::result_type test_complists_le(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = comparison_to_string(-1);
    res.actual = comparison_to_string(
                     Precision::Volatile::Int_Operations::compare_lists
                     (func_variable.m_number, func_gr_variable.m_number)
                 );

    return res;
}

test_and_log_util::result_type test_complists_dig_gr(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = comparison_to_string(1);
    res.actual = comparison_to_string(
                     Precision::Volatile::Int_Operations::compare_lists
                     (func_variable.m_number, func_dig_le_variable.m_number)
                 );

    return res;
}

test_and_log_util::result_type test_complists_dig_le(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = comparison_to_string(-1);
    res.actual = comparison_to_string(
                     Precision::Volatile::Int_Operations::compare_lists
                     (func_variable.m_number, func_dig_gr_variable.m_number)
                 );

    return res;
}

test_and_log_util::result_type test_complists_eq2(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = comparison_to_string(0);
    res.actual = comparison_to_string(
                     Precision::Volatile::Int_Operations::compare_lists
                     (func_variable.m_number, func_dig_eq_variable.m_number)
                 );

    return res;
}

test_and_log_util::result_type test_compare_eq(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = comparison_to_string(0);
    res.actual = comparison_to_string(
                     Precision::Volatile::Int_Operations::compare
                     (func_variable, func_variable)
                 );

    return res;
}

test_and_log_util::result_type test_compare_sign_gr(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = comparison_to_string(1);
    res.actual = comparison_to_string(
                     Precision::Volatile::Int_Operations::compare
                     (func_variable, func_gr_variable)
                 );

    return res;
}

test_and_log_util::result_type test_compare_sign_le(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = comparison_to_string(-1);
    res.actual = comparison_to_string(
                     Precision::Volatile::Int_Operations::compare
                     (func_gr_variable, func_variable)
                 );

    return res;
}

test_and_log_util::result_type test_compare_gr(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = comparison_to_string(1);
    res.actual = comparison_to_string(
                     Precision::Volatile::Int_Operations::compare
                     (func_dig_gr_variable, func_gr_variable)
                 );

    return res;
}

test_and_log_util::result_type test_compare_le(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = comparison_to_string(-1);
    res.actual = comparison_to_string(
                     Precision::Volatile::Int_Operations::compare
                     (func_gr_variable, func_dig_gr_variable)
                 );

    return res;
}

test_and_log_util::result_type test_compare_eq2(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = comparison_to_string(0);
    res.actual = comparison_to_string(
                     Precision::Volatile::Int_Operations::compare
                     (func_variable, func_dig_eq_variable)
                 );

    return res;
}

void test_compare_speed(test_and_log_util::out_type&){
    volatile short res = 
        Precision::Volatile::Int_Operations::compare
            (speed_variable, speed_eq_variable);
    res *= 0;
}

test_and_log_util::result_type test_add_list2_eq0(test_and_log_util::out_type&){
    Core_Int add_copy = all_digs_int;

    Precision::Volatile::Int_Operations::add<Core_Int>( add_copy.m_number,
                                                        zero_list_int.m_number,
                                                        add_copy.m_sign,
                                                        zero_list_int.m_sign,
                                                        Core_Int::base()
                                                        );

    test_and_log_util::result_type res;
    res.expected = "+9876543210";
    res.actual = to_str(add_copy);

    return res;
}

test_and_log_util::result_type test_add_list1_eq0(test_and_log_util::out_type&){
    Core_Int add_copy = zero_list_int;

    Precision::Volatile::Int_Operations::add<Core_Int>( add_copy.m_number,
                                                        all_digs_int.m_number,
                                                        add_copy.m_sign,
                                                        all_digs_int.m_sign,
                                                        Core_Int::base()
                                                        );

    test_and_log_util::result_type res;
    res.expected = "+9876543210";
    res.actual = to_str(add_copy);

    return res;
}

test_and_log_util::result_type test_add_le(test_and_log_util::out_type&){
    Core_Int add_copy = all_digs_int;

    Precision::Volatile::Int_Operations::add<Core_Int>( add_copy.m_number,
                                                        less_digs_int.m_number,
                                                        add_copy.m_sign,
                                                        less_digs_int.m_sign,
                                                        Core_Int::base()
                                                        );

    test_and_log_util::result_type res;
    res.expected = "+9876586420";
    res.actual = to_str(add_copy);

    return res;
}

test_and_log_util::result_type test_add_le2(test_and_log_util::out_type&){
    Core_Int add_copy = mult_fac1;

    Precision::Volatile::Int_Operations::add<Core_Int>( add_copy.m_number,
                                                        mult_fac2.m_number,
                                                        add_copy.m_sign,
                                                        mult_fac2.m_sign,
                                                        Core_Int::base()
                                                        );

    test_and_log_util::result_type res;
    res.expected = "+967901234580";
    res.actual = to_str(add_copy);

    return res;
}

test_and_log_util::result_type test_add(test_and_log_util::out_type&){
    Core_Int add_copy = all_digs_int;

    Precision::Volatile::Int_Operations::add<Core_Int>( add_copy.m_number,
                                                        add_copy.m_number,
                                                        add_copy.m_sign,
                                                        add_copy.m_sign,
                                                        Core_Int::base()
                                                        );

    test_and_log_util::result_type res;
    res.expected = "+19753086420";
    res.actual = to_str(add_copy);

    return res;
}

void test_add_speed(test_and_log_util::out_type&){
    Core_Int add1_copy = speed_add_var1;

    Precision::Volatile::Int_Operations::add<Core_Int>( add1_copy.m_number,
                                                        speed_add_var2.m_number,
                                                        add1_copy.m_sign,
                                                        speed_add_var2.m_sign,
                                                        Core_Int::base()
                                                        );
}

test_and_log_util::result_type test_sub_gr(test_and_log_util::out_type&){
    Core_Int add_copy = all_digs_int;

    Precision::Volatile::Int_Operations::add<Core_Int>( add_copy.m_number,
                                                        sub_le_int.m_number,
                                                        add_copy.m_sign,
                                                        sub_int.m_sign,
                                                        Core_Int::base()
                                                        );

    test_and_log_util::result_type res;
    res.expected = "+9876542210";
    res.actual = to_str(add_copy);

    return res;
}

test_and_log_util::result_type test_sub_neg(test_and_log_util::out_type&){
    Core_Int add_copy = sub_int;

    Precision::Volatile::Int_Operations::add<Core_Int>( add_copy.m_number,
                                                        sub_le_int.m_number,
                                                        add_copy.m_sign,
                                                        sub_le_int.m_sign,
                                                        Core_Int::base()
                                                        );

    test_and_log_util::result_type res;
    res.expected = "-10000001000";
    res.actual = to_str(add_copy);

    return res;
}

test_and_log_util::result_type test_sub_neg2(test_and_log_util::out_type&){
    Core_Int add_copy = sub_add_digs;

    Precision::Volatile::Int_Operations::add<Core_Int>( add_copy.m_number,
                                                        sub_add_digs.m_number,
                                                        add_copy.m_sign,
                                                        sub_add_digs.m_sign,
                                                        Core_Int::base()
                                                        );

    test_and_log_util::result_type res;
    res.expected = "-19753086420";
    res.actual = to_str(add_copy);

    return res;
}

test_and_log_util::result_type test_sub(test_and_log_util::out_type&){
    Core_Int add_copy = all_digs_int;

    Precision::Volatile::Int_Operations::add<Core_Int>( add_copy.m_number,
                                                        sub_int.m_number,
                                                        add_copy.m_sign,
                                                        sub_int.m_sign,
                                                        Core_Int::base()
                                                        );

    test_and_log_util::result_type res;
    res.expected = "-123456790";
    res.actual = to_str(add_copy);

    return res;
}

void test_sub_speed(test_and_log_util::out_type&){
    Core_Int add1_copy = speed_add_var1;

    Precision::Volatile::Int_Operations::add<Core_Int>( add1_copy.m_number,
                                                        speed_sub_var.m_number,
                                                        add1_copy.m_sign,
                                                        speed_sub_var.m_sign,
                                                        Core_Int::base()
                                                        );
}

test_and_log_util::result_type test_mult_list_1(test_and_log_util::out_type&){
    Core_Int mult_copy = all_digs_int;

    Precision::Volatile::Int_Operations::multiply_diglist<Core_Int>(mult_copy, 1);

    test_and_log_util::result_type res;
    res.expected = "+9876543210";
    res.actual = to_str(mult_copy);

    return res;
}

test_and_log_util::result_type test_mult_list_3(test_and_log_util::out_type&){
    Core_Int mult_copy = all_digs_int;

    Precision::Volatile::Int_Operations::multiply_diglist<Core_Int>(mult_copy, 3);

    test_and_log_util::result_type res;
    res.expected = "+29629629630";
    res.actual = to_str(mult_copy);

    return res;
}

test_and_log_util::result_type test_mult_list_7(test_and_log_util::out_type&){
    Core_Int mult_copy = all_digs_int;

    Precision::Volatile::Int_Operations::multiply_diglist<Core_Int>(mult_copy, 7);

    test_and_log_util::result_type res;
    res.expected = "+69135802470";
    res.actual = to_str(mult_copy);

    return res;
}

void test_mult_list_speed(test_and_log_util::out_type&){
    Core_Int mult_copy = speed_mult_var1;

    Precision::Volatile::Int_Operations::multiply_diglist<Core_Int>(mult_copy, 9);
}

test_and_log_util::result_type test_mult_list2_eq0(test_and_log_util::out_type&){
    Core_Int mult_copy = all_digs_int;

    Precision::Volatile::Int_Operations::multiply<Core_Int>( mult_copy,
                                                             zero_list_int
                                                             );

    test_and_log_util::result_type res;
    res.expected = "+0";
    res.actual = to_str(mult_copy);

    return res;
}

test_and_log_util::result_type test_mult_list1_eq0(test_and_log_util::out_type&){
    Core_Int mult_copy = zero_list_int;

    Precision::Volatile::Int_Operations::multiply<Core_Int>( mult_copy,
                                                             all_digs_int
                                                             );

    test_and_log_util::result_type res;
    res.expected = "+0";
    res.actual = to_str(mult_copy);

    return res;
}

test_and_log_util::result_type test_mult_list2_eq1(test_and_log_util::out_type&){
    Core_Int mult_copy = all_digs_int;

    Precision::Volatile::Int_Operations::multiply<Core_Int>( mult_copy,
                                                             one_list_int
                                                             );

    test_and_log_util::result_type res;
    res.expected = "+9876543210";
    res.actual = to_str(mult_copy);

    return res;
}

test_and_log_util::result_type test_mult_list1_eq1(test_and_log_util::out_type&){
    Core_Int mult_copy = one_list_int;

    Precision::Volatile::Int_Operations::multiply<Core_Int>( mult_copy,
                                                             all_digs_int
                                                             );

    test_and_log_util::result_type res;
    res.expected = "+9876543210";
    res.actual = to_str(mult_copy);

    return res;
}

test_and_log_util::result_type test_mult_list2_eqN1(test_and_log_util::out_type&){
    Core_Int mult_copy = all_digs_int;

    Precision::Volatile::Int_Operations::multiply<Core_Int>( mult_copy,
                                                             neg_one_int
                                                             );

    test_and_log_util::result_type res;
    res.expected = "-9876543210";
    res.actual = to_str(mult_copy);

    return res;
}

test_and_log_util::result_type test_mult_list1_eqN1(test_and_log_util::out_type&){
    Core_Int mult_copy = neg_one_int;

    Precision::Volatile::Int_Operations::multiply<Core_Int>( mult_copy,
                                                             all_digs_int
                                                             );

    test_and_log_util::result_type res;
    res.expected = "-9876543210";
    res.actual = to_str(mult_copy);

    return res;
}

test_and_log_util::result_type test_mult_zeros(test_and_log_util::out_type&){
    Core_Int mult_copy = all_digs_int;

    Precision::Volatile::Int_Operations::multiply<Core_Int>( mult_copy,
                                                             sub_le_int
                                                             );

    test_and_log_util::result_type res;
    res.expected = "-9876543210000";
    res.actual = to_str(mult_copy);

    return res;
}

test_and_log_util::result_type test_mult(test_and_log_util::out_type&){
    Core_Int mult_copy = all_digs_int;

    Precision::Volatile::Int_Operations::multiply<Core_Int>( mult_copy,
                                                             all_digs_int
                                                             );

    test_and_log_util::result_type res;
    res.expected = "+97546105778997104100";
    res.actual = to_str(mult_copy);

    return res;
}

void test_mult_speed(test_and_log_util::out_type&){
    Core_Int mult1_copy = speed_mult_var1;

    Precision::Volatile::Int_Operations::multiply<Core_Int>( mult1_copy,
                                                             speed_mult_var2
                                                             );
}