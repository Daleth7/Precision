#include "Test_Shared_Utilities.h"

#include <iostream>
#include <fstream>
#include <chrono>

#include "Debug_Switches.h"

std::ostream& test_console = std::clog;
std::ofstream test_log("log/test_log.txt");

int main(){
    test_console << '\n';

    if(!test_log.is_open()){
        std::cerr << "Could not open/create test_log.txt to save test data."
                     " Logging to default stream."
                     ;
    }

    using clock = test_and_log_util::clock_type;
    using time_span = test_and_log_util::time_type;
    clock::time_point ref = clock::now();



    #ifdef TEST_EXCEPTION
    extern void exception_test();
    exception_test();
    #endif

    #ifdef TEST_SIGNCLASS
    extern void signclass_test();
    signclass_test();
    #endif

    #ifdef TEST_IMG_OPERATIONS
    extern void image_operations_test();
    image_operations_test();
    #endif

    #ifdef TEST_INT_OPERATIONS
    extern void int_operations_test();
    int_operations_test();
    #endif



    clock::time_point fin = clock::now();

    test_console << "Total execution time: "
                 << std::chrono::duration_cast<time_span>(fin-ref).count()
                 << " s\n"
                 << std::endl
                 ;

    test_log.close();

    return 0;
}