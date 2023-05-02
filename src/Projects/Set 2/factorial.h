#pragma once
#include <iostream>
#include "../project.h"

namespace set2
{

	static int factorial_recursive(int x)
	{
		if (x <= 0) {
			return 1;
		}
		else {
			return x * factorial_recursive(x - 1);
		}
	}

	static int factorial_iterative(int x)
	{
		if (x <= 0) {
			return 1;
		}

		int p = 1;
		for (int i = 1; i <= x; i++) {
			p *= i;
		}

		return p;
	}













}