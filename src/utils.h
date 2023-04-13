#ifndef UTILS_H__2Lvr1D4d7Q
#define UTILS_H__2Lvr1D4d7Q

// #include <functional>
#include <string_view>


namespace Raytracer
{


// Aborts the program when a fatal error occurs.
void fatal(std::string_view sv) __attribute__((noreturn));


// // Convert function argument types to tuple
// // https://stackoverflow.com/questions/57622162/get-function-arguments-type-as-tuple
// template<typename T>
// struct function_traits
// {
//     template<typename R, typename... Args>
//     static std::tuple<Args...> pro_args(std::function<R(Args...)>);

//     using arguments = decltype(pro_args(std::function{std::declval<T>()}));
// };

} // namespace Raytracer


#endif