#pragma once

#include <iostream>

namespace set2 {
    // Bubble sort
    template<typename Container>
    static void bubble_sort(Container& c)
    {
        auto end = c.end();
        for (int i = 0; i < c.size(); i++) {
            for (auto it = std::next(c.begin()); it != end; ++it) {
                auto prev = std::prev(it);
                if (*it < *prev) {
                    std::iter_swap(it, prev);
                }
                
            }
            --end;
        }
    }
}