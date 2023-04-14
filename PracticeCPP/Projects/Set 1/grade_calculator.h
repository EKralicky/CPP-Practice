#pragma once
#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include <algorithm>
#include "../project.h"
#include "../utility_lib/stringop.h"

class GradeCalculator : public Project
{
public:
	bool run() override
	{
		std::cout << "Enter percentage grade followed by the weight for that grade in your class.\nExample: >> 85 0.2\nWhen you are finished, enter 'done'\n>>";
		std::string input;
		while (std::getline(std::cin, input))
		{
			if (StringOP::tolower_copy(input) == "done") break;
	
			std::stringstream ss(input);
			int grade;
			float weight;
			ss >> grade >> weight;
			total_grade += (grade * weight);
			std::cout << ">>";
		}
		std::cout << "Your total grade is: " << total_grade << "%\n";
		return true;
	}

private:
	int total_grade = 0;
};
