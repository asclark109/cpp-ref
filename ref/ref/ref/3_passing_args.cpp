#ifndef EXPASSING_ARGS_H
#  define EXPASSING_ARGS_H

#include<string>
#include<iostream>
#include<vector>
#include<memory>

void exPASSING_ARGS() {

    // RECAP:
    // If an expression or variable has a value type (i.e., not a reference type),
    // it gets its own storage
    // --Memory is allocated and a constructor is run
    // --When the variable or expression leaves scope, it’s destructor is run and
    //   the memory for the object is released

    // LVALUE REFERENCE
    // If the expression is a (lvalue) reference type, its
    // storage needs to be supplied as part of initialization
    // --No memory management, construction, or destruction
    //   occurs either during initialization or upon leaving scope

    // PASSING ARGUMENTS
    // 3 ways in c++

    ////////////////////
    // PASS BY VALUE
    ////////////////////
    void f(int x);
    // x is a copy of the caller’s object
    // Any changes f makes to x are not seen by the caller

    // BENEFITS/DRAWBACKS
    // (+)  It is very safe to call a function that takes its
    //      arguments by value because the function you called can’t
    //      actually see the object you passed it.

    // (-)  Copying an object may be very expensive.

    // (-)  Doesn't work with inheritance/OO.
    //        If I copy an Animal, but it’s really a Gorilla, my copy will only
    //        have Animal fields (and virtual methods may try to reference
    //        non-existent Gorilla fields, crashing my program

    // (-)  Sometimes I may want to modify the caller’s object.

    // (-)  Some objects are not copyable, so we can't pass by value
    //        e.g., cout, abstract types, unique_ptr

    //////////////////////
    // PASS BY REFERENCE
    //////////////////////
    void g(int &x);
    // x refers to the caller’s existing object without creating a new copy
    // Any changes g makes to x also change what the caller sees

    // BENEFITS/DRAWBACKS
    // (-)  It is dangerous to call a function that takes its arguments by
    //      reference because it may unexpectedly modify your object

    // (+)  You can fix this by passing the argument by “const reference”,
    //      which says the function is not allowed to modify it
    //      (e.g., by calling a non-const method on it)

    // (+)  Efficient, since object doesn’t need to be copied

    // (+)  Works with inheritance/OO;
    //      No slicing because I am working with the original object

    // (+)  I can modify the object if desired and appropriate

    // (-)  Managing memory is difficult
    //      If my object has many owners, how do I now when it is 
    //      safe to delete

    //////////////////////
    // PASS BY MOVE
    //////////////////////
    void h(int &&x);
    // If the function is called on a temporary
    // Can reuse parts from abandoned x

    //////////////////////////////////////////////////////////////////
    // BEST PRACTICE:
    // use a const reference "const &" instead of passing by value
    //////////////////////////////////////////////////////////////////

}

void f(int x) {  // pass by value
    x = 3;
    std::cout << "f's x is " << x << std::endl; 
}

void g(int &x) { // pass by reference
    x = 4;
    std::cout << "g's x is " << x << std::endl; 
}

#endif