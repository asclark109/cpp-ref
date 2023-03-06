#ifndef EXTEMPLATES_FUNCTIONS_TEMPLATE_H
#  define EXTEMPLATES_FUNCTIONS_TEMPLATE_H

#include <iostream>

// PRE C++20
// Function templates are achieved template, typename, class keywords
// Template headers
template<typename T>
T square(T n) {
    return n*n;
}

void exFunctionTemplatesOld() {

	std::cout << square(2) + square(3.1416);
	/*

	*/
}


#endif