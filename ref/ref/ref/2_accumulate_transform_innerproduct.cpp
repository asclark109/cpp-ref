#ifndef EXACCUMULATE_COPY_TRANSFORM_INNERPRODUCT_H
#  define EXACCUMULATE_COPY_TRANSFORM_INNERPRODUCT_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>

double square(double x) {
	return pow(x, 2);
}

void exACCUMULATE_COPY_TRANSFORM_INNERPRODUCT() {
    double nums[] = { 1.0, 2.0, 4.5, 3.0, 5.0 };
	std::vector<double> vNums; 
	std::vector<double> vSqrdNums;
	
	// (1) put doubles into a vector
	for (double num : nums)
		vNums.push_back(num);
	
	// (2) apply std::transform
	vSqrdNums.resize(vNums.size()); // create space to copy elems into vSqrd
	std::transform(vNums.begin(), vNums.end(), vSqrdNums.begin(), square);

	// (3) use accumulate, then sqrt to calc dist from origin
	auto sqrdDist = std::accumulate(vSqrdNums.begin(), vSqrdNums.end(), 0.0);
	auto dist = sqrt(sqrdDist);

    // (2) use inner_product and sqrt to find euclidean distance in one line
	auto dist = sqrt(std::inner_product(vNums.begin(), vNums.end(), vNums.begin(), 0.0));

	/*
    When the program creates the variable i at
    runtime, it allocates some memory (usually on the stack) to hold i’s data
    
    Any expressions in the code involving i will use the data there
    */

    // COPYING and ASSIGNMENT
    // In C++, when we do an assignment, the object is copied
    int i = 3; 
    int j = i;  // copied!
    i = 5;
    // j == 3, i == 5
    /*
    In this example, both i and j have their own storage
    associated with them in the running program
    */

    // REFERENCES
    int i = 3;
    int &j = i;  // creates a reference!
    i = 5;
    // j == 5, i == 5

    /*
    The only difference between references and values
    is that the value has its own copy of the data, and
    the reference reuses the object it is initialized with
    as its storage without making a copy

    i is a variable of type int and has its own storage

    j is of type int& (“int reference”), and does not have any
    new storage associated with it. It just treats i’s storage as
    its own
    */

    // WARNING ABOUT REFERENCES
    /* 
    If multiple ACCUMULATE_COPY_TRANSFORM_INNERPRODUCT are referring to the same
    object, you have to be careful that the object
    still exists when you use it
    */
    int &j = f(); // f returns a reference to f’s i,
    // so the int& j also uses that as its storage
    // However, the storage for f’s i is released when
    // f is done running, so j has bound itself to a
    // no longer existing object!
    
}

int &f() { // f is a function returning an int&
    int i = 3;
    return i;
}




#endif