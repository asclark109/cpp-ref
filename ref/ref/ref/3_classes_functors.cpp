
#ifndef EXFUNCTORS_H
#  define EXFUNCTORS_H

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iterator>

//////////////////////////////
// FUNCTORS
//////////////////////////////
// a Functor is a class that has overloaded the operator paren
// "operator()"
// This allows you to create stateful objects that can be 
// called like functions

// EXAMPLE
struct Nth_Power
{
    Nth_Power(double _y) : y(_y) {}
    double y;

    double operator()(double x) const
    {
        return pow(x,y);
    }
};

void exFUNCTORS() {
    std::vector<int> v = { 1, 2, 3, 4, 5 };
    Nth_Power cube{ 3 };
    std::cout << cube(7) << std::endl; // prints 343
    // print first five cubes
    std::transform(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, ", "), cube);
}

// EXAMPLE
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