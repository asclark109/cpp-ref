////////////////
// TYPE ERASURE
////////////////
//  One would often like to use templates to work with different types
//  But your use case needs actual classes rather than templates
//  We've already discussed wanting a fixed type to put in a vector

//  Type erasure allows you to store a variety of types in a (non-template) class 

//////////////////////
//  EXAMPLE: std::any
//////////////////////
//           Uses type erasure to store anything at any time
//           Use any_cast to get the value out
//           bad_any_cast exception if you try to take out a different type
#include <iostream>
#include <string>
using std::cout;
using std::string;

#include <any>
using std::any;
using std::any_cast;

void exAny() {
    any a = 7;
    cout << any_cast<int>(a);
    // a = "foo"s;
    a = string("foo");
    cout << any_cast<string>(a);
}

////////////////////////////
//  EXAMPLE: std::function
////////////////////////////
// std::function<int(double)> can contain any
// callable (function, functor, lambda,…) that accepts a double and returns an int
// it uses type erasure to do so.


//////////////////////////////////
// HOW TO IMPLEMENT TYPE ERASURE
//////////////////////////////////
// (1) The class
// (2) The concept
// (3) The model

// (1) CLASS: This is the non-template class you want to be able to hold various types
// Typically it does have a constructor template or a template assignment operator to let you
// store various types in it
struct Erased {
    template<typename T>  // UNIVERSAL? CONSTRUCTOR
    Erased(T&&);

    template<typename T>  // UNIVERSAL? ASSIGNMENT CONSTRUCTOR
    Erased& operator=(T&&);

    // ...
};

// (2) CONCEPT:
// You might not want to store arbitrary types.
// The concept explains what interface you want to support.
// Similar (but not identical) to C++20 concepts
// Declare a nested Concept class with a pure virtual interface

struct Erased { // (A) CLASS
    template<typename T> 
    Erased(T&&);

    template<typename T>
    Erased& operator=(T&&);

    struct Concept { // (B) CONCEPT
        virtual void foo() = 0; 
    };

    // ... 
};

// (3) MODEL
// Class template that stores the actual object (of unknown type)
// and delegates calls
struct Erased { // (A) CLASS
    template<typename T> 
    Erased(T&&);

    template<typename T>
    Erased& operator=(T&&);

    struct Concept { // (B) CONCEPT
        virtual void foo() = 0; 
    };

    template<typename T>
    struct Model : Concept { // (C) MODEL
        Model(T&& val) : val(val) {}  // constructor
        void foo() override { val.foo(); } // delegate calls to data
        T val;  // data
    };
};

// (4) add methods to store and access the type-erased field
#include <memory>
using std::unique_ptr;

struct Erased { 
    template<typename T> 
    Erased(T&& t) : val(make_unique<Model<T>>(t)) {}; // accept the value in constructor

    template<typename T>
    Erased& operator=(T&& t) {val = make_unique<Model<T>>(t)}; // accept the value in constructor

    struct Concept { 
        virtual void foo() = 0; 
    };

    template<typename T>
    struct Model : Concept { 
        Model(T&& val) : val(val) {}
        void foo() override { val.foo(); }
        T val;
    };

    void foo() { val->foo(); } // delegates calls to type erased field
    unique_ptr<Concept> val;   // Erased object holds a pointer to the concept
};

// EXAMPLE USAGE
struct A {void foo();};
struct B {void foo();};

void exTypeErasure() {
    Erased typeErasedObj1{A{}};
    typeErasedObj1.foo();
    Erased typeErasedObj2{B{}};
    typeErasedObj2.foo();
    // This works even though A::foo and B::foo are
    // not virtual (the virtualness is in the Model and the Concept)
}