#pragma once

#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <thread>
#include <locale>
#include <cwchar>

#ifdef WINDOWS
#include <windows.h>
#endif

namespace set2 {

// Toggels visibility of white windows cursor in the command prompt
#ifdef WINDOWS
void show_console_cursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}
#else
void show_console_cursor(bool showFlag)
{
	std::cout << "Hidden console cursor not supported on current platform!";
	return;
}
#endif
/*
Counts the 8 neighbors at position x, y

arr = cell array
row/column = row/column to check neighbors of
rows/columns = total number of rows & columns in the grid
*/
typedef std::vector<std::vector<bool>> vec_grid;

int count_neighbors(const vec_grid& grid, int row, int column, int rows, int columns)
{
	constexpr int neighbor_count = 8;
	constexpr int cell_offsets[][neighbor_count] =
	{
		{-1, -1}, {-1, 0}, {-1, 1}, {1, -1},
		{1, 0}, {1, 1}, {0, -1}, {0, 1}
	};

	int count = 0;
	for (int i = 0; i < neighbor_count; i++) {
		int new_c = column + cell_offsets[i][0]; // new column
		int new_r = row + cell_offsets[i][1]; // new row

		if ((new_c >= 0 && new_c < columns) && (new_r >= 0 && new_r < rows)) { // Checks out of bounds
			bool c = grid[new_r][new_c]; // get cell
			if (c) { // If cell is alive
				++count;   // Update count
			}
		}
	}
	return count;
}

void copy_grid(const vec_grid& src, vec_grid& dest) {
	for (int i = 0; i < src.size(); ++i) {
		for (int j = 0; j < src[i].size(); ++j) {
			dest[i][j] = src[i][j];
		}
	}
}

void render(const vec_grid& grid) {
	const int buf_size = 100 * 100;
	// Allocate buffer on the heap
	char* data = new char[buf_size];
	int ptr = 0;
	// Set the cursor position
	printf("\033[%d;%dH", 0, 0);
	// Write char data to buffer
	data[ptr++] = '\n';
	for (int i = 0; i < grid.size(); i++) {
		for (bool c : grid[i]) {
			data[ptr++] = c ? '#' : ' '; // Use '' for alive cells
			data[ptr++] = ' ';
		}
		data[ptr++] = '\n';
	}

	// Null-terminate the buffer
	data[ptr] = '\0';

	// Print the buffer
	printf("%s", data);
	// delete data from heap
	delete[] data;
}

void gol_start()
{
	std::locale::global(std::locale("")); // Set the global locale to the user's default locale
	std::wcout.imbue(std::locale()); // Set the locale for wcout to the user's default locale
	show_console_cursor(false);

	int rows, columns, gen;
	std::cin >> rows >> columns >> gen;

	vec_grid grid(rows, std::vector<bool>(columns));		// Holds current generation grid
	vec_grid temp_grid(rows, std::vector<bool>(columns));	// Holds next generation grid

	// Initialize current gen grid
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			char state;
			std::cin >> state;
			if (state == '*') {
				grid[i][j] = true;
			}
		}
	}
	copy_grid(grid, temp_grid); // Copy temp grid to grid so we can keep the same value in case 3
	// Run generations
	for (int g = 0; g < gen; g++) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				int count = count_neighbors(grid, i, j, rows, columns);
				if (count < 2 || count > 3) {
					temp_grid[i][j] = false;
				}
				else if (count == 3) {
					temp_grid[i][j] = true;
				}
			}
		}
		render(grid); // Render current generation
		copy_grid(temp_grid, grid); // Assign grid to temp_grid for the next generation
		std::this_thread::sleep_for(std::chrono::milliseconds(50)); // 16 ms frame time (60fps)
	}
	//render(grid); // Render final grid
}

}

