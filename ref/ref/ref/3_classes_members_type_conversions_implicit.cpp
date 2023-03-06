#ifndef EXCLASS_MEMBERS_TYPE_CONVERSIONS_IMPLICIT_H
#  define EXCLASS_MEMBERS_TYPE_CONVERSIONS_IMPLICIT_H

#include <memory>
#include <string>

// note: the `explicit` keyword prevents creation of a type conversion operation

//// IMPLICIT TYPE CONVERSIONS

//////////////////
// BUILT-IN TYPE CONVERSION
//////////////////
int i = 780;
long l = i;
char c = 7;
char c = i; // No warning, but dangerous!

//////////////////
// POLYMORPHISM TYPE CONVERSION
//////////////////
// std::unique_ptr<Animal> ap = std::make_unique<Dog>("Champ");
// void f(Dog &dr) { Animal &ar = dr; }

//////////////////
// USER-DEFINED CONSTRUCTORS
//////////////////
struct A {
    A();
    A(int i); // Creates a type conversion;
    A(int i, std::string s);
    explicit A(double d); // explicit keyword! Does not create a conversion
                          // A(3.3) must be called to explicitly invoke this
                          // A a = 3.3 will actually lead to implicit type conversion
                          // and A(int i) will be used
};

// A a;
// A a0(1, "foo");
// A aa = { 1, "foo"};
// A a1(7); // Calls A(int)
// a1 = 77;// ok
// A a3(5.4); // Calls A(double)
// a3 = 5.5; // Calls A(int)!    implicit type conversion to int.

//////////////////
// OPERATOR OVERLOADING
//////////////////

struct seven {
    operator int() {
        return 7;
    }
};
struct A { 
    A(int);
};

int i = seven();
A a = 7;
// A a = seven(); // Ill-formed, two user-defined
// conversions will not be implicitly composed
// (type conversion leading to int, and then
//  int converted to A)


#endif