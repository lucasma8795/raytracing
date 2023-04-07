#ifndef UTILS_H__2Lvr1D4d7Q
#define UTILS_H__2Lvr1D4d7Q

#include <string_view>


namespace Raytracer
{


// Aborts the program when a fatal error occurs.
void fatal(std::string_view sv) __attribute__((noreturn));


} // namespace Raytracer


#endif