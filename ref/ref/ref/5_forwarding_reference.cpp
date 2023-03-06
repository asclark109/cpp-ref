#include <concepts>

//////////////////////////
// FORWARDING REFERENCE
//////////////////////////
// Yet another “way of argument passing”
// If && is used in a template argument, it means 
// “forwarding reference,” which bind to either an
// rvalue reference or a regular (lvalue) reference

// Template type deduction takes place according
// to the following “collapsing rules” which are only
// applied in templates
// ⚫ T& & ≅ T&
// ⚫ T& && ≅T&
// ⚫ T&& & ≅T&
// ⚫ T&& && ≅T&&

// std::move
// here T&& argument means forwarding reference. will work with lvalue or rvalue
// so move can accept and Lvalue or Rvalue
// will return something like T&&
template <class T>
std::remove_reference_t<T> && move(T&& a) {
    return a;
}
// What happens in the code
struct A{};
void f1(A&& a){}; // accepts an R value; basically telling f1 it is working with a temporary object it can raid for parts
void f1(A&  a){}; // accepts an L value; basically telling f1 it is working with an existing object (can't raid for parts)

void exMove(){
    A a{};
    f1(a);        // a is an Lvalue...so f1(A& a) is invoked because A& means accept an Lvalue and work with an Lvalue reference
    f1(move(a));  // move(a) returns a as a temporary (Rvalue)...so f1(A&& a) is invoked because A&& means accept an Rvalue and work with an Rvalue reference
}