<<<<<<< HEAD
//////////////////////////////////////////
// Best practices around default members
//////////////////////////////////////////
// If you do nothing, the compiler will define the following for you implicitly

// Default constructor (0-args) default constructs all bases and members

// Copy constructor copies all bases and members
// Copy assignment copies assigns all bases and members
// Destructor destroys all bases and members
// Move constructor moves all bases and members
// Move assignment move assigns all bases and members

// (0) classes should NOT have virtual constructors

// (1) classes to be inherited from should have VIRTUAL DESTRUCTOR

// (2) consider whether you need a special copy: e.g. deep copy like btree

// (3) RULE OF THREE
//     if you define any of
//     -- copy constructor
//     -- copy assignment constructor
//     -- destructor
//     then define them all
//     btree b2(b1);   // should deep copy
//     b3 = b2;        // should deep copy

// (4) RULE OF FIVE
//     if you define copy constructor, then move constructors are not created by compiler
//     --if the compiler thinks that if "copying every member" isn't the right way to copy
//       then it is unsafe to assume that "move every member" is the right way to move
//     --not terrible if you don't have move constructor because then you just copy instead
//     IF YOU USE RULE OF FIVE, THINK HARD ABOUT WHETHER YOU SHOULD DEFINE
//     (a) move constructors
//     (b) move assignment operator

// (5) guard against multiple inclusion
// if the same header is included multiple times by files, 
// you may get multiply-defined symbol errors.
// This preprocessor idiom prevents that:
#ifndef FOO_H
# define FOO_H
/* ... code ... */
#endif

// (6) ALWAYS PUT HEADERS IN A NAME SPACE
#ifndef MYHEADER_H
# define MYHEADER_H
namespace mpcs51044 {
    int f();
    /* ... */
}
#endif

// (7) NEVER "use" A NAMESPACE IN A HEADER
// this leaks the entire namespace to any file that includes the header
#include<iostream>
// using namespace std; // DONT DO THIS!!!
// REMEDY: "using std::_____;"
using std::cout; // BETTER! gives you the best of both words
// NOTE: in .cpp file you can do whatever you want because that'll be hidden from others

// (8) PREFER THE C++ VERSIONS OF THE STANDARD C HEADER
#include <stdio.h> // BAD
#include <cstdio>  // BETTER
// -- C versions will sort-of work, but the C++
// versions will more properly define signatures,
// so overload resolution, type-checking, etc.
// will be more robust
// -- If you have a C header with no C++-specific
// version (e.g., unistd.h), then of course use
// the C version

// (8) UNDERSTAND VIRTUAL VS NON-VIRTUAL (WILL BE ON TEST)

// (8a) consider adding static_assert to give useful error
// messages with templates. Also use concepts in your templates

// (8b) BEST PRACTICE: LABEL DESTRUCTORS ALMOST ALWAYS AS NO EXCEPT
// whether you say so or not, your class destructors are implicitly noexcept

// (8c) BEST PRACTICE: If your class’ move and copy constructors are
// noexcept, be sure to declare them that way.
// -- will pay off every time you put them in a container
// -- Passing by value will likely be safer and more efficient as well
// Vector will check if the object has a noexcept move constructor; 
// if not, it will copy. thats why you should label move constructor no except

// (9) PREFER C++ STYLE CASTS TO C STYLE CASTS
// struct A{};
// A* a = (A*)&b;                // BETTER!
// A* a = dynamic_cast<A*>(&b)   // SAFER!
// dynamic_cast type conversion for runtime type casting
// static_cast type conversion for compile time type casting
// C++ casts are more descriptive when they fail.

// (10) PUT CONST AND VOLATILE AFTER TYPE NAMES

// (11) USE CONST APPROPRIATELY:
//      (a) const methods should be const
//      (b) const & (const reference) arguments should be const
//      (c) PUT CONST AFTER THE TYPE
// declaring arguments e.g (int const &) allows them to accept temporaries
// also, declaring e.g. (int const &) is good b/c no copy needs to be made

