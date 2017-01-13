#include "int_operations_test_bit.h"

#include "int_operations_test_fake_int.h" // For Core_Int

static Core_Int all_digs_int, all_digs_rev, rev_int2,
                power_int, power_int2, zero_list_int
                ;
static Core_Int speed_bit_int, speed_bit_rev, speed_exp_pow;



// Bitwise tests
test_and_log_util::result_type test_bit_comp_inf(test_and_log_util::out_type&);
test_and_log_util::result_type test_bit_comp(test_and_log_util::out_type&);
void test_bit_comp_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_bit_and_spec_eq(test_and_log_util::out_type&);
test_and_log_util::result_type test_bit_and_eq(test_and_log_util::out_type&);
test_and_log_util::result_type test_bit_or_eq(test_and_log_util::out_type&);
test_and_log_util::result_type test_bit_xor_eq(test_and_log_util::out_type&);
void test_bit_oper_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_bit_lshift_dig(test_and_log_util::out_type&);
test_and_log_util::result_type test_bit_rshift_dig(test_and_log_util::out_type&);
test_and_log_util::result_type test_bit_lshift(test_and_log_util::out_type&);
void test_bit_lshift_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_bit_rshift(test_and_log_util::out_type&);
void test_bit_rshift_speed(test_and_log_util::out_type&);



void setup_bitwise_variables(){
    all_digs_int.make_positive();
    all_digs_rev.make_negative();
    for(unsigned i = 0; i < 10; ++i){
        all_digs_int.m_number.push_back(i % 10);
        if(i < 9) all_digs_rev.m_number.push_back(10 - 1 - (i % 10));
        else      all_digs_rev.m_number.push_back(1);
    }

    rev_int2.m_number = Core_Int::diglist_type({9, 8, 7, 6, 5, 4, 3, 2, 1});
    rev_int2.make_positive();

    power_int.m_number.push_back(0);
    power_int.m_number.push_back(5);
    power_int.make_positive();

    power_int2.m_number.push_back(5);
    power_int2.m_number.push_back(2);
    power_int2.make_positive();

    zero_list_int.m_number.push_back(0);
    zero_list_int.make_positive();

    speed_bit_int.make_positive();
    speed_bit_rev.make_negative();
    for(unsigned i = 0; i < 100; ++i){
        speed_bit_int.m_number.push_back(i % 10);
        if(i < 9) speed_bit_rev.m_number.push_back(10 - 1 - (i % 10));
        else      speed_bit_rev.m_number.push_back(1);
    }

    speed_exp_pow.m_number.push_back(0);
    speed_exp_pow.m_number.push_back(0);
    speed_exp_pow.m_number.push_back(0);
    speed_exp_pow.m_number.push_back(0);
    speed_exp_pow.m_number.push_back(1);
    speed_exp_pow.make_positive();
}

void add_bitwise_tests(test_and_log_util& dest){
    ADD_TEST(dest, test_bit_comp_inf);
    ADD_TEST_BOTH( dest,
                   test_bit_comp, test_bit_comp_speed,
                   1
                   );
    ADD_TEST(dest, test_bit_and_spec_eq);
    ADD_TEST(dest, test_bit_and_eq);
    ADD_TEST(dest, test_bit_or_eq);
    ADD_TEST_BOTH( dest,
                   test_bit_xor_eq, test_bit_oper_speed,
                   1
                   );
    ADD_TEST_BOTH( dest,
                   test_bit_lshift, test_bit_lshift_speed,
                   1
                   );
    ADD_TEST_BOTH( dest,
                   test_bit_rshift, test_bit_rshift_speed,
                   1
                   );
}

// Cleanup function to free memory
void bitwise_test_cleanup(){
    all_digs_int.m_number.clear();
    all_digs_rev.m_number.clear();
    rev_int2.m_number.clear();
    power_int.m_number.clear();
    power_int2.m_number.clear();
    zero_list_int.m_number.clear();
    speed_bit_int.m_number.clear();
    speed_bit_rev.m_number.clear();
    speed_exp_pow.m_number.clear();
}



