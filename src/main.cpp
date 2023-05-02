#include "Projects/Set 1/hello_world.h"
#include "Projects/Set 1/calculator.h"
#include "Projects/Set 1/temp_convert.h"
#include "Projects/Set 1/guessing_game.h"
#include "Projects/Set 1/palindrome_checker.h"
#include "Projects/Set 1/ATM.h"
#include "Projects/Set 1/prime.h"
#include "Projects/Set 1/fibonacci.h"
#include "Projects/Set 1/grade_calculator.h"
#include "Projects/Set 1/shopping_list.h"
#include "Projects/Set 2/reverse.h"
#include "Projects/Set 2/game_of_life.h"
#include "Projects/Set 2/factorial.h"
#include "Projects/Set 2/bubble_sort.h"

#include <string>

int main()
{
    /*Project* project = new ShoppingList();
    project->run();*/
    std::vector<int> in {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    set2::bubble_sort(in);
    for (auto i : in) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    /*delete project;*/
    return 0;
}
