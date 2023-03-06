#ifndef EXCLASSES_VIRTUAL_H
#  define EXCLASSES_VIRTUAL_H

#include<string>
#include<iostream>
#include<vector>
#include<memory>


// VIRTUAL METHOD:      uses the dynamic type
// NON-VIRTUAL METHOD:  uses the static type

struct Animal {
    void f() { std::cout << "animal f"; }
    virtual void g() { std::cout << "animal g"; }
};

struct Gorilla : public Animal{
    void f() { std::cout << "gorilla f"; }
    void g() { std::cout << "gorilla g"; }
    void h() { std::cout << "gorilla h"; }
};

struct Falcon : public Animal{
    void f() { std::cout << "falcon f"; }
    void g() { std::cout << "falcon g"; }
    void h() { std::cout << "falcon h"; }
};

struct Abstract_student_info { // In header
    std::string name;
    double midterm, final;
    std::vector<double> homework;

    // istream& read(istream&); // Don’t define grading strategy here
    
    virtual double grade() const = 0; // PURE VIRTUAL FUNCTION; no implementation
};

void exCLASSES_VIRTUAL() {
    // if using a reference to a super class
    // calling its virtual functions will call the subclass method
    // whereas calling a non-virtual function will call that base class's function
    std::unique_ptr<Gorilla> g = std::make_unique<Gorilla>();
    Animal &a = *g;
    a.f(); // Not virtual: Animal’s f
    a.g(); // Virtual: Gorilla’s g
    // a.h(); // Error: h is not in animal
    (*g).f(); (*g).g(); (*g).h(); // Gorilla’s f, g, and h

    // BETTER DEREFERENCING NOTATION ->
    g->f(); g->g(); g->h(); // Gorilla’s f, g, and h

    // can also have pointer to reference
    std::unique_ptr<Animal> g = std::make_unique<Gorilla>();

    // Since the compiler doesn’t know what the type is at compile-time, a
    // virtual function is called through a reference to a table of functions
    // that is stored in the object

    // For a non-virtual method, the compiler knows what method will be
    // called and calls it directly

    // In general, this only adds a couple of clock cycles, so the cost of
    // making a function virtual is usually negligible

    // The main performance cost of virtual functions is:
    // (1) the loss of inlining
    // (2) the loss of function level optimization
    // The more virtual functions you use, the less the compiler can understand
    // your code to optimize it

    // BEST PRACTICES

    // Usually it is fine to make methods virtual, the
    // performance cost is "almost always" minimal and the
    // availability of runtime dispatch is powerful in object-oriented code

    // But don't use virtual functions gratuitously if you are not
    // using object-orientation, especially in performance critical or low
    // level code

    // Virtual functions can impede compiler code optimization and
    // unpredictably modify memory layout
}

#endif