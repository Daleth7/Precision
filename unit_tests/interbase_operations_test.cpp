#include "Test_Shared_Utilities.h"

#include "general_base/Int_Static_Base.h"
#include "general_base/impl/Precision_Interbase_Operations.h"

test_and_log_util::result_type test_convert_copy_abstract(test_and_log_util::out_type&);
void test_convert_copy_speed_tens(test_and_log_util::out_type&);
test_and_log_util::result_type test_convert_copy_static(test_and_log_util::out_type&);
void test_convert_copy_speed_same_digs(test_and_log_util::out_type&);
test_and_log_util::result_type test_convert_copy_static_abs(test_and_log_util::out_type&);
void test_convert_copy_speed_mixed(test_and_log_util::out_type&);
test_and_log_util::result_type test_convert_copy_one_dig(test_and_log_util::out_type&);
test_and_log_util::result_type test_convert_copy_static_img_set(test_and_log_util::out_type&);
test_and_log_util::result_type test_convert_copy_static_abs_img(test_and_log_util::out_type&);
test_and_log_util::result_type test_convert(test_and_log_util::out_type&);
test_and_log_util::result_type test_convert_same_base(test_and_log_util::out_type&);

void setup_convert_copy_variables();
// Cleanup function to free memory
void cleanup_convert();

using SGB_Int = Precision::General_Base::Static::Int<>;
using ASGB_Int = Precision::General_Base::Static::Abstract::Int<>;
using hex_ASGB_Int = Precision::General_Base::Static::Abstract::Int
                        <Precision::Default::byte_type, 16>;
using hex_SGB_Int = Precision::General_Base::Static::Int
                        <Precision::Default::image_type, Precision::Default::image_iter_type,
                            Precision::Default::byte_type, 16>;

// Variables for functionality tests
static SGB_Int all_digs_int, rev_digs_int;
static ASGB_Int all_digs_abs_int;

using speed_SGB_Int = Precision::General_Base::Static::Int< Precision::Default::image_type,
                                                            Precision::Default::image_iter_type,
                                                            Precision::Default::byte_type,
                                                            7
                                                            >;

// Variables for speed tests
static const speed_SGB_Int speed_ref;
static SGB_Int speed_100digs_tens, speed_100digs, speed_100digs_mixed;

void interbase_operations_test(){
    test_and_log_util test_list("Precision::convert_base_copy", __FILE__);
        test_list.set_log_output(test_log);
        test_list.set_console_output(test_console);
        test_list.set_assert(true);

    ADD_TEST_BOTH(test_list, test_convert_copy_abstract, test_convert_copy_speed_tens, 1000);
    ADD_TEST_BOTH(test_list, test_convert_copy_static, test_convert_copy_speed_same_digs, 1000);
    ADD_TEST_BOTH(test_list, test_convert_copy_static_abs, test_convert_copy_speed_mixed, 1000);
    ADD_TEST(test_list, test_convert_copy_one_dig);
    ADD_TEST(test_list, test_convert_copy_static_img_set);
    ADD_TEST(test_list, test_convert_copy_static_abs_img);
    ADD_TEST(test_list, test_convert);
    ADD_TEST(test_list, test_convert_same_base);

    setup_convert_copy_variables();

    test_list.execute_tests();

    cleanup_convert();
}

void setup_convert_copy_variables(){
    all_digs_int = SGB_Int("9876543210");
    rev_digs_int = SGB_Int("123456789");

    ASGB_Int::diglist_type abs_diglist(10, 0);
    ASGB_Int::digit_type counter = 0;
    for(auto it = abs_diglist.begin(); it != abs_diglist.end(); ++it, ++counter)
        *it = counter;
    all_digs_abs_int = ASGB_Int(abs_diglist, -1);

    speed_100digs = SGB_Int(SGB_Int::diglist_type(100, 7), 1);
    SGB_Int::str_type img(100, '1');
    for(SGB_Int::size_type i = 1; i < img.size(); ++i)
        img[i] = ( (((img[i-1] * 31) >> 3) * 47) % 10 ) + '0';
    
    speed_100digs_mixed = SGB_Int(img);

    SGB_Int::diglist_type tens_diglist(100, 0);
    *tens_diglist.rbegin() = 1;
    speed_100digs_tens = SGB_Int(tens_diglist, 1);
}

