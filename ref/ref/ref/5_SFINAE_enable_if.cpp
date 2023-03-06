#include <concepts>

////////////
// SFINAE
////////////
//  “Substitution Failure is Not an Error”
// When creating candidate overloads for a function, invalid substitutions in a particular function template mean
// that template is not a possible overload, But no compile error occurs even though the template failed to compile
struct Test {
    typedef int foo;
};

template <typename T>
void f(typename T::foo) { } // Definition #1

template <typename T> 
void f(T) {} // Definition #2

int main() {
    f<Test>(10); // Call #1.
    f<int>(10); // Call #2.
    // Without error (even though there is no int::foo) thanks to SFINAE :(
} 

//////////////
// ENABLE_IF
//////////////
template <bool B, class T = void>
struct enable_if {
    typedef T type;
};

template <class T>
struct enable_if<false, T> {};

template<bool B, typename T>
using enable_if_t = enable_if<B, T>::type;

// Using SFINAE to fix our gcd function template
// ⚫ We only want gcd to be used with integral types
// ⚫ The standard library has an is_integral_v template that checks if a type is integral
// ⚫ is_integral_v<unsigned> is true
// ⚫ is_integral_v<double> is false
// ⚫ Only allow gcd to be called on integral types
template <class T, typename = std::enable_if_t<std::is_integral_v<T>>>
T gcd(T a, T b) {
    if(b == 0)
        return a;
    return gcd(b, a - b*(a/b));
}

// SUMMARY:
// enable_if<b, T>::type is the type T if b is true
// enable_if<b, T>::type is a substitution failure if b is false

// Use it in template parameter lists, return values
// or argument types to suppress or enable the
// generation of certain template functions by SFINAE

void exEnableIf(){
    gcd(4, 6); // OK
    // gcd(4.2, 6.0); // Must be a different gcd
}