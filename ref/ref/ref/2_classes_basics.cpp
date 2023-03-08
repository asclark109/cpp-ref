#ifndef EXCLASSES_H
#  define EXCLASSES_H

#include<string>
#include<iostream>
#include<vector>

namespace classes {

// note: you can create type aliases:
using Row = std::vector<int>;
// But what using does is let you give a new name to an
// existing type, so this is useful, but doesn’t create
// genuinely new types

////////////
// CREATE
////////////
class Student_info1 {}; // private fields by default (functions, fields)
struct Student_info2 {}; // public fields by default (functions, fields)

//////////////////////
// MEMBER VISIBILITY
//////////////////////
class A {
    public:         // visible to all
        int pub;
    protected:      // visible to subclasses
        int prot;
    private:        // visible to no one
        int priv;
};

////////////////
// INHERITANCE
////////////////
class B : public A {
    void g() {
        std::cout << pub; // OK
        std::cout << prot; // OK
        // std::cout << priv; // Error
    }
};

////////////////////////////////////
// HEADER, CPP FILE TYPICAL PRACTICES
////////////////////////////////////
// define the interface in a .h file
// define the implementation in a .cpp file

// In .h file
struct Student_info3 {
    std::string name;
    double midterm, final;
    std::vector<double> homework;
    double grade() const;
};

// In .cpp file
double Student_info3::grade() const {
    return (3.2);
};

}

#endif