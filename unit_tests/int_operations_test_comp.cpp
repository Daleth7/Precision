#include "int_operations_test_comp.h"

#include "int_operations_test_fake_int.h" // For Core_Int

static Core_Int func_variable,
                func_gr_variable, func_le_variable,
                func_dig_gr_variable, func_dig_le_variable,
                func_dig_eq_variable
                ;

static Core_Int speed_variable, speed_eq_variable;



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



void setup_comparison_variables(){
    func_variable.sign(1);
    func_dig_gr_variable.sign(-1);
    func_dig_le_variable.sign(1);
    func_dig_eq_variable.sign(1);
    for(unsigned i = 0; i < 20; ++i){
        func_variable.m_number.push_back(i % 10);
        func_dig_gr_variable.m_number.push_back(i % 10);
        func_dig_le_variable.m_number.push_back(i % 10);
        func_dig_eq_variable.m_number.push_back(i % 10);
    }
    func_dig_gr_variable.m_number.front() = 1;
    func_dig_le_variable.m_number.back() = 8;

    func_gr_variable.sign(-1);
    for(unsigned i = 0; i < 22; ++i)
        func_gr_variable.m_number.push_back(i % 10);

    func_le_variable.sign(1);
    for(unsigned i = 0; i < 18; ++i)
        func_le_variable.m_number.push_back(i % 10);

    speed_variable.sign(-1);
    speed_eq_variable.sign(-1);
    for(unsigned i = 0; i < 100; ++i){
        speed_variable.m_number.push_back(i % 10);
        speed_eq_variable.m_number.push_back(i % 10);
    }
}

void add_comparison_tests(test_and_log_util& dest){
    ADD_TEST(dest, test_complists_eq);
    ADD_TEST(dest, test_complists_gr);
    ADD_TEST(dest, test_complists_le);
    ADD_TEST(dest, test_complists_dig_gr);
    ADD_TEST(dest, test_complists_dig_le);
    ADD_TEST(dest, test_complists_eq2);

    ADD_TEST(dest, test_compare_eq);
    ADD_TEST(dest, test_compare_sign_gr);
    ADD_TEST(dest, test_compare_sign_le);
    ADD_TEST(dest, test_compare_gr);
    ADD_TEST(dest, test_compare_le);
    ADD_TEST(dest, test_compare_eq2);
    ADD_TEST_BOTH( dest,
                   test_compare_eq2, test_compare_speed,
                   10000
                   );
}

// Cleanup function to free memory
void comparison_test_cleanup(){
    func_gr_variable.m_number.clear();
    func_le_variable.m_number.clear();
    func_dig_gr_variable.m_number.clear();
    func_dig_le_variable.m_number.clear();
    func_dig_eq_variable.m_number.clear();
    speed_variable.m_number.clear();
    speed_eq_variable.m_number.clear();
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
