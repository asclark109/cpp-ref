#ifndef EXTEMPLATES_FUNCTIONS_auto_H
#  define EXTEMPLATES_FUNCTIONS_auto_H

#include <iostream>

//// (C++20)
// Function templates can be achieved in modern C++ with auto keywords
auto square1(auto n) {
    return n*n;
}

//// (PRE C++20)
// Function templates are achieved template, typename, class keywords
template<typename T> // Template headers
T square2(T n) {
    return n*n;
}

void exFunctionTemplatesAuto() {
	auto result1 = square1(2);     // int
	auto result2 = square1(2.2);   // double

	auto result3 = square2(2);     // int
	auto result4 = square2(2.2);   // double
}

#endif