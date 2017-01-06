#include "int_operations_test_div.h"

#include "int_operations_test_fake_int.h" // For Core_Int

static Core_Int zero_list_int, one_list_int,
                twos_int, hundred_int,
                all_digs_int, sub_int, less_digs_int,
                div_fac
                ;

static Core_Int speed_add_var1, speed_div_var;



// Division and Modulus tests
test_and_log_util::result_type test_div0(test_and_log_util::out_type&);
test_and_log_util::result_type test_div_list2_eq1(test_and_log_util::out_type&);
test_and_log_util::result_type test_div_eq(test_and_log_util::out_type&);
test_and_log_util::result_type test_div_gr(test_and_log_util::out_type&);
test_and_log_util::result_type test_div_list1_neg(test_and_log_util::out_type&);
test_and_log_util::result_type test_div_list2_neg(test_and_log_util::out_type&);
test_and_log_util::result_type test_div_ones(test_and_log_util::out_type&);
test_and_log_util::result_type test_div_dig_gr(test_and_log_util::out_type&);
test_and_log_util::result_type test_div_2_by_100(test_and_log_util::out_type&);
test_and_log_util::result_type test_div(test_and_log_util::out_type&);
void test_div_speed(test_and_log_util::out_type&);



void setup_division_variables(){
    all_digs_int.make_positive();
    sub_int.make_negative();
    for(unsigned i = 0; i < 10; ++i){
        all_digs_int.m_number.push_back(i % 10);
        sub_int.m_number.push_back(0);
    }
    sub_int.m_number.push_back(1);

    less_digs_int.make_positive();
    for(unsigned i = 0; i < 5; ++i){
        less_digs_int.m_number.push_back(i % 10);
    }

    zero_list_int.m_number.push_back(0);
    zero_list_int.make_positive();
    one_list_int.m_number.push_back(1);
    one_list_int.make_positive();

    twos_int.make_two();

    hundred_int.m_number.push_back(0);
    hundred_int.m_number.push_back(0);
    hundred_int.m_number.push_back(1);
    hundred_int.make_positive();

    div_fac.make_positive();
    div_fac.m_number = Core_Int::diglist_type(4, 3);

    speed_add_var1.make_positive();
    for(unsigned i = 0; i < 100; ++i)
        speed_add_var1.m_number.push_back(i % 10);

    speed_div_var.make_positive();
    speed_div_var.m_number.push_back(7);
}

void add_division_tests(test_and_log_util& dest){
    ADD_TEST(dest, test_div0);
    ADD_TEST(dest, test_div_list2_eq1);
    ADD_TEST(dest, test_div_eq);
    ADD_TEST(dest, test_div_gr);
    ADD_TEST(dest, test_div_list1_neg);
    ADD_TEST(dest, test_div_list2_neg);
    ADD_TEST(dest, test_div_ones);
    ADD_TEST(dest, test_div_dig_gr);
    ADD_TEST(dest, test_div_2_by_100);
    ADD_TEST_BOTH( dest,
                   test_div, test_div_speed,
                   1000
                   );
}

// Cleanup function to free memory
void division_test_cleanup(){
    all_digs_int.m_number.clear();
    sub_int.m_number.clear();
    less_digs_int.m_number.clear();
    one_list_int.m_number.clear();
    zero_list_int.m_number.clear();
    twos_int.m_number.clear();
    hundred_int.m_number.clear();
    div_fac.m_number.clear();
    speed_add_var1.m_number.clear();
    speed_div_var.m_number.clear();
}



test_and_log_util::result_type test_div0(test_and_log_util::out_type&){

    test_and_log_util::result_type res;
    res.expected = "Precision::Volatile::Int_Operations::divide_mod"
                   "(const IntType&, const IntType&, IntType&, IntType&)"
                   " ~ Division by zero attempt."
                   ;
    res.actual = "No exception thrown.";

    Core_Int div_copy = all_digs_int;
    Core_Int div_result, mod_result;

    try {
        Precision::Volatile::Int_Operations::divide_mod<Core_Int>( div_copy,
                                                                   zero_list_int,
                                                                   div_result,
                                                                   mod_result
                                                                   );
    }catch(const std::exception& err){
        res.actual = err.what();
    }

    return res;
}

test_and_log_util::result_type test_div_list2_eq1(test_and_log_util::out_type&){
    Core_Int div_copy = all_digs_int;
    Core_Int div_res, mod_res;

    Precision::Volatile::Int_Operations::divide_mod<Core_Int>( div_copy,
                                                               one_list_int,
                                                               div_res,
                                                               mod_res
                                                               );

    test_and_log_util::result_type res;
    res.expected = "Q = +9876543210 M = +0";
    res.actual = "Q = " + to_str(div_res) + " M = " + to_str(mod_res);

    return res;
}

