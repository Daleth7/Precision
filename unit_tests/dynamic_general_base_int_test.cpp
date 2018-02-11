#include "Test_Shared_Utilities.h"

#include "general_base/Int_Dynamic_Base.h"

// Constructor tests
test_and_log_util::result_type test_dgbi_default(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_new_base(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_signed_size(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_diglist(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_iterators(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_str_unsigned(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_str_signed(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_str_exp(test_and_log_util::out_type&);

// Digit Container tests
test_and_log_util::result_type test_dgbi_is_zero(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_is_mag_one(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_is_even(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_is_odd(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_digit_list(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_count_digits(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_digit(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_shift(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_shift_left(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_shift_right(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_append(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_detach(test_and_log_util::out_type&);

// Signed Interface tests
test_and_log_util::result_type test_dgbi_is_positive(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_is_negative(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_sign(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_negate(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_make_positive(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_make_negative(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_sign_assign(test_and_log_util::out_type&);

// Int read-only tests
test_and_log_util::result_type test_dgbi_magnitude(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_compare(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_negative(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_is_one(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_is_neg_one(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_base(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_str(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_sci_note(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_sci_note_w_spaces(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_abstract(test_and_log_util::out_type&);

// Int modifier tests
test_and_log_util::result_type test_dgbi_make_zero(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_make_one(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_make_neg_one(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_make_two(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_halve(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_halve_spec(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_assign(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_force_assign(test_and_log_util::out_type&);

// Arithmetic tests
test_and_log_util::result_type test_dgbi_add(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_sub(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_mult(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_div(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_mod(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_pre_dec(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_post_dec(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_pre_inc(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_post_inc(test_and_log_util::out_type&);

// Bitwise tests
test_and_log_util::result_type test_dgbi_and(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_or(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_xor(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_compl(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_lshift(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_rshift(test_and_log_util::out_type&);

// Logical tests
test_and_log_util::result_type test_dgbi_log_and(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_log_or(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_log_xor(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_log_compl(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_log_lshift(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_log_rshift(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_log_shift(test_and_log_util::out_type&);

// Template tests
test_and_log_util::result_type test_dgbi_custom_image_int(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_custom_image_str(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_custom_image_mult(test_and_log_util::out_type&);
test_and_log_util::result_type test_dgbi_custom_iter(test_and_log_util::out_type&);

void setup_dgbi_variables();
// Cleanup function to free memory
void cleanup_dgbi();

using DGB_Int = Precision::General_Base::Dynamic::Int<>;


// Variables for functionality tests
static DGB_Int all_digs_int, rev_digs_int, two_int, eight_int, diff_base_int;

void dynamic_general_base_int_test(){
    test_and_log_util test_list("Precision::General_Base::Dynamic::Int", __FILE__);
        test_list.set_log_output(test_log);
        test_list.set_console_output(test_console);
        test_list.set_assert(false);

    ADD_TEST(test_list, test_dgbi_default);
    ADD_TEST(test_list, test_dgbi_new_base);
    ADD_TEST(test_list, test_dgbi_signed_size);
    ADD_TEST(test_list, test_dgbi_diglist);
    ADD_TEST(test_list, test_dgbi_iterators);
    ADD_TEST(test_list, test_dgbi_str_unsigned);
    ADD_TEST(test_list, test_dgbi_str_signed);
    ADD_TEST(test_list, test_dgbi_str_exp);

    ADD_TEST(test_list, test_dgbi_is_zero);
    ADD_TEST(test_list, test_dgbi_is_mag_one);
    ADD_TEST(test_list, test_dgbi_is_even);
    ADD_TEST(test_list, test_dgbi_is_odd);
    ADD_TEST(test_list, test_dgbi_digit_list);
    ADD_TEST(test_list, test_dgbi_count_digits);
    ADD_TEST(test_list, test_dgbi_shift_left);
    ADD_TEST(test_list, test_dgbi_shift_right);
    ADD_TEST(test_list, test_dgbi_append);
    ADD_TEST(test_list, test_dgbi_detach);

    ADD_TEST(test_list, test_dgbi_is_positive);
    ADD_TEST(test_list, test_dgbi_is_negative);
    ADD_TEST(test_list, test_dgbi_sign);
    ADD_TEST(test_list, test_dgbi_negate);
    ADD_TEST(test_list, test_dgbi_make_positive);
    ADD_TEST(test_list, test_dgbi_make_negative);
    ADD_TEST(test_list, test_dgbi_sign_assign);

    ADD_TEST(test_list, test_dgbi_magnitude);
    ADD_TEST(test_list, test_dgbi_compare);
    ADD_TEST(test_list, test_dgbi_negative);
    ADD_TEST(test_list, test_dgbi_is_one);
    ADD_TEST(test_list, test_dgbi_is_neg_one);
    ADD_TEST(test_list, test_dgbi_base);
    ADD_TEST(test_list, test_dgbi_str);
    ADD_TEST(test_list, test_dgbi_sci_note);
    ADD_TEST(test_list, test_dgbi_sci_note_w_spaces);
    ADD_TEST(test_list, test_dgbi_abstract);

    ADD_TEST(test_list, test_dgbi_make_zero);
    ADD_TEST(test_list, test_dgbi_make_one);
    ADD_TEST(test_list, test_dgbi_make_neg_one);
    ADD_TEST(test_list, test_dgbi_make_two);
    ADD_TEST(test_list, test_dgbi_halve);
    ADD_TEST(test_list, test_dgbi_halve_spec);
    ADD_TEST(test_list, test_dgbi_assign);
    ADD_TEST(test_list, test_dgbi_force_assign);

    ADD_TEST(test_list, test_dgbi_add);
    ADD_TEST(test_list, test_dgbi_sub);
    ADD_TEST(test_list, test_dgbi_mult);
    ADD_TEST(test_list, test_dgbi_div);
    ADD_TEST(test_list, test_dgbi_mod);
    ADD_TEST(test_list, test_dgbi_pre_dec);
    ADD_TEST(test_list, test_dgbi_post_dec);
    ADD_TEST(test_list, test_dgbi_pre_inc);
    ADD_TEST(test_list, test_dgbi_post_inc);
    
    ADD_TEST(test_list, test_dgbi_and);
    ADD_TEST(test_list, test_dgbi_or);
    ADD_TEST(test_list, test_dgbi_xor);
    ADD_TEST(test_list, test_dgbi_compl);
    ADD_TEST(test_list, test_dgbi_lshift);
    ADD_TEST(test_list, test_dgbi_rshift);

    ADD_TEST(test_list, test_dgbi_log_and);
    ADD_TEST(test_list, test_dgbi_log_or);
    ADD_TEST(test_list, test_dgbi_log_xor);
    ADD_TEST(test_list, test_dgbi_log_compl);
    ADD_TEST(test_list, test_dgbi_log_lshift);
    ADD_TEST(test_list, test_dgbi_log_rshift);
    ADD_TEST(test_list, test_dgbi_log_shift);

    ADD_TEST(test_list, test_dgbi_custom_image_int);
    ADD_TEST(test_list, test_dgbi_custom_image_str);
    ADD_TEST(test_list, test_dgbi_custom_image_mult);
    ADD_TEST(test_list, test_dgbi_custom_iter);

    setup_dgbi_variables();

    test_list.execute_tests();

    cleanup_dgbi();
}

void setup_dgbi_variables(){
    all_digs_int = DGB_Int("9876543210");
    rev_digs_int = DGB_Int("123456789");
    diff_base_int = DGB_Int("ABCDEF", 0x10);
    two_int.make_two();
    eight_int = DGB_Int(8);
}

void cleanup_dgbi(){
    all_digs_int.make_zero();
    rev_digs_int.make_zero();
    diff_base_int.make_zero();
}

// Constructor tests
test_and_log_util::result_type test_dgbi_default(test_and_log_util::out_type&){
    DGB_Int testee;

    test_and_log_util::result_type res;
    res.expected = "+0";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_dgbi_new_base(test_and_log_util::out_type&){
    DGB_Int testee(0, 7);

    test_and_log_util::result_type res;
    res.expected = "+0777";
    res.actual = testee.str() + test_and_log_util::str_type(3, testee.base() + '0');

    return res;
}

test_and_log_util::result_type test_dgbi_signed_size(test_and_log_util::out_type&){
    DGB_Int testee(-1236547890);

    test_and_log_util::result_type res;
    res.expected = "-1236547890";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_dgbi_diglist(test_and_log_util::out_type&){
<<<<<<< HEAD
    DGB_Int::digstr_type diglist({1, 3, 2, 0, 8, 9, 77, 4, 0, 0});
=======
    DGB_Int::diglist_type diglist({1, 3, 2, 0, 8, 9, 77, 4, 0, 0});
>>>>>>> 8aa772d478473c9a5631f16901893c2d6e710d1b

    DGB_Int testee(diglist, 1);

    test_and_log_util::result_type res;
    res.expected = "+40980231";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_dgbi_iterators(test_and_log_util::out_type&){
    int bad_str[14] = {0, 0, 1, 4, 3, -5, 9, 5, 66, 7, 1, 0, 1, 0};

    DGB_Int testee(static_cast<int*>(bad_str), bad_str+14, 1);

    test_and_log_util::result_type res;
    res.expected = "+1017059034100";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_dgbi_str_unsigned(test_and_log_util::out_type&){
    DGB_Int testee("D3BV823HTZXEU", 31);

    test_and_log_util::result_type res;
    res.expected = "+D3B0823HT00EU";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_dgbi_str_signed(test_and_log_util::out_type&){
    DGB_Int testee("-2 309\t35\n"), testee2("+23092354");

    test_and_log_util::result_type res;
    res.expected = "-203090350+23092354";
    res.actual = testee.str() + testee2.str();

    return res;
}

test_and_log_util::result_type test_dgbi_str_exp(test_and_log_util::out_type&){
    DGB_Int testee("238eA", 0x10), testee2("-239874e-4");

    test_and_log_util::result_type res;
    res.expected = "+2380000000000-23";
    res.actual = testee.str() + testee2.str();

    return res;
}

// Digit Container tests
test_and_log_util::result_type test_dgbi_is_zero(test_and_log_util::out_type&){
    DGB_Int testee;

    test_and_log_util::result_type res;
    res.expected = "Testee is zero.";
    res.actual = "Testee is ";
    res.actual += (!testee.is_zero() ? "not " : "");
    res.actual += "zero.";

    return res;
}

test_and_log_util::result_type test_dgbi_is_mag_one(test_and_log_util::out_type&){
    DGB_Int testee(-1);

    test_and_log_util::result_type res;
    res.expected = "Testee has magnitude of one.";
    res.actual = "Testee has magnitude of ";
    res.actual += (!testee.is_mag_one() ? "not " : "");
    res.actual += "one.";

    return res;
}

test_and_log_util::result_type test_dgbi_is_even(test_and_log_util::out_type&){
    DGB_Int testee(0xA4);

    test_and_log_util::result_type res;
    res.expected = "Testee is even.";
    res.actual = "Testee is ";
    res.actual += (!testee.is_even() ? "not " : "");
    res.actual += "even.";

    return res;
}

test_and_log_util::result_type test_dgbi_is_odd(test_and_log_util::out_type&){
    DGB_Int testee(0xA3);

    test_and_log_util::result_type res;
    res.expected = "Testee is odd.";
    res.actual = "Testee is ";
    res.actual += (!testee.is_odd() ? "not " : "");
    res.actual += "odd.";

    return res;
}

test_and_log_util::result_type test_dgbi_digit_list(test_and_log_util::out_type&){
    DGB_Int testee(-0xA9E38F01, 0x10);

    test_and_log_util::result_type res;
    res.expected = "FF07C165";

    DGB_Int::image_set_type isi = testee.image_set();
<<<<<<< HEAD
    for(auto it = testee.digit_string().begin(); it != testee.digit_string().end(); ++it)
=======
    for(auto it = testee.digit_list().begin(); it != testee.digit_list().end(); ++it)
>>>>>>> 8aa772d478473c9a5631f16901893c2d6e710d1b
        res.actual.push_back(isi.digit(*it));

    return res;
}

test_and_log_util::result_type test_dgbi_count_digits(test_and_log_util::out_type&){
<<<<<<< HEAD
    DGB_Int testee(DGB_Int::digstr_type(1000, 7), 1);
=======
    DGB_Int testee(DGB_Int::diglist_type(1000, 7), 1);
>>>>>>> 8aa772d478473c9a5631f16901893c2d6e710d1b

    test_and_log_util::result_type res;
    res.expected = "Testee is 1000 digits.";
    res.actual = "Testee is ";
    res.actual += (testee.count_digits()!=1000 ? "not " : "");
    res.actual += "1000 digits.";

    return res;
}

test_and_log_util::result_type test_dgbi_digit(test_and_log_util::out_type&){
    DGB_Int testee(1234567890);

    test_and_log_util::result_type res;
    res.expected = "0987654321000";
    for(unsigned i = 0; i < testee.count_digits()+3; ++i)
        res.actual.push_back(testee.digit(i) + '0');

    return res;
}

test_and_log_util::result_type test_dgbi_shift(test_and_log_util::out_type&){
    DGB_Int testee(1234567890);

    testee.shift(7);
    testee.shift(-11);

    test_and_log_util::result_type res;
    res.expected = "+123456";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_dgbi_shift_left(test_and_log_util::out_type&){
    DGB_Int testee(1234567890);

    testee.shift_left(7);

    test_and_log_util::result_type res;
    res.expected = "+12345678900000000";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_dgbi_shift_right(test_and_log_util::out_type&){
    DGB_Int testee(1234567890);

    testee.shift_right(11);

    test_and_log_util::result_type res;
    res.expected = "+0";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_dgbi_append(test_and_log_util::out_type&){
    DGB_Int testee(0, 20);

    testee.append(17);
    testee.append(0xF);
    testee.append(7);

    test_and_log_util::result_type res;
    res.expected = "+7FH0";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_dgbi_detach(test_and_log_util::out_type&){
    DGB_Int testee(11);

    testee.detach();
    testee.detach();
    testee.detach();

    test_and_log_util::result_type res;
    res.expected = "+0";
    res.actual = testee.str();

    return res;
}

// Signed Interface tests
test_and_log_util::result_type test_dgbi_is_positive(test_and_log_util::out_type&){
    DGB_Int testee;

    test_and_log_util::result_type res;
    res.expected = "Testee is positive.";
    res.actual = "Testee is ";
    res.actual += (!testee.is_positive() ? "not " : "");
    res.actual += "positive.";

    return res;
}

test_and_log_util::result_type test_dgbi_is_negative(test_and_log_util::out_type&){
    DGB_Int testee(-1);

    test_and_log_util::result_type res;
    res.expected = "Testee is negative.";
    res.actual = "Testee is ";
    res.actual += (!testee.is_negative() ? "not " : "");
    res.actual += "negative.";

    return res;
}

test_and_log_util::result_type test_dgbi_sign(test_and_log_util::out_type&){
    DGB_Int testee(-133);

    test_and_log_util::result_type res;
    res.expected = "Testee is -1.";
    res.actual = "Testee is ";
    res.actual += (testee.sign() != -1 ? "not " : "");
    res.actual += "-1.";

    return res;
}

test_and_log_util::result_type test_dgbi_negate(test_and_log_util::out_type&){
    DGB_Int testee(11);

    testee.negate();

    test_and_log_util::result_type res;
    res.expected = "-11";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_dgbi_make_positive(test_and_log_util::out_type&){
    DGB_Int testee(-11);

    testee.make_positive();

    test_and_log_util::result_type res;
    res.expected = "+11";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_dgbi_make_negative(test_and_log_util::out_type&){
    DGB_Int testee(6);

    testee.make_negative();

    test_and_log_util::result_type res;
    res.expected = "-6";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_dgbi_sign_assign(test_and_log_util::out_type&){
    DGB_Int testee(777);

    testee.sign(-5);

    test_and_log_util::result_type res;
    res.expected = "-777";
    res.actual = testee.str();

    return res;
}


// Int read-only tests
test_and_log_util::result_type test_dgbi_magnitude(test_and_log_util::out_type&){
    DGB_Int testee(-8932753);

    testee = testee.magnitude();

    test_and_log_util::result_type res;
    res.expected = "+8932753";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_dgbi_compare(test_and_log_util::out_type&){
    DGB_Int testee(-8932753), testee2;

    test_and_log_util::result_type res;
    res.expected = "Testee is less.";
    res.actual = "Testee is ";
    res.actual += (!(testee.compare(testee2) < 0) ? "not " : "");
    res.actual += "less.";

    return res;
}

test_and_log_util::result_type test_dgbi_negative(test_and_log_util::out_type&){
    DGB_Int testee(-8932753);

    testee = -testee;

    test_and_log_util::result_type res;
    res.expected = "+8932753";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_dgbi_is_one(test_and_log_util::out_type&){
    DGB_Int testee(1);

    test_and_log_util::result_type res;
    res.expected = "Testee is +1.";
    res.actual = "Testee is ";
    res.actual += (!testee.is_one() ? "not " : "");
    res.actual += "+1.";

    return res;
}

test_and_log_util::result_type test_dgbi_is_neg_one(test_and_log_util::out_type&){
    DGB_Int testee(-1);

    test_and_log_util::result_type res;
    res.expected = "Testee is -1.";
    res.actual = "Testee is ";
    res.actual += (!testee.is_neg_one() ? "not " : "");
    res.actual += "-1.";

    return res;
}

test_and_log_util::result_type test_dgbi_base(test_and_log_util::out_type&){
    DGB_Int testee, testee2(0, 45);

    test_and_log_util::result_type res;
    res.expected = "Base 1 is 10. Base 2 is 45.";
    res.actual = "Base 1 is ";
    res.actual += ((testee.base() == 10) ? "" : "not ");
    res.actual += "10.";
    res.actual += " Base 2 is ";
    res.actual += ((testee2.base() == 45) ? "" : "not ");
    res.actual += "45.";

    return res;
}

test_and_log_util::result_type test_dgbi_str(test_and_log_util::out_type&){
    DGB_Int testee("+2837ONI3U29S823WELP2L32903N", 35);

    test_and_log_util::result_type res;
    res.expected = "+2837ONI3U29S823WELP2L32903N";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_dgbi_sci_note(test_and_log_util::out_type&){
    DGB_Int testee("+2837ONI3U29S823WELP2L32903N", 35);

    test_and_log_util::result_type res;
    res.expected = "+2.837ONI3U29S823WELP2L32903NeQ";
    res.actual = testee.sci_note();

    return res;
}

test_and_log_util::result_type test_dgbi_sci_note_w_spaces(test_and_log_util::out_type&){
    DGB_Int testee("+2837ONI3U29S823WELP2L32903N", 35);

    test_and_log_util::result_type res;
    res.expected = "+ 2.837ONI3U29S823WELP2L32903N e Q";
    res.actual = testee.sci_note_w_spaces();

    return res;
}

test_and_log_util::result_type test_dgbi_abstract(test_and_log_util::out_type&){
    DGB_Int testee("+1337");

    test_and_log_util::result_type res;
    res.expected = "leet";
    res.actual.clear();

    DGB_Int::abstract_type abs = testee.abstract();
    for(DGB_Int::size_type i = 0; i < abs.count_digits(); ++i){
        switch(abs.digit(i)){
            case 1:
                res.actual.push_back('t');
                break;
            case 3:
                res.actual.push_back('e');
                break;
            case 7:
                res.actual.push_back('l');
                break;
            default:
                res.actual.push_back('~');
                break;
        }
    }

    return res;
}


// Int modifier tests
test_and_log_util::result_type test_dgbi_make_zero(test_and_log_util::out_type&){
    DGB_Int testee(-8932753);

    testee.make_zero();

    test_and_log_util::result_type res;
    res.expected = "+0";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_dgbi_make_one(test_and_log_util::out_type&){
    DGB_Int testee(-8932753);

    testee.make_one();

    test_and_log_util::result_type res;
    res.expected = "+1";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_dgbi_make_neg_one(test_and_log_util::out_type&){
    DGB_Int testee(-8932753);

    testee.make_neg_one();

    test_and_log_util::result_type res;
    res.expected = "-1";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_dgbi_make_two(test_and_log_util::out_type&){
    DGB_Int testee(-8932753);

    testee.make_two();

    test_and_log_util::result_type res;
    res.expected = "+2";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_dgbi_halve(test_and_log_util::out_type&){
    DGB_Int testee(8932753, 0x10);

    testee.halve();

    test_and_log_util::result_type res;
    res.expected = "+4426C8";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_dgbi_halve_spec(test_and_log_util::out_type&){
<<<<<<< HEAD
    DGB_Int testee(DGB_Int::digstr_type({0, 1, 2, 3, 4, 0, 6, 7, 8, 9}), -1);
=======
    DGB_Int testee(DGB_Int::diglist_type({0, 1, 2, 3, 4, 0, 6, 7, 8, 9}), -1);
>>>>>>> 8aa772d478473c9a5631f16901893c2d6e710d1b

    testee.halve();

    test_and_log_util::result_type res;
    res.expected = "-4938021605";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_dgbi_assign(test_and_log_util::out_type&){
    DGB_Int testee(-8932753, 17);

    testee.assign(100, 5);
    testee.assign(4, 15);
    testee.assign(2, 8);

    test_and_log_util::result_type res;
    res.expected = "-6FG831";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_dgbi_force_assign(test_and_log_util::out_type&){
    DGB_Int testee(-8932753);

    testee.force_assign(10, 5);
    testee.force_assign(4, 15);
    testee.force_assign(0, 8);

    test_and_log_util::result_type res;
    res.expected = "-50008932758";
    res.actual = testee.str();

    return res;
}

// Arithmetic tests
test_and_log_util::result_type test_dgbi_add(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+8079B04";
    res.actual = (diff_base_int + rev_digs_int).str();

    return res;
}

test_and_log_util::result_type test_dgbi_sub(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+9753086421";
    res.actual = (all_digs_int - rev_digs_int).str();

    return res;
}

test_and_log_util::result_type test_dgbi_mult(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+111203703705093750";
    res.actual = (all_digs_int * diff_base_int).str();

    return res;
}

test_and_log_util::result_type test_dgbi_div(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+80";
    res.actual = (all_digs_int / rev_digs_int).str();

    return res;
}

test_and_log_util::result_type test_dgbi_mod(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+0";
    res.actual = (all_digs_int % two_int).str();

    return res;
}

test_and_log_util::result_type test_dgbi_pre_dec(test_and_log_util::out_type&){
    DGB_Int testee;

    test_and_log_util::result_type res;
    res.expected = "-1";
    res.actual = (--testee).str();

    return res;
}

test_and_log_util::result_type test_dgbi_post_dec(test_and_log_util::out_type&){
    DGB_Int testee;
    DGB_Int testee2 = testee--;

    test_and_log_util::result_type res;
    res.expected = "-1 +0";
    res.actual = testee.str() + " " + testee2.str();

    return res;
}

test_and_log_util::result_type test_dgbi_pre_inc(test_and_log_util::out_type&){
    DGB_Int testee;

    test_and_log_util::result_type res;
    res.expected = "+1";
    res.actual = (++testee).str();

    return res;
}

test_and_log_util::result_type test_dgbi_post_inc(test_and_log_util::out_type&){
    DGB_Int testee;
    DGB_Int testee2 = testee++;

    test_and_log_util::result_type res;
    res.expected = "+1 +0";
    res.actual = testee.str() + " " + testee2.str();

    return res;
}

// Bitwise tests
test_and_log_util::result_type test_dgbi_and(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+10487018";
    res.actual = (all_digs_int & diff_base_int).str();

    return res;
}

test_and_log_util::result_type test_dgbi_or(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+9931841535";
    res.actual = (all_digs_int | rev_digs_int).str();

    return res;
}

test_and_log_util::result_type test_dgbi_xor(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+7F000FA";
    res.actual = (diff_base_int ^ rev_digs_int).str();

    return res;
}

test_and_log_util::result_type test_dgbi_compl(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "-543210";
    res.actual = (~diff_base_int).str();

    return res;
}

test_and_log_util::result_type test_dgbi_lshift(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+2528395061760";
    res.actual = (all_digs_int << eight_int).str();

    return res;
}

test_and_log_util::result_type test_dgbi_rshift(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+38580246";
    res.actual = (all_digs_int >> eight_int).str();

    return res;
}


// Logical tests
test_and_log_util::result_type test_dgbi_log_and(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+848008480";
    res.actual = (all_digs_int.logical_and(rev_digs_int)).str();

    return res;
}

test_and_log_util::result_type test_dgbi_log_or(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+9151991519";
    res.actual = (all_digs_int.logical_or(rev_digs_int)).str();

    return res;
}

test_and_log_util::result_type test_dgbi_log_xor(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+9999999999";
    res.actual = (all_digs_int.logical_xor(rev_digs_int)).str();

    return res;
}

test_and_log_util::result_type test_dgbi_log_compl(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "-543210";
    res.actual = diff_base_int.logical_complement().str();

    return res;
}

test_and_log_util::result_type test_dgbi_log_lshift(test_and_log_util::out_type&){
    DGB_Int testee(1234567890);

    test_and_log_util::result_type res;
    res.expected = "+12345678900000000";
    res.actual = (testee.logical_shift_left(7)).str();

    return res;
}

test_and_log_util::result_type test_dgbi_log_rshift(test_and_log_util::out_type&){
    DGB_Int testee(1234567890);

    test_and_log_util::result_type res;
    res.expected = "+0";
    res.actual = (testee.logical_shift_right(11)).str();

    return res;
}

test_and_log_util::result_type test_dgbi_log_shift(test_and_log_util::out_type&){
    DGB_Int testee(1234567890);

    test_and_log_util::result_type res;
    res.expected = "+123456";
    res.actual = (testee.logical_shift(7).logical_shift(-11)).str();

    return res;
}



// Template tests
test_and_log_util::result_type test_dgbi_custom_image_int(test_and_log_util::out_type&){
    char const *const new_digs = ")!@#$%^&*(",
               *const new_syms = "=_>3\t?1"
               ;

    DGB_Int testee(1274893786, new_digs, new_syms);

    test_and_log_util::result_type res;
    res.expected = "=!@&$*(#&*^";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_dgbi_custom_image_str(test_and_log_util::out_type&){
    char const *const new_digs = ")!@#$%^&*(`~-+*/",
               *const new_syms = "=_>3\t?1"
               ;
    using Shift_Int = Precision::General_Base::Dynamic::Int
                    <char, char const *, Precision::Default::byte_type,
                    std::vector, Precision::Default::sign_type,
                    Precision::ImgSearchPolicy::Normal
                    >;

    Shift_Int::str_type bad_str("_!)df~@@#*(@f hg@*#(*e/g)# @$3@");

    Shift_Int testee(bad_str, 0x10, new_digs, new_syms);

    test_and_log_util::result_type res;
    res.expected = "_!)))~@@#*(@))))@*#(*)/))#)@$))";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_dgbi_custom_image_mult(test_and_log_util::out_type&){
    char const *const new_digs = ")!@#$%^&*(",
               *const new_syms = "=_>3\t?1"
               ;

    DGB_Int testee1(64, new_digs, new_syms), testee2(127, new_digs, new_syms);

    test_and_log_util::result_type res;
    res.expected = "=*!@*";
    res.actual = (testee1 * testee2).str();

    return res;
}

#include <sstream>

template <typename Iterator>
test_and_log_util::str_type num_str_to_str(Iterator beg, Iterator end){
    test_and_log_util::str_type toreturn;
    for(; beg != end; ++beg){
        std::stringstream ss;
        ss << *beg;
        toreturn += ss.str();
    }
    return toreturn;
}

test_and_log_util::result_type test_dgbi_custom_iter(test_and_log_util::out_type&){
    using img_type = int;
    using int_str = std::vector<img_type>;
    int_str new_digs({0, 1, 2, 3, 4, 5, 6, 7, 8, 9}),
            new_syms({100, 200, 300, 400, 500, 600, 700})
            ;
    using num_Int = Precision::General_Base::Dynamic::Int
                    <img_type, int_str::const_iterator>;

    num_Int testee(-72348, new_digs.cbegin(), new_syms.cbegin());

    num_Int::str_type num_str = testee.sci_note_w_spaces();

    test_and_log_util::result_type res;
    res.expected = "200500730023485004005004";
    res.actual = num_str_to_str(num_str.cbegin(), num_str.cend());

    return res;
}