// (11a) IF A FUNCTION OR EXPRESSION CAN BE EVALUATED AT COMPILE TIME,
//       LABEL IT CONSTEXPR

// (12) USE nullptr INSTEAD OF 0 OR NULL TO INDICATE NULL POINTER
//      -- why? if you use 0 for a pointer it messes with function overloading
// void f(char *) { /* … */ };
// void f(int) { /* … */ };
// f(0); // OK. Calls f(int)
// f(nullptr); // OK. Calls f(char *)
// prefer the type-correct nullptr over the typeincorrect 0 or NULL
// to avoid calling the wrong function/method.

// (13) DEFINE SYMMETRIC BINARY OPERATORS AS GLOBAL FUNCTIONS
// dont use the member for of operator+()
// because both arguments should be treated the same
// DEFINE operator+=() AS A MEMBER
// We don’t want to += to try to assign to a compilergenerated temporary

// (14) WATCH OUT FOR TYPES INFERRED BY TEMPLATES!!!
// double dp[] = { 0.1, 0.2, 0.3 };
// cout << accumulate(dp, dp + 3, 0);    // PRINTS 0 !!!
// TEMPLATE ASSUMED USING INT TYPE RATHER THAN DOUBLE
// WHEN YOU WANTED DOUBLE. this causes accumulation of ints instead of doubles

// (15) BEWARE OF DEPENDENT BASE CLASSES
// you might expect looking at the template class C that f() will invoke
// the global f(). but since it sub class of a base class T, T might give
// struct C new methods, like f(). you can avoid this problem by referencing
// the class or namespace specifically
//  ::f() for the global's f
// T::f() for base class T's f

// #include <iostream>
// using namespace std;
// int f() { return 0; }    // IS GLOBAL F CALLED? 

// template<class T>
// struct C : public T {
//     C() { cout << f() << endl; }
// };

// struct A {
//     int f() { return 1; }  // IS STRUCT A'S F CALLED? 
// };

// int main() {
//     C<A> c;
// }

// template<class T>
// struct C : public T {
// C() { cout << T::f() << endl; }
// };
// ⚫ Alternatively
// template<class T>
// struct C : public T {
// using T::f;
// C() { cout << f() << endl; }
// };
// ⚫ Another choice
// template<class T>
// struct C : public T {
// C() { cout << this->f() << endl; }
// };
// ⚫ If you want the global symbol:
// template<class T>
// struct C : public T {
// C() { cout << ::f() << endl; }
// };

// (16) WATCH OUT FOR METHOD HIDING (USE override AND final)
// using override, final will indicate intent and catch method hiding errors
// override == signals that you are overriding a method in super class. (compiler flags error if doesn't exist)
// final    == designates a virtual functions that cannot be overridden in a derived class
struct Base {
    virtual void func() = 0;
    virtual void mispelledFunc() = 0;
};
struct Derived : public Base {
    virtual void func() override final {}
    // This will give a useful error
    // because we aren’t actually
    // overriding
    // virtual void misspelledFunc() override {}
};
struct MostDerived : public Derived {
    // // Error! Can’t override final
    // virtual void func() { /*...*/}
};

// (17) THROW EXCEPTIONS BY VALUE, CATCH THEM BY const &
// #include <exception>
// #include <string>
// using std::exception;
// using std::string;
// struct MyException : public exception {
//     MyException(string s): myS("My "+s), exception(s) {};
    
//     virtual char const * override what() {
//         return myS.c_str();
//     }

//     string myS;
// };
// void f() {
//     try {
//         throw MyException("foo"); // throw by value.
//     } catch (exception e) { // Bad!
//     //} catch (exception const &e) { // Better
//         cout << e.what(); // May crash due to slicing
//     }
// }

// (18) NEVER HAVE A DESTURCTOR THROW AN EXCEPTION. SHOULD BE noexcept
// include try catch if necessary
// Does the following catch “In A” or “in f”?
// struct A {
//      ~A() { throw runtime_error("In A"); }
// };
// void f() {
//      try {
//          A a;
//          throw runtime_error("in f");
//      } catch (exception const &) {
//      }
// }
// No good answer, so the runtime just calls std::terminate to end your program

