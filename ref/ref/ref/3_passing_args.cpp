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
    
    // PASS BY VALUE
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

    // PASS BY REFERENCE
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

    // PASS BY MOVE
    void h(int &&x);
    // If the function is called on a temporary
    // Can reuse parts from abandoned x

    // BEST PRACTICE:
    // use a const reference "const &" instead of passing by value

}

void f(int x) {  // pass by value
    x = 3;
    std::cout << "f’s x is " << x << std::endl; 
}

void g(int &x) { // pass by reference
    x = 4;
    std::cout << "g’s x is " << x << std::endl; 
}


void funcLValue(        int i) { std::cout<<"called funcLValue";};
void funcLValueRef(     int & i) { std::cout<<"called funcLValueRef";};
void funcRValueRef(     int && i) { std::cout<<"called funcRValueRef";};
void funcLValueConstRef(int const & i) {  std::cout<<"called funcLValueConstRef";};

void exInvocations(){
    ////////////////////////////
    // FUNC ACCEPTING L VALUE
    ////////////////////////////
    // (1a) passing an L value
    int i{2};
    funcLValue(i); // legal. makes a local copy of the int that i holds in storage (i owns the storage)
    // (1b) passing an L value reference
    int& j = i;
    funcLValue(j); // legal. makes a local copy of the int that j refers to (refers to the int whose storage is managed by i)
    // (1c) passing an R value
    funcLValue(1); // legal. makes a local copy of a temporary expression (Rvalue) "1"

    ////////////////////////////
    // FUNC ACCEPTING L VALUE REFERENCE
    ////////////////////////////
    // (2a) passing an L value
    int i{2};
    funcLValueRef(i); // legal. makes a local reference variable that refers to the original int i in caller scope
    // (2b) passing an L value reference
    int& j = i;
    funcLValueRef(j); // legal. makes a local reference variable that refers to the same underlying int that j was referring to
    // (2c) passing an R value
    // funcLValueRef(1); // ILLEGAL. we can't make a reference variable to something that doesn't have its own storage (i.e. an "Rvalue"/"temporary")?

    ////////////////////////////
    // FUNC ACCEPTING R VALUE REFERENCE
    ////////////////////////////
    // (3a) passing an L value
    int i{2};
    // funcRValueRef(i); // ILLEGAL. function only knows how to work with objects it can "raid for parts"
    // (3b) passing an L value reference
    int& j = i;
    // funcRValueRef(j); // ILLEGAL. function only knows how to work with objects it can "raid for parts"
    // (3c) passing an R value
    funcRValueRef(1);       // legal. 1 is a temporary / R value
    funcRValueRef(std::move(i)); // legal. using move gives us a temporary / R value reference...signals we are allowing i to be raided for parts...function accepts things it can raid for parts. makes more sense if i is an object.

    ////////////////////////////////////////////////
    // FUNC ACCEPTING REFERENCE TO A CONST L VALUE
    ////////////////////////////////////////////////
    // (4a) passing an L value
    int i{2};
    funcLValueConstRef(i); // legal. same as (2a). working with a reference to an int it wont change
    // (4b) passing an L value reference
    int& j = i;
    funcLValueConstRef(j); // legal. same as (2b). working with a reference to an int it wont change
    // (4c) passing an R value
    funcLValueConstRef(1); // LEGAL. weird case. since the function works with a reference to an int that it won't modify
                           // then hypothetically it means the function could work with a temporary since it has no intension
                           // of modifying the temporary, which would require that the temporary have its own storage, which it doesn't
}

#endif