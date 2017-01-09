#include "Test_Shared_Utilities.h"

#include "general_base/impl/Precision_Int_Operations_Img.h"

#include <string>
#include <vector>

struct Fake_Int{
    using str_type     = std::string;
    using size_type    = std::size_t;
    using digit_type   = std::uint_fast8_t;
    using diglist_type = std::vector<digit_type>;

    bool is_zero()const
        {return number.size() == 1 && number.front() == 0;}
    bool is_positive()const
        {return positivity;}

    size_type count_digits()const
        {return number.size();}

    digit_type digit(size_type index)const
        {return number[index];}

    static size_type base()
        {return 10;}

    diglist_type number;
    bool positivity;
};

static char const * const digs = "0123456789";
static char const * const syms = "+-.e /i";

static Fake_Int func_variable;
static Fake_Int speed_variable;
static Fake_Int::str_type speed_string;

void setup_speed_variables();

test_and_log_util::result_type test_str_zero(test_and_log_util::out_type&);
test_and_log_util::result_type test_str(test_and_log_util::out_type&);
void test_str_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_sci_note_e0(test_and_log_util::out_type&);
test_and_log_util::result_type test_sci_note_all(test_and_log_util::out_type&);
void test_sci_note_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_sci_note_lim(test_and_log_util::out_type&);
void test_sci_note_lim_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_sci_note_w_spaces(test_and_log_util::out_type&);
void test_sci_note_w_spaces_speed(test_and_log_util::out_type&);
test_and_log_util::result_type test_parse_typos(test_and_log_util::out_type&);
test_and_log_util::result_type test_parse(test_and_log_util::out_type&);
void test_parse_speed(test_and_log_util::out_type&);

void image_operations_test(){
    test_and_log_util test_list("Precision::Volatile::Int_Operations::Img", __FILE__);
        test_list.set_log_output(test_log);
        test_list.set_console_output(test_console);
        test_list.set_assert(true);

    ADD_TEST(test_list, test_str_zero);
    ADD_TEST_BOTH( test_list,
                   test_str, test_str_speed,
                   10000
                   );
    ADD_TEST(test_list, test_sci_note_e0);
    ADD_TEST_BOTH( test_list,
                   test_sci_note_all, test_sci_note_speed,
                   10000
                   );
    ADD_TEST_BOTH( test_list,
                   test_sci_note_lim, test_sci_note_lim_speed,
                   10000
                   );
    ADD_TEST_BOTH( test_list,
                   test_sci_note_w_spaces, test_sci_note_w_spaces_speed,
                   10000
                   );
    ADD_TEST(test_list, test_parse_typos);
    ADD_TEST_BOTH( test_list,
                   test_parse, test_parse_speed,
                   10000
                   );

    setup_speed_variables();

    test_list.execute_tests();
}

void setup_speed_variables(){
    func_variable.positivity = true;

    for(unsigned i = 0; i < 20; ++i)
        func_variable.number.push_back(i % 10);

    speed_variable.positivity = false;

    for(unsigned i = 0; i < 100; ++i)
        speed_variable.number.push_back(i % 10);

    for(unsigned i = 0; i < 100; ++i)
        speed_string.push_back((i % 10) + '0');
}

test_and_log_util::result_type test_str_zero(test_and_log_util::out_type&){

    Fake_Int integer;
    integer.positivity = false;
    integer.number.push_back(0);

    test_and_log_util::result_type res;
    res.expected = "+0";
    res.actual = Precision::Volatile::Int_Operations::Img::str(integer, digs, syms);

    return res;
}

test_and_log_util::result_type test_str(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+98765432109876543210";
    res.actual = Precision::Volatile::Int_Operations::Img::str
                 (func_variable, digs, syms);

    return res;
}

void test_str_speed(test_and_log_util::out_type&){
    volatile Fake_Int::str_type res = 
        Precision::Volatile::Int_Operations::Img::str(speed_variable, digs, syms);
}

test_and_log_util::result_type test_sci_note_e0(test_and_log_util::out_type&){
    Fake_Int integer;
    integer.positivity = false;
    integer.number.push_back(7);

    test_and_log_util::result_type res;
    res.expected = "-7e0";
    res.actual = Precision::Volatile::Int_Operations::Img::sci_note
                 (integer, 100, digs, syms);

    return res;
}

test_and_log_util::result_type test_sci_note_all(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+9.8765432109876543210e19";
    res.actual = Precision::Volatile::Int_Operations::Img::sci_note
                 (func_variable, 100, digs, syms);

    return res;
}

void test_sci_note_speed(test_and_log_util::out_type&){
    volatile Fake_Int::str_type res = 
        Precision::Volatile::Int_Operations::Img::sci_note
            (speed_variable, 1000, digs, syms);
}

test_and_log_util::result_type test_sci_note_lim(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+9.8765432e19";
    res.actual = Precision::Volatile::Int_Operations::Img::sci_note
                 (func_variable, 7, digs, syms);

    return res;
}

void test_sci_note_lim_speed(test_and_log_util::out_type&){
    volatile Fake_Int::str_type res = 
        Precision::Volatile::Int_Operations::Img::sci_note
            (speed_variable, 50, digs, syms);
}

test_and_log_util::result_type test_sci_note_w_spaces(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+ 9.87654 e 19";
    res.actual = Precision::Volatile::Int_Operations::Img::sci_note_w_spaces
                 (func_variable, 5, digs, syms);

    return res;
}

void test_sci_note_w_spaces_speed(test_and_log_util::out_type&){
    volatile Fake_Int::str_type res = 
        Precision::Volatile::Int_Operations::Img::sci_note_w_spaces
            (speed_variable, 1000, digs, syms);
}

test_and_log_util::result_type test_parse_typos(test_and_log_util::out_type&){
    Fake_Int::str_type image = "-1230a45b 607n890";
    Fake_Int storage;
    storage.positivity = true;
    Precision::Volatile::Int_Operations::Img::parse<Fake_Int>
        (image, storage.number, Fake_Int::base(), digs);

    test_and_log_util::result_type res;
    res.expected = "+1230045006070890";
    res.actual = Precision::Volatile::Int_Operations::Img::str(storage, digs, syms);

    return res;
}

test_and_log_util::result_type test_parse(test_and_log_util::out_type&){
    Fake_Int::str_type image = "123045607890";
    Fake_Int storage;
    storage.positivity = true;
    Precision::Volatile::Int_Operations::Img::parse<Fake_Int>
        (image, storage.number, Fake_Int::base(), digs);

    test_and_log_util::result_type res;
    res.expected = "+123045607890";
    res.actual = Precision::Volatile::Int_Operations::Img::str(storage, digs, syms);

    return res;
}

void test_parse_speed(test_and_log_util::out_type&){
    Fake_Int storage;
    Precision::Volatile::Int_Operations::Img::parse<Fake_Int>
        (speed_string, storage.number, Fake_Int::base(), digs);
}