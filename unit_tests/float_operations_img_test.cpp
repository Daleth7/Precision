#include "Test_Shared_Utilities.h"

#include "general_base/impl/Precision_Float_Operations_Img.h"

#include <string>
#include <vector>



struct Fake_Float{
    using str_type          = std::string;
    using size_type         = std::size_t;
    using signed_size_type  = long long int;
    using digit_type        = std::uint_fast8_t;
    using digstr_type       = std::vector<digit_type>;

    bool is_zero()const
        {return number.size() == 1 && number.front() == 0;}
    bool is_positive()const
        {return positivity;}

    size_type count_digits()const
        {return this->precision()+1;}

    digit_type digit(size_type index)const{
        if( index >= this->count_digits() ||
            index < (this->precision()-number.size()+1)
            )
            return 0;
        size_type offset = this->precision()-number.size()+1;
        return number[index-offset];
    }

    static size_type base()
        {return 10;}

    size_type precision()const
        {return this->prec;}

    signed_size_type power()const
        {return this->pow;}

    digstr_type         number;
    bool                positivity;
    size_type           prec;
    signed_size_type    pow;
};

using Img_Set_Type = Precision::Image_Set_Interface<char, char const *, Fake_Float::digit_type>;

static char const * const digs = "0123456789ABCDEF";
static char const * const syms = "+-.e /i";

static Img_Set_Type img_set(digs, syms);

static Fake_Float func_variable, func_variable2;
static Fake_Float speed_variable, speed_variable2;
static Fake_Float::str_type speed_string, speed_string_sign, speed_string_exp;

static void setup_speed_variables();
static void clean_up_speed_variables();

static test_and_log_util::result_type test_sci_note_zero(test_and_log_util::out_type&);
static test_and_log_util::result_type test_sci_note_e0(test_and_log_util::out_type&);
static test_and_log_util::result_type test_sci_note_epos(test_and_log_util::out_type&);
static test_and_log_util::result_type test_sci_note_eneg(test_and_log_util::out_type&);
static test_and_log_util::result_type test_sci_note_diffprec(test_and_log_util::out_type&);
static test_and_log_util::result_type test_sci_note_all(test_and_log_util::out_type&);
static void test_sci_note_speed(test_and_log_util::out_type&);
static test_and_log_util::result_type test_sci_note_lim(test_and_log_util::out_type&);
static void test_sci_note_lim_speed(test_and_log_util::out_type&);
static test_and_log_util::result_type test_sci_note_w_spaces(test_and_log_util::out_type&);
static void test_sci_note_w_spaces_speed(test_and_log_util::out_type&);
static test_and_log_util::result_type test_str_zero(test_and_log_util::out_type&);
static test_and_log_util::result_type test_str(test_and_log_util::out_type&);
static test_and_log_util::result_type test_str_diffprec(test_and_log_util::out_type&);
static test_and_log_util::result_type test_str_diffpow(test_and_log_util::out_type&);
static void test_str_speed(test_and_log_util::out_type&);
//static test_and_log_util::result_type test_parse_typos(test_and_log_util::out_type&);
//static test_and_log_util::result_type test_parse(test_and_log_util::out_type&);
//static void test_parse_speed(test_and_log_util::out_type&);

void float_image_operations_test(){
    test_and_log_util test_list("Precision::Volatile::Float_Operations::Img", __FILE__);
        test_list.set_log_output(test_log);
        test_list.set_console_output(test_console);
        test_list.set_assert(true);

    ADD_TEST(test_list, test_sci_note_zero);
    ADD_TEST(test_list, test_sci_note_e0);
    ADD_TEST(test_list, test_sci_note_epos);
    ADD_TEST(test_list, test_sci_note_eneg);
    ADD_TEST(test_list, test_sci_note_diffprec);
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
    ADD_TEST(test_list, test_str_zero);
    ADD_TEST(test_list, test_str_diffprec);
    ADD_TEST(test_list, test_str_diffpow);
    ADD_TEST_BOTH( test_list,
                   test_str, test_str_speed,
                   10000
                   );
//    ADD_TEST(test_list, test_parse_typos);
//    ADD_TEST_BOTH( test_list,
//                   test_parse, test_parse_speed,
//                   10000
//                   );

    setup_speed_variables();

    test_list.execute_tests();

    clean_up_speed_variables();
}

