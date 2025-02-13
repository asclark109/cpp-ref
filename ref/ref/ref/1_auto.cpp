#ifndef EXAUTO_FUNCS_H
#  define EXAUTO_FUNCS_H

#include <iostream>

int square(int n) {
	return n * n;
}

auto square(double n) {
	// OK to have two functions with
	// same name (overloading) as long
	// as compiler can tell which you
	// mean by context
	return n * n;
}

// The type "auto" means the compiler should perform type inferencing
void exPreprocessor() {
	auto result1 = square(2);
	auto result2 = square(2.2);
}

#endif