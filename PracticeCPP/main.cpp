#include "Projects/hello_world.h"
#include "Projects/calculator.h"
#include "Projects/temp_convert.h"
#include "Projects/guessing_game.h"
#include "Projects/palindrome_checker.h"
#include "Projects/ATM.h"
#include "Projects/prime.h"


int main()
{
    Project* project = new Prime();
    project->run();

    delete project;
    return 0;
}
