/** \file
 *  Exception type that inherits from the standard library
 *  std::exception class. For debugging, this exception class
 *  provide an error code and a message that includes the name
 *  of the function that threw the exception and a brief description
 *  of what the error was. 
 */

#ifndef PRECISION_EXCEPTION_DEFINITION_CLASS_H__
#define PRECISION_EXCEPTION_DEFINITION_CLASS_H__

#include <exception>
#include <string>

namespace Precision{
    /** Exception type that inherits from the standard library
     *  std::exception class. For debugging, this exception class
     *  provide an error code and a message that includes the name
     *  of the function that threw the exception and a brief
     *  description of what the error was. 
     */
    class exception : public std::exception{
        public:
            /** Error codes to provide information on how the result of
             *  an operation would fail:
             *  * insufficient_memory: The result would have infinite digits
             *  * divide_by_zero: Similar to insufficient_memory but is more
             *                    specific on how
             *  * indeterminate: The result is not calculable at all. Most
             *                   likely, this will be rarely used.
             *  * unsupported: The result is in an unsupported number format
             *                 that the number type cannot store/represent.
             *  * invalid_digit: Similar to unsupported but is specifically
             *                   about unsupported glyphs.
             *  * none: No error.
             */
            enum code : unsigned short{
                insufficient_memory = 0,
                divide_by_zero,
                indeterminate,
                unsupported,
                invalid_digit,
                none
            };

            /** Type alias for the string type used by this class */
            using str_type = std::string;

            /** Provides a short message composed of the name of the
             *  function that threw the exception and a brief description
             *  of what the error was.
             *
             * \return A character string with the error message. 
             */
            const char* what()const noexcept;

            /** Provide an error code whose value represents what
             *  kind of error occurred.
             *
             * \return The error code
             */
            code type()const noexcept;

            /** Provides just the name of the function that threw the exception.
             *
             * \return A character string with function name. 
             */
            const char* source()const noexcept;

            /** Construct an exception with an error code and function name.
             *
             * \param err Error code 
             * \param src_name Function name 
             */
            exception(code err, const char* src_name= "Unknown source")noexcept;

            /** Construct an exception with an error code and function name
             *  in a str_type object.
             *
             * \param err Error code 
             * \param src_name Function name 
             */
            explicit exception(code err, const str_type& src_name)noexcept;

            /** Compiler generated copy constructor. */
            exception(const exception&)             = default;

            /** Compiler generated copy assignment operator. */
            exception& operator=(const exception&)  = default;

            ~exception()noexcept{}
        private:
            code err_type;
            str_type src;
            str_type full_message;
            static constexpr char const* message_map[none] = {
                "Insufficient memory.",
                "Division by zero attempt.",
                "Indeterminate result.",
                "Unsupported number format.",
                "Invalid digit."
            };
    };
}

#endif
