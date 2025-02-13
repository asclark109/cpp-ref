#include <concepts>
using std::floating_point;

////////////////////////////////////
// CLASS TEMPLATES (WITH CONCEPTS)
////////////////////////////////////
template<floating_point T> // Good design. using a concept to constrain
struct complex; 

// Concepts play the analogous role for generic
// programming that base classes do in object oriented
// programming

//////////////////
// CONCEPTS
//////////////////
// A concept explains what operations a type supports
using std::convertible_to;
#include <string>
using std::string;

////////////////////
// CREATE CONCEPT
////////////////////
template<typename T>
concept Animal2 = requires(T a) {
    { a.eats() } -> convertible_to<string>;
    { a.name() } -> convertible_to<string>;
};

void exConcept(){
    // With the above concept defined, we can
    // specify that a must satisfy the Animal
    // concept, and the compiler will not let us
    // initialize it with a non-Animal type like House
    // or int

    //////////////////
    // USING CONCEPT
    //////////////////
    Animal2 auto a = Cat2();

    // std::cout << "A " << a.name() << " eats " << a.eats();
}

////////////////////////////////////////////////////
// TEMPLATES + CONCEPTS CAN BE USED INSTEAD OF OO
////////////////////////////////////////////////////
// OO and Templates can solve similar problems
#include <memory>
using std::unique_ptr;
using std::make_unique;
#include <iostream>
using std::cout;


////////////////////////////
// EXAMPLE: OO
struct Animal { 
    virtual std::string name() = 0;               // pure virtual functions
    virtual std::string eats() = 0;
};

class Cat : public Animal {
    std::string name() override { return "cat"; } // implement functions
    std::string eats() override { return "delicious mice"; }
};

void exOO(){
    unique_ptr<Animal> a = make_unique<Cat>();    // static type: Animal; dynamic type: Cat
    // cout << "A " << a->name() << " eats " << a->eats();
}

// EXAMPLE: using auto (works but not great)
struct Cat2 {
    std::string eats() { return "delicious mice"; }
    std::string name() { return "cat";}
};

void exNaiveTemplate(){
    auto a = Cat2(); // can use auto! but we lost interface :(
    std::cout << "A " << a.name() << " eats " << a.eats();

    // BUT We lost the understanding that a is an animal

    // a could have the type House or int and we
    // might not find out that something went wrong
    // until much later when we did something that
    // depends on a being an animal

    // What we need is a way to codify our
    // expectations for a without all of the overhead
    // and complexity of creating a base class
}

// EXAMPLE: using concept with auto (GREAT)
void exTemplateWConcept(){
    // With the above concept defined, we can
    // specify that a must satisfy the Animal2
    // concept, and the compiler will not let us
    // initialize it with a non-Animal type like House
    // or int
    Animal2 auto a = Cat2();
    // cout << "A " << a.name() << " eats " << a.eats();
}

// DRAWBACK: can't store concepts in containers e.g. can't 
// have vector<Animal2> since Animal2 is a concept not type