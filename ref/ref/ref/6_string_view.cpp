#include <iostream>
#include <string>
// C Strings
// ⚫ C-style string literals give you pointers
// ⚫ "foo" is actually a literal of type char const[4]
// ⚫ Sort of works
auto cp = "foo"; // c is a char const *
// std::cout << cp[1]; // prints o

// ⚫ But obviously not nearly as powerful or typesafe
// a C++ strings, which have many methods,
// addition, etc.
// ⚫ Using C++-string literals is a good habit

////////////////////////////////////////////////////
// DONT USE C STYLE STRINGS, USE C++ STYLE STRINGS
////////////////////////////////////////////////////
// auto s = "foo"s; // s is a std::string

////////////////////////////////////////////////////
// STRING_VIEW: string_view
////////////////////////////////////////////////////
void f(std::string const &){};

void exString(){
    f(std::string("foo")); // OK
    // f("foo"s); // OK. Same with user-defined literal
    f("foo"); // Has to copy text into string
    f({"foobar", 3}); // Has to copy text into string
}

// A string_view wraps a char const * and a length

void f2(std::string_view mystr){};

void exStringView(){
    f2(std::string("foo")); // OK. Views buffer
    // f2("foo"s); // OK.
    f2("foo"); // OK. No more copying text
    // f2({"foobar", 3}); // OK. No more copying text
}

// The hope is that functions that now take a
// string const & or a const char * will take a
// string_view instead

// HARD TO CONVERT string_view to string conversions

//////////////////////////////////////////////////////////////////////
// BEST PRACTICE: IF THE FUNCTION STAKES A CONST REFERENCE TO A STRING,
// CHANGE IT TO A STRING VIEW 
//////////////////////////////////////////////////////////////////////

////////////////////////////
// RAW STRING LITERALS
////////////////////////////
auto str = R"delim(text)delim"; // delim is optional and to disambiguate the end of the str