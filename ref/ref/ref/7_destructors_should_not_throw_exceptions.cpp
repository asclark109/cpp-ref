#include <memory>
using std::make_unique;

// What if a destructor throws during exception processing?
// ⚫ Consider the following
struct X { 
    ~X() {
        throw "X";
    }

    void f(int x);
};

int g(){return 0;};

void f1() {
    auto x = make_unique<X>("foo");
    x->f(g());
}

// If g throws an exception, then x’s destructor will call X’s
// destructor, which will throw an exception in the middle of
// processing g’s exception

// This makes no sense, so the language runtime will
// immediately call std::terminate(), abruptly halting your
// program. Oops

//////////////////////////////////////////////////////////
// BEST PRACTICE: DON'T THROW EXCEPTIONS FROM DESTRUCTORS
//////////////////////////////////////////////////////////
// If your destructor calls something that may
// throw, be sure to catch before returning
void g(X2 x);
struct X2 {
    ~X2() {
        try {
            g(*this); // g may throw
        } catch(...) {} // Ignoring may be only option
    }
};

////////////////////////////////////////////////////
// BEST PRACTICE: WRITE EXCEPTION-SAFE INTERFACES
////////////////////////////////////////////////////
// std::stack has two methods instead of one for pop
// for exception safety
// void std::stack::pop()   destroys the top element
// T&   std::stack::top()   returns a reference to top element
#include <stack>
using std::stack;
struct A{};

void exStack(){
    stack<A> stk;
    A a(stk.top()); // Copy the reference we have to top elem
    stk.pop();      // destroy the top item.
}

// bad in multi-threaded environments