#ifndef EXINLINE_FRIEND_H
#  define EXINLINE_FRIEND_H

#include<iostream>

////////////////////
// OBJECT DURATION
////////////////////

//////////////////////////////
// AUTOMATIC STORAGE DURATION
//////////////////////////////
// Local variables
// Lifetime is the same as the lifetime of the function/method

// RE: if we want our object to outlive the automatic scope?
// -- It might be that we want our dynamic object to be 
//    longer-lived than the unique_ptr that is managing it
// -- Just transfer ownership to another unique_ptr
//    up2 = move(up);
//    This allows us to chain into new scopes while always
//    maintaining an owner of the object. SEE MOVE

//////////////////////////////
// STATIC    STORAGE DURATION
//////////////////////////////
// Global and static variables
// Lifetime is the lifetime of the program

//////////////////////////////
// DYNAMIC   STORAGE DURATION
//////////////////////////////
// Lifetime is explicit
// Created with commands like “make_unique”
// Programmer controls when it ends

// In all cases, the constructor is called when the
// object is created and the destructor is called when
// the object is destroyed

//////////////////////////////
// AUTOMATIC DURATION
//////////////////////////////
struct A {
    A() { std::cout << "A() "; }
    ~A() { std::cout << "~A()"; }
};

struct B {
    B() { std::cout << "B()"; }
    ~B() { std::cout << "~B()"; }
};

void f() {
    A a; // local variables created in order declared
    B b; // local variables deleted in reverse order of creation
}

int main() { 
    f();
    return 0;
}
// Prints A() B() ~B() ~A()

struct A {
    A() { std::cout << " A() "; }
    ~A() { std::cout << " ~A()"; }
};

struct C {
    C() { std::cout << " C()"; }
    ~C() { std::cout << " ~C()"; }
    A a; // Goes away when C does; A destroyed first
};

void f() {
    C c;
} 
// Prints A() C() ~C() ~A()

//////////////////////////////
// STATIC DURATION
//////////////////////////////
// These objects have the same lifetime as the program

// They are created (and their constructors called) when the program starts
// In the order they are declared within a file
// Order is undefined if they are in separately linked files
// Even before main()

// They are destroyed (and their destructors called) when the program ends
// Right after main() returns
int i; // Created at program start
struct A {
    static int j; // Created at program start
    
    void f() {
        static int k{}; // Created first time f() is called.
        // Does not lose its value between calls
    }
};

A a; // Created at program start
static A a2; // Created at program start
             // a2 not visible outside of current translation unit

void g() {
    static A a3; // Created first time g() is called
}

// FUNCTION-STATIC LIFETIMES
// A static variable in a function is initialized the first time the function runs
// -- Even if the function is called from multiple threads, the language
//    is responsible for making sure it gets initialized exactly once.
// -- If the function is never called, the object is never initialized
// -- As usual, static duration objects are destroyed in the reverse order in which
//    they are created

//////////////////////////////
// DYNAMIC DURATION OBJECTS
//////////////////////////////
// These are created and destroyed under the control of the program
// -- Dynamic objects allow you to write programs whose data structures
//    can be determined at runtime based on user input, etc.
// -- As we’ve mentioned, you can control their lifetimes with a unique_ptr

#endif