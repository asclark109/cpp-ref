#ifndef EXFUNCTION_TEMPLATES_WITH_CONCEPTS_H
#  define EXFUNCTION_TEMPLATES_WITH_CONCEPTS_H

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

// OO and Templates can solve similar problems
// consider OO
struct Animal {
    virtual std::string name() = 0;
    virtual std::string eats() = 0;
};

class Cat : public Animal {
    std::string name() override { return "cat"; }
    std::string eats() override { return "delicious mice"; }
};

void exOO(){
    std::unique_ptr<Animal> a = std::make_unique<Cat>();
    std::cout << "A " << a->name() << " eats " << a->eats();
}

// Do not need OO!
// 
struct Cat2 {
    std::string eats() { return "delicious mice"; }
    std::string name() { return "cat";}
};

void exNaiveTemplate(){
    auto a = Cat2(); // can use auto! but we lost interface :(
    std::cout << "A " << a.name() << " eats " << a.eats();

    // We lost the understanding that a is an animal

    // a could have the type House or int and we
    // might not find out that something went wrong
    // until much later when we did something that
    // depends on a being an animal

    // What we need is a way to codify our
    // expectations for a without all of the overhead
    // and complexity of creating a base class
}

//////////////
// CONCEPTS
//////////////
// Concepts play the analogous role for generic
// programming that base classes do in object oriented
// programming

// A concept explains what operations a type supports
template<typename T>
concept Animal2 = requires(T a) {
    { a.eats() } -> std::convertible_to<std::string>;
    { a.name() } -> std::convertible_to<std::string>;
};

void exTemplateWConcept(){
    // With the above concept defined, we can
    // specify that a must satisfy the Animal
    // concept, and the compiler will not let us
    // initialize it with a non-Animal type like House
    // or int
    Animal2 auto a = Cat2();
    std::cout << "A " << a.name() << " eats " << a.eats();
}

void exFUNCTION_TEMPLATES_WITH_CONCEPTS() {
    std::unique_ptr<Animal> a = std::make_unique<Cat>();
    std::cout << "A " << a->name() << " eats " << a->eats();
};

#endif

