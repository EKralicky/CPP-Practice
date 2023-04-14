#include "Projects/Set 1/hello_world.h"
#include "Projects/Set 1/calculator.h"
#include "Projects/Set 1/temp_convert.h"
#include "Projects/Set 1/guessing_game.h"
#include "Projects/Set 1/palindrome_checker.h"
#include "Projects/Set 1/ATM.h"
#include "Projects/Set 1/prime.h"
#include "Projects/Set 1/Fibonacci.h"
#include "Projects/Set 1/grade_calculator.h"

int main()
{
    Project* project = new GradeCalculator();
    project->run();

    delete project;
    return 0;
}
