#ifndef EXCLASSES_INITIALIZER_LIST_H
#  define EXCLASSES_INITIALIZER_LIST_H

// #include<string>
// #include<iostream>
// #include<vector>

//////////////////////
// INITIALIZER_LIST
//////////////////////
// allows variadic number of parameters to be passed into function

#include<initializer_list>
using std::initializer_list;

struct B {
    B(int i, int j); // #3
    B(initializer_list<int> l); // #4
};

void exCLASSES_INITIALIZER_LIST() {    
    B b0(3, 5); // #3
    B b00 = {1, 2, 3, 4}; // #4
    B b1 = { 3, 5}; // #4
    B b2{3, 5}; // #4 Initializer list is preferred
}

#endif