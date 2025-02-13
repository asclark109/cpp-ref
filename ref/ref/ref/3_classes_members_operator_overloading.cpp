#ifndef EXCLASS_MEMBERS_OPERATOR_OVERLOADING_H
#  define EXCLASS_MEMBERS_OPERATOR_OVERLOADING_H


#include <ostream>
#include <iostream>
//////////////////
// OPERATOR OVERLOADING
//////////////////

// You can overload operators just like functions
//   Unary operators:   + - * & ~ ! ++ -- -> ->*
//   Binary operators:  + - * / % ^ & | << >>
//                      += -= *= /= %= ^= &= |= <<= >>=
//                      < <= > >= == != && ||
//                      , [] () <=>
//                      new new[] delete delete[] 
// cant overload: .  .*  ?:  ::

// Sometimes you have a choice whether to use a special member
// SPECIAL MEMBER FUNCTION OR GLOBAL FUNCTION???
class myString {
    myString(const char *cp);
    char operator[](size_t idx) const;
    myString operator+(myString const &addend) const;
    myString operator+=(myString const &addend);
};

// OR
class myString {
    myString(const char *cp);
    char operator[](size_t idx) const;
};
myString operator+(const myString &s1, const myString &s2);
myString operator+=(const myString &s1, const myString &s2);

// WHEN TO USE GLOBAL FUNCTION
// Using a global function makes sure both arguments are
// treated the same way, which fits the intuition that
// addition operators, which are generally commutative,
// should apply the same rules to each arguments:
// (1) WHEN YOU WANT IMPLICIT TYPE CONVERISONS AND TO HAVE
//     THE OPERANDS TREATED EQUALLY

// WHEN TO USE MEMBER FUNCTION
// (1) WHEN YOU DON'T WANT TYPE CONVERSIONS DONE TO
//     ONE OF THE OPERATORS (E.G. the LHS operator)

// ostream is really an instance of a class template
using ostream = std::basic_ostream<char, std::char_traits<char>>;
// To be able to print to any output stream, use a function template
// struct A {};
// auto & operator<<(std::basic_ostream<auto, auto> &os, A const &ms) {
//     os << 5; 
//     return os;
// }

// void f() {
//     A a;
//     std::cout << a;
//     std::wcout << a; // OK
// }

// How does a unique_ptr work?
// Overloading operator->() and operator*() of course!
//    operator->() overloads with a unique rule:    Keep doing -> until it is illegal
// As mentioned above, the destructor calls the destructor of the managed object and releases its memory

#endif