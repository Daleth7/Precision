#include "int_operations_test_mult.h"

#include "int_operations_test_fake_int.h" // For Core_Int

static Core_Int all_digs_int, sub_le_int,
                zero_list_int, one_list_int, neg_one_int
                ;

                // Variables for testing comparisons
static Core_Int speed_mult_var1, speed_mult_var2;



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



void setup_multiplication_variables(){
    all_digs_int.make_positive();
    for(unsigned i = 0; i < 10; ++i)
        all_digs_int.m_number.push_back(i % 10);

    sub_le_int.make_negative();
    sub_le_int.m_number.push_back(0);
    sub_le_int.m_number.push_back(0);
    sub_le_int.m_number.push_back(0);
    sub_le_int.m_number.push_back(1);

    zero_list_int.m_number.push_back(0);
    zero_list_int.make_positive();
    one_list_int.m_number.push_back(1);
    one_list_int.make_positive();
    neg_one_int.m_number.push_back(1);
    neg_one_int.make_negative();

    speed_mult_var1.m_number = Core_Int::digstr_type(5, 0);
    speed_mult_var2.m_number = Core_Int::digstr_type(5, 0);
    for(unsigned i = 0; i < 95; ++i){
        speed_mult_var1.m_number.push_back((i*4) % 10);
        speed_mult_var2.m_number.push_back((i*4) % 10);
    }
}

void add_multiplication_tests(test_and_log_util& dest){
    ADD_TEST(dest, test_mult_list_1);
    ADD_TEST(dest, test_mult_list_3);
    ADD_TEST_BOTH( dest,
                   test_mult_list_7, test_mult_list_speed,
                   10000
                   );
    ADD_TEST(dest, test_mult_list2_eq0);
    ADD_TEST(dest, test_mult_list1_eq0);
    ADD_TEST(dest, test_mult_list2_eq1);
    ADD_TEST(dest, test_mult_list1_eq1);
    ADD_TEST(dest, test_mult_list2_eqN1);
    ADD_TEST(dest, test_mult_list1_eqN1);
    ADD_TEST(dest, test_mult_zeros);
    ADD_TEST_BOTH( dest,
                   test_mult, test_mult_speed,
                   1000
                   );
}

// Cleanup function to free memory
void multiplication_test_cleanup(){
    all_digs_int.m_number.clear();
    sub_le_int.m_number.clear();
    zero_list_int.m_number.clear();
    one_list_int.m_number.clear();
    neg_one_int.m_number.clear();
    speed_mult_var1.m_number.clear();
    speed_mult_var2.m_number.clear();
}



test_and_log_util::result_type test_mult_list_1(test_and_log_util::out_type&){
    Core_Int mult_copy = all_digs_int;

    Precision::Volatile::Int_Operations::multiply_factor<Core_Int>(mult_copy, 1);

    test_and_log_util::result_type res;
    res.expected = "+9876543210";
    res.actual = to_str(mult_copy);

    return res;
}

test_and_log_util::result_type test_mult_list_3(test_and_log_util::out_type&){
    Core_Int mult_copy = all_digs_int;

    Precision::Volatile::Int_Operations::multiply_factor<Core_Int>(mult_copy, 3);

    test_and_log_util::result_type res;
    res.expected = "+29629629630";
    res.actual = to_str(mult_copy);

    return res;
}

test_and_log_util::result_type test_mult_list_7(test_and_log_util::out_type&){
    Core_Int mult_copy = all_digs_int;

    Precision::Volatile::Int_Operations::multiply_factor<Core_Int>(mult_copy, 7);

    test_and_log_util::result_type res;
    res.expected = "+69135802470";
    res.actual = to_str(mult_copy);

    return res;
}

void test_mult_list_speed(test_and_log_util::out_type&){
    Core_Int mult_copy = speed_mult_var1;

    Precision::Volatile::Int_Operations::multiply_factor<Core_Int>(mult_copy, 9);
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
