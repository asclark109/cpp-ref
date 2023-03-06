#ifndef EXCALLABLES_LAMBDAS_H
#  define EXCALLABLES_LAMBDAS_H

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

auto f() {
    int i{3};
    auto lambda = [=](){ std::cout << i;}; // lambda has a copy of i
    return lambda;
}

class Person{
public:
    int hand;
};

struct CardDeck{   
    int draw( ){
        return 1;
    };
};

void exCALLABLES_LAMBDAS() {

    // Even if the original i has gone away, you can still run lambda
    f()(); // prints 3 even though original i no longer exists

    ////////////////
    // LAMBDAS
    ////////////////
    [](int x)->int { 
        return x*x;
    };

    // If your lambda does not contain return statements that return
    // different types, the compiler can usually figure out the return type
    // without your saying anything
    [](int x, int y) {
        int z = x + y; return z + x;
    };
    
    // If needed, you can explicitly specify the return
    // type with the following notation
    [](int x, int y) -> int {
        int z = x + y; return z + x;
    };

    ////////////////
    // CAPTURE LISTS
    ////////////////
    // To capture local variables by reference, use [&]
    // To capture local variables by value, use [=]
    // https://en.cppreference.com/w/cpp/language/lambda

    ////////////////
    // 'mutable' keyword
    ////////////////
    // C++ annoyingly makes const copies, so they may be hard to modify.
    // You can turn this off with the keyword mutable as follows
    int i{3};
    auto lambda = [=]() mutable { 
        std::cout << i++;
    }; // lambda has a copy of i
    // Note: Only modifies lambda’s i, not the original variable

    // While lambdas act a lot like functions, they
    // may not actually be functions
    int i = 7;
    auto x = [&i](int j) { return i*j; };
    std::cout << x(5);
    // x isn’t really a function because it doesn’t just
    // depend on its argument j, it also depends on
    // the captured reference to i.

    // They are implemented as functors
    struct X {
        X(int &i) : i(i) {} // Captures i
        int operator()(int j) {
            return i*j;
        }
        int &i;
    };

    ////////////////
    // POLYMORPHIC LAMBDAS
    ////////////////
    // Lambdas can take auto parameters and inference them
    [](auto x) { return x*x; }(7); // 49
    [](auto x) { return x*x; }(7.5); // 56.25
    // How does this work? Again, the type of the above lambda is a class
    // with an overloaded operator()
    // struct polymorphicSquare {
    //     auto operator()(auto x) { return x*x; }
    // };

    ////////////////
    // USING LAMBDAS IN ALGORITHMS
    ////////////////
    std::vector<int> someVec;
    int total = 0;
    std::for_each(someVec.begin(), someVec.end(),[&](int x) { total += x; });

    // Let’s say we wanted to print the number of even members of a vector
    
    // With a for loop
    std::vector v = {2, 5, 6, 9};
    size_t evenCount = 0;
    for(int i: v)
        if(i % 2 == 0) evenCount++;
    std::cout << evenCount;
    
    // With an algorithm
    std::vector v = {2, 5, 6, 9};
    // std::cout << v.count_if([](int i) { return i%2 == 0; });

    //Captures can be helpful too
    // for loop to draw a hand of cards for each player
    CardDeck d;
    std::vector<Person> players;
    for(auto p: players) {
        p.hand = d.draw();
    }
    // With algorithm
    CardDeck d;
    std::vector<Person> players;
    // std::for_each(players, [&](auto p) {p.hand = d.draw(); } 
};

#endif

