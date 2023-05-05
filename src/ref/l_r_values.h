#pragma once
#include <iostream>
/*
lvalue - a value that has a memory address assigned to it e.g. int x = 54. [x] here is an lvalue
rvalues - a values that is not bound to a memory address, kind of like a temporary. e.g int x = 54. [54] here is an lvalue
lvalue reference - a reference to an lvalues memory. kind of like a pointer, but more robust as it acts like an lvalue and you cannot dereference it
rvalue reference - a reference that binds to an rvalue denoted by the double ampersand X&&. This is mainly used for move semantics and perfect forwarding for templates.
                    When we use rvalue references, the compiler allows us to "steal" resources from the rvalue (temporary object) that it refers to (No copying!). Since rvalues have short-lived lifetimes and are destroyed at 
                    the next semicolon, we don't need to worry about using it later on; thats why we can steal from it. Otherwise, if we *could* use the rvalue later on and it wasn't destroyed, it could lead
                    to undefined behavior because it doesn't own anything! we already stole its resources! Now, what if we want to move lvalues instead of rvalues? thats where std::move comes into play. C++ doesn't allow
                    implicit casts to rvalue references from lvalues due to the potential for undefined behavior and data loss when using lvalues after a move operation. Lets say we have a class Foo with a move constructor:

                    Foo(Foo&& other) { // Move constructor which takes in an rvalue reference "other"
                        ... // Move data, leaving other in a valid, but "empty" state
                    }

                    Now if we construct Foo with an LVALUE, and then use that lvalue afterwards:

                    Foo lvalue(...) // Create the lvalue with some data
                    Foo c(lvalue) // move the data from lvalue to c. **Assuming an implicit cast is used**
                    lvalue.doSomething() // UNDEFINED BEHAVIOR! lvalue no longer has its data because we already moved it!!

                    This is why C++ doesn't allow implicit casts to rvalue references. It is very dangerous and could lead to undefined behavior. How do we solve this? with std::move. 
                    std::move is a function that takes in a lvalue or rvalue and casts it to an rvalue reference. It doesn't actually *move* anything, it simply casts an l or rvalue to an rvalue reference 
                    so they can be used for moving. Using std::move is an explicit way of saying to the compiler: I want to move this data, from this lvalue, and I promise I wont use the lvalue again afterwards. 
                    Its there to be a safeguard so you don't accidentally move an lvalue you're planning on using later on in the code.
*/

void l_r_value() {
    int x = 5; // x is an lvalue since it has an address in memory, 5 is an rvalue
}

void l_value_reference() {
    int x = 10;
    int& y = x; // y now refers to x's memory, so y "holds" the value 10. it does not own it, it just refers to x
}

void r_value_reference(int&& rvr) { // rvr only binds to r value references
    std::cout << rvr << "\n"; // prints the r value reference
}

void test_r_value_reference() {
    int x = 7;
    r_value_reference(10);
    r_value_reference(int(5));
    //r_value_reference(x); <-- does not work! because x is an lvalue and it cannot bind to an rvalue
}


//====================
// Move Semantics
//====================


class MoveSemantics {

public:
    MoveSemantics(int d) { // Regular Constructor
        m_data = new int(d);
    }

    ~MoveSemantics() { // Destructor
        delete m_data;
    }

    // Use the rule of 5 since this class handles memory!
    // The rule of 5 means that if any class manages resources, it should include a destructor, copy constructor, copy assignment operator, move constructor and move assignment operator.

    // Copy constructor. 
    // Takes in an lvalue reference to another MoveSemantics type object
    MoveSemantics(const MoveSemantics& other) { 
        std::cout << "Copy Constructed!" << "\n";
        m_data = new int(*other.m_data); // create a copy of other.m_data and assign it to m_data. since there is no memory currently in m_data we don't need to delete it
    }

    // Copy assignment (=) operator. So when we want to use the equals sign like x = y; 
    // Takes in an lvalue reference to another MoveSemantics type object
    MoveSemantics& operator=(const MoveSemantics& other) { 
        std::cout << "Copy Assigned!" << "\n";
        if (this != &other) { // we don't want to self assign!
            delete m_data; // delete our current data to avoid memory leak! If we are using assignment operator, the object must have already been constructed and had some value assigned to m_data
            m_data = new int(*other.m_data);    
        }
        return *this;
    }

    // Move constructor. when we want to *move* resources from x to y instead of *copying* which takes time.
    // Takes in an *rvalue reference* which can only bind to an rvalue! 
    MoveSemantics(MoveSemantics&& other) noexcept { 
        std::cout << "Move Constructed!" << '\n';
        m_data = other.m_data; // assign our data to others data
        other.m_data = nullptr; // delete others data
    }

    MoveSemantics& operator=(MoveSemantics&& other) noexcept { 
        std::cout << "Move Assigned!" << '\n';
        if (this != &other) { // we don't want to self assign!
            delete m_data; // delete our current data to avoid memory leak! If we are using assignment operator, the object must have already been constructed and had some value assigned to m_data
            m_data = other.m_data;
            other.m_data = nullptr;
        }
        return *this;
    }

private:
    int* m_data; // we have some data, in this case a pointer to an integer
};


