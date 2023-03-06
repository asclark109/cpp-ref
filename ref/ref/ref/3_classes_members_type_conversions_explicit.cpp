#ifndef EXCLASS_MEMBERS_TYPE_CONVERSIONS_EXPLICIT_H
#  define EXCLASS_MEMBERS_TYPE_CONVERSIONS_EXPLICIT_H

#include <memory>
#include <string>
#include <iostream>

// OLD C-STYLE CASTS (Legal but bad!)
// char *cp f(void *vp) { return (char *)vp; }

//// TEMPLATE CASTING OPERATORS

// STATIC_CAST (static_cast<T>)
// Like C casts, but only makes conversions that are always valid. 
// E.g, convert one integral type to another (truncation may still occur).

// DYNAMIC_CAST (dynamic_cast<T&>)
// Casts between reference types. Can even cast a Base& to a Derived& but
// only does the cast if the target object really is a Derived&.

// Only works when the base class has a vtable (because the compiler adds a
// secret virtual function that keeps track of the real run-time type of the object).

// If the object is not really a T &, dynamic_cast<T&> throws std::bad_cast;

// REINTERPRET_CAST (reinterpret_cast<T*>)
// Does a bitwise reinterpretation between any two pointer types, even for
// unrelated types. Never changes the raw address stored in the pointer. Also
// can convert between integral and pointer types.

// CONST_CAST (const_cast<T>)
// Can change constness or volatileness only. 
// There are usually better alternatives

void exCLASS_MEMBERS_TYPE_CONVERSIONS_EXPLICIT(){
    float f = 3.5;

    //////////////////
    // STATIC CAST: may still lead to truncation but more safe than c-style cast
    //////////////////
    int b = static_cast<int>(f);
    // It is a compile time cast. It does things like implicit conversions 
    // between types (such as int to float, or pointer to void*), and it can
    // also call explicit conversion functions (or implicit ones)
    int a = 10;
    char c = 'a';
    int* q = (int*)&c;  // this will pass at compile time but may fail at runtime
    // int* p = static_cast<int*>(&c); // [Error] invalid static_cast from type 'char*' to type 'int*'
    // see? static_cast is safer than c-style cast

    // static_cast works on objects of custom classes by using the type conversion
    // operators defined in the class

    //////////////////
    // DYNAMIC CAST
    //////////////////
    // dynamic casting is mainly used for safe downcasting at run time.
    // To work on dynamic_cast there must be one virtual function in the
    // base class. A dynamic_cast works only polymorphic base class because
    // it uses this information to decide safe downcasting.
    // Base class declaration
    class Base {
        void print()
        {
            std::cout << "Base" << std::endl;
        }
    };
    
    // Derived Class 1 declaration
    class Derived1 : public Base {
        void print()
        {
            std::cout << "Derived1" << std::endl;
        }
    };

    // create subclass
    Derived1 d1;

    // Base class pointer hold Derived1 class object
    // goes from raw Derived pointer to Base pointer
    // (DONT USE RAW POINTERS) but it at least does the check
    Base* bp = dynamic_cast<Base*>(&d1); // holds nullptr if fails
    if (bp == nullptr)
        std::cout << "null" << std::endl;

    //////////////////
    // REINTERPRET_CAST
    //////////////////
    int* p = new int(65);
    char* ch = reinterpret_cast<char*>(p);
    // reinterpret_cast is a very special and dangerous type of
    // casting operator. And is suggested to use it using proper
    // data type i.e., (pointer data type should be same as original data type).
    // It can typecast any pointer to any other data type.
    // It is used when we want to work with bits.

    //////////////////
    // CONST_CAST
    //////////////////
    // const_cast is used to cast away the constness of variables. 
    // Following are some interesting facts about const_cast.
    https://www.geeksforgeeks.org/const_cast-in-c-type-casting-operators/
    // --const_cast can be used to change non-const class members inside a const member function.
    // --const_cast can be used to pass const data to a function that doesn’t receive const. 
    int val = 10;
    const int *ptr = &val;
    int *ptr1 = const_cast <int *>(ptr);
    fun(ptr1);
}

int fun(int* ptr) {
    *ptr = *ptr + 10;
    return (*ptr);
};
#endif