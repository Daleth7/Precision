#include "int_operations_test_log.h"

#include "int_operations_test_fake_int.h" // For Core_Int

static Core_Int all_digs_int, all_digs_rev;
static Core_Int speed_log_int, speed_log_rev;



// Logical tests
test_and_log_util::result_type test_log_comp(test_and_log_util::out_type&);
void test_log_comp_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_log_and_eq(test_and_log_util::out_type&);
test_and_log_util::result_type test_log_or_eq(test_and_log_util::out_type&);
test_and_log_util::result_type test_log_xor_eq(test_and_log_util::out_type&);
void test_log_oper_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_log_xor_rev_eq(test_and_log_util::out_type&);
void test_log_xor_rev_oper_speed(test_and_log_util::out_type&);



void setup_logical_variables(){
    all_digs_int.make_positive();
    all_digs_rev.make_negative();
    for(unsigned i = 0; i < 10; ++i){
        all_digs_int.m_number.push_back(i % 10);
        if(i < 9) all_digs_rev.m_number.push_back(10 - 1 - (i % 10));
        else      all_digs_rev.m_number.push_back(1);
    }

    speed_log_int.make_positive();
    speed_log_rev.make_negative();
    for(unsigned i = 0; i < 100; ++i){
        speed_log_int.m_number.push_back(i % 10);
        if(i < 9) speed_log_rev.m_number.push_back(10 - 1 - (i % 10));
        else      speed_log_rev.m_number.push_back(1);
    }
}

void add_logical_tests(test_and_log_util& dest){
    ADD_TEST_BOTH( dest,
                   test_log_comp, test_log_comp_speed,
                   10000
                   );
    ADD_TEST(dest, test_log_and_eq);
    ADD_TEST(dest, test_log_or_eq);
    ADD_TEST_BOTH( dest,
                   test_log_xor_eq, test_log_oper_speed,
                   10000
                   );
    ADD_TEST_BOTH( dest,
                   test_log_xor_rev_eq, test_log_xor_rev_oper_speed,
                   10000
                   );
}

// Cleanup function to free memory
void logical_test_cleanup(){
    all_digs_int.m_number.clear();
    all_digs_rev.m_number.clear();
    speed_log_int.m_number.clear();
    speed_log_rev.m_number.clear();
}




test_and_log_util::result_type test_log_comp(test_and_log_util::out_type&){
    Core_Int log_copy = all_digs_int;

    Precision::Volatile::Int_Operations::logical_complement_eq(log_copy);

    test_and_log_util::result_type res;
    res.expected = "-123456789";
    res.actual = to_str(log_copy);

    return res;
}

void test_log_comp_speed(test_and_log_util::out_type&){
    Core_Int log_copy = speed_log_int;

    Precision::Volatile::Int_Operations::logical_complement_eq(log_copy);
}

test_and_log_util::result_type test_log_and_eq(test_and_log_util::out_type&){
    Core_Int log_copy = all_digs_int;

    Precision::Volatile::Int_Operations::logical_and_eq(log_copy, all_digs_rev);

    test_and_log_util::result_type res;
    res.expected = "+9848008480";
    res.actual = to_str(log_copy);

    return res;
}

test_and_log_util::result_type test_log_or_eq(test_and_log_util::out_type&){
    Core_Int log_copy = all_digs_int;

    Precision::Volatile::Int_Operations::logical_or_eq(log_copy, all_digs_rev);

    test_and_log_util::result_type res;
    res.expected = "-9151991519";
    res.actual = to_str(log_copy);

    return res;
}

test_and_log_util::result_type test_log_xor_eq(test_and_log_util::out_type&){
    Core_Int log_copy = all_digs_int;
    log_copy.make_negative();

    Precision::Volatile::Int_Operations::logical_xor_eq(log_copy, all_digs_rev);

    test_and_log_util::result_type res;
    res.expected = "+999999999";
    res.actual = to_str(log_copy);

    return res;
}

void test_log_oper_speed(test_and_log_util::out_type&){
    Core_Int log_copy = speed_log_int;

    Precision::Volatile::Int_Operations::logical_xor_eq(log_copy, speed_log_rev);
}

test_and_log_util::result_type test_log_xor_rev_eq(test_and_log_util::out_type&){
    Core_Int log_copy = all_digs_int;
    log_copy.make_negative();

    Precision::Volatile::Int_Operations::logical_xor_eq(log_copy, all_digs_rev);

    Precision::Volatile::Int_Operations::logical_xor_rev_eq(log_copy, all_digs_rev);

    test_and_log_util::result_type res;
    res.expected = "-9876543210";
    res.actual = to_str(log_copy);

    return res;
}

void test_log_xor_rev_oper_speed(test_and_log_util::out_type&){
    Core_Int log_copy = speed_log_int;

    Precision::Volatile::Int_Operations::logical_xor_rev_eq(log_copy, speed_log_rev);
}