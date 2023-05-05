#include <memory>
#include <iostream>






//=========================
// Smart Pointers
//=========================


int non_t_rvalue(std::string&& r) {
    return 1;
}

static int smart_ptr() {

    // Unique Pointers

    // Creation with constructor
    std::unique_ptr<int> u_constr_ptr(new int(5)); 
    std::cout << *u_constr_ptr << "\n"; // Prints 5

    // Creation with std::make_unique. make unique implicitly calls the constructor of the type with the passed input
    std::unique_ptr<int> u_make_ptr = std::make_unique<int>(10);
    std::cout << *u_constr_ptr << "\n"; // Prints 10
    std::string a = "AAA";
    non_t_rvalue(std::move(a));
    std::cout << a;


}