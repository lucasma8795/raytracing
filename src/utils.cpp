#include "utils.h"

#include <execinfo.h>
#include <iostream>
#include <string_view>


namespace Raytracer
{


void fatal(std::string_view sv)
{
    // TODO: look at this instead
    // https://stackoverflow.com/questions/77005/how-to-automatically-generate-a-stacktrace-when-my-program-crashes

    // Maximum call stack trace size.
    static const size_t MAX_STACK_SIZE = 128UL;

    // Log fatal error message.
    std::cerr << "fatal: " << sv << std::endl;

    // Log call stack.
    void* array[MAX_STACK_SIZE];

    size_t size = backtrace(array, MAX_STACK_SIZE);
    char** strings = backtrace_symbols(array, size);

    std::cerr << "Obtained " << size << " stack frames." << std::endl;

    for (size_t i = 0; i < size; i++)
    {
        std::cerr << strings[i] << std::endl;
    }

    // Terminate the program.
    free(strings);
    std::abort();
}


}