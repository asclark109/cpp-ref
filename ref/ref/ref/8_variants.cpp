//////////////
// VARIANTS
//////////////

// Think of a variant is like a tuple, but instead of holding all of
// its fields at once, it only contains one of them at a time
// Supports a very similar interface to tuples
#include <variant>
using std::variant;

void exVariant(){
    variant<int, double> v = 3; // Holds int
    get<0>(v); // Returns 3
    get<1>(v); // Throws std::bad_variant_access
    v = 3.5; // Now holds a double
    get<double>(v); // Returns 3.5
    //  You can also check what is in it
    // v.index; // returns 1
    holds_alternative<double>(v); // returns true
    holds_alternative<int>(v); // returns false
    // We will learn some more ways to access variants when we cover object-oriented design
}