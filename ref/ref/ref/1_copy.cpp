#ifndef EXCOPY_H
#  define EXCOPY_H

#include<string>
#include<iostream>
#include<vector>

void exCopy() {
	// beware of copying objects
	// if a deep copy is needed of an object, the class will have its 
	// own implementation of the copy, copy-assignment constructor

	// to copy a collection of objects potentially needing a deep copy,
	// you can use std::copy (ultimate in abstraction)

	// it can copy from anything to anything else (anything from memory
	// to containers to the	console) and even does deep copies

	// vector to array
	std::vector<char> v;
	char arr[10];
	std::copy(v.begin(), v.end(), arr);

	// The compiler uses a mechanism called TEMPLATE programming to
	// automatically generate the most efficient code at compile - time,
	// so if a block - move memory would do the trick, the compiler will
	// simply generate the same memcpy as C
	
	// This results in an 800 % performance improvement in such cases.
	// Since copying objects is very common, this is not an unimportant
	// optimization
}

#endif