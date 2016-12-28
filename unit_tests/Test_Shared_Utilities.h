#ifndef SHARED_TEST_UTILITIES__H__
#define SHARED_TEST_UTILITIES__H__

#include <string>
#include <ostream>
#include <functional>
#include <vector>
#include <utility>
#include <chrono>

#define STRINGIFY_RAW(S) #S
#define STRINGIFY(S) STRINGIFY_RAW(S)

#define ADD_TEST(TEST_OBJ, FUNCTIONALITY_TEST)            \
        TEST_OBJ.add_test( STRINGIFY(FUNCTIONALITY_TEST), \
                           FUNCTIONALITY_TEST             \
                           )
#define ADD_TEST_BOTH(TEST_OBJ, FUNCTIONALITY_TEST, SPEED_TEST, REPEATS) \
        TEST_OBJ.add_test( STRINGIFY(FUNCTIONALITY_TEST),                \
                           FUNCTIONALITY_TEST, SPEED_TEST, REPEATS       \
                           )

class test_and_log_util {
    public:
        // Type aliases
        /** Simple alias for size such as when using a counter variable. */
        using size_type = std::uint_fast64_t;
        /** Simple alias for character strings. */
        using str_type = std::string;
        /** Representation for clock used in time span measurements. */
        using clock_type = std::chrono::high_resolution_clock;
        /** Representation for time spans in seconds. */
        using time_type = std::chrono::duration<double>;
        /** Output stream type for printing messages and logging. */
        using out_type  = std::ostream;
        /** A universal return type for tests that contains expected
         *  and actual calculated results in string format.
         */
        struct result_type{
            str_type expected, actual;
        };
        /** Type of function expected to test just functionality.
         *
         *  \param out_type& Stream output made available for
         *                   possible logging by the testing
         *                   function.
         *  \return A structure containing strings with the expected
         *          and actual results for later comparison.
         */
        using functional_test_type = std::function<result_type (out_type&)>;
        /** Type of function expected to test how fast an operation takes.
         *  The speed will be measured externally, so be aware that the
         *  reported time taken may include delay from jumping to the
         *  function.
         *
         *  \param out_type& Stream output made available for possible
         *                   logging by the testing function.
         */
        using speed_test_type = std::function<void (out_type&)>;
        /** Simple box for grouping both types of tests. */
        struct test_group {
            str_type             func_name;
            functional_test_type func_test;
            speed_test_type      speed_test;
            size_type            max_repeats;
        };
        /** Alias for how all tests are stored. std::vector is chosen since
         *  the penalty for adding items is neglible and iterating is quicker.
         */
        using test_list = std::vector<test_group>;



        // Setup functions

        /** Set whether or not the assert() macro is used. If set to true,
         *  the program will stop tests upon encountering the first failed
         *  test.
         *
         *  \param force_abort Set true to abort program when a test fails.
         */
        void set_assert(bool force_abort);

        /** Add a new test to the list. Note that the test is not performed
         *  yet. At minimum, a functionality test needs to be passed, but a
         *  speed test can be passed as well along with the maximum number
         *  of times the speed test may repeat the operation under test.
         *
         *  \param functionality_test_name Name of func_test
         *  \param func_test The function that tests functionality.
         *  \param speed_test The function that tests operation speed.
         *  \param repeats The maximum number of times the operation may
         *                 be repeated during the speed test.
         */
        void add_test( const str_type& functionality_test_name,
                       functional_test_type func_test,
                       speed_test_type speed_test = speed_test_type(),
                       size_type repeats = 0
                       );

        /** Set the output stream for logging to media. By default,
         *  upon construction, no output is set.
         *
         *  \param new_output Output stream for logging information to
         *                    media for further review later.
         */
        void set_log_output(out_type& new_output);

        /** Set the output stream for printing to a console. By default,
         *  upon construction, the output is set to std::clog.
         *
         *  \param new_output Output stream for logging information to
         *                    a console for a human reading.
         */
        void set_console_output(out_type& new_output);



        // Modifiers

        /** Iterate through the list and perform each test. For each
         *  list item, the functionality test is performed first and
         *  console messages are formatted.
         *  If assertion is not enforced, after performing all tests,
         *  the line number and source file of each test is
         *  printed to the console.
         */
        void execute_tests();



        // Statics

        /** Provide common utility to print the type's characteristics
         *
         *  \param output The output stream to print information
         */
        template <typename Testee>
        static void print_type_information(out_type& output);




        // Constructors and destructors

        /** Creates an empty test list with assertion not enforced.
         *  In addition, the default outputs are set.
         *
         *  \param list_name Name of this list of tests
         *  \param file_name Name of file these tests are in
         */
        test_and_log_util(const str_type& list_name, const str_type& file_name);

        // Compiler generated constructors and destructors
        test_and_log_util(const test_and_log_util&)            = default;
        test_and_log_util& operator=(const test_and_log_util&) = default;
        test_and_log_util(test_and_log_util&&)                 = default;
        test_and_log_util& operator=(test_and_log_util&&)      = default;
        ~test_and_log_util()                                   = default;

    private:
        bool      m_force_assert;
        test_list m_tests;
        out_type* p_console;
        out_type* p_log_dest;
        str_type  m_test_list_name;
        str_type  m_file_src;
};

#include <fstream>

extern std::ostream& test_console;
extern std::ofstream test_log;

#endif
