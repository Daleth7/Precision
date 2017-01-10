#include "Test_Shared_Utilities.h"

#include "int_operations_tests/int_operations_test_comp.h" // Comparison tests
#include "int_operations_tests/int_operations_test_add.h"  // Addition tests
#include "int_operations_tests/int_operations_test_mult.h" // Multiplication tests
#include "int_operations_tests/int_operations_test_div.h"  // Division and Modulus tests
#include "int_operations_tests/int_operations_test_exp.h"  // Exponentiation tests
#include "int_operations_tests/int_operations_test_bit.h"  // Bitwise tests
#include "int_operations_tests/int_operations_test_log.h"  // Logical tests

void setup_variables();
// Cleanup function to free memory
void cleanup();

void int_operations_test(){
    test_and_log_util test_list("Precision::Volatile::Int_Operations", __FILE__);
        test_list.set_log_output(test_log);
        test_list.set_console_output(test_console);
        test_list.set_assert(false);

    add_comparison_tests(test_list);
    add_addition_tests(test_list);
    add_multiplication_tests(test_list);
    add_division_tests(test_list);
    add_exponentiation_tests(test_list);
    add_bitwise_tests(test_list);
    add_logical_tests(test_list);

    setup_variables();

    test_list.execute_tests();

    cleanup();
}

void setup_variables(){
    setup_comparison_variables();
    setup_addition_variables();
    setup_multiplication_variables();
    setup_division_variables();
    setup_exponentiation_variables();
    setup_bitwise_variables();
    setup_logical_variables();
}

void cleanup(){
    comparison_test_cleanup();
    addition_test_cleanup();
    multiplication_test_cleanup();
    division_test_cleanup();
    exponentiation_test_cleanup();
    bitwise_test_cleanup();
    logical_test_cleanup();
}