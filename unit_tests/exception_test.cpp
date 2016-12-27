#include "Test_Shared_Utilities.h"

#include "general_base/impl/Precision_Exception.h"

test_and_log_util::result_type test_type_return(test_and_log_util::out_type&);
test_and_log_util::result_type test_src_return(test_and_log_util::out_type&);
test_and_log_util::result_type test_what_return(test_and_log_util::out_type&);

void exception_test(){
    test_and_log_util test_list("Precision::execption", __FILE__);
        test_list.set_log_output(test_log);
        test_list.set_console_output(test_console);
        test_list.set_assert(false);

    ADD_TEST(test_list, test_type_return);
    ADD_TEST(test_list, test_src_return);
    ADD_TEST(test_list, test_what_return);

    test_list.execute_tests();
}

test_and_log_util::result_type test_type_return(test_and_log_util::out_type&){
    auto code_to_str = [](Precision::exception::code c){
        switch(c){
            case Precision::exception::insufficient_memory:
                return "insufficient memory";
            case Precision::exception::divide_by_zero:
                return "divide by zero";
            case Precision::exception::indeterminate:
                return "indeterminate";
            case Precision::exception::unsupported:
                return "unsupported";
            case Precision::exception::invalid_digit:
                return "invalid digit";
            case Precision::exception::none:
                return "none";
        }
        return "error";
    };

    test_and_log_util::result_type res;
    res.expected = code_to_str(Precision::exception::code::indeterminate);

    try{
        throw Precision::exception( Precision::exception::code::indeterminate,
                                    "test function name(bool)"
                                    );
    }catch(const Precision::exception& err){
        res.actual = code_to_str(err.type());
    }

    return res;
}

test_and_log_util::result_type test_src_return(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "test function name(bool)";

    try{
        throw Precision::exception( Precision::exception::code::indeterminate,
                                    "test function name(bool)"
                                    );
    }catch(const Precision::exception& err){
        res.actual = err.source();
    }

    return res;
}

test_and_log_util::result_type test_what_return(test_and_log_util::out_type&){
    test_and_log_util::result_type res;
    res.expected = "test function name(bool) ~ Indeterminate result.";

    try{
        throw Precision::exception( Precision::exception::code::indeterminate,
                                    "test function name(bool)"
                                    );
    }catch(const Precision::exception& err){
        res.actual = err.what();
    }

    return res;
}