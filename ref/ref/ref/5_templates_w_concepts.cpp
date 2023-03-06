// TEMPLATES BEFORE CONCEPTS

#include <concepts>
#include <vector>
#include <list>
#include <algorithm>

// Besides auto, the other major C++20 template feature is Concepts, which us allow
// us to constrain our templates
template<std::floating_point T, int m, int n = m>
struct Matrix { /* ... */ };

// The algorithms we've been discussing often require a callable
// ⚫ How would we write a function template that expects its argument is callable with an int?
// https://godbolt.org/z/M8axbv7Ys
void f1(std::invocable<int> auto callable) {
    callable(5);
}

// What if we just didn't use a Concept?
// https://godbolt.org/z/M8axbv7Ys
void f2(auto callable) {
callable(5); 
}
// still works. runs with a valid callable and fails to compile if callable cannot be called with an int
// However, the error will be inside the body of f where the call takes place
// ⚫ In this case, it's not a big deal since f is so simple
// ⚫ But let's look at some real-life examples where it really helps to constrain the template

// What goes wrong with the following natural code?
template<typename T>
void f3(T &t) {
    sort(t.begin(), t.end()); // OK
}
std::vector<int> v = { 3, 1, 4, 1};
std::list<int> l = {5, 9, 2};

void exTemplatesAndConcepts() {
    f3(v); // OK
    f3(l); // Huge compiler error
};

// sort requires random access iterators
// ⚫ Since lists need to be walked through a node at a time, their iterators are not considered random access
// ⚫ Somewhere deep inside of the sort algorithm, something goes wrong, leading to an incomprehensible error message
// ⚫ Might be hundreds of lines long

// You can’t overstate what a big problem this is
// ⚫ As we’ve discussed numerous times, C++ is a language of lightweight abstractions
// ⚫ The theory of templates is to provide the ideal abstract interface at zero cost as a template library
// ⚫ In practice, that works well if your client uses your templates correctly
// ⚫ But any mistake leads to incomprehensible error messages

//////////////
// CONCEPTS
//////////////
// template<std::random_access_iterator it>
// sort(it beg, it end);
// Now the error would be something  understandable like
// “Sorry, list::iterator does not satisfy the random_access_iterator concept”

// TO ENSURE CORRECTNESS, USE CONCEPTS TO MAKE SURE WE DONT GET CRYPTIC
// ERROR MESSAGES, OR WORSE A RESULT BUT ONE THAT IS WRONG

// In C++20, we can give an analogous “prototype” to our template
template<std::integral T>
T gcd(T a, T b) {
    if(b == 0)
        return a;
    return gcd(b, a - b*(a/b));
}

