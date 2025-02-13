#ifndef EXCLASS_ON_RIGHT_H
#  define EXCLASS_ON_RIGHT_H

// NOTE: const can be put on the left of an expression or the right:
// "const X" and "X const"

// BEST PRACTICE: PUT const ON THE RIGHT OF THE IDENTIFIER

// when declaring pointers and their values as `const`, the order _does_ matter:  
const int* year;         // (1) declares a pointer to a constant variable.... MOVE TO RIGHT!!! AMBIGUOUS! change to "int const * year"
int const * year;        // (2) declares a pointer to a constant variable.  
int* const year;         // (3) declares a const pointer to a non-const variable.  
const int* const year;   // (4) declares a const pointer to a const variable.

// THINK ABOUT WHAT HAPPENS WHEN THE CONST IS ON THE RIGHT (READ RIGHT TO LEFT)
int const * year;        // clearly a non-const ptr to a const     int
int* const year;         // clearly a const     ptr to a non-const int
const int* const year;   // clearly a const     ptr to a const     int
// basically if you put the const to the right of the thing you're trying to const
// it'll always be that the const applies to the thing directly to the left.

int & const x; // x is a const reference to a non-const int...pointless since references can't be unbounded
int const & x; // x is a       reference to a const     int
// const& int x; // illegal
const int & x; // x is a       reference to a const int... MOVE TO RIGHT!!! AMBIGUOUS change to "int const & x"


//////////////////////////////////////
// REFACTOR TO PUT const ON THE RIGHT
//////////////////////////////////////
const int* year; // BAD; change to --> int const * year;

#endif