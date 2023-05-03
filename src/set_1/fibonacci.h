#pragma once
#include <iostream>
#include "../project.h"


class Fibonacci : public Project
{
public:

	int basic_fib(int x)
	{
		if (x < 2)
		{
			return x;
		}
		return basic_fib(x - 1) + basic_fib(x - 2);
	}


	bool run() override
	{
		int n;
		std::cout << "Enter a number: ";
		std::cin >> n;
		std::cout << "fib(" << n << ") is " << basic_fib(n) << "\n";
		return true;
	}
};