void setup_speed_variables(){
    func_variable.positivity = true;
    func_variable.prec = 20;
    func_variable.pow = -1337;

    for(unsigned i = 0; i < 20; ++i)
        func_variable.number.push_back(i % 10);

    func_variable2 = func_variable;
    func_variable2.prec = 19;
    func_variable2.pow = 10;

    speed_variable.positivity = false;
    speed_variable.prec = 99;
    speed_variable.pow = 7777777;

    for(unsigned i = 0; i < 100; ++i)
        speed_variable.number.push_back(i % 10);

    speed_variable2 = speed_variable;
    speed_variable2.prec = 99;
    speed_variable2.pow = -50;

    for(unsigned i = 0; i < 100; ++i)
        speed_string.push_back((i % 10) + '0');

    speed_string_sign = speed_string;
    speed_string_sign.insert(0, 1, '-');

    speed_string_exp = speed_string_sign;
    speed_string_exp += "e123";
}

void clean_up_speed_variables(){
    func_variable.number.clear();
    func_variable2.number.clear();
    speed_variable.number.clear();
    speed_string.clear();
    speed_string_sign.clear();
    speed_string_exp.clear();
}

test_and_log_util::result_type test_sci_note_zero(test_and_log_util::out_type&){
    Fake_Float floating;
    floating.positivity = false;
    floating.number.push_back(0);

    test_and_log_util::result_type res;
    res.expected = "+0";
    res.actual = Precision::Volatile::Float_Operations::Img::sci_note
                 <Fake_Float, Img_Set_Type>(floating, 100, img_set);

    return res;
}

test_and_log_util::result_type test_sci_note_e0(test_and_log_util::out_type&){
    Fake_Float floating;
    floating.positivity = false;
    floating.number.push_back(7);
    floating.prec = floating.pow = 0;

    test_and_log_util::result_type res;
    res.expected = "-7e0";
    res.actual = Precision::Volatile::Float_Operations::Img::sci_note
                 <Fake_Float, Img_Set_Type>(floating, 100, img_set);

    return res;
}

test_and_log_util::result_type test_sci_note_epos(test_and_log_util::out_type&){
    Fake_Float floating;
    floating.positivity = false;
    floating.number.push_back(7);
    floating.prec = 0;
    floating.pow = 6;

    test_and_log_util::result_type res;
    res.expected = "-7e6";
    res.actual = Precision::Volatile::Float_Operations::Img::sci_note
                 <Fake_Float, Img_Set_Type>(floating, 100, img_set);

    return res;
}

test_and_log_util::result_type test_sci_note_eneg(test_and_log_util::out_type&){
    Fake_Float floating;
    floating.positivity = false;
    floating.number.push_back(7);
    floating.prec = 0;
    floating.pow = -6;

    test_and_log_util::result_type res;
    res.expected = "-7e-6";
    res.actual = Precision::Volatile::Float_Operations::Img::sci_note
                 <Fake_Float, Img_Set_Type>(floating, 100, img_set);

    return res;
}

test_and_log_util::result_type test_sci_note_diffprec(test_and_log_util::out_type&){
    Fake_Float floating;
      floating.positivity = false;
      floating.number.push_back(7);
      floating.prec = 3;
      floating.pow = -6;
    Fake_Float floating2;
      floating2.positivity = true;
      floating2.number.push_back(1);
      floating2.number.push_back(0);
      floating2.number.push_back(3);
      floating2.number.push_back(7);
      floating2.prec = 7;
      floating2.pow = 2;
    Fake_Float floating3;
      floating3.positivity = true;
      floating3.number.push_back(5);
      floating3.number.push_back(0);
      floating3.number.push_back(0);
      floating3.number.push_back(3);
      floating3.number.push_back(9);
      floating3.number.push_back(6);
      floating3.number.push_back(1);
      floating3.number.push_back(4);
      floating3.number.push_back(7);
      floating3.prec = 15;
      floating3.pow = 0;

    test_and_log_util::result_type res;
    res.expected = "-7.000e-6 +7.3010000e2 +7.41e0 +7e2";
    res.actual = Precision::Volatile::Float_Operations::Img::sci_note
                 <Fake_Float, Img_Set_Type>(floating, 100, img_set);
    res.actual.push_back(' ');
    res.actual += Precision::Volatile::Float_Operations::Img::sci_note
                 <Fake_Float, Img_Set_Type>(floating2, 100, img_set);
    res.actual.push_back(' ');
    res.actual += Precision::Volatile::Float_Operations::Img::sci_note
                 <Fake_Float, Img_Set_Type>(floating3, 2, img_set);
    res.actual.push_back(' ');
    res.actual += Precision::Volatile::Float_Operations::Img::sci_note
                 <Fake_Float, Img_Set_Type>(floating2, 0, img_set);

    return res;
}

