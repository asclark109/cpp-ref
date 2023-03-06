#ifndef EXCLASSES_CONSTRUCTORS_H
#  define EXCLASSES_CONSTRUCTORS_H

#include<string>
#include<iostream>
#include<vector>
#include<memory>

// ORDER OF CONSTRUCTION FOR CLASS
// Virtual base classes are always first (Even if not immediate)
// (1) base class constructors are run in the order they are declared
// (2) member constructors are run in the order of declaration

// BEST PRACTICE: don’t use virtual functions in constructors

// What is A(2).f()?
class A {
public:
    A(int i) : y(i++), x(i++) {}
    int x, y; // x declared first so created first

    int f() { return x*y*y; }
};
// Answer: 18! 
// (x is initialized first, because it was declared first.
// Order in constructor initializer list doesn’t matter)

void exCLASSES_CONSTRUCTORS() {
    
}

#endif