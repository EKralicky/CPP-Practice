#pragma once
#include "Project.h"
#include <iostream>
#include <cctype>

/*
get user conversion: c to f, or, f to c
get number
print result


*/
class TemperatureConverter : public Project {

public:

	double convert(char from, char to, double val) {

		if (tolower(from) == tolower(to)) {
			return val;
		}

		if (tolower(to) != 'c' || tolower(to) != 'f') {
			std::cout << "Unknown conversion to [" << to << "]. Valid options are c, or f.";
			return 0;
		}

		else if (tolower(from) == 'f') {
			return (val - 32) * (5.0f / 9.0f);
		}
		else if (tolower(from) == 'c') {
			return (val * (9.0f / 5.0f)) + 32;
		}
		else {
			std::cout << "Unknown conversion from [" << from << "]. Valid options are c, or f.";
			return 0;
		}
	}


	bool run() override {
		
		char from, to;
		double val;
		

		std::cout << "value: ";
		std::cin >> val;
		std::cout << "From: ";
		std::cin >> from;
		std::cout << "To: ";
		std::cin >> to;

		from = toupper(from);
		to = toupper(to);

		std::cout << val << from << " is equivalent to " << convert(from, to, val) << to << "\n";

		return 0;
	}



};