test_and_log_util::result_type test_sci_note_all(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+9.87654321098765432100e-1337";
    res.actual = Precision::Volatile::Float_Operations::Img::sci_note
                 <Fake_Float, Img_Set_Type>(func_variable, 100, img_set);

    return res;
}

void test_sci_note_speed(test_and_log_util::out_type&){
    volatile Fake_Float::str_type res = 
        Precision::Volatile::Float_Operations::Img::sci_note
            <Fake_Float, Img_Set_Type>(speed_variable, 1000, img_set);
}

test_and_log_util::result_type test_sci_note_lim(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+9.8765432e-1337";
    res.actual = Precision::Volatile::Float_Operations::Img::sci_note
                 <Fake_Float, Img_Set_Type>(func_variable, 7, img_set);

    return res;
}

void test_sci_note_lim_speed(test_and_log_util::out_type&){
    volatile Fake_Float::str_type res = 
        Precision::Volatile::Float_Operations::Img::sci_note
            <Fake_Float, Img_Set_Type>(speed_variable, 50, img_set);
}

test_and_log_util::result_type test_sci_note_w_spaces(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+ 9.87654 e -1337";
    res.actual = Precision::Volatile::Float_Operations::Img::sci_note_w_spaces
                 <Fake_Float, Img_Set_Type>(func_variable, 5, img_set);

    return res;
}

void test_sci_note_w_spaces_speed(test_and_log_util::out_type&){
    volatile Fake_Float::str_type res = 
        Precision::Volatile::Float_Operations::Img::sci_note_w_spaces
            <Fake_Float, Img_Set_Type>(speed_variable, 1000, img_set);
}

test_and_log_util::result_type test_str_zero(test_and_log_util::out_type&){
    Fake_Float floating;
    floating.positivity = false;
    floating.prec = 0;
    floating.pow = 0;
    floating.number.push_back(0);

    test_and_log_util::result_type res;
    res.expected = "+0";
    res.actual = Precision::Volatile::Float_Operations::Img::str
                 <Fake_Float, Img_Set_Type>(floating, 10, img_set);

    return res;
}

test_and_log_util::result_type test_str(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "+98765432109.876543210";
    res.actual = Precision::Volatile::Float_Operations::Img::str
                 <Fake_Float, Img_Set_Type>(func_variable2, 100, img_set);

    return res;
}

test_and_log_util::result_type test_str_diffprec(test_and_log_util::out_type&){
    Fake_Float floating;
      floating.positivity = false;
      floating.number = Fake_Float::digstr_type({4, 5});
      floating.prec = 3;
      floating.pow = 0;
    Fake_Float floating2;
      floating2.positivity = false;
      floating2.number = Fake_Float::digstr_type({4, 5, 3, 2, 1, 0, 9, 8, 7});
      floating2.prec = 10;
      floating2.pow = 0;

    test_and_log_util::result_type res;
    res.expected = "-5.400 -7";
    res.actual = Precision::Volatile::Float_Operations::Img::str
                 <Fake_Float, Img_Set_Type>(floating, 10, img_set);
    res.actual.push_back(' ');
    res.actual += Precision::Volatile::Float_Operations::Img::str
                 <Fake_Float, Img_Set_Type>(floating2, 0, img_set);

    return res;
}

