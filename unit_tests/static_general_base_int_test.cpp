#include "Test_Shared_Utilities.h"

#include "general_base/Int_Static_Base.h"

// Constructor tests
test_and_log_util::result_type test_sgbi_default(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_signed_size(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_diglist(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_iterators(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_str_unsigned(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_str_signed(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_str_exp(test_and_log_util::out_type&);

// Digit Container tests
test_and_log_util::result_type test_sgbi_is_zero(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_is_mag_one(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_is_even(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_is_odd(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_digit_string(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_count_digits(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_digit(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_shift(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_shift_left(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_shift_right(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_append(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_detach(test_and_log_util::out_type&);

// Signed Interface tests
test_and_log_util::result_type test_sgbi_is_positive(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_is_negative(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_sign(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_negate(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_make_positive(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_make_negative(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_sign_assign(test_and_log_util::out_type&);

// Int read-only tests
test_and_log_util::result_type test_sgbi_magnitude(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_compare(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_negative(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_is_one(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_is_neg_one(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_base(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_str(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_sci_note(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_sci_note_w_spaces(test_and_log_util::out_type&);

// Int modifier tests
test_and_log_util::result_type test_sgbi_make_zero(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_make_one(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_make_neg_one(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_make_two(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_halve(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_halve_spec(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_assign(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_force_assign(test_and_log_util::out_type&);

// Arithmetic tests
test_and_log_util::result_type test_sgbi_add(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_sub(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_mult(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_div(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_mod(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_pre_dec(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_post_dec(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_pre_inc(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_post_inc(test_and_log_util::out_type&);

// Bitwise tests
test_and_log_util::result_type test_sgbi_and(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_or(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_xor(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_compl(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_lshift(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_rshift(test_and_log_util::out_type&);

// Logical tests
test_and_log_util::result_type test_sgbi_log_and(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_log_or(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_log_xor(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_log_compl(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_log_lshift(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_log_rshift(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_log_shift(test_and_log_util::out_type&);

// Template tests
test_and_log_util::result_type test_sgbi_custom_image_int(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_custom_image_str(test_and_log_util::out_type&);
test_and_log_util::result_type test_sgbi_custom_image_mult(test_and_log_util::out_type&);

void setup_sgbi_variables();
// Cleanup function to free memory
void cleanup_sgbi();

using SGB_Int = Precision::General_Base::Static::Int<>;


// Variables for functionality tests
static SGB_Int all_digs_int, rev_digs_int, two_int, eight_int;

void static_general_base_int_test(){
    test_and_log_util test_list("Precision::General_Base::Static::Int", __FILE__);
        test_list.set_log_output(test_log);
        test_list.set_console_output(test_console);
        test_list.set_assert(false);

    ADD_TEST(test_list, test_sgbi_default);
    ADD_TEST(test_list, test_sgbi_signed_size);
    ADD_TEST(test_list, test_sgbi_diglist);
    ADD_TEST(test_list, test_sgbi_iterators);
    ADD_TEST(test_list, test_sgbi_str_unsigned);
    ADD_TEST(test_list, test_sgbi_str_signed);
    ADD_TEST(test_list, test_sgbi_str_exp);

    ADD_TEST(test_list, test_sgbi_is_zero);
    ADD_TEST(test_list, test_sgbi_is_mag_one);
    ADD_TEST(test_list, test_sgbi_is_even);
    ADD_TEST(test_list, test_sgbi_is_odd);
    ADD_TEST(test_list, test_sgbi_digit_string);
    ADD_TEST(test_list, test_sgbi_count_digits);
    ADD_TEST(test_list, test_sgbi_shift_left);
    ADD_TEST(test_list, test_sgbi_shift_right);
    ADD_TEST(test_list, test_sgbi_append);
    ADD_TEST(test_list, test_sgbi_detach);

    ADD_TEST(test_list, test_sgbi_is_positive);
    ADD_TEST(test_list, test_sgbi_is_negative);
    ADD_TEST(test_list, test_sgbi_sign);
    ADD_TEST(test_list, test_sgbi_negate);
    ADD_TEST(test_list, test_sgbi_make_positive);
    ADD_TEST(test_list, test_sgbi_make_negative);
    ADD_TEST(test_list, test_sgbi_sign_assign);

    ADD_TEST(test_list, test_sgbi_magnitude);
    ADD_TEST(test_list, test_sgbi_compare);
    ADD_TEST(test_list, test_sgbi_negative);
    ADD_TEST(test_list, test_sgbi_is_one);
    ADD_TEST(test_list, test_sgbi_is_neg_one);
    ADD_TEST(test_list, test_sgbi_base);
    ADD_TEST(test_list, test_sgbi_str);
    ADD_TEST(test_list, test_sgbi_sci_note);
    ADD_TEST(test_list, test_sgbi_sci_note_w_spaces);

    ADD_TEST(test_list, test_sgbi_make_zero);
    ADD_TEST(test_list, test_sgbi_make_one);
    ADD_TEST(test_list, test_sgbi_make_neg_one);
    ADD_TEST(test_list, test_sgbi_make_two);
    ADD_TEST(test_list, test_sgbi_halve);
    ADD_TEST(test_list, test_sgbi_halve_spec);
    ADD_TEST(test_list, test_sgbi_assign);
    ADD_TEST(test_list, test_sgbi_force_assign);

    ADD_TEST(test_list, test_sgbi_add);
    ADD_TEST(test_list, test_sgbi_sub);
    ADD_TEST(test_list, test_sgbi_mult);
    ADD_TEST(test_list, test_sgbi_div);
    ADD_TEST(test_list, test_sgbi_mod);
    ADD_TEST(test_list, test_sgbi_pre_dec);
    ADD_TEST(test_list, test_sgbi_post_dec);
    ADD_TEST(test_list, test_sgbi_pre_inc);
    ADD_TEST(test_list, test_sgbi_post_inc);
    
    ADD_TEST(test_list, test_sgbi_and);
    ADD_TEST(test_list, test_sgbi_or);
    ADD_TEST(test_list, test_sgbi_xor);
    ADD_TEST(test_list, test_sgbi_compl);
    ADD_TEST(test_list, test_sgbi_lshift);
    ADD_TEST(test_list, test_sgbi_rshift);

    ADD_TEST(test_list, test_sgbi_log_and);
    ADD_TEST(test_list, test_sgbi_log_or);
    ADD_TEST(test_list, test_sgbi_log_xor);
    ADD_TEST(test_list, test_sgbi_log_compl);
    ADD_TEST(test_list, test_sgbi_log_lshift);
    ADD_TEST(test_list, test_sgbi_log_rshift);
    ADD_TEST(test_list, test_sgbi_log_shift);

    ADD_TEST(test_list, test_sgbi_custom_image_int);
    ADD_TEST(test_list, test_sgbi_custom_image_str);
    ADD_TEST(test_list, test_sgbi_custom_image_mult);

    setup_sgbi_variables();

    test_list.execute_tests();

    cleanup_sgbi();
}

void setup_sgbi_variables(){
    all_digs_int = SGB_Int("9876543210");
    rev_digs_int = SGB_Int("123456789");
    two_int.make_two();
    eight_int = SGB_Int(8);
}

void cleanup_sgbi(){
    all_digs_int.make_zero();
    rev_digs_int.make_zero();
}

// Constructor tests
test_and_log_util::result_type test_sgbi_default(test_and_log_util::out_type&){
    SGB_Int testee;

    test_and_log_util::result_type res;
    res.expected = "+0";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_sgbi_signed_size(test_and_log_util::out_type&){
    SGB_Int testee(-1236547890);

    test_and_log_util::result_type res;
    res.expected = "-1236547890";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_sgbi_diglist(test_and_log_util::out_type&){
    SGB_Int::digstr_type diglist({1, 3, 2, 0, 8, 9, 77, 4, 0, 0});

    SGB_Int testee(diglist, 1);

    test_and_log_util::result_type res;
    res.expected = "+40980231";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_sgbi_iterators(test_and_log_util::out_type&){
    int bad_str[14] = {0, 0, 1, 4, 3, -5, 9, 5, 66, 7, 1, 0, 1, 0};

    SGB_Int testee(static_cast<int*>(bad_str), bad_str+14, 1);

    test_and_log_util::result_type res;
    res.expected = "+1017059034100";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_sgbi_str_unsigned(test_and_log_util::out_type&){
    SGB_Int testee("23092354");

    test_and_log_util::result_type res;
    res.expected = "+23092354";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_sgbi_str_signed(test_and_log_util::out_type&){
    SGB_Int testee("-23092354"), testee2("+23092354");

    test_and_log_util::result_type res;
    res.expected = "-23092354+23092354";
    res.actual = testee.str() + testee2.str();

    return res;
}

test_and_log_util::result_type test_sgbi_str_exp(test_and_log_util::out_type&){
    SGB_Int testee("238e4"), testee2("-239874e-4");

    test_and_log_util::result_type res;
    res.expected = "+2380000-23";
    res.actual = testee.str() + testee2.str();

    return res;
}

// Digit Container tests
test_and_log_util::result_type test_sgbi_is_zero(test_and_log_util::out_type&){
    SGB_Int testee;

    test_and_log_util::result_type res;
    res.expected = "Testee is zero.";
    res.actual = "Testee is ";
    res.actual += (!testee.is_zero() ? "not " : "");
    res.actual += "zero.";

    return res;
}

test_and_log_util::result_type test_sgbi_is_mag_one(test_and_log_util::out_type&){
    SGB_Int testee(-1);

    test_and_log_util::result_type res;
    res.expected = "Testee has magnitude of one.";
    res.actual = "Testee has magnitude of ";
    res.actual += (!testee.is_mag_one() ? "not " : "");
    res.actual += "one.";

    return res;
}

test_and_log_util::result_type test_sgbi_is_even(test_and_log_util::out_type&){
    SGB_Int testee(0xA4);

    test_and_log_util::result_type res;
    res.expected = "Testee is even.";
    res.actual = "Testee is ";
    res.actual += (!testee.is_even() ? "not " : "");
    res.actual += "even.";

    return res;
}

test_and_log_util::result_type test_sgbi_is_odd(test_and_log_util::out_type&){
    SGB_Int testee(0xA3);

    test_and_log_util::result_type res;
    res.expected = "Testee is odd.";
    res.actual = "Testee is ";
    res.actual += (!testee.is_odd() ? "not " : "");
    res.actual += "odd.";

    return res;
}

test_and_log_util::result_type test_sgbi_digit_string(test_and_log_util::out_type&){
    SGB_Int testee(-123654879);

    test_and_log_util::result_type res;
    res.expected = "978456321";

    for(auto it = testee.digit_string().begin(); it != testee.digit_string().end(); ++it)
        res.actual.push_back(*it + '0');

    return res;
}

test_and_log_util::result_type test_sgbi_count_digits(test_and_log_util::out_type&){
    SGB_Int testee(SGB_Int::digstr_type(1000, 7), 1);

    test_and_log_util::result_type res;
    res.expected = "Testee is 1000 digits.";
    res.actual = "Testee is ";
    res.actual += (testee.count_digits()!=1000 ? "not " : "");
    res.actual += "1000 digits.";

    return res;
}

test_and_log_util::result_type test_sgbi_digit(test_and_log_util::out_type&){
    SGB_Int testee(1234567890);

    test_and_log_util::result_type res;
    res.expected = "0987654321000";
    for(unsigned i = 0; i < testee.count_digits()+3; ++i)
        res.actual.push_back(testee.digit(i) + '0');

    return res;
}

test_and_log_util::result_type test_sgbi_shift(test_and_log_util::out_type&){
    SGB_Int testee(1234567890);

    testee.shift(7);
    testee.shift(-11);

    test_and_log_util::result_type res;
    res.expected = "+123456";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_sgbi_shift_left(test_and_log_util::out_type&){
    SGB_Int testee(1234567890);

    testee.shift_left(7);

    test_and_log_util::result_type res;
    res.expected = "+12345678900000000";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_sgbi_shift_right(test_and_log_util::out_type&){
    SGB_Int testee(1234567890);

    testee.shift_right(11);

    test_and_log_util::result_type res;
    res.expected = "+0";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_sgbi_append(test_and_log_util::out_type&){
    SGB_Int testee;

    testee.append(9);
    testee.append(0);
    testee.append(7);

    test_and_log_util::result_type res;
    res.expected = "+790";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_sgbi_detach(test_and_log_util::out_type&){
    SGB_Int testee(11);

    testee.detach();
    testee.detach();
    testee.detach();

    test_and_log_util::result_type res;
    res.expected = "+0";
    res.actual = testee.str();

    return res;
}

// Signed Interface tests
test_and_log_util::result_type test_sgbi_is_positive(test_and_log_util::out_type&){
    SGB_Int testee;

    test_and_log_util::result_type res;
    res.expected = "Testee is positive.";
    res.actual = "Testee is ";
    res.actual += (!testee.is_positive() ? "not " : "");
    res.actual += "positive.";

    return res;
}

test_and_log_util::result_type test_sgbi_is_negative(test_and_log_util::out_type&){
    SGB_Int testee(-1);

    test_and_log_util::result_type res;
    res.expected = "Testee is negative.";
    res.actual = "Testee is ";
    res.actual += (!testee.is_negative() ? "not " : "");
    res.actual += "negative.";

    return res;
}

test_and_log_util::result_type test_sgbi_sign(test_and_log_util::out_type&){
    SGB_Int testee(-133);

    test_and_log_util::result_type res;
    res.expected = "Testee is -1.";
    res.actual = "Testee is ";
    res.actual += (testee.sign() != -1 ? "not " : "");
    res.actual += "-1.";

    return res;
}

test_and_log_util::result_type test_sgbi_negate(test_and_log_util::out_type&){
    SGB_Int testee(11);

    testee.negate();

    test_and_log_util::result_type res;
    res.expected = "-11";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_sgbi_make_positive(test_and_log_util::out_type&){
    SGB_Int testee(-11);

    testee.make_positive();

    test_and_log_util::result_type res;
    res.expected = "+11";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_sgbi_make_negative(test_and_log_util::out_type&){
    SGB_Int testee(6);

    testee.make_negative();

    test_and_log_util::result_type res;
    res.expected = "-6";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_sgbi_sign_assign(test_and_log_util::out_type&){
    SGB_Int testee(777);

    testee.sign(-5);

    test_and_log_util::result_type res;
    res.expected = "-777";
    res.actual = testee.str();

    return res;
}


// Int read-only tests
test_and_log_util::result_type test_sgbi_magnitude(test_and_log_util::out_type&){
    SGB_Int testee(-8932753);

    testee = testee.magnitude();

    test_and_log_util::result_type res;
    res.expected = "+8932753";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_sgbi_compare(test_and_log_util::out_type&){
    SGB_Int testee(-8932753), testee2;

    test_and_log_util::result_type res;
    res.expected = "Testee is less.";
    res.actual = "Testee is ";
    res.actual += (!(testee.compare(testee2) < 0) ? "not " : "");
    res.actual += "less.";

    return res;
}

test_and_log_util::result_type test_sgbi_negative(test_and_log_util::out_type&){
    SGB_Int testee(-8932753);

    testee = -testee;

    test_and_log_util::result_type res;
    res.expected = "+8932753";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_sgbi_is_one(test_and_log_util::out_type&){
    SGB_Int testee(1);

    test_and_log_util::result_type res;
    res.expected = "Testee is +1.";
    res.actual = "Testee is ";
    res.actual += (!testee.is_one() ? "not " : "");
    res.actual += "+1.";

    return res;
}

test_and_log_util::result_type test_sgbi_is_neg_one(test_and_log_util::out_type&){
    SGB_Int testee(-1);

    test_and_log_util::result_type res;
    res.expected = "Testee is -1.";
    res.actual = "Testee is ";
    res.actual += (!testee.is_neg_one() ? "not " : "");
    res.actual += "-1.";

    return res;
}

test_and_log_util::result_type test_sgbi_base(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "Base is 10.";
    res.actual = "Base is ";
    res.actual += ((SGB_Int::base() == 10) ? "" : "not ");
    res.actual += "10.";

    return res;
}

test_and_log_util::result_type test_sgbi_str(test_and_log_util::out_type&){
    SGB_Int testee("+98765432109876543210");

    test_and_log_util::result_type res;
    res.expected = "+98765432109876543210";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_sgbi_sci_note(test_and_log_util::out_type&){
    SGB_Int testee("+98765432109876543210");

    test_and_log_util::result_type res;
    res.expected = "+9.8765432109876543210e19";
    res.actual = testee.sci_note();

    return res;
}

test_and_log_util::result_type test_sgbi_sci_note_w_spaces(test_and_log_util::out_type&){
    SGB_Int testee("+98765432109876543210");

    test_and_log_util::result_type res;
    res.expected = "+ 9.8765432109876543210 e 19";
    res.actual = testee.sci_note_w_spaces();

    return res;
}


// Int modifier tests
test_and_log_util::result_type test_sgbi_make_zero(test_and_log_util::out_type&){
    SGB_Int testee(-8932753);

    testee.make_zero();

    test_and_log_util::result_type res;
    res.expected = "+0";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_sgbi_make_one(test_and_log_util::out_type&){
    SGB_Int testee(-8932753);

    testee.make_one();

    test_and_log_util::result_type res;
    res.expected = "+1";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_sgbi_make_neg_one(test_and_log_util::out_type&){
    SGB_Int testee(-8932753);

    testee.make_neg_one();

    test_and_log_util::result_type res;
    res.expected = "-1";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_sgbi_make_two(test_and_log_util::out_type&){
    SGB_Int testee(-8932753);

    testee.make_two();

    test_and_log_util::result_type res;
    res.expected = "+2";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_sgbi_halve(test_and_log_util::out_type&){
    SGB_Int testee(8932753);

    testee.halve();

    test_and_log_util::result_type res;
    res.expected = "+4466376";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_sgbi_halve_spec(test_and_log_util::out_type&){
    SGB_Int testee({0, 1, 2, 3, 4, 0, 6, 7, 8, 9}, -1);

    testee.halve();

    test_and_log_util::result_type res;
    res.expected = "-4938021605";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_sgbi_assign(test_and_log_util::out_type&){
    SGB_Int testee(-8932753);

    testee.assign(10, 5);
    testee.assign(4, 15);
    testee.assign(0, 8);

    test_and_log_util::result_type res;
    res.expected = "-8932758";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_sgbi_force_assign(test_and_log_util::out_type&){
    SGB_Int testee(-8932753);

    testee.force_assign(10, 5);
    testee.force_assign(4, 15);
    testee.force_assign(0, 8);

    test_and_log_util::result_type res;
    res.expected = "-50008932758";
    res.actual = testee.str();

    return res;
}

// Arithmetic tests
test_and_log_util::result_type test_sgbi_add(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+9999999999";
    res.actual = (all_digs_int + rev_digs_int).str();

    return res;
}

test_and_log_util::result_type test_sgbi_sub(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+9753086421";
    res.actual = (all_digs_int - rev_digs_int).str();

    return res;
}

test_and_log_util::result_type test_sgbi_mult(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+1219326311126352690";
    res.actual = (all_digs_int * rev_digs_int).str();

    return res;
}

test_and_log_util::result_type test_sgbi_div(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+80";
    res.actual = (all_digs_int / rev_digs_int).str();

    return res;
}

test_and_log_util::result_type test_sgbi_mod(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+0";
    res.actual = (all_digs_int % two_int).str();

    return res;
}

test_and_log_util::result_type test_sgbi_pre_dec(test_and_log_util::out_type&){
    SGB_Int testee;

    test_and_log_util::result_type res;
    res.expected = "-1";
    res.actual = (--testee).str();

    return res;
}

test_and_log_util::result_type test_sgbi_post_dec(test_and_log_util::out_type&){
    SGB_Int testee;
    SGB_Int testee2 = testee--;

    test_and_log_util::result_type res;
    res.expected = "-1 +0";
    res.actual = testee.str() + " " + testee2.str();

    return res;
}

test_and_log_util::result_type test_sgbi_pre_inc(test_and_log_util::out_type&){
    SGB_Int testee;

    test_and_log_util::result_type res;
    res.expected = "+1";
    res.actual = (++testee).str();

    return res;
}

test_and_log_util::result_type test_sgbi_post_inc(test_and_log_util::out_type&){
    SGB_Int testee;
    SGB_Int testee2 = testee++;

    test_and_log_util::result_type res;
    res.expected = "+1 +0";
    res.actual = testee.str() + " " + testee2.str();

    return res;
}

// Bitwise tests
test_and_log_util::result_type test_sgbi_and(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+68158464";
    res.actual = (all_digs_int & rev_digs_int).str();

    return res;
}

test_and_log_util::result_type test_sgbi_or(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+9931841535";
    res.actual = (all_digs_int | rev_digs_int).str();

    return res;
}

test_and_log_util::result_type test_sgbi_xor(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+9863683071";
    res.actual = (all_digs_int ^ rev_digs_int).str();

    return res;
}

test_and_log_util::result_type test_sgbi_compl(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "-7303325973";
    res.actual = (~all_digs_int).str();

    return res;
}

test_and_log_util::result_type test_sgbi_lshift(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+2528395061760";
    res.actual = (all_digs_int << eight_int).str();

    return res;
}

test_and_log_util::result_type test_sgbi_rshift(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+38580246";
    res.actual = (all_digs_int >> eight_int).str();

    return res;
}


// Logical tests
test_and_log_util::result_type test_sgbi_log_and(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+848008480";
    res.actual = (all_digs_int.logical_and(rev_digs_int)).str();

    return res;
}

test_and_log_util::result_type test_sgbi_log_or(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+9151991519";
    res.actual = (all_digs_int.logical_or(rev_digs_int)).str();

    return res;
}

test_and_log_util::result_type test_sgbi_log_xor(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+9999999999";
    res.actual = (all_digs_int.logical_xor(rev_digs_int)).str();

    return res;
}

test_and_log_util::result_type test_sgbi_log_compl(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "-123456789";
    res.actual = (all_digs_int.logical_complement()).str();

    return res;
}

test_and_log_util::result_type test_sgbi_log_lshift(test_and_log_util::out_type&){
    SGB_Int testee(1234567890);

    test_and_log_util::result_type res;
    res.expected = "+12345678900000000";
    res.actual = (testee.logical_shift_left(7)).str();

    return res;
}

test_and_log_util::result_type test_sgbi_log_rshift(test_and_log_util::out_type&){
    SGB_Int testee(1234567890);

    test_and_log_util::result_type res;
    res.expected = "+0";
    res.actual = (testee.logical_shift_right(11)).str();

    return res;
}

test_and_log_util::result_type test_sgbi_log_shift(test_and_log_util::out_type&){
    SGB_Int testee(1234567890);

    test_and_log_util::result_type res;
    res.expected = "+123456";
    res.actual = (testee.logical_shift(7).logical_shift(-11)).str();

    return res;
}



// Template tests
test_and_log_util::result_type test_sgbi_custom_image_int(test_and_log_util::out_type&){
    char const *const new_digs = ")!@#$%^&*(",
               *const new_syms = "=_>3\t?1"
               ;

    SGB_Int testee(1274893786, new_digs, new_syms);

    test_and_log_util::result_type res;
    res.expected = "=!@&$*(#&*^";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_sgbi_custom_image_str(test_and_log_util::out_type&){
    char const *const new_digs = ")!@#$%^&*(",
               *const new_syms = "=_>3\t?1"
               ;
    using Shift_Int = Precision::General_Base::Static::Int
                    <char, char const *, Precision::Default::byte_type, 10,
                    std::vector, Precision::Default::sign_type,
                    Precision::ImgSearchPolicy::Normal
                    >;

    Shift_Int::str_type bad_str("_!)df @@#*(@f hg@*#(*erg)# @$3@");

    Shift_Int testee(bad_str, new_digs, new_syms);

    test_and_log_util::result_type res;
    res.expected = "_!))))@@#*(@))))@*#(*))))#)@$))";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_sgbi_custom_image_mult(test_and_log_util::out_type&){
    char const *const new_digs = ")!@#$%^&*(",
               *const new_syms = "=_>3\t?1"
               ;

    SGB_Int testee1(64, new_digs, new_syms), testee2(127, new_digs, new_syms);

    test_and_log_util::result_type res;
    res.expected = "=*!@*";
    res.actual = (testee1 * testee2).str();

    return res;
}