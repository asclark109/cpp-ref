////////////////////////
// NOEXCEPT noexcept
////////////////////////
// labelling a function noexcept means it will never throw an exception

// EXAMPLE MOTIVATION
// we want to copy a vector.
// but if it is vector<unique_ptr<T>>? 
// Then we can't copy the elems, we need to move.
// But moving can throw an exception
// If there is any chance a move throws, then we have to copy

// All of these are symptoms of the fact that
// writing code that can tolerate an exception at
// any conceivable moment is a drag at best
// and disastrous at worse

// While C++ does not have exception
// specifications like Java, you can label a
// function or method as noexcept, which means
// it will never throw an exception

// How vector decides whether to move or copy?
// -- If the type stored in it has a noexcept move constructor, then it moves it
// -- If not, it copies
// Since unique_ptr’s move constructor is annotated as noexcept
// unique_ptr(unique_ptr&& u) noexcept;
// To make this easier, there is a type trait 
// is_nothrow_move_constructible_v that Concepts
// or SFINAE can leverage to call the right code

////////////////////////////////////////////////////////////////////////////
// LABEL MOVE CONSTRUCTOR AS noexcept SO THAT IT MAY BE USED BY E.G. VECTOR
////////////////////////////////////////////////////////////////////////////

// EXAMPLE IN TEMPLATES
#include <type_traits>
using std::is_nothrow_move_constructible_v;
template<typename T>
auto square(T &&x)
noexcept(is_nothrow_move_constructible_v<T>) {
    return x*x;
}

// Sometimes you don’t have a convenient type trait

////////////////////
// noexcept()
////////////////////
// function that takes an expression and returns true if it is noexcept
template<typename T>
auto square(T &&x)
noexcept(noexcept(x*x) && is_nothrow_move_constructible_v<T>) {
    return x*x;
}

////////////////////////////////////////////////////////////////
// BEST PRACTICE: LABEL DESTRUCTORS ALMOST ALWAYS AS NO EXCEPT
////////////////////////////////////////////////////////////////
// whether you say so or not, your class destructors are implicitly noexcept

////////////////////////////////////////////////////////////////
// BEST PRACTICE: If your class’ move and copy constructors are
// noexcept, be sure to declare them that way.
// -- will pay off every time you put them in a container
// -- Passing by value will likely be safer and more efficient as well
////////////////////////////////////////////////////////////////

// Don’t try to declare everything with the correct noexcept specifier
// -- That way madness lies
// -- But don’t hesitate it if there is a specific benefit