////////////////////////////////////////////////
// BEST PRACTICE:
// Because it is ugly and not well-known, only
// prefer variant-based polymorphism over virtuals
// or templates when there is a clear benefit
// "In practice, I use it a lot, but less than I do virtual functions or templates"
////////////////////////////////////////////////

//////////////////////
// DYNAMIC DISPATCH
//////////////////////
// ⚫ While C++ templates have always been duck typed,
// templates are used for compile-time dispatch
// ⚫ By contrast, OO is used for dynamic dispatch
// ⚫ Because duck typing is flexible and forgiving while
// remaining statically typesafe, people have asked
// whether we could use dynamically-dispatched duck
// typing as an alternative to inheritance

////////////////////////////////////////////
// Using Duck-Typed Variants in place of OO
////////////////////////////////////////////
// Instead of inheriting from an abstract Animal base class
// we could ahve an Animal variant
#include <variant>
using std::variant;

struct Cat { int getAge(); };
struct Dog { int getAge(); };
using Animal = variant<Cat, Dog>;

// how to simulate virtual functions and call the right name()
// method for the type it is holding?
////////////////////////////
// STD::VISIT  visit(v, c)
////////////////////////////
// If v is a variant, and c is a callable, visit(v, c) calls c
// with whatever is stored in v as its argument
#include <iostream>
using std::visit;

// void exVariant(){
//     Animal a = Cat();
//     std::cout << visit(a, [](auto &x) {x.getAge(); });
// }

// ALMOST AS FAST AS TEMPLATES
// ⚫ Since Animal is a single type that can hold a Cat or a Dog,
//     we can just use animals by value instead of having to do
//     memory allocations
// AS DYNAMIC AS TRADITIONAL OO
// ⚫ A set<Animal> works great
// ⚫ Unlike our Concepts version


// USERS CAN ADD METHODS
// ⚫ Just like we discussed with the Visitor Pattern,
// users of the Animal type can add their own
// methods
// ⚫ To do this, we will use the “overloaded pattern”

// OVERLOADED PATTERN
// Define an overloaded class (you only need to do this once)
template<class... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};
// This inherits the function call operator of everything it is constructed with
// Let’s make this clear by creating a lifeSpan() “method” like we did before
// overloaded lifeSpan(
//     [](Cat &) { return 12; },
//     [](Dog &) { return 10; },
//     );
// Get life span without knowing whether
// a is a Cat or a Dog
// std::cout << visit(lifeSpan, a); // Prints 12
// Note that this idiom relies on CTAD and aggregates deducing the template arguments for you

// PROBLEMS WITH DUCK TYPING
// (-) The notation is much uglier than calling a virtual function
// (-) While the flexibility is nice, duck typing reduces type safety
//     -- It cannot tell that a Shape’s draw() method for drawing
//        a picture is different than a Cowboy’s draw() method
//        for drawing a gun
// (-) Variants always uses as much space as the biggest type
//     -- Whenever we create a new kind of Animal, we
//        have to add it to the variant, which can create
//        maintenance problems
