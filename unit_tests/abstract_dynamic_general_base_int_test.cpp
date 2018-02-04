#include "Test_Shared_Utilities.h"

#include "general_base/Int_Dynamic_Abstract_Base.h"
#include "general_base/impl/Precision_Int_Operations_Img.h"

#include <list>

// Constructor tests
test_and_log_util::result_type test_adgbi_default(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_new_base(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_signed_size(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_diglist(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_iterators(test_and_log_util::out_type&);

// Digit Container tests
test_and_log_util::result_type test_adgbi_is_zero(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_is_mag_one(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_is_even(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_is_odd(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_digit_list(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_count_digits(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_digit(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_shift(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_shift_left(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_shift_right(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_append(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_detach(test_and_log_util::out_type&);

// Signed Interface tests
test_and_log_util::result_type test_adgbi_is_positive(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_is_negative(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_sign(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_negate(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_make_positive(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_make_negative(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_sign_assign(test_and_log_util::out_type&);

// Int read-only tests
test_and_log_util::result_type test_adgbi_magnitude(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_compare(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_negative(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_is_one(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_is_neg_one(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_base(test_and_log_util::out_type&);

// Int modifier tests
test_and_log_util::result_type test_adgbi_make_zero(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_make_one(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_make_neg_one(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_make_two(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_halve(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_halve_spec(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_assign(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_force_assign(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_set_base(test_and_log_util::out_type&);

// Arithmetic tests
test_and_log_util::result_type test_adgbi_add(test_and_log_util::out_type&);
void test_adgbi_add_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_sub(test_and_log_util::out_type&);
void test_adgbi_sub_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_mult(test_and_log_util::out_type&);
void test_adgbi_mult_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_div(test_and_log_util::out_type&);
void test_adgbi_div_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_mod(test_and_log_util::out_type&);
void test_adgbi_mod_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_pre_dec(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_post_dec(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_pre_inc(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_post_inc(test_and_log_util::out_type&);

// Bitwise tests
test_and_log_util::result_type test_adgbi_and(test_and_log_util::out_type&);
void test_adgbi_and_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_or(test_and_log_util::out_type&);
void test_adgbi_or_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_xor(test_and_log_util::out_type&);
void test_adgbi_xor_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_compl(test_and_log_util::out_type&);
void test_adgbi_compl_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_lshift(test_and_log_util::out_type&);
void test_adgbi_lshift_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_rshift(test_and_log_util::out_type&);
void test_adgbi_rshift_speed(test_and_log_util::out_type&);

// Logical tests
test_and_log_util::result_type test_adgbi_log_and(test_and_log_util::out_type&);
void test_adgbi_log_and_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_log_or(test_and_log_util::out_type&);
void test_adgbi_log_or_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_log_xor(test_and_log_util::out_type&);
void test_adgbi_log_xor_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_log_compl(test_and_log_util::out_type&);
void test_adgbi_log_compl_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_log_lshift(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_log_rshift(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_log_shift(test_and_log_util::out_type&);

// Customer template parameter tests
test_and_log_util::result_type test_adgbi_cust_dig(test_and_log_util::out_type&);
test_and_log_util::result_type test_adgbi_cust_contain(test_and_log_util::out_type&);
void test_adgbi_cust_contain_speed(test_and_log_util::out_type&);

void setup_adgbi_variables();
// Cleanup function to free memory
void cleanup_adgbi();

using ADGB_Int = Precision::General_Base::Dynamic::Abstract::Int<>;
template <typename Data_Type>
struct dumb_container : public std::list<Data_Type>{
    using list_type = std::list<Data_Type>;

    using typename list_type::const_reference;
    using typename list_type::reference;
    using typename list_type::size_type;
    using typename list_type::const_iterator;
    using typename list_type::iterator;
    using typename list_type::value_type;

    const_reference operator[](size_type idx)const{
        const_iterator cit = this->cbegin();
        std::advance(cit, idx);
        return *cit;
    }

    reference operator[](size_type idx){
        iterator it = this->begin();
        std::advance(it, idx);
        return *it;
    }

    dumb_container() = default;
    dumb_container(size_type sz, value_type val)
        : list_type(sz, val)
    {}
};
using list_Int = Precision::General_Base::Dynamic::Abstract::Int
    <Precision::Default::byte_type, dumb_container>;

template <class ABS_Int_Type>
test_and_log_util::str_type to_str(const ABS_Int_Type& num);
template <class ABS_Int_Type, typename Base_Type>
ABS_Int_Type to_adgbi(const test_and_log_util::str_type& src, Base_Type base);

// Variables for functionality tests
static ADGB_Int all_digs_int, rev_digs_int, diff_base_int, two_int, eight_int;

// Variables for speed tests
static ADGB_Int speed_100digs, rev_100digs, diff_100digs, hun_int, quart_hun_int;
static list_Int speed_list_100digs, rev_list_100digs;

void abstract_dynamic_general_base_int_test(){
    test_and_log_util test_list( "Precision::General_Base::Dynamic::"
                                 "Abstract::Int", __FILE__);
        test_list.set_log_output(test_log);
        test_list.set_console_output(test_console);
        test_list.set_assert(true);

    ADD_TEST(test_list, test_adgbi_default);
    ADD_TEST(test_list, test_adgbi_new_base);
    ADD_TEST(test_list, test_adgbi_signed_size);
    ADD_TEST(test_list, test_adgbi_diglist);
    ADD_TEST(test_list, test_adgbi_iterators);
    ADD_TEST(test_list, test_adgbi_is_zero);
    ADD_TEST(test_list, test_adgbi_is_mag_one);
    ADD_TEST(test_list, test_adgbi_is_even);
    ADD_TEST(test_list, test_adgbi_is_odd);
    ADD_TEST(test_list, test_adgbi_digit_list);
    ADD_TEST(test_list, test_adgbi_count_digits);
    ADD_TEST(test_list, test_adgbi_shift_left);
    ADD_TEST(test_list, test_adgbi_shift_right);
    ADD_TEST(test_list, test_adgbi_append);
    ADD_TEST(test_list, test_adgbi_detach);

    ADD_TEST(test_list, test_adgbi_is_positive);
    ADD_TEST(test_list, test_adgbi_is_negative);
    ADD_TEST(test_list, test_adgbi_sign);
    ADD_TEST(test_list, test_adgbi_negate);
    ADD_TEST(test_list, test_adgbi_make_positive);
    ADD_TEST(test_list, test_adgbi_make_negative);
    ADD_TEST(test_list, test_adgbi_sign_assign);

    ADD_TEST(test_list, test_adgbi_magnitude);
    ADD_TEST(test_list, test_adgbi_compare);
    ADD_TEST(test_list, test_adgbi_negative);
    ADD_TEST(test_list, test_adgbi_is_one);
    ADD_TEST(test_list, test_adgbi_is_neg_one);
    ADD_TEST(test_list, test_adgbi_base);

    ADD_TEST(test_list, test_adgbi_make_zero);
    ADD_TEST(test_list, test_adgbi_make_one);
    ADD_TEST(test_list, test_adgbi_make_neg_one);
    ADD_TEST(test_list, test_adgbi_make_two);
    ADD_TEST(test_list, test_adgbi_halve);
    ADD_TEST(test_list, test_adgbi_halve_spec);
    ADD_TEST(test_list, test_adgbi_assign);
    ADD_TEST(test_list, test_adgbi_force_assign);
    ADD_TEST(test_list, test_adgbi_set_base);

    ADD_TEST_BOTH(test_list, test_adgbi_add, test_adgbi_add_speed,   50);
    ADD_TEST_BOTH(test_list, test_adgbi_sub, test_adgbi_sub_speed,   500);
    ADD_TEST_BOTH(test_list, test_adgbi_mult, test_adgbi_mult_speed, 50);
    ADD_TEST_BOTH(test_list, test_adgbi_div, test_adgbi_div_speed,   500);
    ADD_TEST_BOTH(test_list, test_adgbi_mod, test_adgbi_mod_speed,   500);
    ADD_TEST(test_list, test_adgbi_pre_dec);
    ADD_TEST(test_list, test_adgbi_post_dec);
    ADD_TEST(test_list, test_adgbi_pre_inc);
    ADD_TEST(test_list, test_adgbi_post_inc);

    ADD_TEST_BOTH(test_list, test_adgbi_and, test_adgbi_and_speed, 1);
    ADD_TEST_BOTH(test_list, test_adgbi_or, test_adgbi_or_speed, 1);
    ADD_TEST_BOTH(test_list, test_adgbi_xor, test_adgbi_xor_speed, 1);
    ADD_TEST_BOTH(test_list, test_adgbi_compl, test_adgbi_compl_speed, 1);
    ADD_TEST_BOTH(test_list, test_adgbi_lshift, test_adgbi_lshift_speed, 10);
    ADD_TEST_BOTH(test_list, test_adgbi_rshift, test_adgbi_rshift_speed, 10);

    ADD_TEST_BOTH(test_list, test_adgbi_log_and, test_adgbi_log_and_speed, 100);
    ADD_TEST_BOTH(test_list, test_adgbi_log_or, test_adgbi_log_or_speed, 500);
    ADD_TEST_BOTH(test_list, test_adgbi_log_xor, test_adgbi_log_xor_speed, 100);
    ADD_TEST_BOTH(test_list, test_adgbi_log_compl, test_adgbi_log_compl_speed, 500);
    ADD_TEST(test_list, test_adgbi_log_lshift);
    ADD_TEST(test_list, test_adgbi_log_rshift);
    ADD_TEST(test_list, test_adgbi_log_shift);

    ADD_TEST(test_list, test_adgbi_cust_dig);
    ADD_TEST_BOTH(test_list, test_adgbi_cust_contain, test_adgbi_cust_contain_speed, 10000);

    setup_adgbi_variables();

    test_list.execute_tests();

    cleanup_adgbi();
}

void setup_adgbi_variables(){
    all_digs_int = to_adgbi<ADGB_Int, ADGB_Int::digit_type>("9876543210", 10);
    rev_digs_int = to_adgbi<ADGB_Int, ADGB_Int::digit_type>("123456789", 10);
    diff_base_int = to_adgbi<ADGB_Int, ADGB_Int::digit_type>("123456789", 0x10);
    two_int.make_two();
    two_int.base(3);
    eight_int = ADGB_Int(8);

    speed_100digs = ADGB_Int(ADGB_Int::diglist_type(100, 7), 1, 15);
    rev_100digs = ADGB_Int(ADGB_Int::diglist_type(100, 9), -1, 10);
    diff_100digs = ADGB_Int(ADGB_Int::diglist_type(100, 0xC), 1, 21);
    hun_int = ADGB_Int(100, 7);
    quart_hun_int = ADGB_Int(25);
    speed_list_100digs = list_Int(list_Int::diglist_type(100, 7), 1);
    rev_list_100digs = list_Int(list_Int::diglist_type(100, 9), -1);
}

void cleanup_adgbi(){
    all_digs_int.make_zero();
    rev_digs_int.make_zero();
    diff_base_int.make_zero();
    speed_100digs.make_zero();
    rev_100digs.make_zero();
    diff_100digs.make_zero();
    speed_list_100digs.make_zero();
    rev_list_100digs.make_zero();
}

// Constructor tests
test_and_log_util::result_type test_adgbi_default(test_and_log_util::out_type&){
    ADGB_Int testee;

    test_and_log_util::result_type res;
    res.expected = "+0";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_adgbi_new_base(test_and_log_util::out_type&){
    ADGB_Int testee(0, 7);

    test_and_log_util::result_type res;
    res.expected = "+0777";
    res.actual = to_str(testee) + test_and_log_util::str_type(3, testee.base() + '0');

    return res;
}

test_and_log_util::result_type test_adgbi_signed_size(test_and_log_util::out_type&){
    ADGB_Int testee(-1236547890);

    test_and_log_util::result_type res;
    res.expected = "-1236547890";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_adgbi_diglist(test_and_log_util::out_type&){
    ADGB_Int::diglist_type diglist({1, 3, 2, 0, 8, 9, 77, 4, 0, 0});

    ADGB_Int testee(diglist, 1);

    test_and_log_util::result_type res;
    res.expected = "+40980231";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_adgbi_iterators(test_and_log_util::out_type&){
    int bad_str[14] = {0, 0, 1, 4, 3, -5, 9, 5, 66, 7, 1, 0, 1, 0};

    ADGB_Int testee(static_cast<int*>(bad_str), bad_str+14, 1);

    test_and_log_util::result_type res;
    res.expected = "+1017059034100";
    res.actual = to_str(testee);

    return res;
}

// Digit Container tests
test_and_log_util::result_type test_adgbi_is_zero(test_and_log_util::out_type&){
    ADGB_Int testee;

    test_and_log_util::result_type res;
    res.expected = "Testee is zero.";
    res.actual = "Testee is ";
    res.actual += (!testee.is_zero() ? "not " : "");
    res.actual += "zero.";

    return res;
}

test_and_log_util::result_type test_adgbi_is_mag_one(test_and_log_util::out_type&){
    ADGB_Int testee(-1);

    test_and_log_util::result_type res;
    res.expected = "Testee has magnitude of one.";
    res.actual = "Testee has magnitude of ";
    res.actual += (!testee.is_mag_one() ? "not " : "");
    res.actual += "one.";

    return res;
}

test_and_log_util::result_type test_adgbi_is_even(test_and_log_util::out_type&){
    ADGB_Int testee(0xA4);

    test_and_log_util::result_type res;
    res.expected = "Testee is even.";
    res.actual = "Testee is ";
    res.actual += (!testee.is_even() ? "not " : "");
    res.actual += "even.";

    return res;
}

test_and_log_util::result_type test_adgbi_is_odd(test_and_log_util::out_type&){
    ADGB_Int testee(0xA3);

    test_and_log_util::result_type res;
    res.expected = "Testee is odd.";
    res.actual = "Testee is ";
    res.actual += (!testee.is_odd() ? "not " : "");
    res.actual += "odd.";

    return res;
}

test_and_log_util::result_type test_adgbi_digit_list(test_and_log_util::out_type&){
    ADGB_Int testee(-123654879);

    test_and_log_util::result_type res;
    res.expected = "978456321";

    for(auto it = testee.digit_list().begin(); it != testee.digit_list().end(); ++it)
        res.actual.push_back(*it + '0');

    return res;
}

test_and_log_util::result_type test_adgbi_count_digits(test_and_log_util::out_type&){
    ADGB_Int testee(ADGB_Int::diglist_type(1000, 7), 1);

    test_and_log_util::result_type res;
    res.expected = "Testee is 1000 digits.";
    res.actual = "Testee is ";
    res.actual += (testee.count_digits()!=1000 ? "not " : "");
    res.actual += "1000 digits.";

    return res;
}

test_and_log_util::result_type test_adgbi_digit(test_and_log_util::out_type&){
    ADGB_Int testee(1234567890);

    test_and_log_util::result_type res;
    res.expected = "0987654321000";
    for(unsigned i = 0; i < testee.count_digits()+3; ++i)
        res.actual.push_back(testee.digit(i) + '0');

    return res;
}

test_and_log_util::result_type test_adgbi_shift(test_and_log_util::out_type&){
    ADGB_Int testee(1234567890);

    testee.shift(7);
    testee.shift(-11);

    test_and_log_util::result_type res;
    res.expected = "+123456";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_adgbi_shift_left(test_and_log_util::out_type&){
    ADGB_Int testee(1234567890);

    testee.shift_left(7);

    test_and_log_util::result_type res;
    res.expected = "+12345678900000000";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_adgbi_shift_right(test_and_log_util::out_type&){
    ADGB_Int testee(1234567890);

    testee.shift_right(11);

    test_and_log_util::result_type res;
    res.expected = "+0";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_adgbi_append(test_and_log_util::out_type&){
    ADGB_Int testee;

    testee.append(9);
    testee.append(0);
    testee.append(7);

    test_and_log_util::result_type res;
    res.expected = "+790";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_adgbi_detach(test_and_log_util::out_type&){
    ADGB_Int testee(11);

    testee.detach();
    testee.detach();
    testee.detach();

    test_and_log_util::result_type res;
    res.expected = "+0";
    res.actual = to_str(testee);

    return res;
}

// Signed Interface tests
test_and_log_util::result_type test_adgbi_is_positive(test_and_log_util::out_type&){
    ADGB_Int testee;

    test_and_log_util::result_type res;
    res.expected = "Testee is positive.";
    res.actual = "Testee is ";
    res.actual += (!testee.is_positive() ? "not " : "");
    res.actual += "positive.";

    return res;
}

test_and_log_util::result_type test_adgbi_is_negative(test_and_log_util::out_type&){
    ADGB_Int testee(-1);

    test_and_log_util::result_type res;
    res.expected = "Testee is negative.";
    res.actual = "Testee is ";
    res.actual += (!testee.is_negative() ? "not " : "");
    res.actual += "negative.";

    return res;
}

test_and_log_util::result_type test_adgbi_sign(test_and_log_util::out_type&){
    ADGB_Int testee(-133);

    test_and_log_util::result_type res;
    res.expected = "Testee is -1.";
    res.actual = "Testee is ";
    res.actual += (testee.sign() != -1 ? "not " : "");
    res.actual += "-1.";

    return res;
}

test_and_log_util::result_type test_adgbi_negate(test_and_log_util::out_type&){
    ADGB_Int testee(11);

    testee.negate();

    test_and_log_util::result_type res;
    res.expected = "-11";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_adgbi_make_positive(test_and_log_util::out_type&){
    ADGB_Int testee(-11);

    testee.make_positive();

    test_and_log_util::result_type res;
    res.expected = "+11";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_adgbi_make_negative(test_and_log_util::out_type&){
    ADGB_Int testee(6);

    testee.make_negative();

    test_and_log_util::result_type res;
    res.expected = "-6";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_adgbi_sign_assign(test_and_log_util::out_type&){
    ADGB_Int testee(777);

    testee.sign(-5);

    test_and_log_util::result_type res;
    res.expected = "-777";
    res.actual = to_str(testee);

    return res;
}


// Int read-only tests
test_and_log_util::result_type test_adgbi_magnitude(test_and_log_util::out_type&){
    ADGB_Int testee(-8932753, 30);

    testee = testee.magnitude();

    test_and_log_util::result_type res;
    res.expected = "+B0P8D";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_adgbi_compare(test_and_log_util::out_type&){
    ADGB_Int testee1(-8932753, 4), testee2, testee3(0xFFFFFFFF, 0x10);

    test_and_log_util::result_type res;
    res.expected = "Testee 1 is less than testee 2. Testee 3 is greater than testee 1.";
    res.actual = "Testee 1 is ";
    res.actual += (!(testee1.compare(testee2) < 0) ? "not " : "");
    res.actual += "less than testee 2.";
    res.actual += " Testee 3 is ";
    res.actual += (!(testee3.compare(testee1) > 0) ? "not " : "");
    res.actual += "greater than testee 1.";

    return res;
}

test_and_log_util::result_type test_adgbi_negative(test_and_log_util::out_type&){
    ADGB_Int testee(-8932753);

    testee = -testee;

    test_and_log_util::result_type res;
    res.expected = "+8932753";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_adgbi_is_one(test_and_log_util::out_type&){
    ADGB_Int testee(1);

    test_and_log_util::result_type res;
    res.expected = "Testee is +1.";
    res.actual = "Testee is ";
    res.actual += (!testee.is_one() ? "not " : "");
    res.actual += "+1.";

    return res;
}

test_and_log_util::result_type test_adgbi_is_neg_one(test_and_log_util::out_type&){
    ADGB_Int testee(-1);

    test_and_log_util::result_type res;
    res.expected = "Testee is -1.";
    res.actual = "Testee is ";
    res.actual += (!testee.is_neg_one() ? "not " : "");
    res.actual += "-1.";

    return res;
}

test_and_log_util::result_type test_adgbi_base(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "Base is 10.";
    res.actual = "Base is ";
    res.actual += ((all_digs_int.base() == 10) ? "" : "not ");
    res.actual += "10.";

    return res;
}


// Int modifier tests
test_and_log_util::result_type test_adgbi_make_zero(test_and_log_util::out_type&){
    ADGB_Int testee(-8932753);

    testee.make_zero();

    test_and_log_util::result_type res;
    res.expected = "+0";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_adgbi_make_one(test_and_log_util::out_type&){
    ADGB_Int testee(-8932753);

    testee.make_one();

    test_and_log_util::result_type res;
    res.expected = "+1";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_adgbi_make_neg_one(test_and_log_util::out_type&){
    ADGB_Int testee(-8932753);

    testee.make_neg_one();

    test_and_log_util::result_type res;
    res.expected = "-1";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_adgbi_make_two(test_and_log_util::out_type&){
    ADGB_Int testee(-8932753);

    testee.make_two();

    test_and_log_util::result_type res;
    res.expected = "+2";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_adgbi_halve(test_and_log_util::out_type&){
    ADGB_Int testee(8932753, 30);

    testee.halve();

    test_and_log_util::result_type res;
    res.expected = "+5FCJ6";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_adgbi_halve_spec(test_and_log_util::out_type&){
    ADGB_Int testee({0, 1, 2, 3, 4, 0, 6, 7, 8, 9}, -1);

    testee.halve();

    test_and_log_util::result_type res;
    res.expected = "-4938021605";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_adgbi_assign(test_and_log_util::out_type&){
    ADGB_Int testee(-8932753, 17);

    testee.assign(100, 5);
    testee.assign(4, 15);
    testee.assign(2, 8);

    test_and_log_util::result_type res;
    res.expected = "-6FG831";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_adgbi_force_assign(test_and_log_util::out_type&){
    ADGB_Int testee(-8932753);

    testee.force_assign(10, 5);
    testee.force_assign(4, 15);
    testee.force_assign(0, 8);

    test_and_log_util::result_type res;
    res.expected = "-50008932758";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_adgbi_set_base(test_and_log_util::out_type&){
    ADGB_Int cpy = diff_base_int;
    cpy.base(10);

    test_and_log_util::result_type res;
    res.expected = "+4886718345";
    res.actual = to_str(cpy);

    return res;
}

// Arithmetic tests
test_and_log_util::result_type test_adgbi_add(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+9999999999";
    res.actual = to_str(all_digs_int + rev_digs_int);

    return res;
}

void test_adgbi_add_speed(test_and_log_util::out_type&){
    volatile ADGB_Int res = speed_100digs + rev_100digs;
}

test_and_log_util::result_type test_adgbi_sub(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+4989824865";
    res.actual = to_str(all_digs_int - diff_base_int);

    return res;
}

void test_adgbi_sub_speed(test_and_log_util::out_type&){
    volatile ADGB_Int res = diff_100digs - rev_100digs;
}

test_and_log_util::result_type test_adgbi_mult(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+1219326311126352690";
    res.actual = to_str(all_digs_int * rev_digs_int);

    return res;
}

void test_adgbi_mult_speed(test_and_log_util::out_type&){
    volatile ADGB_Int res = speed_100digs * diff_100digs;
}

test_and_log_util::result_type test_adgbi_div(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+27";
    res.actual = to_str(diff_base_int / rev_digs_int);

    return res;
}

void test_adgbi_div_speed(test_and_log_util::out_type&){
    volatile ADGB_Int res = speed_100digs / two_int;
}

test_and_log_util::result_type test_adgbi_mod(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+0";
    res.actual = to_str(all_digs_int % two_int);

    return res;
}

void test_adgbi_mod_speed(test_and_log_util::out_type&){
    volatile ADGB_Int res = speed_100digs % two_int;
}

test_and_log_util::result_type test_adgbi_pre_dec(test_and_log_util::out_type&){
    ADGB_Int testee;

    test_and_log_util::result_type res;
    res.expected = "-1";
    res.actual = to_str(--testee);

    return res;
}

test_and_log_util::result_type test_adgbi_post_dec(test_and_log_util::out_type&){
    ADGB_Int testee;
    ADGB_Int testee2 = testee--;

    test_and_log_util::result_type res;
    res.expected = "-1 +0";
    res.actual = to_str(testee) + " " + to_str(testee2);

    return res;
}

test_and_log_util::result_type test_adgbi_pre_inc(test_and_log_util::out_type&){
    ADGB_Int testee;

    test_and_log_util::result_type res;
    res.expected = "+1";
    res.actual = to_str(++testee);

    return res;
}

test_and_log_util::result_type test_adgbi_post_inc(test_and_log_util::out_type&){
    ADGB_Int testee;
    ADGB_Int testee2 = testee++;

    test_and_log_util::result_type res;
    res.expected = "+1 +0";
    res.actual = to_str(testee) + " " + to_str(testee2);

    return res;
}

// Bitwise tests
test_and_log_util::result_type test_adgbi_and(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+68158464";
    res.actual = to_str(all_digs_int & rev_digs_int);

    return res;
}

void test_adgbi_and_speed(test_and_log_util::out_type&){
    volatile ADGB_Int res = speed_100digs & rev_100digs;
}

test_and_log_util::result_type test_adgbi_or(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+9931841535";
    res.actual = to_str(all_digs_int | rev_digs_int);

    return res;
}

void test_adgbi_or_speed(test_and_log_util::out_type&){
    volatile ADGB_Int res = speed_100digs | rev_100digs;
}

test_and_log_util::result_type test_adgbi_xor(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+9863683071";
    res.actual = to_str(all_digs_int ^ rev_digs_int);

    return res;
}

void test_adgbi_xor_speed(test_and_log_util::out_type&){
    volatile ADGB_Int res = speed_100digs ^ rev_100digs;
}

test_and_log_util::result_type test_adgbi_compl(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "-7303325973";
    res.actual = to_str(~all_digs_int);

    return res;
}

void test_adgbi_compl_speed(test_and_log_util::out_type&){
    volatile ADGB_Int res = ~speed_100digs;
}

test_and_log_util::result_type test_adgbi_lshift(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+2528395061760";
    res.actual = to_str(all_digs_int << eight_int);

    return res;
}

void test_adgbi_lshift_speed(test_and_log_util::out_type&){
    volatile ADGB_Int res = speed_100digs << hun_int;
}

test_and_log_util::result_type test_adgbi_rshift(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+38580246";
    res.actual = to_str(all_digs_int >> eight_int);

    return res;
}

void test_adgbi_rshift_speed(test_and_log_util::out_type&){
    volatile ADGB_Int res = speed_100digs >> quart_hun_int;
}


// Logical tests
test_and_log_util::result_type test_adgbi_log_and(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+5478B8D";
    res.actual = to_str(diff_base_int.logical_and(rev_digs_int));

    return res;
}

void test_adgbi_log_and_speed(test_and_log_util::out_type&){
    volatile ADGB_Int res = speed_100digs.logical_and(rev_100digs);
}

test_and_log_util::result_type test_adgbi_log_or(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+9151991519";
    res.actual = to_str(all_digs_int.logical_or(rev_digs_int));

    return res;
}

void test_adgbi_log_or_speed(test_and_log_util::out_type&){
    volatile ADGB_Int res = speed_100digs.logical_or(diff_100digs);
}

test_and_log_util::result_type test_adgbi_log_xor(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+9999999999";
    res.actual = to_str(all_digs_int.logical_xor(rev_digs_int));

    return res;
}

void test_adgbi_log_xor_speed(test_and_log_util::out_type&){
    volatile ADGB_Int res = diff_100digs.logical_xor(rev_100digs);
}

test_and_log_util::result_type test_adgbi_log_compl(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "-123456789";
    res.actual = to_str(all_digs_int.logical_complement());

    return res;
}

void test_adgbi_log_compl_speed(test_and_log_util::out_type&){
    volatile ADGB_Int res = speed_100digs.logical_complement();
}

test_and_log_util::result_type test_adgbi_log_lshift(test_and_log_util::out_type&){
    ADGB_Int testee(1234567890);

    test_and_log_util::result_type res;
    res.expected = "+12345678900000000";
    res.actual = to_str(testee.logical_shift_left(7));

    return res;
}

test_and_log_util::result_type test_adgbi_log_rshift(test_and_log_util::out_type&){
    ADGB_Int testee(1234567890);

    test_and_log_util::result_type res;
    res.expected = "+0";
    res.actual = to_str(testee.logical_shift_right(11));

    return res;
}

test_and_log_util::result_type test_adgbi_log_shift(test_and_log_util::out_type&){
    ADGB_Int testee(1234567890);

    test_and_log_util::result_type res;
    res.expected = "+123456";
    res.actual = to_str(testee.logical_shift(7).logical_shift(-11));

    return res;
}

// Customer template parameter tests
test_and_log_util::result_type test_adgbi_cust_dig(test_and_log_util::out_type&){
    using byte_Int = Precision::General_Base::Dynamic::Abstract::Int<std::uint8_t>;

    byte_Int byt(0xA4E5, 0x10), bit(7);

    test_and_log_util::result_type res;
    res.expected = "+178E";
    res.actual = to_str(byt / bit);

    return res;
}


test_and_log_util::result_type test_adgbi_cust_contain(test_and_log_util::out_type&){
    list_Int::diglist_type all_list(10, 0);
    list_Int::digit_type count = 0;
    for(auto& dig : all_list) dig = count++;

    list_Int alll(all_list, 1), revl(to_adgbi<list_Int, list_Int::digit_type>("123456789", 10));

    test_and_log_util::result_type res;
    res.expected = "+9999999999";
    res.actual = to_str(alll + revl);

    return res;
}

void test_adgbi_cust_contain_speed(test_and_log_util::out_type&){
    volatile list_Int res = speed_list_100digs + rev_list_100digs;
}



using Img_Set_Type = Precision::Image_Set_Interface<char, char const *, ADGB_Int::digit_type>;

static const Img_Set_Type img_set(Precision::Default::digs, Precision::Default::syms);

template <class ABS_Int_Type>
test_and_log_util::str_type to_str(const ABS_Int_Type& num){
    return Precision::Volatile::Int_Operations::Img::str
           <ABS_Int_Type, Img_Set_Type>(num, img_set);
}

template <class ABS_Int_Type, typename Base_Type>
ABS_Int_Type to_adgbi(const test_and_log_util::str_type& src, Base_Type base){
    typename ABS_Int_Type::diglist_type toreturn;
    typename ABS_Int_Type::sign_type sign;

    Precision::Volatile::Int_Operations::Img::parse
           <ABS_Int_Type, Img_Set_Type>(src, toreturn, sign, base, img_set);

    return ABS_Int_Type(toreturn, 1, base);
}