// (19) IF A BASE CLASS IT TO BE INHERITED, MAKE ITS DESTRUCTOR VIRTUAL!!
// if you have a reference or pointer to your base class, and the destructor is not virtual
// then if it is a reference or pointer to a sub class, then it will only end up invoking
// the destructor of the base class, and not the subclass! bad!
// class A {
// public:
//      virtual ~A() = default;
// };
// class B : public A {
// public:
//      ~B() { ... }
// };
// A *ap = new B;
// delete ap; // Doesn’t call B’s destuctor

// (20) DONT USE MACROS. PREFER TEMPLATES
// BAD:
// #define bad_min(x, y) x<y? x: y;
// int i = 3;
// bad_min(5, i++); // increments i twice!
// 2*bad_min(3, 5); // Returns 5!
// Even figuring out why they fail is tricky.
// If we had used a function template, we
// wouldn't even have needed to worry

// (21) DON'T MAKE TRICKY ASSUMPTIONS ABOUT ORDER OF EVALUATION
// struct S {
//     S(int i) : a(i), b(i++) {
//         f(i,i++) // Undefined behavior
//     }
//     int b;
//     int a;
// };

// (22) REMEMBER. PRIMITIVE TYPES HAVE TRIVIAL CONSTRUCTORS AND HOLD GARBAGE
// VALUES UNLESS INITIALIZED.
void f1(){
    int i;   // bad! if try to access this, it will have garbage
    int i{}; // better!
}

// (23) DON'T RETURN A REFERENCE/POINTER TO A LOCAL VARIABLE
int & f2() {
    int i = 3;
    return i; // Bad!
}

// (24) BEST PRACTICE: PREFER RANGE MEMBER FUNCTIONS TO THEIR SINGLE-ELEMENT COUNTERPARTS
// Given two vectors, v1 and v2, what’s easiest way to make 
// v1’s contents be the same as the second half of v2’s?
// BASIC (BAD): iterate in for-loop
// vector<Widget> v1, v2
// ...
// for(vector<Widget>::const_iterator ci = v2.begin() + v2.size()/2; ci != v2.end(); ++ci) {
//      v1.push_back(*ci);
// }
// BETTER!:
//      copy(v2.begin() + v2.size()/2, v2.end(), back_inserter(v1));
// BETTER!!
//      v1.resize(v2.size() - v2.size()/2);
//      copy(v2.begin() + v2.size()/2, v2.end(), v1.begin());
// BETTER!!
//      v1.insert(v1.end(),v2.begin() + v2.size()/2,v2.end());

// (25) BEST PRACTICE: PREFER empty() TO size()==0
// if you have a massive linked list, it'll be O(n). but the empty() is O(1)

// (26) ALWAYS USE SMART POINTER TO MANAGE THE LIFETIME OF AN OBJECT
// Foo *fp = new Foo; // Bad
// // stuff
// delete fp; // May be missed if exception occurred
// (+) CLEANER CODE (no destructor logic)
// (+) SAFER (exceptions)
// GENERALLY, USE RAII
// auto ap = make_unique<Foo>(); // BEST
// auto ap = make_shared<Foo>(); // BEST

///// MULTI-THREADING /////

// (27) USE RAII TO MANAGE LOCKS
// use a scoped locking class whose destructor releases
// the lock to make sure locks get released even
// when exceptions bypass normal control flow
// TYPICALLY, use the std::scoped_lock class, like we do in the false sharing example
// std::lock_guard if you need to lock exactly 1 mutex for an entire scope.
// std::scoped_lock if you need to lock a number of mutexes that is not exactly 1.
// std::unique_lock if you need to unlock within the scope of the block (which includes use with a condition_variable).

