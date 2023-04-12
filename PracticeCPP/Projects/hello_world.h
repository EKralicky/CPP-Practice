#pragma once
#include <iostream>
#include "Project.h"

class HelloWorld : public Project {

public:
	bool run() override {
		std::cout << "Hello World!" << "\n";
		return true;
	}

};


