export module StringOP;
import <string>;
import <algorithm>;
import <cctype>;
#include <chrono>

export class StringOP
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