test_and_log_util::result_type test_str_diffpow(test_and_log_util::out_type&){
    Fake_Float floating;
      floating.positivity = false;
      floating.number = Fake_Float::digstr_type({9, 8, 7, 6, 0, 5, 4, 3, 2, 1});
      floating.prec = 9;
      floating.pow = 0;

    test_and_log_util::result_type res;
    res.expected = "-1.234506789 -0.1234506789 +0 -0.00001234506789 -1234.506789"
                   " -1234 -1230 -1000 -123450678900000000000 -123450000000000000000"
                   ;
    res.actual = Precision::Volatile::Float_Operations::Img::str
                 <Fake_Float, Img_Set_Type>(floating, 20, img_set);
    res.actual.push_back(' ');
    floating.pow = -1;
    res.actual += Precision::Volatile::Float_Operations::Img::str
                 <Fake_Float, Img_Set_Type>(floating, 20, img_set);
    res.actual.push_back(' ');
    res.actual += Precision::Volatile::Float_Operations::Img::str
                 <Fake_Float, Img_Set_Type>(floating, 0, img_set);
    res.actual.push_back(' ');
    floating.pow = -5;
    res.actual += Precision::Volatile::Float_Operations::Img::str
                 <Fake_Float, Img_Set_Type>(floating, 20, img_set);
    res.actual.push_back(' ');
    floating.pow = 3;
    res.actual += Precision::Volatile::Float_Operations::Img::str
                 <Fake_Float, Img_Set_Type>(floating, 15, img_set);
    res.actual.push_back(' ');
    res.actual += Precision::Volatile::Float_Operations::Img::str
                 <Fake_Float, Img_Set_Type>(floating, 3, img_set);
    res.actual.push_back(' ');
    res.actual += Precision::Volatile::Float_Operations::Img::str
                 <Fake_Float, Img_Set_Type>(floating, 2, img_set);
    res.actual.push_back(' ');
    res.actual += Precision::Volatile::Float_Operations::Img::str
                 <Fake_Float, Img_Set_Type>(floating, 0, img_set);
    res.actual.push_back(' ');
    floating.pow = 20;
    res.actual += Precision::Volatile::Float_Operations::Img::str
                 <Fake_Float, Img_Set_Type>(floating, 15, img_set);
    res.actual.push_back(' ');
    res.actual += Precision::Volatile::Float_Operations::Img::str
                 <Fake_Float, Img_Set_Type>(floating, 5, img_set);

    return res;
}

void test_str_speed(test_and_log_util::out_type&){
    volatile Fake_Float::str_type res = Precision::Volatile::Float_Operations::Img::str
                                      <Fake_Float, Img_Set_Type>
                                      (speed_variable2, 200, img_set);
}
/*
test_and_log_util::result_type test_parse_typos(test_and_log_util::out_type&){
    Img_Set_Type::str_type image = "+123.45678";
    Fake_Float storage;
    storage.positivity = true;
    Fake_Sign sign(storage.positivity);
    Precision::Volatile::Float_Operations::Img::parse<Fake_Float, Img_Set_Type>
        (image, storage.number, sign, Fake_Float::base(), img_set);

    test_and_log_util::result_type res;
    res.expected = "-1230045006070890";
    res.actual = Precision::Volatile::Float_Operations::Img::str
                 <Fake_Float, Img_Set_Type>(storage, img_set);

    return res;
}

test_and_log_util::result_type test_parse(test_and_log_util::out_type&){
    Img_Set_Type::str_type image = "123045607890";
    Fake_Float storage;
    storage.positivity = true;
    Fake_Sign sign(storage.positivity);
    Precision::Volatile::Float_Operations::Img::parse<Fake_Float, Img_Set_Type>
        (image, storage.number, sign, Fake_Float::base(), img_set);

    test_and_log_util::result_type res;
    res.expected = "+123045607890";
    res.actual = Precision::Volatile::Float_Operations::Img::str
                 <Fake_Float, Img_Set_Type>(storage, img_set);

    return res;
}

void test_parse_speed(test_and_log_util::out_type&){
    Fake_Float storage;
    Fake_Sign sign(storage.positivity);
    Precision::Volatile::Float_Operations::Img::parse<Fake_Float, Img_Set_Type>
        (speed_string, storage.number, sign, Fake_Float::base(), img_set);
}
*/