// Create and extend classes with duck-typed variants
// ⚫ Supports runtime dispatch
// ⚫ Can work with values instead of unique_ptrs
// ⚫ (Usually) efficient
// ⚫ Clunky notation
#include<variant>
#include<string>
#include<iostream>
using namespace std;
template<class... Ts> 
struct overloaded : Ts... { using Ts::operator()...; }; 

struct Cat {
    string name() { return "Cat"; }
    string eats() { return "Mice"; }
};

struct Dog {
    string name() { return "Dog"; }
    string eats() { return "Cats"; }
};

using Animal = variant<Cat, Dog>;

overloaded lifeSpan {[](Cat &) { return 12; },
                     [](Dog &) { return 10; } };

int main()
{
    Animal a = Cat();
    cout << visit([](auto &x) { return x.name(); }, a) << endl;;
    cout << visit(lifeSpan, a);
}
