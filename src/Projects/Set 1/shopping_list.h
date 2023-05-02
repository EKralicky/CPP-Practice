#pragma once
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <functional>
#include "../project.h"
#include "../utility_lib/stringop.h"


class ShoppingList : public Project
{
public:
	bool run() override
	{
		std::cout << "SHOPPING LIST\nAvailable Commands: Add, Update, Remove, View\n";
		std::string command;
		while (true) {
			std::cout << ">>";
			std::cin >> command;
			auto it = command_map.find(stringutil::tolower_copy(command));
			if (it != command_map.end()) {
				it->second();
			}
			else {
				std::cout << "Invalid Command\n";
			}
		}
		return true;
	}
private:

	// Keep track of the item and the count
	std::map<std::string, int> item_counts;
	std::map<std::string, std::function<void()>> command_map{
		{"add", std::bind(&ShoppingList::update, this, true)},
		{"update", std::bind(&ShoppingList::update, this, false)},
		{"remove", std::bind(&ShoppingList::remove, this)},
		{"view", std::bind(&ShoppingList::view, this)}
	};

	int getIntegerInput()
	{
		int data;
		while (std::cout << ">>" && !(std::cin >> data)) {
			std::cout << "Invalid input!\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		return data;
	}

	bool confirm(std::string message)
	{
		char a;
		std::cout << message;
		while (!(std::cin >> a) && ((a != 'y') || (a != 'n'))) {
			std::cout << "Invalid input. Try again: ";
		}
		a = tolower(a);
		if (a == 'y') return true;
		else if (a == 'n') return false;
	}

	void update(bool isAdding)
	{
		std::string item;
		std::cin.ignore();
		std::getline(std::cin, item);

		auto item_iter = item_counts.find(item);

		if (isAdding && item_iter == item_counts.end()) // Adding and item is NOT in shopping list
		{
			std::cout << "How many do you want to add?\n";
			int count = getIntegerInput();
			item_counts[item] = count;
		}
		else if (!isAdding && item_iter != item_counts.end()) // Updating and item is in shopping list
		{
			std::cout << "Enter a new count for the item\n";
			int count = getIntegerInput();
			item_counts[item] = count;
		}
		else
		{
			std::cout << (isAdding ? "Item already exists!\n" : "Item not found!\n");
		}
	}

	void remove()
	{
		std::string item;
		std::cin.ignore();
		std::getline(std::cin, item);

		if (item_counts.find(item) == item_counts.end()) // If item is NOT in shopping list
		{
			std::cout << "Item not found!\n";
			return;
		}
		if (confirm("Are your sure you want to remove " + item + " from your shopping list? (y/n): "))
		{
			item_counts.erase(item);
		}
	}

	void view()
	{
		std::cout << "Shopping List\n-------------\n";
		for (auto& entry : item_counts)
		{
			std::cout << entry.first << " " << entry.second << "\n";
		}
	}
};