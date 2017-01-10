#include "int_operations_test_add.h"

#include "int_operations_test_fake_int.h" // For Core_Int

static Core_Int zero_list_int, one_list_int, neg_one_int,
                all_digs_int, less_digs_int, sub_int,
                sub_le_int, sub_add_digs,
                mult_fac1, mult_fac2
                ;

static Core_Int speed_add_var1, speed_add_var2,
                speed_sub_var
                ;



// Addition tests
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



void setup_addition_variables(){
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

    sub_le_int.make_negative();
    sub_le_int.m_number.push_back(0);
    sub_le_int.m_number.push_back(0);
    sub_le_int.m_number.push_back(0);
    sub_le_int.m_number.push_back(1);

    sub_add_digs = all_digs_int;
    sub_add_digs.make_negative();

    zero_list_int.m_number.push_back(0);
    zero_list_int.make_positive();
    one_list_int.m_number.push_back(1);
    one_list_int.make_positive();
    neg_one_int.m_number.push_back(1);
    neg_one_int.make_negative();


    mult_fac1.make_positive();
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
    mult_fac2.make_positive();
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



    speed_add_var1.make_positive();
    speed_add_var2.make_positive();
    speed_sub_var.make_negative();
    for(unsigned i = 0; i < 100; ++i){
        speed_add_var1.m_number.push_back(i % 10);
        speed_add_var2.m_number.push_back((i*2) % 10);
        speed_sub_var.m_number.push_back((i*3) % 10);
    }
}

void add_addition_tests(test_and_log_util& dest){
    ADD_TEST(dest, test_add_list2_eq0);
    ADD_TEST(dest, test_add_list1_eq0);
    ADD_TEST(dest, test_add_le);
    ADD_TEST(dest, test_add_le2);
    ADD_TEST_BOTH( dest,
                   test_add, test_add_speed,
                   10000
                   );
    ADD_TEST(dest, test_sub_gr);
    ADD_TEST(dest, test_sub_neg);
    ADD_TEST(dest, test_sub_neg2);
    ADD_TEST_BOTH( dest,
                   test_sub, test_sub_speed,
                   10000
                   );
}

// Cleanup function to free memory
void addition_test_cleanup(){
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
    speed_add_var1.m_number.clear();
    speed_add_var2.m_number.clear();
    speed_sub_var.m_number.clear();
}



test_and_log_util::result_type test_add_list2_eq0(test_and_log_util::out_type&){
    Core_Int add_copy = all_digs_int;

    Precision::Volatile::Int_Operations::add(add_copy, zero_list_int);

    test_and_log_util::result_type res;
    res.expected = "+9876543210";
    res.actual = to_str(add_copy);

    return res;
}

test_and_log_util::result_type test_add_list1_eq0(test_and_log_util::out_type&){
    Core_Int add_copy = zero_list_int;

    Precision::Volatile::Int_Operations::add(add_copy, all_digs_int);

    test_and_log_util::result_type res;
    res.expected = "+9876543210";
    res.actual = to_str(add_copy);

    return res;
}

test_and_log_util::result_type test_add_le(test_and_log_util::out_type&){
    Core_Int add_copy = all_digs_int;

    Precision::Volatile::Int_Operations::add(add_copy, less_digs_int);

    test_and_log_util::result_type res;
    res.expected = "+9876586420";
    res.actual = to_str(add_copy);

    return res;
}

test_and_log_util::result_type test_add_le2(test_and_log_util::out_type&){
    Core_Int add_copy = mult_fac1;

    Precision::Volatile::Int_Operations::add(add_copy, mult_fac2);

    test_and_log_util::result_type res;
    res.expected = "+967901234580";
    res.actual = to_str(add_copy);

    return res;
}

test_and_log_util::result_type test_add(test_and_log_util::out_type&){
    Core_Int add_copy = all_digs_int;

    Precision::Volatile::Int_Operations::add(add_copy, add_copy);

    test_and_log_util::result_type res;
    res.expected = "+19753086420";
    res.actual = to_str(add_copy);

    return res;
}

void test_add_speed(test_and_log_util::out_type&){
    Core_Int add1_copy = speed_add_var1;

    Precision::Volatile::Int_Operations::add(add1_copy, speed_add_var2);
}

test_and_log_util::result_type test_sub_gr(test_and_log_util::out_type&){
    Core_Int add_copy = all_digs_int;

    Precision::Volatile::Int_Operations::add(add_copy, sub_le_int);

    test_and_log_util::result_type res;
    res.expected = "+9876542210";
    res.actual = to_str(add_copy);

    return res;
}

test_and_log_util::result_type test_sub_neg(test_and_log_util::out_type&){
    Core_Int add_copy = sub_int;

    Precision::Volatile::Int_Operations::add(add_copy, sub_le_int);

    test_and_log_util::result_type res;
    res.expected = "-10000001000";
    res.actual = to_str(add_copy);

    return res;
}

test_and_log_util::result_type test_sub_neg2(test_and_log_util::out_type&){
    Core_Int add_copy = sub_add_digs;

    Precision::Volatile::Int_Operations::add(add_copy, sub_add_digs);

    test_and_log_util::result_type res;
    res.expected = "-19753086420";
    res.actual = to_str(add_copy);

    return res;
}

test_and_log_util::result_type test_sub(test_and_log_util::out_type&){
    Core_Int add_copy = all_digs_int;

    Precision::Volatile::Int_Operations::add(add_copy, sub_int);

    test_and_log_util::result_type res;
    res.expected = "-123456790";
    res.actual = to_str(add_copy);

    return res;
}

void test_sub_speed(test_and_log_util::out_type&){
    Core_Int add1_copy = speed_add_var1;

    Precision::Volatile::Int_Operations::add(add1_copy, speed_sub_var);
}
