#pragma once
#include "Project.h"
#include <iostream>

/*
lets do this assembly style

ask for lhs value
ask for rhs value
ask for operator

evaluate & print
*/
class Calculator : public Project {
public:

	double eval(double n1, double n2, char op) {

		switch (op) {
			case '+':
				return n1 + n2;
				break;
			case '-':
				return n1 - n2;
				break;
			case '*':
				return n1 * n2;
				break;
			case '/':
			case '\\':
				return n1 / n2;
				break;
			default:
				std::cout << "Invalid operator: [" << op << "]. Please use either +, -, *, /, or \\" << "\n";
				return 0;
		}
	}

	bool run() override {
		double a, b;
		char op;

		std::cout << "Enter first number (float): ";
		std::cin >> a;

		std::cout << "Enter second number (float): ";
		std::cin >> b;

		std::cout << "Enter operator: ";
		std::cin >> op;

		std::cout << "Result: " << eval(a, b, op);
		
		return true;
	}
};