// (28) (A) AVOID DEADLOCKS BY DEFINING A LOCK ORDERING, AND DOCUMENT IT
//      (B) USE std::scoped_lock TO ACQUIRE MULTIPLE LOCKS. WILL ALWAYS GET MULTIPLE LOCKS WITHOUT DEADLOCKING

// (29) MEMORY MODEL BEST PRACTICES
//      (A) AVOID SHARING DATA BETWEEN THREADS EXCEPT WHEN NECESSARY
//      (B) IF SHARING DATA B/W THREADS, ALWAYS USE LOCKS OR ATOMICS TO ENSURE THREADS HAVE COHERENT VIEW OF DATA

// (30) MAKE MUTEX MEMBERS mutable. THIS ALLOWS YOU TO DECLARE METHODS LOGICALLY CONST
//      (so you can communicate a method is const outside of the mutex changing state)

// (31) PREFER "using typename = int" OVER "typedef int typename;"
//      typedef does not work with templates!!! but "using" does!!!
#include <map>
#include <string>
#include <variant>
using std::map;
using std::string;
using std::variant;

using ConfigVariables = map < string, variant<string *, bool *, double *>>; // BETTER!!! WORKS WITH TEMPLATES
typedef map < string, variant<string *, bool *, double *>> ConfigVariables; // WORSE!!!

// (31) CONSTRAIN YOUR TEMPLATES
// if templates just have typename parameters,
// your user will not be protected from using incorrect types for template arguments. they will get
// (a) incomprehensible error messages (solve this with "static_assert"..or concepts)
// (b) worse: silently incorrect answers
#include <concepts>
using std::integral;
using std::enable_if_t;
using std::is_integral_v;
template<typename T>
T gcd(T a, T b) {
    return (b == 0) ? a : gcd(b, a - b*(a/b));
}
// REMEDY: (    C++20) SOLVE WITH CONCEPTS (BUT NEEDS C++20)
template<integral T>
T gcd(T a, T b) {
    return (b == 0) ? a : gcd(b, a - b*(a/b));
}
// REMEDY: (PRE-C++20) SOLVE WITH SFINAE
template<typename T, typename = enable_if_t<is_integral_v<T>>>
T gcd(T a, T b) {
    return (b == 0) ? a : gcd(b, a - b*(a/b));
}


// (32) FUNCTIONS THAT TAKE IN TEXT (E.G. string const &) SHOULD USE string_view INSTEAD
#include <string_view>
using std::string_view;
int f(string_view const s);
string str("foo");
auto a = f(str) + f("bar") + f("baz"); // No copying!

// (33) sometimes when you work with complex types, you can confuse the compiler
// int f(double d); // Declares function double -> int
// int f(double (d)); // Also function double -> int
// Foo f(istream_iterator<int>(datafile)); // Oops! Function istream_iterator<int> -> Foo
// int f(double(*p)()); // function double(*)()->int
// int f(double p()); // Also function double(*)()->int
// // Can always omit parameter name
// int f(double()); // Again function double(*)()->int
// Foo f(istream_iterator<int>());
// // Oops. Function istream_iterator(*)() -> Foo
// USE UNIFORM INITIALIZATION with "{}"...

// (34) NAMESPACE VERSIONING
// good way to version APIs
// this way you can code to say you are using v1 functions and interfaces
// also want to be able to say "I always want to be on the latest version"
// MyLib.h
namespace mpcs51044 {
    namespace v1 {
        int f() { // Original way of calculating f 
        }
    }

    namespace v2 {
        int f() { // Modern efficient way 
        }
    }

    using namespace v2; // Make v2 the default
}
// // MyMissionCriticalProgram.cpp
// #include "MyLib.h"
// auto x = mpcs51044::v1::f();
// // MyYoloProgram.cpp
// #include "MyLib.h"
// auto x = mpcs51044::f(); // Latest version

// (35) NUMBER 1 RULE OF OPTIMIZATION: DON'T

=======
//////////////////////////////////////////
// Best practices around default members
//////////////////////////////////////////
// If you do nothing, the compiler will define the following for you implicitly

