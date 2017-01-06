#include "int_operations_test_exp.h"

#include "int_operations_test_fake_int.h" // For Core_Int

static Core_Int twos_int, power_int, sixteen_int, odd_power_int, thousands_int,
                zero_list_int, one_list_int, neg_one_int
                ;
static Core_Int speed_exp_base, speed_exp_pow;



// Exponentiation tests
test_and_log_util::result_type test_exp_ind(test_and_log_util::out_type&);
test_and_log_util::result_type test_exp_e0(test_and_log_util::out_type&);
test_and_log_util::result_type test_exp_e1(test_and_log_util::out_type&);
test_and_log_util::result_type test_exp_eN1(test_and_log_util::out_type&);
test_and_log_util::result_type test_exp_odd_power(test_and_log_util::out_type&);
test_and_log_util::result_type test_exp_10000(test_and_log_util::out_type&);
test_and_log_util::result_type test_exp(test_and_log_util::out_type&);
void test_exp_speed(test_and_log_util::out_type&);



void setup_exponentiation_variables(){
    twos_int.make_two();

    power_int.m_number.push_back(0);
    power_int.m_number.push_back(0);
    power_int.m_number.push_back(1);
    power_int.make_positive();

    sixteen_int.m_number.push_back(6);
    sixteen_int.m_number.push_back(1);
    sixteen_int.make_positive();

    odd_power_int.m_number.push_back(7);
    odd_power_int.m_number.push_back(1);
    odd_power_int.make_positive();

    thousands_int.m_number.push_back(0);
    thousands_int.m_number.push_back(0);
    thousands_int.m_number.push_back(0);
    thousands_int.m_number.push_back(0);
    thousands_int.m_number.push_back(0);
    thousands_int.m_number.push_back(1);
    thousands_int.make_positive();

    zero_list_int.m_number.push_back(0);
    zero_list_int.make_positive();
    one_list_int.m_number.push_back(1);
    one_list_int.make_positive();
    neg_one_int.m_number.push_back(1);
    neg_one_int.make_negative();

    speed_exp_base.make_positive();
    for(unsigned i = 0; i < 10; ++i)
        speed_exp_base.m_number.push_back(i % 10);

    speed_exp_pow.m_number.push_back(0);
    speed_exp_pow.m_number.push_back(0);
    speed_exp_pow.m_number.push_back(1);
    speed_exp_pow.make_positive();
}

void add_exponentiation_tests(test_and_log_util& dest){
    ADD_TEST(dest, test_exp_ind);
    ADD_TEST(dest, test_exp_e0);
    ADD_TEST(dest, test_exp_e1);
    ADD_TEST(dest, test_exp_eN1);
    ADD_TEST(dest, test_exp_odd_power);
//    ADD_TEST(dest, test_exp_10000); // Warning: takes more than 1 minute
    ADD_TEST_BOTH( dest,
                   test_exp, test_exp_speed,
                   25
                   );
}

// Cleanup function to free memory
void exponentiation_test_cleanup(){
    twos_int.m_number.clear();
    power_int.m_number.clear();
    sixteen_int.m_number.clear();
    odd_power_int.m_number.clear();
    thousands_int.m_number.clear();
    zero_list_int.m_number.clear();
    one_list_int.m_number.clear();
    neg_one_int.m_number.clear();
    speed_exp_base.m_number.clear();
    speed_exp_pow.m_number.clear();
}



test_and_log_util::result_type test_exp_ind(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "Precision::Volatile::Int_Operations::"
                   "exponentiate(const IntType&, const IntType&)"
                   " ~ Indeterminate result."
                   ;
    res.actual = "No exception caught";

    try{
        Core_Int exp_copy = zero_list_int;
        Precision::Volatile::Int_Operations::exponentiate(exp_copy, zero_list_int);
    } catch(const std::exception& err){
        res.actual = err.what();
    }

    return res;
}

test_and_log_util::result_type test_exp_e0(test_and_log_util::out_type&){
    Core_Int exp_copy = speed_exp_base;

    Precision::Volatile::Int_Operations::exponentiate(exp_copy, zero_list_int);

    test_and_log_util::result_type res;
    res.expected = "+1";
    res.actual = to_str(exp_copy);

    return res;
}

test_and_log_util::result_type test_exp_e1(test_and_log_util::out_type&){
    Core_Int exp_copy = speed_exp_base;

    Precision::Volatile::Int_Operations::exponentiate(exp_copy, one_list_int);

    test_and_log_util::result_type res;
    res.expected = "+9876543210";
    res.actual = to_str(exp_copy);

    return res;
}

test_and_log_util::result_type test_exp_eN1(test_and_log_util::out_type&){
    Core_Int exp_copy = speed_exp_base;

    Precision::Volatile::Int_Operations::exponentiate(exp_copy, neg_one_int);

    test_and_log_util::result_type res;
    res.expected = "+0";
    res.actual = to_str(exp_copy);

    return res;
}

test_and_log_util::result_type test_exp_odd_power(test_and_log_util::out_type&){
    Core_Int exp_copy = sixteen_int;

    Precision::Volatile::Int_Operations::exponentiate(exp_copy, odd_power_int);

    test_and_log_util::result_type res;
    res.expected = "+295147905179352825856";
    res.actual = to_str(exp_copy);

    return res;
}

test_and_log_util::result_type test_exp_10000(test_and_log_util::out_type&){
    Core_Int exp_copy = twos_int;

    Precision::Volatile::Int_Operations::exponentiate(exp_copy, thousands_int);

    test_and_log_util::result_type res;
    res.expected = "+9.9900209301438450794403276433003359098042913905418e30102";
    res.actual = to_sci_note_str(exp_copy, 49);

    return res;
}

test_and_log_util::result_type test_exp(test_and_log_util::out_type&){
    Core_Int exp_copy = twos_int;

    Precision::Volatile::Int_Operations::exponentiate(exp_copy, power_int);

    test_and_log_util::result_type res;
    res.expected = "+1267650600228229401496703205376";
    res.actual = to_str(exp_copy);

    return res;
}

void test_exp_speed(test_and_log_util::out_type&){
    Core_Int exp_copy = speed_exp_base;

    Precision::Volatile::Int_Operations::exponentiate(exp_copy, speed_exp_pow);
}