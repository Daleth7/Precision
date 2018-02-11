#include "Test_Shared_Utilities.h"

#include "general_base/impl/Precision_Digit_Container_View.h"
#include "general_base/impl/Precision_Digit_Container.h"

// Constructor tests
test_and_log_util::result_type test_digstr_view_iteriter(test_and_log_util::out_type&);
test_and_log_util::result_type test_digstr_view_itersize(test_and_log_util::out_type&);
test_and_log_util::result_type test_digstr_view_diglistoffsize(test_and_log_util::out_type&);

// Read-only tests
test_and_log_util::result_type test_digstr_view_is_zero(test_and_log_util::out_type&);
test_and_log_util::result_type test_digstr_view_is_mag_one(test_and_log_util::out_type&);
test_and_log_util::result_type test_digstr_view_is_even(test_and_log_util::out_type&);
test_and_log_util::result_type test_digstr_view_is_odd(test_and_log_util::out_type&);
test_and_log_util::result_type test_digstr_view_digit(test_and_log_util::out_type&);

using dig_str = Precision::Digit_Container<>;
using dig_str_view = Precision::Digit_Container_View<dig_str::digstr_type>;

test_and_log_util::str_type to_str(const dig_str_view& num);

// Variables for functionality tests
static dig_str all_digs_int({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});

void digit_container_view_test(){
    test_and_log_util test_list( "Precision::Digit_Container_View", __FILE__);
        test_list.set_log_output(test_log);
        test_list.set_console_output(test_console);
        test_list.set_assert(false);

    ADD_TEST(test_list, test_digstr_view_iteriter);
    ADD_TEST(test_list, test_digstr_view_itersize);
    ADD_TEST(test_list, test_digstr_view_diglistoffsize);

    ADD_TEST(test_list, test_digstr_view_is_zero);
    ADD_TEST(test_list, test_digstr_view_is_mag_one);
    ADD_TEST(test_list, test_digstr_view_is_even);
    ADD_TEST(test_list, test_digstr_view_is_odd);
    ADD_TEST(test_list, test_digstr_view_digit);

    test_list.execute_tests();
}

// Constructor tests
test_and_log_util::result_type test_digstr_view_iteriter(test_and_log_util::out_type&){
    auto beg = all_digs_int.digit_string().begin() + 3;
    auto end = beg + 4;
    dig_str_view testee(beg, end);

    test_and_log_util::result_type res;
    res.expected = "6543";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_digstr_view_itersize(test_and_log_util::out_type&){
    dig_str_view testee(all_digs_int.digit_string().begin(), 5);

    test_and_log_util::result_type res;
    res.expected = "43210";
    res.actual = to_str(testee);

    return res;
}

test_and_log_util::result_type test_digstr_view_diglistoffsize(test_and_log_util::out_type&){
    dig_str_view testee(all_digs_int.digit_string(), 2, 7);
    dig_str_view testee2(all_digs_int.digit_string(), 4);

    test_and_log_util::result_type res;
    res.expected = "8765432 987654";
    res.actual = to_str(testee) + " " + to_str(testee2);

    return res;
}


// Read-only tests
test_and_log_util::result_type test_digstr_view_is_zero(test_and_log_util::out_type&){
    dig_str_view testee(all_digs_int.digit_string(), 0, 1);
    dig_str_view testee2(all_digs_int.digit_string(), 4);

    test_and_log_util::result_type res;
    res.expected = "Testee 1 is zero. Testee 2 is not zero.";
    res.actual = "Testee 1 is ";
    res.actual += (!testee.is_zero() ? "not " : "");
    res.actual += "zero. ";
    res.actual += "Testee 2 is ";
    res.actual += (!testee2.is_zero() ? "not " : "");
    res.actual += "zero.";

    return res;
}

test_and_log_util::result_type test_digstr_view_is_mag_one(test_and_log_util::out_type&){
    dig_str_view testee(all_digs_int.digit_string(), 1, 1);
    dig_str_view testee2(all_digs_int.digit_string(), 4);

    test_and_log_util::result_type res;
    res.expected = "Testee 1 has magnitude of one. Testee 2 has magnitude of not one.";
    res.actual = "Testee 1 has magnitude of ";
    res.actual += (!testee.is_mag_one() ? "not " : "");
    res.actual += "one. ";
    res.actual += "Testee 2 has magnitude of ";
    res.actual += (!testee2.is_mag_one() ? "not " : "");
    res.actual += "one.";

    return res;
}

test_and_log_util::result_type test_digstr_view_is_even(test_and_log_util::out_type&){
    dig_str_view testee(all_digs_int.digit_string(), 1);
    dig_str_view testee2(all_digs_int.digit_string(), 4);

    test_and_log_util::result_type res;
    res.expected = "Testee 1 is not even. Testee 2 is even.";
    res.actual = "Testee 1 is ";
    res.actual += (!testee.is_even() ? "not " : "");
    res.actual += "even. ";
    res.actual += "Testee 2 is ";
    res.actual += (!testee2.is_even() ? "not " : "");
    res.actual += "even.";

    return res;
}

test_and_log_util::result_type test_digstr_view_is_odd(test_and_log_util::out_type&){
    dig_str_view testee(all_digs_int.digit_string(), 1);
    dig_str_view testee2(all_digs_int.digit_string(), 4);

    test_and_log_util::result_type res;
    res.expected = "Testee 1 is odd. Testee 2 is not odd.";
    res.actual = "Testee 1 is ";
    res.actual += (!testee.is_odd() ? "not " : "");
    res.actual += "odd. ";
    res.actual += "Testee 2 is ";
    res.actual += (!testee2.is_odd() ? "not " : "");
    res.actual += "odd.";

    return res;
}


test_and_log_util::result_type test_digstr_view_digit(test_and_log_util::out_type&){
    dig_str_view testee(all_digs_int.digit_string());

    test_and_log_util::result_type res;
    res.expected = "0123456789000";
    for(unsigned i = 0; i < testee.count_digits()+3; ++i)
        res.actual.push_back(testee.digit(i) + '0');

    return res;
}



test_and_log_util::str_type to_str(const dig_str_view& num){
    test_and_log_util::str_type toreturn;
    for(auto it = num.raw_rbegin(); it != num.raw_rend(); ++it)
        toreturn.push_back('0' + *it);
    return toreturn;
}