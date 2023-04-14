#pragma once
#include <string>
#include <algorithm>
#include <cctype>
#include <chrono>

class StringOP
{
public:
	static std::string tolower_copy(const std::string& data)
	{
		std::string copy = data;
		std::transform(copy.begin(), copy.end(), copy.begin(),
			[](unsigned char c) { return std::tolower(c); });
		return copy;
	}
};