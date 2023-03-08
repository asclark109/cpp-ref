#ifndef EXCLASSES_MEMBERS_CONSTRUCTOR_AGGREGATE_H
#  define EXCLASSES_MEMBERS_CONSTRUCTOR_AGGREGATE_H

#include<string>
#include<initializer_list>
using std::initializer_list;

////////////////////////////////////
// AGGREGATE CONSTRUCTOR (Implicit)
////////////////////////////////////

struct S { 
    int i;
    double d;
};

// If a class is like a simple data structure with public members,
// C++ considers that to be an aggregate and generates a
// constructor that takes initializer
struct S2 {
    S2(int const &i, double const &d) : i(i), d(d) {} 

    int i;
    double d;
};

S s = {1, 2.3}; // OK
S s2 = {.i =1, .d = 5.2 }; // OK. Designated initializer

// This is a little bit of an oversimplification as a constructor
// is not actually synthesized here for highly technical reasons,
// but “close enough for jazz.”

#endif