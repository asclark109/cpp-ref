#include <memory>

////////////////////////////////////////////
// What does it mean to move an object?
////////////////////////////////////////////
// Means that the value of x is the same as the value y started at
// So one way to do this is by using ordinary copying like
void exCopy(){
    int x{};
    int y{};
    x = y;
}

//////////////////
// MOVE vs COPY?
//////////////////
// the difference between a copy and a move is that y is allowed to be changed by the move
// Subsequent code should not use the value of y

////////////////
// why MOVE?
////////////////

// EFFICIENCY: a move can “raid the old object for parts,” it can be a lot more efficient than copy
// -- Copying a tree requires copying all of the branches
// -- Moving a tree only requires moving the root

// SEMANTICS: Some classes don’t make sense to copy and therefore have deleted copy constructors
// -- E.g., if you copied a unique_ptr, the managed object would be owned by two unique_ptrs (not allowed!)
// -- E.g., what does it mean to copy std::cout (we should delete copy constructor then)
// -- Better to use a move

////////////////////////////////////
// When does C++ use move or copy?
////////////////////////////////////
// If it is sure that the old object doesn’t need its value any more!

////////////////////////////////////////////////////////////////////////////////////////////////
// (1) IF THE OLD OBJECT IS A TEMPORARY VALUE AND HAS NO NAME, SO IT CAN'T BE REFERRED TO AGAIN
////////////////////////////////////////////////////////////////////////////////////////////////
// e.g. it is safe to move the unique_ptr returned by make_unique into x,
// since that is the only place the return value is visible
struct X{};
auto x = std::make_unique<X>(); // x owns the X obj;

//////////////////////////////////////////////////////////////////////////
// (2) if the programmer uses std::move to say that it is ok to move from
//////////////////////////////////////////////////////////////////////////
auto y = move(x); // Now y owns the X obj; may invalidate x

////////////////////////////////////////////
// How does move work? RVALUE REFERENCES
////////////////////////////////////////////
// a reference with "&&" can bind to a temporary and move it elsewhere
// (a) objects are often much cheaper to "move" than copy (e.g. deep copying a tree)
// (b) some objects like unique_ptr can be moved but not copied (copy constructor deleted)

// Ex: swap. great situation to move things instead of copy. more efficient.
template<class T>
void swap(T& a, T& b)// "perfect swap"(almost)
{
    T tmp = move(a); // could invalidate a;
    a = move(b);     // could invalidate b;
    b = move(tmp);   // could invalidate tmp;
}

// Ex: putting items into a vector
// std::unique_ptr is not copyable. they are movable.
// can construct a temporary unique_ptr and move it into a vector
template<typename T> class vector1{
public:
    push_back(T const &T);
    push_back(T &&t); 
};
struct btree{};

void exPassRval(){
    vector1<std::unique_ptr<btree>> vt;
    for(size_t i = 0; i < 10; i++){
        vt.push_back(std::make_unique<btree>());
    }
}

/////////////////////
// LVALUE vs RVALUE
/////////////////////
// in old days of C:
// Lvalue referred to what appeared on LHS of an assignment
// Rvalue referred to what appeared on RHS of an assignment

// but that's not quite right in C++:
//////////////////////////////////////////////////////////////////////
// LVALUE is a "locator value": refers to a defined region of storage.
// Although, additionally functions are Lvalues even though they are not objects.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////
// RVALUE can be considered as a value of an expression.
//////////////////////////////////////////////////////////
void exLRvalues(){
    // lvalues:
    int i{};
    i = 43;           // ok, i is an lvalue
    int* p = &i;      // ok, i is an lvalue
    // foo() = 42;       // ok, foo() is an lvalue
    // int* p1 = &foo(); // ok, foo() is an lvalue

    // rvalues:
    int foobar();
    int j = 0;
    j = foobar();           // ok, foobar() is an rvalue
    // int* p2 = &foobar(); // error, cannot take the address of an rvalue
    j = 42; // ok, 42 is an rvalue
}

//////////////////////////////////////
// RVALUE REFERENCE: 
// represents a modifiable object where the value is no
// longer needed so that you can steal its contents and 
// provide move semantics
//////////////////////////////////////

////////////////////////////////
// How to make a type movable?
////////////////////////////////
// (!) you don't need to make a class movable.
//     It is only a performance optimization
//     because C++ will just copy if there are no move operations.

//     If moving is more efficient, you should create move 
//     constructors and move assignment operators,
//     just like standard library containers do:
template<class T> class vector3 {
    // ...
    vector3(vector3<T> const &); // copy constructor
    vector3(vector3<T> &&); // move constructor
    vector3& operator=(const vector3<T>&); // copy assignment
    vector3& operator=(vector3<T>&&); // move assignment
};
// Sometimes, the compiler will automatically generate 
// move constructors and move assignment operators that
// just move all the members ( Basically if you don't 
// define a copy constructor/assignment operator or a 
// destructor)

//////////////////////////////////////////////////////////////////////////////////////
// IF YOU SPECIFY COPY CONSTRUCTOR, DEFAULT MOVE CONSTRUCTOR/ASSIGNMENT NOT GENERATED
//////////////////////////////////////////////////////////////////////////////////////
// If you want to force the compiler to generate the default move
// constructor even though it wouldn't normally, you can force that with default
struct S {
    S(S const &);      // OK, defining a copy constructor stops move constructor generation though
    S(S &&) = default; // Gets it back
    /* ... */
};
