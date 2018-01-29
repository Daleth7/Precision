#include "Test_Shared_Utilities.h"

#include "general_base/impl/Precision_Image_Set_Interface.h"

using test_digit_type = std::uint_fast8_t;
using Img_Set_Type = Precision::Image_Set_Interface<char, char const *, test_digit_type>;

static char const * const digs = "0123456789";
static char const * const syms = "+-.e /i";
static char const * const dig_speed = " !\"#$%&'()*+,-./0123456789:;<=>?"
                                      "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
                                      "abcdefghijklmnopqrstuvwxyz{|}~"
                                      ;
std::size_t dig_speed_size = 94;
const char missing_char = '`';

static Img_Set_Type img_set(digs, syms);
static Img_Set_Type img_speed_set(dig_speed, syms);

test_and_log_util::result_type test_is_valid(test_and_log_util::out_type&);
test_and_log_util::result_type test_get_index(test_and_log_util::out_type&);
void test_get_index_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_get_index_wrong(test_and_log_util::out_type&);
void test_get_index_wrong_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_get_index_wrong_norm(test_and_log_util::out_type&);
void test_get_index_wrong_norm_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_digit(test_and_log_util::out_type&);
void test_digit_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_symbol(test_and_log_util::out_type&);
test_and_log_util::result_type test_plus(test_and_log_util::out_type&);
test_and_log_util::result_type test_minus(test_and_log_util::out_type&);
test_and_log_util::result_type test_point(test_and_log_util::out_type&);
test_and_log_util::result_type test_exponent(test_and_log_util::out_type&);
test_and_log_util::result_type test_space(test_and_log_util::out_type&);
test_and_log_util::result_type test_slash(test_and_log_util::out_type&);
test_and_log_util::result_type test_imaginary(test_and_log_util::out_type&);
test_and_log_util::result_type test_digit_set(test_and_log_util::out_type&);
test_and_log_util::result_type test_symbol_set(test_and_log_util::out_type&);

void image_set_interface_test(){
    test_and_log_util test_list("Precision::Image_Set_Interface", __FILE__);
        test_list.set_log_output(test_log);
        test_list.set_console_output(test_console);
        test_list.set_assert(true);

    ADD_TEST(test_list, test_is_valid);
    ADD_TEST_BOTH( test_list,
                   test_get_index, test_get_index_speed,
                   10000
                   );
    ADD_TEST_BOTH( test_list,
                   test_get_index_wrong, test_get_index_wrong_speed,
                   10000
                   );
    ADD_TEST_BOTH( test_list,
                   test_get_index_wrong_norm, test_get_index_wrong_norm_speed,
                   10000
                   );
    ADD_TEST_BOTH( test_list,
                   test_digit, test_digit_speed,
                   10000
                   );
    ADD_TEST(test_list, test_symbol);
    ADD_TEST(test_list, test_plus);
    ADD_TEST(test_list, test_minus);
    ADD_TEST(test_list, test_point);
    ADD_TEST(test_list, test_exponent);
    ADD_TEST(test_list, test_space);
    ADD_TEST(test_list, test_slash);
    ADD_TEST(test_list, test_imaginary);
    ADD_TEST(test_list, test_digit_set);
    ADD_TEST(test_list, test_symbol_set);

    test_list.execute_tests();
}

test_and_log_util::result_type test_is_valid(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "true";
    res.actual = img_set.is_valid<>('4', 10) ? "true" : "false";

    return res;
}

test_and_log_util::result_type test_get_index(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "7777777";
    res.actual.insert(0, img_set.get_index<>('7', 10), '7');

    return res;
}

void test_get_index_speed(test_and_log_util::out_type&){
    volatile test_digit_type idx = img_speed_set.get_index<>('\\', dig_speed_size);
    idx = idx;
}

test_and_log_util::result_type test_get_index_wrong(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "||||||||||";
    res.actual.insert(0, img_set.get_index<>('#', 10), '|');

    return res;
}

void test_get_index_wrong_speed(test_and_log_util::out_type&){
    volatile test_digit_type idx = img_speed_set.get_index<>(missing_char, dig_speed_size);
    idx = idx;
}

test_and_log_util::result_type test_get_index_wrong_norm(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "||||||||||";
    res.actual.insert(0, img_set.get_index
        <Precision::ImgSearchPolicy::Normal>('#', 10), '|');

    return res;
}

void test_get_index_wrong_norm_speed(test_and_log_util::out_type&){
    volatile test_digit_type idx = img_speed_set.get_index
        <Precision::ImgSearchPolicy::Normal>(missing_char, dig_speed_size);
    idx = idx;
}

test_and_log_util::result_type test_digit(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "7";
    res.actual.insert(0, 1, img_set.digit(7));

    return res;
}

void test_digit_speed(test_and_log_util::out_type&){
    volatile Img_Set_Type::image_type img = img_speed_set.digit(42);
    img = img;
}

test_and_log_util::result_type test_symbol(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = " ";
    res.actual.insert(0, 1, img_set.symbol(4));

    return res;
}

test_and_log_util::result_type test_plus(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+";
    res.actual.insert(0, 1, img_set.plus());

    return res;
}

test_and_log_util::result_type test_minus(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "-";
    res.actual.insert(0, 1, img_set.minus());

    return res;
}

test_and_log_util::result_type test_point(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = ".";
    res.actual.insert(0, 1, img_set.point());

    return res;
}

test_and_log_util::result_type test_exponent(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "e";
    res.actual.insert(0, 1, img_set.exponent());

    return res;
}

test_and_log_util::result_type test_space(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = " ";
    res.actual.insert(0, 1, img_set.space());

    return res;
}

test_and_log_util::result_type test_slash(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "/";
    res.actual.insert(0, 1, img_set.slash());

    return res;
}

test_and_log_util::result_type test_imaginary(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "i";
    res.actual.insert(0, 1, img_set.imaginary());

    return res;
}

test_and_log_util::result_type test_digit_set(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "0123456789";
    res.actual = img_set.digit_set();

    return res;
}

test_and_log_util::result_type test_symbol_set(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+-.e /i";
    res.actual = img_set.symbol_set();

    return res;
}