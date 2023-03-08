////////////
////////////
// TUPLES
////////////
// Basically, it is an anonymous class on the fly
// A tuple is an anonymous struct with fields of given types

// You can think of tuples having the same relation to structs
// as lambdas do to functions
#include <tuple>
#include <string>
using std::tuple;
using std::string;

void exTuple() {
    // CREATING A TUPLE
    tuple<string, int, double> si("str", 2, 3.5);
    tuple di(2.5, 3, 'c'); // CTAD: di will be a tuple<double,int, char>

    // You can use get<> to access the fields
    get<0>(di);    // prints 2.5
    get<char>(di); // prints 'c'
    int three = get<1>(di);
}

////////////////////////////
// MULTIPLE RETURN VALUES
////////////////////////////
// One natural use for pair and tuple is to let
// functions return multiple values
#include <utility>
using std::pair;

pair<int, int> f() {
    return {1, 2}; // ok
}

tuple<int, int, char> g() {
    return {1, 2, 'u'}; // OK starting in C++17
}