// Default constructor (0-args) default constructs all bases and members

// Copy constructor copies all bases and members
// Copy assignment copies assigns all bases and members
// Destructor destroys all bases and members
// Move constructor moves all bases and members
// Move assignment move assigns all bases and members

// (0) classes should NOT have virtual constructors

// (1) classes to be inherited from should have VIRTUAL DESTRUCTOR

// (2) consider whether you need a special copy: e.g. deep copy like btree

// (3) RULE OF THREE
//     if you define any of
//     -- copy constructor
//     -- copy assignment constructor
//     -- destructor
//     then define them all
//     btree b2(b1);   // should deep copy
//     b3 = b2;        // should deep copy

// (3a) RULE OF TWO
//     if using all RAII objects, then destructor is not needed because all fields
//     exhibit automatic lifetime duration.

// (4) RULE OF FIVE
//     if you define copy constructor, then move constructors are not created by compiler
//     --if the compiler thinks that if "copying every member" isn't the right way to copy
//       then it is unsafe to assume that "move every member" is the right way to move
//     --not terrible if you don't have move constructor because then you just copy instead
//     IF YOU USE RULE OF FIVE, THINK HARD ABOUT WHETHER YOU SHOULD DEFINE
//     (a) move constructors
//     (b) move assignment operator

// (5) guard against multiple inclusion
// if the same header is included multiple times by files, 
// you may get multiply-defined symbol errors.
// This preprocessor idiom prevents that:
#ifndef FOO_H
# define FOO_H
/* ... code ... */
#endif

// (6) ALWAYS PUT HEADERS IN A NAME SPACE
#ifndef MYHEADER_H
# define MYHEADER_H
namespace mpcs51044 {
    int f();
    /* ... */
}
#endif

// (7) NEVER "use" A NAMESPACE IN A HEADER
// this leaks the entire namespace to any file that includes the header
#include<iostream>
// using namespace std; // DONT DO THIS!!!
// REMEDY: "using std::_____;"
using std::cout; // BETTER! gives you the best of both words
// NOTE: in .cpp file you can do whatever you want because that'll be hidden from others

// (8) PREFER THE C++ VERSIONS OF THE STANDARD C HEADER
#include <stdio.h> // BAD
#include <cstdio>  // BETTER (prepend c, include .h instead)
// -- C versions will sort-of work, but the C++
// versions will more properly define signatures,
// so overload resolution, type-checking, etc.
// will be more robust
// -- If you have a C header with no C++-specific
// version (e.g., unistd.h), then of course use
// the C version

// (8) UNDERSTAND VIRTUAL VS NON-VIRTUAL (WILL BE ON TEST)

// (8a) consider adding static_assert to give useful error
// messages with templates. Also use concepts in your templates

// (8b) BEST PRACTICE: LABEL DESTRUCTORS ALMOST ALWAYS AS NO EXCEPT
// whether you say so or not, your class destructors are implicitly noexcept

// (8c) BEST PRACTICE: If your class’ move and copy constructors are
// noexcept, be sure to declare them that way.
// -- will pay off every time you put them in a container
// -- Passing by value will likely be safer and more efficient as well
// Vector will check if the object has a noexcept move constructor; 
// if not, it will copy. thats why you should label move constructor no except

// (9) PREFER C++ STYLE CASTS TO C STYLE CASTS
// struct A{};
// A* a = (A*)&b;                // BETTER!
// A* a = dynamic_cast<A*>(&b)   // SAFER!
// dynamic_cast type conversion for runtime type casting
// static_cast type conversion for compile time type casting
// C++ casts are more descriptive when they fail.

// (10) PUT CONST AND VOLATILE AFTER TYPE NAMES (put on the right!)

// (11) USE CONST APPROPRIATELY:
//      (a) const methods should be const
//      (b) const & (const reference) arguments should be const
//      (c) PUT CONST AFTER THE TYPE
// declaring arguments e.g (int const &) allows them to accept temporaries
// also, declaring e.g. (int const &) is good b/c no copy needs to be made