void cleanup_convert(){
    all_digs_int.make_zero();
    rev_digs_int.make_zero();
    all_digs_abs_int.make_zero();
    speed_100digs_tens.make_zero();
    speed_100digs.make_zero();
    speed_100digs_mixed.make_zero();
}

test_and_log_util::result_type test_convert_copy_abstract(test_and_log_util::out_type&){
    hex_ASGB_Int ref;
    hex_ASGB_Int testee = Precision::convert_base_copy(all_digs_abs_int, ref);

    test_and_log_util::result_type res;
    res.expected = "-24CB016EA";
    res.actual = hex_SGB_Int(testee).str();

    return res;
}

void test_convert_copy_speed_tens(test_and_log_util::out_type&){
    volatile speed_SGB_Int res = Precision::convert_base_copy(speed_100digs_tens, speed_ref);
}

test_and_log_util::result_type test_convert_copy_static(test_and_log_util::out_type&){
    hex_SGB_Int ref;
    hex_SGB_Int testee = Precision::convert_base_copy(all_digs_int, ref);

    test_and_log_util::result_type res;
    res.expected = "+24CB016EA";
    res.actual = testee.str();

    return res;
}

void test_convert_copy_speed_same_digs(test_and_log_util::out_type&){
    volatile speed_SGB_Int res = Precision::convert_base_copy(speed_100digs, speed_ref);
}

test_and_log_util::result_type test_convert_copy_static_abs(test_and_log_util::out_type&){
    hex_ASGB_Int ref;
    hex_ASGB_Int testee = Precision::convert_base_copy(rev_digs_int, ref);

    test_and_log_util::result_type res;
    res.expected = "+75BCD15";
    res.actual = hex_SGB_Int(testee).str();

    return res;
}

void test_convert_copy_speed_mixed(test_and_log_util::out_type&){
    volatile speed_SGB_Int res = Precision::convert_base_copy(speed_100digs_mixed, speed_ref);
}

test_and_log_util::result_type test_convert_copy_one_dig(test_and_log_util::out_type&){
    hex_SGB_Int hex_testee(0xD);
    SGB_Int testee = Precision::convert_base_copy(hex_testee, all_digs_int);

    test_and_log_util::result_type res;
    res.expected = "+13";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_convert_copy_static_img_set(test_and_log_util::out_type&){
    //                             0123456789ABCDEF
    char const * const new_digs = "zyxwvutsrqponmlk";

    hex_SGB_Int ref(0, new_digs, Precision::Default::syms);
    hex_SGB_Int testee = Precision::convert_base_copy(all_digs_int, ref);

    test_and_log_util::result_type res;
    res.expected = "+xvnozytlp";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_convert_copy_static_abs_img(test_and_log_util::out_type&){
    //                             0123456789ABCDEF
    char const * const new_digs = "zyxwvutsrqponmlk";

    hex_SGB_Int ref(0, new_digs, Precision::Default::syms);
    hex_SGB_Int testee = Precision::convert_base_copy(all_digs_abs_int, ref);

    test_and_log_util::result_type res;
    res.expected = "-xvnozytlp";
    res.actual = testee.str();

    return res;
}

test_and_log_util::result_type test_convert(test_and_log_util::out_type&){
    hex_SGB_Int testee = Precision::convert_base<hex_SGB_Int>(rev_digs_int, 16);

    //                             0123456789ABCDEF
    char const * const new_digs = "zyxwvutsrqponmlk";
    SGB_Int cpy(all_digs_abs_int, new_digs, Precision::Default::syms);
    hex_SGB_Int testee2 = Precision::convert_base<hex_SGB_Int>(cpy, 16);

    test_and_log_util::result_type res;
    res.expected = "+75BCD15-24CB016EA";
    res.actual = testee.str() + testee2.str();

    return res;
}

test_and_log_util::result_type test_convert_same_base(test_and_log_util::out_type&){
    SGB_Int testee = Precision::convert_base_copy(rev_digs_int, all_digs_int),
            testee2 = Precision::convert_base_copy(-rev_digs_int, all_digs_abs_int)
            ;

    test_and_log_util::result_type res;
    res.expected = "+123456789-123456789";
    res.actual = testee.str() + testee2.str();

    return res;
}