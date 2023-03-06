
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
// a Functor is a class that has overloaded the operator parent 
// "operator ()"

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

#endif