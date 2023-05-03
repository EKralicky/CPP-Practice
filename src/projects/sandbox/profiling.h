#pragma once
#include <chrono>
#include <iostream>
#include <typeinfo>
#include <algorithm>
#include "chrono_names.h"

typedef std::chrono::high_resolution_clock::time_point time_point;

template<typename T>
struct SCOPED_PROFILING_TIMER {
    time_point m_start_time;
    time_point m_end_time;
    const char* m_name;
    SCOPED_PROFILING_TIMER(const char* name) {
        m_name = name;
        m_start_time = std::chrono::high_resolution_clock::now();
    }
    ~SCOPED_PROFILING_TIMER() {
        m_end_time = std::chrono::high_resolution_clock::now();
        auto runtime = std::chrono::duration_cast<T>(m_end_time - m_start_time).count();
        std::cout << "Timer [" << m_name << "] ran for " << runtime << " " << duration_type_string<T>() << "\n";
    }
};

// Combining two tokens. e.g. CONCAT(I drink, tea) -> "I drink tea"
#define CONCAT_IMPL(x, y) x##y
#define CONCAT(x, y) CONCAT_IMPL(x, y)

// For converting ints to string with preprocessor
#define STR_IMPL(x) #x
#define STR(x) STR_IMPL(x)

// For timing a scoped code block such as a function
#define RUN_SCOPED_PROFILER(T) \
        SCOPED_PROFILING_TIMER<T> CONCAT(timer_,__LINE__)(STR(__LINE__)); \
        (void)CONCAT(timer_,__LINE__); // Makes sure the timer gets "used"

// Pull Request Test!