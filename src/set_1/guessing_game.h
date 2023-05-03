#pragma once
#include <iostream>
#include <random>
#include <chrono>
#include <sstream>
#include "../project.h"

// Im going to start using the newline brace convention from here on 
// also, one line ifs aren't going to have braces
class GuessingGame : public Project 
{

public:
	/*
	* generates a random number from low to high inclusive
	*/
	int generate_random(int low, int high) 
	{
		// Initialize mt with system clock as seed
		std::mt19937 mt{
			static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count())
		};
		std::uniform_int_distribution dist{ low, high };
		return dist(mt);
	}

	bool run() override
	{
		int number = generate_random(0, 100);
		int guess = -1;
		std::string line;


		std::cout << "Welcome to hi-lo!\nI have a number between 0 and 100. After you guess, I will tell you if its higher than the number or lower." << "\n";

		while (guess != number) 
		{
			std::cout << "Guess: ";
			// validate guess to integers
			while (std::getline(std::cin, line)) 
			{
				std::stringstream ss(line);
				if (ss >> guess)
				{
					if (ss.eof())
						break;
				}
				std::cout << "Invalid input. Please try again.\n Guess: ";
			}
			if (guess < number) 
				std::cout << "Too low! Guess again." << "\n";
			
			else if (guess > number) 
				std::cout << "Too high! Guess again." << "\n";
			
		}
		std::cout << "Correct!";
		return true;
	}










};