#include "Test_Shared_Utilities.h"

#include "general_base/Precision_Sign_Class.h"

#include <sstream>

test_and_log_util::result_type test_value_positive(test_and_log_util::out_type&);
void test_speed_value_positive(test_and_log_util::out_type& out);
test_and_log_util::result_type test_value_negative(test_and_log_util::out_type&);
test_and_log_util::result_type test_is_positive(test_and_log_util::out_type&);
test_and_log_util::result_type test_is_negative(test_and_log_util::out_type&);
test_and_log_util::result_type test_cast(test_and_log_util::out_type&);
test_and_log_util::result_type test_flip(test_and_log_util::out_type&);
test_and_log_util::result_type test_assign(test_and_log_util::out_type&);
test_and_log_util::result_type test_make_positive(test_and_log_util::out_type&);
test_and_log_util::result_type test_make_negative(test_and_log_util::out_type&);

void signclass_test(){
    test_and_log_util test_list("Precision::SignClass", __FILE__);
        test_list.set_log_output(test_log);
        test_list.set_console_output(test_console);
        test_list.set_assert(false);

    ADD_TEST_BOTH( test_list,
                   test_value_positive, test_speed_value_positive,
                   1000
                   );
    ADD_TEST(test_list, test_value_negative);
    ADD_TEST(test_list, test_is_positive);
    ADD_TEST(test_list, test_is_negative);
    ADD_TEST(test_list, test_cast);
    ADD_TEST(test_list, test_flip);
    ADD_TEST(test_list, test_assign);
    ADD_TEST(test_list, test_make_positive);
    ADD_TEST(test_list, test_make_negative);

    test_list.execute_tests();
}

test_and_log_util::result_type test_value_positive(test_and_log_util::out_type&){

    const Precision::SignClass sign(0);

    test_and_log_util::result_type res;
    res.expected = "+1";

    switch(sign.value()){
        case 1: res.actual = "+1"; break;
        case -1: res.actual = "-1"; break;
        default: res.actual = "0"; break;
    }

    return res;
}

void test_speed_value_positive(test_and_log_util::out_type& out){
    test_value_positive(out);
}

test_and_log_util::result_type test_value_negative(test_and_log_util::out_type&){

    const Precision::SignClass sign(-101);

    test_and_log_util::result_type res;
    res.expected = "-1";

    switch(sign.value()){
        case 1: res.actual = "+1"; break;
        case -1: res.actual = "-1"; break;
        default: res.actual = "0"; break;
    }

    return res;
}

test_and_log_util::result_type test_is_positive(test_and_log_util::out_type&){

    const Precision::SignClass sign(-1);

    test_and_log_util::result_type res;
    res.expected = "negative";
    res.actual = sign.is_positive() ? "positive" : "negative";

    return res;
}

test_and_log_util::result_type test_is_negative(test_and_log_util::out_type&){

    const Precision::SignClass sign(-1);

    test_and_log_util::result_type res;
    res.expected = "negative";
    res.actual = sign.is_negative() ? "negative" : "positive";

    return res;
}

test_and_log_util::result_type test_cast(test_and_log_util::out_type&){

    const Precision::SignClass sign(-1);

    const int num = 999 * sign;

    test_and_log_util::result_type res;
    res.expected = "-999";

    std::stringstream ss;
    ss << num;
    ss >> res.actual;

    return res;
}

test_and_log_util::result_type test_flip(test_and_log_util::out_type&){

    Precision::SignClass sign(-1);

    sign.flip();

    test_and_log_util::result_type res;
    res.expected = "positive";
    res.actual = sign.is_positive() ? "positive" : "negative";

    return res;
}

test_and_log_util::result_type test_assign(test_and_log_util::out_type&){

    Precision::SignClass sign;

    sign.assign(-1);

    test_and_log_util::result_type res;
    res.expected = "negative";
    res.actual = sign.is_positive() ? "positive" : "negative";

    return res;
}

test_and_log_util::result_type test_make_positive(test_and_log_util::out_type&){

    Precision::SignClass sign;

    sign.make_positive();

    test_and_log_util::result_type res;
    res.expected = "positive";
    res.actual = sign.is_positive() ? "positive" : "negative";

    return res;
}

test_and_log_util::result_type test_make_negative(test_and_log_util::out_type&){

    Precision::SignClass sign;

    sign.make_negative();

    test_and_log_util::result_type res;
    res.expected = "negative";
    res.actual = sign.is_positive() ? "positive" : "negative";

    return res;
}