//////////////////
// "OO" DESIGN
//////////////////
// C++ offers many ways to address the sort of problems covered by OO design
// Not all of these are considered "OO" techniques
// TEMPLATES AND OO CAN SOLVE SIMILAR PROBLEMS

////////////////////////////////////////////////////////
// USING TEMPLATES INSTEAD OF INHERITANCE AND VIRTUALS
////////////////////////////////////////////////////////
// OO and templates can be used for many of the same problems

// EXAMPLE: OO
#include <string>
#include <memory>
#include <iostream>
using std::string;
using std::unique_ptr;
using std::make_unique;
using std::cout;
using std::endl;

struct Animal {
    virtual string name() = 0; // pure virtual function
    virtual string eats() = 0;
};

class Cat : public Animal {
    string name() override { return "cat"; }
    string eats() override { return "delicious mice"; }
};

// More animals...
int main() {
    unique_ptr<Animal> a = make_unique<Cat>();
    cout << "A " << a->name() << " eats " << a->eats();
}

////////////////////////////////////////////////////////
// USE CONCEPTS AND TEMPLATES TO ACHIEVE POLYMORHPISM
////////////////////////////////////////////////////////
// Concepts play the analogous role for generic
// programming that base classes do in object oriented
// programming

// A concept explains what operations a type supports
// The following concept encapsulates the same info as the base class
#include <concepts>
using std::convertible_to;

template<typename T>
concept Animal = requires(T a) {
    { a.eats() } -> convertible_to<string>;
    { a.name() } -> convertible_to<string>;
};

struct Cat2 {
    string eats() { return "delicious mice"; }
    string name() { return "cat";}
};

void exConceptAndTemplate() {
    // Animal auto a = Cat2();
    // cout << "A " << a.name() << " eats " << a.eats();
}

// PERFORMANCE IS BETTER
// ⚫ Objects created on stack
// ⚫ No virtual dispatch
// ⚫ No inheritance
// MAKES IT EASIER TO ADAPT CLASSES TO OUR CODE WITHOUT RISKING "SPAGHETTI INHERITANCE"
// ⚫ On the other hand, it weakens type safety
// ⚫ Pacman is not an animal but eats and has a name
// ⚫ No runtime polymorphism
// ⚫ The following is legal if Animal is a class but not if it is a concept (Why?)
// set<unique_ptr<Animal>> zoo;

// EXAMPLE: C-STYLE MUTEXES
struct mutex {
    void lock();
    void unlock();
};

template<typename T>
struct lock_guard {
    lock_guard(T &m) : m(m) { m.lock(); }
    ~lock_guard() { m.unlock(); }
    T &m;
};

//////////////////////////////////////
// CLASS TEMPLATE ARGUMENT DEDUCTION
//////////////////////////////////////
// ⚫ Note the following line depended on C++17 CTAD
// lock_guard lk(m);
// ⚫ CTAD infers the template arguments for
//    lock_guard<mutex> from the constructor similarly to how
//    Function Template Argument Deduction infers the
//    template arguments for function templates
// ⚫ CTAD can often be useful in this way when using
// templates instead of virtuals. E.g., if tp1 and tp2 are of
// type time_point<C, duration<R>>
// ⚫ duration d = tp1 - tp2; // duration<R>

// there is usually a choice between base classes/virtuals
// and templates/concepts