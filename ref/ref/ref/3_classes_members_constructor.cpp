#ifndef EXCLASS_MEMBERS_CONSTRUCTOR_H
#  define EXCLASS_MEMBERS_CONSTRUCTOR_H

#include<initializer_list>
using std::initializer_list;

struct A {
    A(int i, int j = 0); // #1
    explicit A(int i); // #2
};

struct B {
    B(int i, int j); // #3
    B(initializer_list<int> l); // #4
};

struct A {
    A(int _i = 0) : i{_i} {}  // Alternate     uses the initializer list
    A(int _i = 0) { i = _i; } // Alternate 2   also allowed.
    int i;
};

//////////////////////////////////////////
// “Constructors” for fundamental types
//////////////////////////////////////////
// since fundamental types don’t have constructors, creating one without an
// initializer gives you garbage values
int i; // i could be anything

// Reading uninitialized memory like this is a common source of bugs
// If you explicitly pass it zero constructor arguments, the memory is zero-initialized
int i{}; // i is 0  BETTER

// To make it easier to create objects,
// C++ will automatically generate some constructors for you
// -- DEFAULT CONSTRUCTOR
// -- COPY CONSTRUCTOR
// -- AGGREGATE CONSTRUCTOR
// -- MOVE CONSTRUCTOR

void exCLASS_MEMBERS_CONSTRUCTOR() {
    A a0 = 3; // A(3, 0) #1
    A a1(3); // A(3) #2
    A a1{3}; // A(3) #2. Uniform init: best practice but

    B b0(3, 5); // #3
    B b00 = {1, 2, 3, 4}; // #4
    B b1 = { 3, 5}; // #4
    B b2{3, 5}; // #4 Initializer list is preferred
}

#endif