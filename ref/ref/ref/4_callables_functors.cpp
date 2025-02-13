#ifndef EXCALLABLES_FUNCTORS_H
#  define EXCALLABLES_FUNCTORS_H

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

// If you write your own class with an overloaded operator(), it’s called a functor
// This allows you to create stateful objects that can be called like functions
struct Accumulator {
    int operator()(int j) {
        i = i + j;
        return i;
    };
    int i = 0;
};
Accumulator acc;


// lambdas are often implemented as functors

void exCALLABLES_FUNCTORS() {
    std::cout << acc(1); // Prints 1
    std::cout << acc(2); // Prints 3 = 1+2
    std::cout << acc(4); // Prints 7 = 1+2+4
}


#endif