// (11a) IF A FUNCTION OR EXPRESSION CAN BE EVALUATED AT COMPILE TIME,
//       LABEL IT CONSTEXPR

// (12) USE nullptr INSTEAD OF 0 OR NULL TO INDICATE NULL POINTER
//      -- why? if you use 0 for a pointer it messes with function overloading
// void f(char *) { /* … */ };
// void f(int) { /* … */ };
// f(0); // OK. Calls f(int)
// f(nullptr); // OK. Calls f(char *)
// prefer the type-correct nullptr over the typeincorrect 0 or NULL
// to avoid calling the wrong function/method.

// (13) DEFINE SYMMETRIC BINARY OPERATORS AS GLOBAL FUNCTIONS
// dont use the member for of operator+()
// because both arguments should be treated the same
// DEFINE operator+=() AS A MEMBER
// We don’t want to += to try to assign to a compilergenerated temporary

// (14) WATCH OUT FOR TYPES INFERRED BY TEMPLATES!!!
// double dp[] = { 0.1, 0.2, 0.3 };
// cout << accumulate(dp, dp + 3, 0);    // PRINTS 0 !!!
// TEMPLATE ASSUMED USING INT TYPE RATHER THAN DOUBLE
// WHEN YOU WANTED DOUBLE. this causes accumulation of ints instead of doubles

// (15) BEWARE OF DEPENDENT BASE CLASSES
// you might expect looking at the template class C that f() will invoke
// the global f(). but since it sub class of a base class T, T might give
// struct C new methods, like f(). you can avoid this problem by referencing
// the class or namespace specifically
//  ::f() for the global's f
// T::f() for base class T's f

// #include <iostream>
// using namespace std;
// int f() { return 0; }    // IS GLOBAL F CALLED? 

// template<class T>
// struct C : public T {
//     C() { cout << f() << endl; }
// };

// struct A {
//     int f() { return 1; }  // IS STRUCT A'S F CALLED? 
// };

// int main() {
//     C<A> c;
// }

// template<class T>
// struct C : public T {
// C() { cout << T::f() << endl; }
// };
// ⚫ Alternatively
// template<class T>
// struct C : public T {
// using T::f;
// C() { cout << f() << endl; }
// };
// ⚫ Another choice
// template<class T>
// struct C : public T {
// C() { cout << this->f() << endl; }
// };
// ⚫ If you want the global symbol:
// template<class T>
// struct C : public T {
// C() { cout << ::f() << endl; }
// };

// (16) WATCH OUT FOR METHOD HIDING (USE override AND final)
// using override, final will indicate intent and catch method hiding errors
// override == signals that you are overriding a method in super class. (compiler flags error if doesn't exist)
// final    == designates a virtual functions that cannot be overridden in a derived class
struct Base {
    virtual void func() = 0;
    virtual void mispelledFunc() = 0;
};
struct Derived : public Base {
    virtual void func() override final {}
    // This will give a useful error
    // because we aren’t actually
    // overriding
    // virtual void misspelledFunc() override {}
};
struct MostDerived : public Derived {
    // // Error! Can’t override final
    // virtual void func() { /*...*/}
};

// (17) THROW EXCEPTIONS BY VALUE, CATCH THEM BY const &
// #include <exception>
// #include <string>
// using std::exception;
// using std::string;
// struct MyException : public exception {
//     MyException(string s): myS("My "+s), exception(s) {};
    
//     virtual char const * override what() {
//         return myS.c_str();
//     }

//     string myS;
// };
// void f() {
//     try {
//         throw MyException("foo"); // throw by value.
//     } catch (exception e) { // Bad!
//     //} catch (exception const &e) { // Better
//         cout << e.what(); // May crash due to slicing
//     }
// }

