#include "Test_Shared_Utilities.h"

#include "general_base/Int_Static_Abstract_Base.h"
#include "general_base/impl/Precision_Int_Operations_Img.h"

#include <string>

// Constructor tests
test_and_log_util::result_type test_asgbi_signed_size(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_diglist(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_iterators(test_and_log_util::out_type&);

// Digit Container tests
test_and_log_util::result_type test_asgbi_is_zero(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_is_mag_one(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_is_even(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_is_odd(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_digit_list(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_count_digits(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_digit(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_shift(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_shift_left(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_shift_right(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_detach(test_and_log_util::out_type&);

// Signed Interface tests
test_and_log_util::result_type test_asgbi_is_positive(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_is_negative(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_sign(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_negate(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_make_positive(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_make_negative(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_sign_assign(test_and_log_util::out_type&);

// Int read-only tests
test_and_log_util::result_type test_asgbi_magnitude(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_compare(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_negative(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_is_one(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_is_neg_one(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_base(test_and_log_util::out_type&);

// Int modifier tests
test_and_log_util::result_type test_asgbi_sign(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_make_zero(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_make_one(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_make_neg_one(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_make_two(test_and_log_util::out_type&);

// Arithmetic tests
test_and_log_util::result_type test_asgbi_add(test_and_log_util::out_type&);
void test_asgbi_add_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_sub(test_and_log_util::out_type&);
void test_asgbi_sub_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_mult(test_and_log_util::out_type&);
void test_asgbi_mult_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_div(test_and_log_util::out_type&);
void test_asgbi_div_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_mod(test_and_log_util::out_type&);
void test_asgbi_mod_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_pre_dec(test_and_log_util::out_type&);
void test_asgbi_pre_dec_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_post_dec(test_and_log_util::out_type&);
void test_asgbi_post_dec_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_pre_inc(test_and_log_util::out_type&);
void test_asgbi_pre_inc_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_post_inc(test_and_log_util::out_type&);
void test_asgbi_post_inc_speed(test_and_log_util::out_type&);

// Bitwise tests
test_and_log_util::result_type test_asgbi_and(test_and_log_util::out_type&);
void test_asgbi_and_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_or(test_and_log_util::out_type&);
void test_asgbi_or_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_xor(test_and_log_util::out_type&);
void test_asgbi_xor_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_compl(test_and_log_util::out_type&);
void test_asgbi_compl_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_lshift(test_and_log_util::out_type&);
void test_asgbi_lshift_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_rshift(test_and_log_util::out_type&);
void test_asgbi_rshift_speed(test_and_log_util::out_type&);

// Logical tests
test_and_log_util::result_type test_asgbi_log_and(test_and_log_util::out_type&);
void test_asgbi_log_and_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_log_or(test_and_log_util::out_type&);
void test_asgbi_log_or_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_log_xor(test_and_log_util::out_type&);
void test_asgbi_log_xor_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_log_compl(test_and_log_util::out_type&);
void test_asgbi_log_compl_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_log_lshift(test_and_log_util::out_type&);
void test_asgbi_log_lshift_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_log_rshift(test_and_log_util::out_type&);
void test_asgbi_log_rshift_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_log_shift(test_and_log_util::out_type&);
void test_asgbi_log_shift_speed(test_and_log_util::out_type&);

void setup_asgbi_variables();
// Cleanup function to free memory
void cleanup_asgbi();

template <typename IntType>
test_and_log_util::str_type to_str(const IntType& num){
    static char const *const digs = "0123456789";
    static char const *const syms = "+-.e /i";

    return Precision::Volatile::Int_Operations::Img::str
           <test_and_log_util::str_type, IntType>(num, digs, syms);
}

using ASGB_Int = Precision::General_Base::Static::Abstract::Int<>;

void abstract_static_general_base_int_test(){
    test_and_log_util test_list( "Precision::General_Base::Static::"
                                 "Abstract::Int_Operations", __FILE__);
        test_list.set_log_output(test_log);
        test_list.set_console_output(test_console);
        test_list.set_assert(false);

    ADD_TEST(test_list, test_asgbi_signed_size);

    setup_asgbi_variables();

    test_list.execute_tests();

    cleanup_asgbi();
}

void setup_asgbi_variables(){
}

void cleanup_asgbi(){
}

// Constructor tests
test_and_log_util::result_type test_asgbi_signed_size(test_and_log_util::out_type&){
    ASGB_Int testee(-123654789);

    test_and_log_util::result_type res;
    res.expected = "-123654789";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_asgbi_diglist(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_iterators(test_and_log_util::out_type&);

// Digit Container tests
test_and_log_util::result_type test_asgbi_is_zero(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_is_mag_one(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_is_even(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_is_odd(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_digit_list(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_count_digits(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_digit(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_shift(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_shift_left(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_shift_right(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_detach(test_and_log_util::out_type&);

// Signed Interface tests
test_and_log_util::result_type test_asgbi_is_positive(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_is_negative(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_sign(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_negate(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_make_positive(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_make_negative(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_sign_assign(test_and_log_util::out_type&);

// Int read-only tests
test_and_log_util::result_type test_asgbi_magnitude(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_compare(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_negative(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_is_one(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_is_neg_one(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_base(test_and_log_util::out_type&);

// Int modifier tests
test_and_log_util::result_type test_asgbi_sign(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_make_zero(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_make_one(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_make_neg_one(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_make_two(test_and_log_util::out_type&);

// Arithmetic tests
test_and_log_util::result_type test_asgbi_add(test_and_log_util::out_type&);
void test_asgbi_add_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_sub(test_and_log_util::out_type&);
void test_asgbi_sub_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_mult(test_and_log_util::out_type&);
void test_asgbi_mult_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_div(test_and_log_util::out_type&);
void test_asgbi_div_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_mod(test_and_log_util::out_type&);
void test_asgbi_mod_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_pre_dec(test_and_log_util::out_type&);
void test_asgbi_pre_dec_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_post_dec(test_and_log_util::out_type&);
void test_asgbi_post_dec_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_pre_inc(test_and_log_util::out_type&);
void test_asgbi_pre_inc_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_post_inc(test_and_log_util::out_type&);
void test_asgbi_post_inc_speed(test_and_log_util::out_type&);

// Bitwise tests
test_and_log_util::result_type test_asgbi_and(test_and_log_util::out_type&);
void test_asgbi_and_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_or(test_and_log_util::out_type&);
void test_asgbi_or_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_xor(test_and_log_util::out_type&);
void test_asgbi_xor_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_compl(test_and_log_util::out_type&);
void test_asgbi_compl_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_lshift(test_and_log_util::out_type&);
void test_asgbi_lshift_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_rshift(test_and_log_util::out_type&);
void test_asgbi_rshift_speed(test_and_log_util::out_type&);

// Logical tests
test_and_log_util::result_type test_asgbi_log_and(test_and_log_util::out_type&);
void test_asgbi_log_and_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_log_or(test_and_log_util::out_type&);
void test_asgbi_log_or_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_log_xor(test_and_log_util::out_type&);
void test_asgbi_log_xor_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_log_compl(test_and_log_util::out_type&);
void test_asgbi_log_compl_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_log_lshift(test_and_log_util::out_type&);
void test_asgbi_log_lshift_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_log_rshift(test_and_log_util::out_type&);
void test_asgbi_log_rshift_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_log_shift(test_and_log_util::out_type&);
void test_asgbi_log_shift_speed(test_and_log_util::out_type&);