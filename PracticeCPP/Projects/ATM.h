/*
Simple ATM machine:
Design a basic ATM program that allows users to check their balance, deposit, and withdraw money.
*/

#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "Project.h"


class ATM : public Project 
{

public:




	char getInputAction() 
	{
		std::cout << ">>";
		std::string line;
		while (std::getline(std::cin, line))
		{
			if (isalpha(line[0]) && line.size() == 1) 
			{
				break;
			}
			std::cout << "Invalid input. Please try again.\n>>";
		}
		return line[0];
	}

	int getInputAmount() 
	{
		int amount;
		std::string line;
		while (std::getline(std::cin, line))
		{
			std::stringstream ss(line);
			if (ss >> amount) 
			{
				break;
			}
			std::cout << "Invalid input. Please try again.\n>>";
		}
		return amount;
	}



	bool run() {
		while (true) 
		{
			char action = tolower(getInputAction());

			switch (action)
			{

			case 'w':
			{
				std::cout << "Enter amount to withdraw: ";
				int amount = getInputAmount();
				if (amount > balance)
				{
					std::cout << "Insufficient funds." << "\n";
				}
				else
				{
					balance -= amount;
					std::cout << "Successfully withdrew $" << amount << ". Your current balance is: $" << balance << "\n";
				}
				break;
			}

			case 'd':
			{
				std::cout << "Enter amount to deposit: ";
				int amount = getInputAmount();
				balance += amount;
				std::cout << "Successfully deposited $" << amount << ". Your current balance is: $" << balance << "\n";
				break;
			}

			case 'c':
			{
				std::cout << "Your current balance is: $" << balance << "\n";
				break;
			}

			default:
			{
				std::cout << "ERROR: Unknown input. You broke af lmao\n";
				break;
			}
			}
		}
		
		return true;
	}
private:
	int balance = 0;
};