// (18) NEVER HAVE A DESTURCTOR THROW AN EXCEPTION. SHOULD BE noexcept
// include try catch if necessary
// Does the following catch “In A” or “in f”?
// struct A {
//      ~A() { throw runtime_error("In A"); }
// };
// void f() {
//      try {
//          A a;
//          throw runtime_error("in f");
//      } catch (exception const &) {
//      }
// }
// No good answer, so the runtime just calls std::terminate to end your program

// (19) IF A BASE CLASS IT TO BE INHERITED, MAKE ITS DESTRUCTOR VIRTUAL!!
// if you have a reference or pointer to your base class, and the destructor is not virtual
// then if it is a reference or pointer to a sub class, then it will only end up invoking
// the destructor of the base class, and not the subclass! bad!
// class A {
// public:
//      virtual ~A() = default;
// };
// class B : public A {
// public:
//      ~B() { ... }
// };
// A *ap = new B;
// delete ap; // Doesn’t call B’s destuctor

// (20) DONT USE MACROS. PREFER TEMPLATES
// BAD:
// #define bad_min(x, y) x<y? x: y;
// int i = 3;
// bad_min(5, i++); // increments i twice!
// 2*bad_min(3, 5); // Returns 5!
// Even figuring out why they fail is tricky.
// If we had used a function template, we
// wouldn't even have needed to worry

// (21) DON'T MAKE TRICKY ASSUMPTIONS ABOUT ORDER OF EVALUATION
// struct S {
//     S(int i) : a(i), b(i++) {
//         f(i,i++) // Undefined behavior
//     }
//     int b;
//     int a;
// };

// (22) REMEMBER. PRIMITIVE TYPES HAVE TRIVIAL CONSTRUCTORS AND HOLD GARBAGE
// VALUES UNLESS INITIALIZED.
void f1(){
    int i;   // bad! if try to access this, it will have garbage
    int i{}; // better!
}

// (23) DON'T RETURN A REFERENCE/POINTER TO A LOCAL VARIABLE
int & f2() {
    int i = 3;
    return i; // Bad!
}

// (24) BEST PRACTICE: PREFER RANGE MEMBER FUNCTIONS TO THEIR SINGLE-ELEMENT COUNTERPARTS
// Given two vectors, v1 and v2, what’s easiest way to make 
// v1’s contents be the same as the second half of v2’s?
// BASIC (BAD): iterate in for-loop
// vector<Widget> v1, v2
// ...
// for(vector<Widget>::const_iterator ci = v2.begin() + v2.size()/2; ci != v2.end(); ++ci) {
//      v1.push_back(*ci);
// }
// BETTER!:
//      copy(v2.begin() + v2.size()/2, v2.end(), back_inserter(v1));
// BETTER!!
//      v1.resize(v2.size() - v2.size()/2);
//      copy(v2.begin() + v2.size()/2, v2.end(), v1.begin());
// BETTER!!
//      v1.insert(v1.end(),v2.begin() + v2.size()/2,v2.end());

// (25) BEST PRACTICE: PREFER empty() TO size()==0
// if you have a massive linked list, it'll be O(n). but the empty() is O(1)

// (26) ALWAYS USE SMART POINTER TO MANAGE THE LIFETIME OF AN OBJECT
// Foo *fp = new Foo; // Bad
// // stuff
// delete fp; // May be missed if exception occurred
// (+) CLEANER CODE (no destructor logic)
// (+) SAFER (exceptions)
// GENERALLY, USE RAII
// auto ap = make_unique<Foo>(); // BEST
// auto ap = make_shared<Foo>(); // BEST

///// MULTI-THREADING /////

// (27) USE RAII TO MANAGE LOCKS
// use a scoped locking class whose destructor releases
// the lock to make sure locks get released even
// when exceptions bypass normal control flow
// TYPICALLY, use the std::scoped_lock class, like we do in the false sharing example
// std::lock_guard if you need to lock exactly 1 mutex for an entire scope.
// std::scoped_lock if you need to lock a number of mutexes that is not exactly 1.
// std::unique_lock if you need to unlock within the scope of the block (which includes use with a condition_variable).

