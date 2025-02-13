#ifndef EXFUNCTION_TEMPLATES_H
#  define EXFUNCTION_TEMPLATES_H

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

// MODERN WAY TO DO FUNCTION TEMPLATE
// a function template is a recipe the compiler uses to generate functions
auto square(auto x) {
    return x*x;
}

int i = square(21); // 441
double d = square(2.1); // 4.41

// FUNCTION TEMPLATES (PRE C++20)
template<typename T>
auto square2(T n) {
    return n*n;
}

void exFUNCTION_TEMPLATES() {

};

#endif

