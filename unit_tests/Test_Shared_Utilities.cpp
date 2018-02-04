#include "Test_Shared_Utilities.h"

#include <iostream>
#include <iomanip>
#include <cassert>
#include <exception>

// Setup functions

/** Set whether or not the assert() macro is used. If set to true,
 *  the program will stop tests upon encountering the first failed
 *  test.
 *
 *  \param force_abort Set true to abort program when a test fails.
 */
void test_and_log_util::set_assert(bool force_abort)
    {m_force_assert = force_abort;}

/** Add a new test to the list. Note that the test is not performed
 *  yet. At minimum, a functionality test needs to be passed, but a
 *  speed test can be passed as well along with the maximum number
 *  of times the speed test may repeat the operation under test.
 *
 *  \param func_test The function that tests functionality.
 *  \param speed_test The function that tests operation speed.
 *  \param repeats The maximum number of times the operation may
 *                 be repeated during the speed test.
 */
void test_and_log_util::add_test( const str_type& func_name,
                                  functional_test_type func_test,
                                  speed_test_type speed_test,
                                  size_type repeats
){
    test_group&& new_test { func_name,
                            func_test, speed_test,
                            repeats
                            };
    m_tests.emplace_back(new_test);
}

/** Set the output stream for logging to media. By default,
 *  upon construction, no output is set.
 *
 *  \param new_output Output stream for logging information to
 *                    media for further review later.
 */
void test_and_log_util::set_log_output(out_type& new_output){
    p_log_dest = &new_output;
}

/** Set the output stream for printing to a console. By default,
 *  upon construction, the output is set to std::clog.
 *
 *  \param new_output Output stream for logging information to
 *                    a console for a human reading.
 */
void test_and_log_util::set_console_output(out_type& new_output){
    p_console = &new_output;
}



// Modifiers

/** Iterate through the list and perform each test. For each
 *  list item, the functionality test is performed first and
 *  console messages are formatted.
 *  If assertion is not enforced, after performing all tests,
 *  the line number and source file of each test is
 *  printed to the console.
 */
void test_and_log_util::execute_tests(){
    out_type& console = p_console != nullptr ? *p_console : std::clog;
    out_type& log = p_log_dest != nullptr ? *p_log_dest : std::cout;

    console << m_test_list_name << " [" << m_file_src << "]:\n";
    log << m_test_list_name << " [" << m_file_src << "]:\n";
    for(auto cit = m_tests.cbegin(); cit != m_tests.cend(); ++cit){

        // Perform functionality test
        result_type test_result;
        try{
            test_result = cit->func_test(console);
        }catch(const std::exception& err){
            // Do not attempt running further tests that may depend on this
            // failed test
            console << "\nExperienced error: " << err.what() << '\n';
            log << "\nExperienced error: " << err.what() << '\n';
            break;
        }catch(...){
            console << "\nExperienced unexpected error..." << '\n';
            log << "\nExperienced unexpected error..." << '\n';
            break;
        }
        bool result_matched = test_result.expected == test_result.actual;
        try{
            assert(!m_force_assert | result_matched);
        } catch(const std::exception& err){
            // If an exception is thrown, do not attempt to run other tests
            console << err.what();
            return;
        }catch(...){
            console << "\nExperienced unexpected error..." << '\n';
            log << "\nExperienced unexpected error..." << '\n';
            break;
        }

        // Format to print: Test #N (File = src.cpp | Line = L): [Passed/Failed]
        console << '\t' << std::setw(35) << std::left << cit->func_name
                << ": " << (result_matched ? "Passed" : "Failed")
                ;
        log << '\t' << std::setw(35) << std::left << cit->func_name << '\t'
            << ": " << (result_matched ? "Passed" : "Failed")
            ;
        // If failed, also print: (Expected: result1 Got: result2)
        if(!result_matched){
            console << " (Expected: " << test_result.expected
                    << " Got: " << test_result.actual << ")"
                    ;
            log << " (Expected: " << test_result.expected
                << " Got: " << test_result.actual << ")"
                ;
        }

        // Perform speed tests
        if(result_matched && cit->max_repeats > 0 && cit->speed_test){
            size_type test_repeat_counter = cit->max_repeats;
            double average_time = 0.0;
            bool err_encountered = false;

            // Measure total time taken and then divide by number of runs
            clock_type::time_point ref = clock_type::now();

            // Repeat speed test
            while(test_repeat_counter-- > 0){
                try{
                    cit->speed_test(log);
                }catch(const std::exception& err){
                    console << " ; Error!  " << err.what(); 
                    err_encountered = true;
                    break;
                }
            }

            // Calculate average time taken
            clock_type::time_point fin = clock_type::now();
            average_time = std::chrono::duration_cast<time_type>
                            (fin - ref).count() / cit->max_repeats;

            if(!err_encountered){
                console << " ; Average execution time: " << average_time << " s";
                log << " ; Average execution time: " << average_time << " s";
            }
        }
        console << std::endl;
        log << std::endl;
    }
    console << '\n';
    log << '\n';
}



// Statics

/** Provide common utility to print the type's characteristics
 *
 *  \param output The output stream to print information
 */
template <typename Testee>
void test_and_log_util::print_type_information(out_type& output){
    output << "Is trivial? " << std::is_trivial<Testee>::value << '\n'
           << "Is standard layout? "
               << std::is_standard_layout<Testee>::value << '\n'
           << "Is POD? " << std::is_pod<Testee>::value << '\n'
           << "Size: " << sizeof(Testee) << " bytes\n"
           << "Size of diglist_type: "
               << sizeof(typename Testee::diglist_type) << " bytes\n"
           << "Size of digit_type: "
               << sizeof(typename Testee::digit_type) << " bytes\n"
           << "\n"
           ;
}



// Constructors and destructors

/** Creates an empty test list with assertion not enforced.
 *  In addition, the default outputs are set.
 *
 *  \param list_name Name of this list of tests
 */
test_and_log_util::test_and_log_util( const str_type& list_name,
                                      const str_type& file_name
)
    : m_force_assert(true)
    , m_tests()
    , p_console(&std::clog)
    , p_log_dest(nullptr)
    , m_test_list_name(list_name)
    , m_file_src(file_name)
{}