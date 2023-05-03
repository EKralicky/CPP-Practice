#include <string>
#include <chrono>

template<typename T>
std::string duration_type_string();

template<>
std::string duration_type_string<std::chrono::nanoseconds>() {
    return "nanoseconds";
}

template<>
std::string duration_type_string<std::chrono::microseconds>() {
    return "microseconds";
}

template<>
std::string duration_type_string<std::chrono::milliseconds>() {
    return "milliseconds";
}

template<>
std::string duration_type_string<std::chrono::seconds>() {
    return "seconds";
}