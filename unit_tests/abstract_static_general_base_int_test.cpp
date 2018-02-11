#include "Test_Shared_Utilities.h"

#include "general_base/Int_Static_Abstract_Base.h"
#include "general_base/impl/Precision_Int_Operations_Img.h"

#include <list>

// Constructor tests
test_and_log_util::result_type test_asgbi_default(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_signed_size(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_diglist(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_iterators(test_and_log_util::out_type&);

// Digit Container tests
test_and_log_util::result_type test_asgbi_is_zero(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_is_mag_one(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_is_even(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_is_odd(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_digit_string(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_count_digits(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_digit(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_shift(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_shift_left(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_shift_right(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_append(test_and_log_util::out_type&);
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
test_and_log_util::result_type test_asgbi_make_zero(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_make_one(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_make_neg_one(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_make_two(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_halve(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_halve_spec(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_assign(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_force_assign(test_and_log_util::out_type&);

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
test_and_log_util::result_type test_asgbi_post_dec(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_pre_inc(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_post_inc(test_and_log_util::out_type&);

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
test_and_log_util::result_type test_asgbi_log_rshift(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_log_shift(test_and_log_util::out_type&);

// Customer template parameter tests
test_and_log_util::result_type test_asgbi_cust_dig(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_cust_base(test_and_log_util::out_type&);
test_and_log_util::result_type test_asgbi_cust_contain(test_and_log_util::out_type&);
void test_asgbi_cust_contain_speed(test_and_log_util::out_type&);

void setup_asgbi_variables();
// Cleanup function to free memory
void cleanup_asgbi();

using ASGB_Int = Precision::General_Base::Static::Abstract::Int<>;
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
using list_Int = Precision::General_Base::Static::Abstract::Int
    <Precision::Default::byte_type, 10, dumb_container>;

template <class ABS_Int_Type>
test_and_log_util::str_type to_str(const ABS_Int_Type& num);
template <class ABS_Int_Type>
ABS_Int_Type to_asgbi(const test_and_log_util::str_type& src);

// Variables for functionality tests
static ASGB_Int all_digs_int, rev_digs_int, two_int, eight_int;

// Variables for speed tests
static ASGB_Int speed_100digs, rev_100digs, hun_int, quart_hun_int;
static list_Int speed_list_100digs, rev_list_100digs;

void abstract_static_general_base_int_test(){
    test_and_log_util test_list( "Precision::General_Base::Static::"
                                 "Abstract::Int", __FILE__);
        test_list.set_log_output(test_log);
        test_list.set_console_output(test_console);
        test_list.set_assert(false);

    ADD_TEST(test_list, test_asgbi_default);
    ADD_TEST(test_list, test_asgbi_signed_size);
    ADD_TEST(test_list, test_asgbi_diglist);
    ADD_TEST(test_list, test_asgbi_iterators);
    ADD_TEST(test_list, test_asgbi_is_zero);
    ADD_TEST(test_list, test_asgbi_is_mag_one);
    ADD_TEST(test_list, test_asgbi_is_even);
    ADD_TEST(test_list, test_asgbi_is_odd);
    ADD_TEST(test_list, test_asgbi_digit_string);
    ADD_TEST(test_list, test_asgbi_count_digits);
    ADD_TEST(test_list, test_asgbi_shift_left);
    ADD_TEST(test_list, test_asgbi_shift_right);
    ADD_TEST(test_list, test_asgbi_append);
    ADD_TEST(test_list, test_asgbi_detach);

    ADD_TEST(test_list, test_asgbi_is_positive);
    ADD_TEST(test_list, test_asgbi_is_negative);
    ADD_TEST(test_list, test_asgbi_sign);
    ADD_TEST(test_list, test_asgbi_negate);
    ADD_TEST(test_list, test_asgbi_make_positive);
    ADD_TEST(test_list, test_asgbi_make_negative);
    ADD_TEST(test_list, test_asgbi_sign_assign);

    ADD_TEST(test_list, test_asgbi_magnitude);
    ADD_TEST(test_list, test_asgbi_compare);
    ADD_TEST(test_list, test_asgbi_negative);
    ADD_TEST(test_list, test_asgbi_is_one);
    ADD_TEST(test_list, test_asgbi_is_neg_one);
    ADD_TEST(test_list, test_asgbi_base);

    ADD_TEST(test_list, test_asgbi_make_zero);
    ADD_TEST(test_list, test_asgbi_make_one);
    ADD_TEST(test_list, test_asgbi_make_neg_one);
    ADD_TEST(test_list, test_asgbi_make_two);
    ADD_TEST(test_list, test_asgbi_halve);
    ADD_TEST(test_list, test_asgbi_halve_spec);
    ADD_TEST(test_list, test_asgbi_assign);
    ADD_TEST(test_list, test_asgbi_force_assign);

    ADD_TEST_BOTH(test_list, test_asgbi_add, test_asgbi_add_speed,   10000);
    ADD_TEST_BOTH(test_list, test_asgbi_sub, test_asgbi_sub_speed,   10000);
    ADD_TEST_BOTH(test_list, test_asgbi_mult, test_asgbi_mult_speed, 500);
    ADD_TEST_BOTH(test_list, test_asgbi_div, test_asgbi_div_speed,   500);
    ADD_TEST_BOTH(test_list, test_asgbi_mod, test_asgbi_mod_speed,   500);
    ADD_TEST(test_list, test_asgbi_pre_dec);
    ADD_TEST(test_list, test_asgbi_post_dec);
    ADD_TEST(test_list, test_asgbi_pre_inc);
    ADD_TEST(test_list, test_asgbi_post_inc);
    
    ADD_TEST_BOTH(test_list, test_asgbi_and, test_asgbi_and_speed, 1);
    ADD_TEST_BOTH(test_list, test_asgbi_or, test_asgbi_or_speed, 1);
    ADD_TEST_BOTH(test_list, test_asgbi_xor, test_asgbi_xor_speed, 1);
    ADD_TEST_BOTH(test_list, test_asgbi_compl, test_asgbi_compl_speed, 1);
    ADD_TEST_BOTH(test_list, test_asgbi_lshift, test_asgbi_lshift_speed, 10);
    ADD_TEST_BOTH(test_list, test_asgbi_rshift, test_asgbi_rshift_speed, 10);

    ADD_TEST_BOTH(test_list, test_asgbi_log_and, test_asgbi_log_and_speed, 10000);
    ADD_TEST_BOTH(test_list, test_asgbi_log_or, test_asgbi_log_or_speed, 10000);
    ADD_TEST_BOTH(test_list, test_asgbi_log_xor, test_asgbi_log_xor_speed, 10000);
    ADD_TEST_BOTH(test_list, test_asgbi_log_compl, test_asgbi_log_compl_speed, 10000);
    ADD_TEST(test_list, test_asgbi_log_lshift);
    ADD_TEST(test_list, test_asgbi_log_rshift);
    ADD_TEST(test_list, test_asgbi_log_shift);

    ADD_TEST(test_list, test_asgbi_cust_dig);
    ADD_TEST(test_list, test_asgbi_cust_base);
    ADD_TEST_BOTH(test_list, test_asgbi_cust_contain, test_asgbi_cust_contain_speed, 10000);

    setup_asgbi_variables();

    test_list.execute_tests();

    cleanup_asgbi();
}

void setup_asgbi_variables(){
    all_digs_int = to_asgbi<ASGB_Int>("9876543210");
    rev_digs_int = to_asgbi<ASGB_Int>("123456789");
    two_int.make_two();
    eight_int = ASGB_Int(8);

    speed_100digs = ASGB_Int(ASGB_Int::digstr_type(100, 7), 1);
    rev_100digs = ASGB_Int(ASGB_Int::digstr_type(100, 9), -1);
    hun_int = ASGB_Int(100);
    quart_hun_int = ASGB_Int(25);
    speed_list_100digs = list_Int(list_Int::digstr_type(100, 7), 1);
    rev_list_100digs = list_Int(list_Int::digstr_type(100, 9), -1);
}

void cleanup_asgbi(){
    all_digs_int.make_zero();
    rev_digs_int.make_zero();
    speed_100digs.make_zero();
    rev_100digs.make_zero();
    speed_list_100digs.make_zero();
    rev_list_100digs.make_zero();
}

// Constructor tests
test_and_log_util::result_type test_asgbi_default(test_and_log_util::out_type&){
    ASGB_Int testee;

    test_and_log_util::result_type res;
    res.expected = "+0";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_asgbi_signed_size(test_and_log_util::out_type&){
    ASGB_Int testee(-1236547890);

    test_and_log_util::result_type res;
    res.expected = "-1236547890";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_asgbi_diglist(test_and_log_util::out_type&){
    ASGB_Int::digstr_type diglist({1, 3, 2, 0, 8, 9, 77, 4, 0, 0});

    ASGB_Int testee(diglist, 1);

    test_and_log_util::result_type res;
    res.expected = "+40980231";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_asgbi_iterators(test_and_log_util::out_type&){
    int bad_str[14] = {0, 0, 1, 4, 3, -5, 9, 5, 66, 7, 1, 0, 1, 0};

    ASGB_Int testee(static_cast<int*>(bad_str), bad_str+14, 1);

    test_and_log_util::result_type res;
    res.expected = "+1017059034100";
    res.actual = to_str(testee);

    return res;
}

// Digit Container tests
test_and_log_util::result_type test_asgbi_is_zero(test_and_log_util::out_type&){
    ASGB_Int testee;

    test_and_log_util::result_type res;
    res.expected = "Testee is zero.";
    res.actual = "Testee is ";
    res.actual += (!testee.is_zero() ? "not " : "");
    res.actual += "zero.";

    return res;
}

test_and_log_util::result_type test_asgbi_is_mag_one(test_and_log_util::out_type&){
    ASGB_Int testee(-1);

    test_and_log_util::result_type res;
    res.expected = "Testee has magnitude of one.";
    res.actual = "Testee has magnitude of ";
    res.actual += (!testee.is_mag_one() ? "not " : "");
    res.actual += "one.";

    return res;
}

test_and_log_util::result_type test_asgbi_is_even(test_and_log_util::out_type&){
    ASGB_Int testee(0xA4);

    test_and_log_util::result_type res;
    res.expected = "Testee is even.";
    res.actual = "Testee is ";
    res.actual += (!testee.is_even() ? "not " : "");
    res.actual += "even.";

    return res;
}

test_and_log_util::result_type test_asgbi_is_odd(test_and_log_util::out_type&){
    ASGB_Int testee(0xA3);

    test_and_log_util::result_type res;
    res.expected = "Testee is odd.";
    res.actual = "Testee is ";
    res.actual += (!testee.is_odd() ? "not " : "");
    res.actual += "odd.";

    return res;
}

test_and_log_util::result_type test_asgbi_digit_string(test_and_log_util::out_type&){
    ASGB_Int testee(-123654879);

    test_and_log_util::result_type res;
    res.expected = "978456321";

    for(auto it = testee.digit_string().begin(); it != testee.digit_string().end(); ++it)
        res.actual.push_back(*it + '0');

    return res;
}

test_and_log_util::result_type test_asgbi_count_digits(test_and_log_util::out_type&){
    ASGB_Int testee(ASGB_Int::digstr_type(1000, 7), 1);

    test_and_log_util::result_type res;
    res.expected = "Testee is 1000 digits.";
    res.actual = "Testee is ";
    res.actual += (testee.count_digits()!=1000 ? "not " : "");
    res.actual += "1000 digits.";

    return res;
}

test_and_log_util::result_type test_asgbi_digit(test_and_log_util::out_type&){
    ASGB_Int testee(1234567890);

    test_and_log_util::result_type res;
    res.expected = "0987654321000";
    for(unsigned i = 0; i < testee.count_digits()+3; ++i)
        res.actual.push_back(testee.digit(i) + '0');

    return res;
}

test_and_log_util::result_type test_asgbi_shift(test_and_log_util::out_type&){
    ASGB_Int testee(1234567890);

    testee.shift(7);
    testee.shift(-11);

    test_and_log_util::result_type res;
    res.expected = "+123456";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_asgbi_shift_left(test_and_log_util::out_type&){
    ASGB_Int testee(1234567890);

    testee.shift_left(7);

    test_and_log_util::result_type res;
    res.expected = "+12345678900000000";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_asgbi_shift_right(test_and_log_util::out_type&){
    ASGB_Int testee(1234567890);

    testee.shift_right(11);

    test_and_log_util::result_type res;
    res.expected = "+0";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_asgbi_append(test_and_log_util::out_type&){
    ASGB_Int testee;

    testee.append(9);
    testee.append(0);
    testee.append(7);

    test_and_log_util::result_type res;
    res.expected = "+790";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_asgbi_detach(test_and_log_util::out_type&){
    ASGB_Int testee(11);

    testee.detach();
    testee.detach();
    testee.detach();

    test_and_log_util::result_type res;
    res.expected = "+0";
    res.actual = to_str(testee);

    return res;
}

// Signed Interface tests
test_and_log_util::result_type test_asgbi_is_positive(test_and_log_util::out_type&){
    ASGB_Int testee;

    test_and_log_util::result_type res;
    res.expected = "Testee is positive.";
    res.actual = "Testee is ";
    res.actual += (!testee.is_positive() ? "not " : "");
    res.actual += "positive.";

    return res;
}

test_and_log_util::result_type test_asgbi_is_negative(test_and_log_util::out_type&){
    ASGB_Int testee(-1);

    test_and_log_util::result_type res;
    res.expected = "Testee is negative.";
    res.actual = "Testee is ";
    res.actual += (!testee.is_negative() ? "not " : "");
    res.actual += "negative.";

    return res;
}

test_and_log_util::result_type test_asgbi_sign(test_and_log_util::out_type&){
    ASGB_Int testee(-133);

    test_and_log_util::result_type res;
    res.expected = "Testee is -1.";
    res.actual = "Testee is ";
    res.actual += (testee.sign() != -1 ? "not " : "");
    res.actual += "-1.";

    return res;
}

test_and_log_util::result_type test_asgbi_negate(test_and_log_util::out_type&){
    ASGB_Int testee(11);

    testee.negate();

    test_and_log_util::result_type res;
    res.expected = "-11";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_asgbi_make_positive(test_and_log_util::out_type&){
    ASGB_Int testee(-11);

    testee.make_positive();

    test_and_log_util::result_type res;
    res.expected = "+11";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_asgbi_make_negative(test_and_log_util::out_type&){
    ASGB_Int testee(6);

    testee.make_negative();

    test_and_log_util::result_type res;
    res.expected = "-6";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_asgbi_sign_assign(test_and_log_util::out_type&){
    ASGB_Int testee(777);

    testee.sign(-5);

    test_and_log_util::result_type res;
    res.expected = "-777";
    res.actual = to_str(testee);

    return res;
}


// Int read-only tests
test_and_log_util::result_type test_asgbi_magnitude(test_and_log_util::out_type&){
    ASGB_Int testee(-8932753);

    testee = testee.magnitude();

    test_and_log_util::result_type res;
    res.expected = "+8932753";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_asgbi_compare(test_and_log_util::out_type&){
    ASGB_Int testee(-8932753), testee2;

    test_and_log_util::result_type res;
    res.expected = "Testee is less.";
    res.actual = "Testee is ";
    res.actual += (!(testee.compare(testee2) < 0) ? "not " : "");
    res.actual += "less.";

    return res;
}

test_and_log_util::result_type test_asgbi_negative(test_and_log_util::out_type&){
    ASGB_Int testee(-8932753);

    testee = -testee;

    test_and_log_util::result_type res;
    res.expected = "+8932753";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_asgbi_is_one(test_and_log_util::out_type&){
    ASGB_Int testee(1);

    test_and_log_util::result_type res;
    res.expected = "Testee is +1.";
    res.actual = "Testee is ";
    res.actual += (!testee.is_one() ? "not " : "");
    res.actual += "+1.";

    return res;
}

test_and_log_util::result_type test_asgbi_is_neg_one(test_and_log_util::out_type&){
    ASGB_Int testee(-1);

    test_and_log_util::result_type res;
    res.expected = "Testee is -1.";
    res.actual = "Testee is ";
    res.actual += (!testee.is_neg_one() ? "not " : "");
    res.actual += "-1.";

    return res;
}

test_and_log_util::result_type test_asgbi_base(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "Base is 10.";
    res.actual = "Base is ";
    res.actual += ((ASGB_Int::base() == 10) ? "" : "not ");
    res.actual += "10.";

    return res;
}


// Int modifier tests
test_and_log_util::result_type test_asgbi_make_zero(test_and_log_util::out_type&){
    ASGB_Int testee(-8932753);

    testee.make_zero();

    test_and_log_util::result_type res;
    res.expected = "+0";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_asgbi_make_one(test_and_log_util::out_type&){
    ASGB_Int testee(-8932753);

    testee.make_one();

    test_and_log_util::result_type res;
    res.expected = "+1";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_asgbi_make_neg_one(test_and_log_util::out_type&){
    ASGB_Int testee(-8932753);

    testee.make_neg_one();

    test_and_log_util::result_type res;
    res.expected = "-1";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_asgbi_make_two(test_and_log_util::out_type&){
    ASGB_Int testee(-8932753);

    testee.make_two();

    test_and_log_util::result_type res;
    res.expected = "+2";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_asgbi_halve(test_and_log_util::out_type&){
    ASGB_Int testee(8932753);

    testee.halve();

    test_and_log_util::result_type res;
    res.expected = "+4466376";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_asgbi_halve_spec(test_and_log_util::out_type&){
    ASGB_Int testee({0, 1, 2, 3, 4, 0, 6, 7, 8, 9}, -1);

    testee.halve();

    test_and_log_util::result_type res;
    res.expected = "-4938021605";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_asgbi_assign(test_and_log_util::out_type&){
    ASGB_Int testee(-8932753);

    testee.assign(10, 5);
    testee.assign(4, 15);
    testee.assign(0, 8);

    test_and_log_util::result_type res;
    res.expected = "-8932758";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_asgbi_force_assign(test_and_log_util::out_type&){
    ASGB_Int testee(-8932753);

    testee.force_assign(10, 5);
    testee.force_assign(4, 15);
    testee.force_assign(0, 8);

    test_and_log_util::result_type res;
    res.expected = "-50008932758";
    res.actual = to_str(testee);

    return res;
}

// Arithmetic tests
test_and_log_util::result_type test_asgbi_add(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+9999999999";
    res.actual = to_str(all_digs_int + rev_digs_int);

    return res;
}

void test_asgbi_add_speed(test_and_log_util::out_type&){
    volatile ASGB_Int res = speed_100digs + rev_100digs;
}

test_and_log_util::result_type test_asgbi_sub(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+9753086421";
    res.actual = to_str(all_digs_int - rev_digs_int);

    return res;
}

void test_asgbi_sub_speed(test_and_log_util::out_type&){
    volatile ASGB_Int res = speed_100digs - rev_100digs;
}

test_and_log_util::result_type test_asgbi_mult(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+1219326311126352690";
    res.actual = to_str(all_digs_int * rev_digs_int);

    return res;
}

void test_asgbi_mult_speed(test_and_log_util::out_type&){
    volatile ASGB_Int res = speed_100digs * rev_100digs;
}

test_and_log_util::result_type test_asgbi_div(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+80";
    res.actual = to_str(all_digs_int / rev_digs_int);

    return res;
}

void test_asgbi_div_speed(test_and_log_util::out_type&){
    volatile ASGB_Int res = speed_100digs / two_int;
}

test_and_log_util::result_type test_asgbi_mod(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+0";
    res.actual = to_str(all_digs_int % two_int);

    return res;
}

void test_asgbi_mod_speed(test_and_log_util::out_type&){
    volatile ASGB_Int res = speed_100digs % two_int;
}

test_and_log_util::result_type test_asgbi_pre_dec(test_and_log_util::out_type&){
    ASGB_Int testee;

    test_and_log_util::result_type res;
    res.expected = "-1";
    res.actual = to_str(--testee);

    return res;
}

test_and_log_util::result_type test_asgbi_post_dec(test_and_log_util::out_type&){
    ASGB_Int testee;
    ASGB_Int testee2 = testee--;

    test_and_log_util::result_type res;
    res.expected = "-1 +0";
    res.actual = to_str(testee) + " " + to_str(testee2);

    return res;
}

test_and_log_util::result_type test_asgbi_pre_inc(test_and_log_util::out_type&){
    ASGB_Int testee;

    test_and_log_util::result_type res;
    res.expected = "+1";
    res.actual = to_str(++testee);

    return res;
}

test_and_log_util::result_type test_asgbi_post_inc(test_and_log_util::out_type&){
    ASGB_Int testee;
    ASGB_Int testee2 = testee++;

    test_and_log_util::result_type res;
    res.expected = "+1 +0";
    res.actual = to_str(testee) + " " + to_str(testee2);

    return res;
}

// Bitwise tests
test_and_log_util::result_type test_asgbi_and(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+68158464";
    res.actual = to_str(all_digs_int & rev_digs_int);

    return res;
}

void test_asgbi_and_speed(test_and_log_util::out_type&){
    volatile ASGB_Int res = speed_100digs & rev_100digs;
}

test_and_log_util::result_type test_asgbi_or(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+9931841535";
    res.actual = to_str(all_digs_int | rev_digs_int);

    return res;
}

void test_asgbi_or_speed(test_and_log_util::out_type&){
    volatile ASGB_Int res = speed_100digs | rev_100digs;
}

test_and_log_util::result_type test_asgbi_xor(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+9863683071";
    res.actual = to_str(all_digs_int ^ rev_digs_int);

    return res;
}

void test_asgbi_xor_speed(test_and_log_util::out_type&){
    volatile ASGB_Int res = speed_100digs ^ rev_100digs;
}

test_and_log_util::result_type test_asgbi_compl(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "-7303325973";
    res.actual = to_str(~all_digs_int);

    return res;
}

void test_asgbi_compl_speed(test_and_log_util::out_type&){
    volatile ASGB_Int res = ~speed_100digs;
}

test_and_log_util::result_type test_asgbi_lshift(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+2528395061760";
    res.actual = to_str(all_digs_int << eight_int);

    return res;
}

void test_asgbi_lshift_speed(test_and_log_util::out_type&){
    volatile ASGB_Int res = speed_100digs << hun_int;
}

test_and_log_util::result_type test_asgbi_rshift(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+38580246";
    res.actual = to_str(all_digs_int >> eight_int);

    return res;
}

void test_asgbi_rshift_speed(test_and_log_util::out_type&){
    volatile ASGB_Int res = speed_100digs >> quart_hun_int;
}


// Logical tests
test_and_log_util::result_type test_asgbi_log_and(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+848008480";
    res.actual = to_str(all_digs_int.logical_and(rev_digs_int));

    return res;
}

void test_asgbi_log_and_speed(test_and_log_util::out_type&){
    volatile ASGB_Int res = speed_100digs.logical_and(rev_100digs);
}

test_and_log_util::result_type test_asgbi_log_or(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+9151991519";
    res.actual = to_str(all_digs_int.logical_or(rev_digs_int));

    return res;
}

void test_asgbi_log_or_speed(test_and_log_util::out_type&){
    volatile ASGB_Int res = speed_100digs.logical_or(rev_100digs);
}

test_and_log_util::result_type test_asgbi_log_xor(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+9999999999";
    res.actual = to_str(all_digs_int.logical_xor(rev_digs_int));

    return res;
}

void test_asgbi_log_xor_speed(test_and_log_util::out_type&){
    volatile ASGB_Int res = speed_100digs.logical_xor(rev_100digs);
}

test_and_log_util::result_type test_asgbi_log_compl(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "-123456789";
    res.actual = to_str(all_digs_int.logical_complement());

    return res;
}

void test_asgbi_log_compl_speed(test_and_log_util::out_type&){
    volatile ASGB_Int res = speed_100digs.logical_complement();
}

test_and_log_util::result_type test_asgbi_log_lshift(test_and_log_util::out_type&){
    ASGB_Int testee(1234567890);

    test_and_log_util::result_type res;
    res.expected = "+12345678900000000";
    res.actual = to_str(testee.logical_shift_left(7));

    return res;
}

test_and_log_util::result_type test_asgbi_log_rshift(test_and_log_util::out_type&){
    ASGB_Int testee(1234567890);

    test_and_log_util::result_type res;
    res.expected = "+0";
    res.actual = to_str(testee.logical_shift_right(11));

    return res;
}

test_and_log_util::result_type test_asgbi_log_shift(test_and_log_util::out_type&){
    ASGB_Int testee(1234567890);

    test_and_log_util::result_type res;
    res.expected = "+123456";
    res.actual = to_str(testee.logical_shift(7).logical_shift(-11));

    return res;
}

// Customer template parameter tests
test_and_log_util::result_type test_asgbi_cust_dig(test_and_log_util::out_type&){
    using byte_Int = Precision::General_Base::Static::Abstract::Int<std::uint8_t>;

    byte_Int byt(0x3445), bit(7);

    test_and_log_util::result_type res;
    res.expected = "+1911";
    res.actual = to_str(byt / bit);

    return res;
}

test_and_log_util::result_type test_asgbi_cust_base(test_and_log_util::out_type&){
    using sept_Int = Precision::General_Base::Static::Abstract::Int
        <Precision::Default::byte_type, 7>;

    sept_Int sept(77), sept2(-43);

    test_and_log_util::result_type res;
    res.expected = "+140-61-12440";
    res.actual = to_str(sept) + to_str(sept2) + to_str(sept*sept2);

    return res;
}

test_and_log_util::result_type test_asgbi_cust_contain(test_and_log_util::out_type&){
    list_Int::digstr_type all_list(10, 0);
    list_Int::digit_type count = 0;
    for(auto& dig : all_list) dig = count++;

    list_Int alll(all_list, 1), revl(to_asgbi<list_Int>("123456789"));

    test_and_log_util::result_type res;
    res.expected = "+9999999999";
    res.actual = to_str(alll + revl);

    return res;
}

void test_asgbi_cust_contain_speed(test_and_log_util::out_type&){
    volatile list_Int res = speed_list_100digs + rev_list_100digs;
}



static char const *const digs = "0123456789";
static char const *const syms = "+-.e /i";

using Img_Set_Type = Precision::Image_Set_Interface<char, char const *, ASGB_Int::digit_type>;

static const Img_Set_Type img_set(digs, syms);

template <class ABS_Int_Type>
test_and_log_util::str_type to_str(const ABS_Int_Type& num){
    return Precision::Volatile::Int_Operations::Img::str
           <ABS_Int_Type, Img_Set_Type>(num, img_set);
}

template <class ABS_Int_Type>
ABS_Int_Type to_asgbi(const test_and_log_util::str_type& src){
    typename ABS_Int_Type::digstr_type toreturn;
    typename ABS_Int_Type::sign_type sign;

    Precision::Volatile::Int_Operations::Img::parse
           <ABS_Int_Type, Img_Set_Type>
           (src, toreturn, sign, ABS_Int_Type::base(), img_set);

    return ABS_Int_Type(toreturn, 1);
}