test_and_log_util::result_type test_div_eq(test_and_log_util::out_type&){
    Core_Int div_copy = all_digs_int;
    Core_Int div_res, mod_res;

    Precision::Volatile::Int_Operations::divide_mod<Core_Int>( div_copy,
                                                               all_digs_int,
                                                               div_res,
                                                               mod_res
                                                               );

    test_and_log_util::result_type res;
    res.expected = "Q = +1 M = +0";
    res.actual = "Q = " + to_str(div_res) + " M = " + to_str(mod_res);

    return res;
}

test_and_log_util::result_type test_div_gr(test_and_log_util::out_type&){
    Core_Int div_copy = less_digs_int;
    Core_Int div_res, mod_res;

    Precision::Volatile::Int_Operations::divide_mod<Core_Int>( div_copy,
                                                               all_digs_int,
                                                               div_res,
                                                               mod_res
                                                               );

    test_and_log_util::result_type res;
    res.expected = "Q = +0 M = " + to_str(less_digs_int);
    res.actual = "Q = " + to_str(div_res) + " M = " + to_str(mod_res);

    return res;
}

test_and_log_util::result_type test_div_list1_neg(test_and_log_util::out_type& out){
    Core_Int div_copy = all_digs_int, div2_copy = less_digs_int;
    div_copy.make_negative();
    Core_Int div_res, mod_res;

    Precision::Volatile::Int_Operations::divide_mod<Core_Int>( div_copy,
                                                               div2_copy,
                                                               div_res,
                                                               mod_res
                                                               );

    test_and_log_util::result_type res;
    res.expected = "Q = -228570 M = -33510";
    res.actual = "Q = " + to_str(div_res) + " M = " + to_str(mod_res);

    return res;
}

test_and_log_util::result_type test_div_list2_neg(test_and_log_util::out_type&){
    Core_Int div_copy = all_digs_int, div2_copy = less_digs_int;
    div2_copy.make_negative();
    Core_Int div_res, mod_res;

    Precision::Volatile::Int_Operations::divide_mod<Core_Int>( div_copy,
                                                               div2_copy,
                                                               div_res,
                                                               mod_res
                                                               );

    test_and_log_util::result_type res;
    res.expected = "Q = -228570 M = -33510";
    res.actual = "Q = " + to_str(div_res) + " M = " + to_str(mod_res);

    return res;
}

test_and_log_util::result_type test_div_ones(test_and_log_util::out_type&){
    Core_Int div_copy = all_digs_int;
    Core_Int div_res, mod_res;

    Precision::Volatile::Int_Operations::divide_mod<Core_Int>( div_copy,
                                                               div_fac,
                                                               div_res,
                                                               mod_res
                                                               );

    test_and_log_util::result_type res;
    res.expected = "Q = +2963259 M = +963";
    res.actual = "Q = " + to_str(div_res) + " M = " + to_str(mod_res);

    return res;
}

test_and_log_util::result_type test_div_dig_gr(test_and_log_util::out_type&){
    Core_Int div_copy = sub_int;
    Core_Int div_res, mod_res;

    Precision::Volatile::Int_Operations::divide_mod<Core_Int>( div_copy,
                                                               div_fac,
                                                               div_res,
                                                               mod_res
                                                               );

    test_and_log_util::result_type res;
    res.expected = "Q = -3000300 M = -100";
    res.actual = "Q = " + to_str(div_res) + " M = " + to_str(mod_res);

    return res;
}

test_and_log_util::result_type test_div_2_by_100(test_and_log_util::out_type&){
    Core_Int div_copy = hundred_int;
    Core_Int div_res, mod_res;

    Precision::Volatile::Int_Operations::divide_mod<Core_Int>( div_copy,
                                                               twos_int,
                                                               div_res,
                                                               mod_res
                                                               );

    test_and_log_util::result_type res;
    res.expected = "Q = +50 M = +0";
    res.actual = "Q = " + to_str(div_res) + " M = " + to_str(mod_res);

    return res;
}

test_and_log_util::result_type test_div(test_and_log_util::out_type&){
    Core_Int div_copy = all_digs_int;
    Core_Int div_res, mod_res;

    Precision::Volatile::Int_Operations::divide_mod<Core_Int>( div_copy,
                                                               less_digs_int,
                                                               div_res,
                                                               mod_res
                                                               );

    test_and_log_util::result_type res;
    res.expected = "Q = +228570 M = +33510";
    res.actual = "Q = " + to_str(div_res) + " M = " + to_str(mod_res);

    return res;
}

void test_div_speed(test_and_log_util::out_type&){
    Core_Int div_copy = speed_add_var1;
    Core_Int div_result, mod_result;

    Precision::Volatile::Int_Operations::divide_mod<Core_Int>( div_copy,
                                                               speed_div_var,
                                                               div_result,
                                                               mod_result
                                                               );
}
