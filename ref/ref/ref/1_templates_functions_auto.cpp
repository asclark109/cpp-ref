#ifndef EXTEMPLATES_FUNCTIONS_auto_H
#  define EXTEMPLATES_FUNCTIONS_auto_H

#include <iostream>

// Function templates can be achieved in modern C++ with auto keywords
auto square(auto n) {
    return n*n;
}

void exFunctionTemplatesAuto() {

	std::cout << square(2) + square(3.1416);
	/*

	*/
}

#endif