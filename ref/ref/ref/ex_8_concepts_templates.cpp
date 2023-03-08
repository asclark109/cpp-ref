// Create and extend classes with templates

// ⚫ Compile-time dispatch
// ⚫ Can work with values instead of unique_ptrs
// ⚫ Efficient
// ⚫ Great open-closed support
// ⚫ But cannot be used when runtime dispatch is needed
// ⚫ E.g., if the user chooses an animal type
// ⚫ Or containers that need fixed types
// ⚫ using Zoo = vector<???>;

// Concept version like normal programming
#include<string>
#include<type_traits>
#include<iostream>

using namespace std;

template<typename T>
concept Animal = requires(T a) {
    { a.eats() } -> convertible_to<string>;
    { a.name() } -> convertible_to<string>;
};

struct Cat {
    string eats() { return "mice"; }
    string name() { return "cat";}
};

struct Dog {
    string eats() { return "cats"; }
    string name() { return "dog";}
};

int lifespan(Cat const &) { return 12; }
int lifespan(Dog const &) { return 10; }
int main() {
    Animal auto a = Cat();
    cout << "A " << a.name() << " eats " << a.eats();
    cout << " and lives " << lifespan(a) << " years";
}