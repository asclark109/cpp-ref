#ifndef EXCLASSES_H
#  define EXCLASSES_H

#include<string>
#include<iostream>
#include<vector>

void exCLASSES() {
    // CREATE your own type

    // note: you can create type aliases:
    using Row = std::vector<int>;
    // But what using does is let you give a new name to an
    // existing type, so this is useful, but doesn’t create
    // genuinely new types

    // CREATE CLASS, STRUCT
    class Student_info1 {}; // private fields by default (functions, fields)
    struct Student_info2 {}; // public fields by default (functions, fields)
    
    // VISIBILITY OF MEMBERS
    class A {
        void f() {
            std::cout << pub; // OK
            std::cout << prot; // OK
            std::cout << priv; // OK
        }
    public: // visible to all
        int pub;
    protected: // visible to subclasses
        int prot;
    private: // visible to no one
        int priv;
    };

    class B : public A {
        void g() {
            std::cout << pub; // OK
            std::cout << prot; // OK
            // std::cout << priv; // Error
        }
    };

    // void h(A a) {
    //     std::cout << a.pub; // OK
    //     // std::cout << a.prot; // Error
    //     // std::cout << a.priv; // Error
    // };
    // #endif


    // DEFINING METHODS OUTSIDE CLASS
    // can declare some or all of the implementation for a class separately
    // typical to have a .h file with the declaration of classes,structs and their fields, methods
    // but put their implementation in a separate cpp file under the same file name

    // In .h file
    struct Student_info3 {
        std::string name;
        double midterm, final;
        std::vector<double> homework;
        double grade() const;
    };
    
    // // In .cpp file
    // double Student_info3::grade() const {
    //     return (3.2);
    // };

    

}

#endif