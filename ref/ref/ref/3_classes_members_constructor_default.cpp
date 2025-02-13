
#ifndef EXCLASSES_MEMBERS_CONSTRUCTOR_DEFAULT_H
#  define EXCLASSES_MEMBERS_CONSTRUCTOR_DEFAULT_H

#include<string>
#include<initializer_list>
using std::initializer_list;

//////////////////
// DEFAULT CONSTRUCTOR (implicitly-generated)
//////////////////

// Suppose I don’t declare any constructors for my class
struct S { 
    int i;
    double d;
};
// Will it be impossible to construct an object of type S?
// No!
S s; // Valid C
// That would break compatibility with C and feel punitive

// If you don’t declare any constructors, C++ will create 
// a no-argument constructor for you. 
// Even though the Struct S is defined without a constructor,
// The compiler generates one as if you wrote
struct S {
    S() {}
    int i;
    double d;
};

// What if you don’t want your own default constructor?
// For example, if I default-constructed an S object,
// I would get uninitialized memory
S s; // s.i and s.d are garbage
// One option is to write your own default constructor,
// and the compiler won’t generate one
struct S {
    S() : i(), j(1.2) {}
    int i; int j;
};
S s; // s.i == 0, s.j =- 1.2

// NON-STATIC DATA MEMBER INITIALIZERS (NSDMI)
// you can provide default initializers
// for members and the compiler-generated default
// constructor will do the right thing
struct S {
    int i = 0;
    double j = 1.2;
};
S s; // s.i == 0, s.j = 1.2

// NOTE: For technical reasons, 
// STATIC DATA MEMBERS cannot be initialized in class

// What if you don’t want a default constructor at all
//  -- Our Student_info constructor expected a name
//  -- If the compiler generated a default constructor,
//     you would get invalid nameless students

//     Fortunately, IF YOU DEFINE ANY CONSTRUCTOR,
//     THE COMPILER WON'T GENERATE A DEFAULT CONSTRUCTOR

struct Student_info {
    Student_info(std::string n) : name(n) {}
    std::string name = "Mofei";
    /* ... */
};
Student_info si1("Mike"); // OK
// Student_info si2; // ill-formed! Will not compile

// What if you want a default constructor anyway?
//  -- Suppose we were OK with nameless students
//  -- We could write a default constructor, but the
//     compiler-generated one is really what we
//     wanted, so we just say it has the default
//     definition
struct Student_info2 {
    Student_info2(std::string n) : name(n) {}
    Student_info2() = default; // GIVES YOU DEFAULT CONSTRUCTOR
    std::string name = "Mofei";
    /* ... */
};

#endif