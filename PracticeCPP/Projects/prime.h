#pragma once
#include <iostream>
#include "Project.h"


// This was hacked together in 5 mins. No input validation :)
class Prime : public Project
{
public:

	bool check_prime(int a)
	{
		if (a < 2) return false;
		if (a == 2) return true;
		if (a % 2 == 0) return false;
		for (int i = 3; i * i <= a; i += 2)
		{
			if (a % i == 0) return false;
		}
		return true;
	}


	bool run() override
	{
		std::cout << "Prime Checker" << "\n";
		while (true) {
			int a;
			std::cout << "Enter a number: ";
			std::cin >> a;

			bool b = check_prime(a);
			if (b) 
			{
				std::cout << "\nPrime\n";
			}
			else
			{
				std::cout << "\nComposite\n";
			}
			
		}
		
	}
};