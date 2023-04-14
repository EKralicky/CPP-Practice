#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include "../project.h"


class Palindrome : public Project
{

	bool no_stl() 
	{
		std::string input;
		std::cout << "Palindrome checker\nEnter a string: ";
		std::cin >> input;

		std::size_t input_len = input.size();
		for (int i = 0; i < input_len; i++) 
		{
			if (input[i] != input[(input_len - 1) - i]) 
			{ // if fromt and back chars are not equal, the string is automatically not a palindrome so return
				std::cout << "Input is NOT a palindrome!";
				return false;
			}
			if (i == floor(input_len / 2)) 
			{ // if comparisons have reached the middle
				std::cout << "Input is a palindrome!";
				return true;
			}
		}
	}

	/*
	this works because the std::string cosntructor can take in two iterators, start and end,
	and construct a string with the charatcers starting at start and ending at end. Since we
	passed the end of the string as start and the start of the string as end, we will get a
	reversed string. Then we simply have to compare it against the original string

	rbegin = last element of string
	rend = 1 before first element of string

	*/
	bool string_constructor_reverse() 
	{
		std::string input;
		std::cout << "Palindrome checker\nEnter a string: ";
		std::cin >> input;

		if (input == std::string(input.rbegin(), input.rend())) {
			std::cout << "Input is a palindrome!";
			return true;
		}
		std::cout << "Input is NOT a palindrome!";
		return false;
	}

	/*
	This version compares the values bewteen the front of the string to the middle, and from the back of the string
	to the middle (hence the reverse iterator). The equal function assumes that both ranges have the same length, so there
	is no need to put an end iterator for the second input.
	*/
	bool fast_stl_equal()
	{
		std::string input;
		std::cout << "Palindrome checker\nEnter a string: ";
		std::cin >> input;

		if (equal(input.begin(), input.begin() + input.size() / 2, input.rbegin())) {
			std::cout << "Input is a palindrome!";
			return true;
		}
		std::cout << "Input is NOT a palindrome!";
		return false;
	}


	/*
	* Steps:
	* 1. Read input and validate
	* 2. Read input from index 0 to n, and from index n to 0, compare
	* 3. True if comparison success
	* 
	* Fastest version is fast_stl_equal
	* 
	*/
	bool run() override
	{
		return fast_stl_equal();
	}
};