test_and_log_util::result_type test_bit_comp_inf(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "Precision::Volatile::Int_Operations::operator~"
                   "(const IntType&) ~ Insufficient memory."
                   ;
    res.actual = "No exception caught";

    try{
        Core_Int bit_copy = zero_list_int;
        Precision::Volatile::Int_Operations::bitwise_complement(bit_copy);
    } catch(const std::exception& err){
        res.actual = err.what();
    }

    return res;
}

test_and_log_util::result_type test_bit_comp(test_and_log_util::out_type&){
    Core_Int bit_copy = all_digs_int;

    Precision::Volatile::Int_Operations::bitwise_complement(bit_copy);

    test_and_log_util::result_type res;
    res.expected = "-7303325973";
    res.actual = to_str(bit_copy);

    return res;
}

void test_bit_comp_speed(test_and_log_util::out_type&){
    Core_Int bit_copy = speed_bit_int;

    Precision::Volatile::Int_Operations::bitwise_complement(bit_copy);
}

test_and_log_util::result_type test_bit_and_spec_eq(test_and_log_util::out_type&){
    Core_Int bit_copy = all_digs_int;

    Precision::Volatile::Int_Operations::bitwise_and_eq(bit_copy, rev_int2);

    test_and_log_util::result_type res;
    res.expected = "+68158464";
    res.actual = to_str(bit_copy);

    return res;
}

test_and_log_util::result_type test_bit_and_eq(test_and_log_util::out_type&){
    Core_Int bit_copy = all_digs_int;

    Precision::Volatile::Int_Operations::bitwise_and_eq(bit_copy, all_digs_rev);

    test_and_log_util::result_type res;
    res.expected = "+1085281792";
    res.actual = to_str(bit_copy);

    return res;
}

test_and_log_util::result_type test_bit_or_eq(test_and_log_util::out_type&){
    Core_Int bit_copy = all_digs_int;

    Precision::Volatile::Int_Operations::bitwise_or_eq(bit_copy, all_digs_rev);

    test_and_log_util::result_type res;
    res.expected = "-9914718207";
    res.actual = to_str(bit_copy);

    return res;
}

test_and_log_util::result_type test_bit_xor_eq(test_and_log_util::out_type&){
    Core_Int bit_copy = all_digs_int;
    bit_copy.make_negative();

    Precision::Volatile::Int_Operations::bitwise_xor_eq(bit_copy, all_digs_rev);

    test_and_log_util::result_type res;
    res.expected = "+8829436415";
    res.actual = to_str(bit_copy);

    return res;
}

void test_bit_oper_speed(test_and_log_util::out_type&){
    Core_Int bit_copy = speed_bit_int;

    Precision::Volatile::Int_Operations::bitwise_xor_eq
                                         (bit_copy, speed_bit_rev);
}

test_and_log_util::result_type test_bit_lshift(test_and_log_util::out_type&){
    Core_Int bit_copy = all_digs_int;

    Precision::Volatile::Int_Operations::bitwise_lshift_eq(bit_copy, power_int);

    test_and_log_util::result_type res;
    res.expected = "+11119999080066150605783040";
    res.actual = to_str(bit_copy);

    return res;
}

void test_bit_lshift_speed(test_and_log_util::out_type&){
    Core_Int bit_copy = speed_bit_int;

    Precision::Volatile::Int_Operations::bitwise_lshift_eq(bit_copy, speed_exp_pow);
}

test_and_log_util::result_type test_bit_rshift(test_and_log_util::out_type&){
    Core_Int bit_copy = all_digs_int;

    Precision::Volatile::Int_Operations::bitwise_rshift_eq(bit_copy, power_int2);

    test_and_log_util::result_type res;
    res.expected = "+294";
    res.actual = to_str(bit_copy);

    return res;
}

void test_bit_rshift_speed(test_and_log_util::out_type&){
    Core_Int bit_copy = speed_bit_int;

    Precision::Volatile::Int_Operations::bitwise_rshift_eq(bit_copy, speed_exp_pow);
}