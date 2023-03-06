#ifndef EXCLASS_MEMBERS_STATIC_H
#  define EXCLASS_MEMBERS_STATIC_H

#include<string>
#include<iostream>
#include<vector>

// fields, methods are members of classes. there's more

//////////////////
// STATIC CLASS MEMBERS
//////////////////
// class member to be shared by all objects of a class

// INITIALIZING static class members
// Warning: For technical reasons, you may have to 
// initialize static data members with class types in 
// a separate .cpp file. This is so its memory is only
// allocated once, not every time the header is included

// in A.h:
//    struct A { static B ab; };
// in A.cpp:
//    B A::ab("xyz");

struct CountedObject {
    CountedObject() { 
        objectCount++;
    }

    ~CountedObject() { 
        objectCount--;
    }

    static size_t objectCount; // STATIC MEMBER
};

//////////////////
// STATIC METHODS
//////////////////

struct CountedObject2 {
    CountedObject2() { objectCount++; }
    ~CountedObject2() { objectCount--; }

    static size_t memUsed() { // STATIC METHOD
        return objectCount * sizeof(CountedObject);
    }

    static size_t objectCount;
};


void exCLASS_MEMBERS_STATIC() {
    // USING STATIC FIELD
    CountedObject c1, c2;
    CountedObject::objectCount; // access static field
    std::cout << CountedObject::objectCount; // 2

    // USING STATIC METHOD
    CountedObject2 c1, c2;
    CountedObject2::memUsed(); // invoke static method
}

#endif