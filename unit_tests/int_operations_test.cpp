#include "Test_Shared_Utilities.h"

#include "general_base/impl/Precision_Int_Operations.h"
#include "general_base/Precision_Sign_Class.h"

#include <vector>

struct Fake_Int{
    using size_type    = std::size_t;
    using digit_type   = std::uint_fast8_t;
    using diglist_type = std::vector<digit_type>;
    using sign_type    = Precision::SignClass;

    bool is_zero()const
        {return m_number.size() == 1 && m_number.front() == 0;}
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



    diglist_type m_number;
    sign_type m_sign;
};

static Fake_Int func_variable,
                func_gr_variable, func_le_variable,
                func_dig_gr_variable, func_dig_le_variable,
                func_dig_eq_variable
                ;
static Fake_Int speed_variable,
                speed_eq_variable
                ;

void setup();

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

void int_operations_test(){
    test_and_log_util test_list("Precision::Volatile::Int_Operations", __FILE__);
        test_list.set_log_output(test_log);
        test_list.set_console_output(test_console);
        test_list.set_assert(false);

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

    setup();

    test_list.execute_tests();
}

void setup(){
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