// (28) (A) AVOID DEADLOCKS BY DEFINING A LOCK ORDERING, AND DOCUMENT IT
//      (B) USE std::scoped_lock TO ACQUIRE MULTIPLE LOCKS. WILL ALWAYS GET MULTIPLE LOCKS WITHOUT DEADLOCKING

// (29) MEMORY MODEL BEST PRACTICES
//      (A) AVOID SHARING DATA BETWEEN THREADS EXCEPT WHEN NECESSARY
//      (B) IF SHARING DATA B/W THREADS, ALWAYS USE LOCKS OR ATOMICS TO ENSURE THREADS HAVE COHERENT VIEW OF DATA

// (30) MAKE MUTEX MEMBERS mutable. THIS ALLOWS YOU TO DECLARE METHODS LOGICALLY CONST
//      (so you can communicate a method is const outside of the mutex changing state)

// (31) PREFER "using typename = int" OVER "typedef int typename;"
//      typedef does not work with templates!!! but "using" does!!!
#include <map>
#include <string>
#include <variant>
using std::map;
using std::string;
using std::variant;

using ConfigVariables = map < string, variant<string *, bool *, double *>>; // BETTER!!! WORKS WITH TEMPLATES
typedef map < string, variant<string *, bool *, double *>> ConfigVariables; // WORSE!!!

// (31) CONSTRAIN YOUR TEMPLATES
// if templates just have typename parameters,
// your user will not be protected from using incorrect types for template arguments. they will get
// (a) incomprehensible error messages (solve this with "static_assert"..or concepts)
// (b) worse: silently incorrect answers
#include <concepts>
using std::integral;
using std::enable_if_t;
using std::is_integral_v;
template<typename T>
T gcd(T a, T b) {
    return (b == 0) ? a : gcd(b, a - b*(a/b));
}
// REMEDY: (    C++20) SOLVE WITH CONCEPTS (BUT NEEDS C++20)
template<integral T>
T gcd(T a, T b) {
    return (b == 0) ? a : gcd(b, a - b*(a/b));
}
// REMEDY: (PRE-C++20) SOLVE WITH SFINAE
template<typename T, typename = enable_if_t<is_integral_v<T>>>
T gcd(T a, T b) {
    return (b == 0) ? a : gcd(b, a - b*(a/b));
}


// (32) FUNCTIONS THAT TAKE IN TEXT (E.G. string const &) SHOULD USE string_view INSTEAD
#include <string_view>
using std::string_view;
int f(string_view const s);
string str("foo");
auto a = f(str) + f("bar") + f("baz"); // No copying!

// (33) sometimes when you work with complex types, you can confuse the compiler
// int f(double d); // Declares function double -> int
// int f(double (d)); // Also function double -> int
// Foo f(istream_iterator<int>(datafile)); // Oops! Function istream_iterator<int> -> Foo
// int f(double(*p)()); // function double(*)()->int
// int f(double p()); // Also function double(*)()->int
// // Can always omit parameter name
// int f(double()); // Again function double(*)()->int
// Foo f(istream_iterator<int>());
// // Oops. Function istream_iterator(*)() -> Foo
// USE UNIFORM INITIALIZATION with "{}"...

// (34) NAMESPACE VERSIONING
// good way to version APIs
// this way you can code to say you are using v1 functions and interfaces
// also want to be able to say "I always want to be on the latest version"
// MyLib.h
namespace mpcs51044 {
    namespace v1 {
        int f() { // Original way of calculating f 
        }
    }

    namespace v2 {
        int f() { // Modern efficient way 
        }
    }

    using namespace v2; // Make v2 the default
}
// // MyMissionCriticalProgram.cpp
// #include "MyLib.h"
// auto x = mpcs51044::v1::f();
// // MyYoloProgram.cpp
// #include "MyLib.h"
// auto x = mpcs51044::f(); // Latest version

// (35) NUMBER 1 RULE OF OPTIMIZATION: DON'T

>>>>>>> daaac18b9a6fa6ae774efaf9b921fe69fc86d677
