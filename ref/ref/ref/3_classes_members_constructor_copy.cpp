
#ifndef EXCLASSES_MEMBERS_CONSTRUCTOR_COPY_H
#  define EXCLASSES_MEMBERS_CONSTRUCTOR_COPY_H

#include<string>

//////////////////
// COPY CONSTRUCTOR (Implicitly-generated)
//////////////////

struct S { 
    int i;
    double d;
};

// COPY CONSTRUCTOR is invoked when copying an existing object
S s;
S s2 = s; // copy-assignment constructor invoked!

// The compiler implicitly generates a copy
// constructor that copies all of the base classes
// and members (in the order described last week), as if you wrote
struct S2 {
    S2(S const &s) : i(s.i), d(s.d) {}
    
    int i{}; 
    double d = 1.2;
};

// While convenient, the compiler-generated copy constructor
// is not always correct. For example, suppose you have a binary
//  tree class. The compiler-generated copy constructor would only
// copy the root, leaving us with tangled trees. you need to implement your own
struct BinaryTree {
    BinaryTree(BinaryTree const &b) { /* ... */ }
    /* ... */
};

// What if I don’t want a copy constructor at all?
// One important design pattern is the “Singleton Pattern” that
// represents a class that only ever has one object
// For example, you may want to guarantee that all of your
// program uses the same Logger

// DELETE COPY CONSTRUCTOR
struct Logger {
    Logger(Logger const &) = delete;  // copy constructor deleted!
    static Logger myLogger;
private:
    Logger() { /* ... */; }
    /* ... */
};

#endif