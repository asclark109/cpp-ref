#ifndef EXRULE_OF_THREE_H
#  define EXRULE_OF_THREE_H

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>


void exRULE_OF_THREE() {

    // Even if you don't write them, the compiler automatically generates a

    //////////////////////
    // Copy constructor
    //////////////////////
    struct X { X(X const &); /* ... */ };
    // X x2(x1);
    
    //////////////////////
    // Copy assignment operator
    //////////////////////
    struct X { X &operator=(X const &); /* ... */ };
    // x2 = x1;

    //////////////////////
    // Destructor
    //////////////////////
    struct X { ~X(); /* ... */ };

    // Although the compiler generates those
    // The built-in ones often aren't what you want
    // -  This typically occurs when you need special copying behavior
    //    like a deep copy Which usually means you need to do a deep
    //    copy-assignment And a deep destruction

    //////////////////////
    // RULE OF THREE
    //////////////////////
    // If your class defines any of the following
    // -- A copy constructor
    // -- A copy assignment operator
    // -- A destructor
    // You should consider whether you need to define all three

    //////////////////////
    // Rule of the Big Two
    //////////////////////
    // If you use RAII then those objects will auto manage the lifetime of
    // the object it manages, so we do not need a destructor.
    // We didn't need to redefine the destructor because unique_ptrs do
    // all the work
    // The rule of the Big Two says you don't need to worry about the
    // destructor if the member. destructors clean everything up

    //////////////////////
    // BASE CLASSES SHOULD HAVE VIRTUAL DESTRUCTORS
    //////////////////////
    // If you have a class that is designed to be inherited from
    // ⚫ Make sure its destructor is virtual
    // ⚫ Since it might get destroyed by a unique_ptr to the base type
    struct Animal {
        /* ... */
        virtual ~Animal() = default;
    };
};

#endif

