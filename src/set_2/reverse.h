#pragma once

#include <string>
#include <algorithm>

namespace set2 {

	// My original method
	constexpr void reverse(std::string& s) 
	{
		for (auto it = s.begin(); it != (s.begin() + s.size() / 2); ++it) {
			std::iter_swap(it, s.end() - (it - s.begin()) - 1);
		}
	}

	// STL method
	constexpr void reverse_stl(std::string::iterator first, std::string::iterator last)
	{
		while (first != last && first != --last) {
			std::iter_swap(first, last);
		}
	}

	// STL templated method
	template<typename Iter>
	constexpr void reverse_templ(Iter first, Iter last)
	{
		while (first != last && first != --last) {
			std::iter_swap(first, last);
		}
	}
}