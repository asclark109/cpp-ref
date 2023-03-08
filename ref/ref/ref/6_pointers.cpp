
//////////////
// POINTERS
//////////////
// Pointers to a type contain the address of an object of the given type.
struct A{ void foo(){};};
A *ap = new A();
// ap contains the address of an object of type A in memory
// new A() constructs an object of type A in memory and returns its address
// new A() has the same relation to A* as make_unique<A>() has to unique_ptr<A>

//////////////////////////////////////////////////////////
// ADDRESS-OF OPERATOR TO OBTAIN ADDRESS TO VARIABLE (&)
//////////////////////////////////////////////////////////
void exAddressOf(){
    A a;
    ap = &a; // & is the addressof operator. ap now holds the address of a
}

//////////////////////////////////////////////////////////
// DREFERENCE OPERATOR TO OBTAIN VARIABLE FROM ADDRESS (*)
//////////////////////////////////////////////////////////
void exDereference(){
    A a;
    ap = &a; // ap holds an address
    A b;
    A b = *ap; // copies the thing at address ap.
    // -> is an abbreviation for (*_).
    ap->foo(); // Same as (*ap).foo()
}

// All of these should be familiar from unique_ptr
// (which intentionally provides a pointer-like interface)

// Warning: Unlike unique_ptr, raw pointers do not
// have destructors and do not manage the lifetime of
// the object they point to. They simply store its
// address

//////////////////////////////////
// nullptr
//////////////////////////////////
// If a pointer is not pointing to any object, you should
// make sure it is nullptr

//////////////////////////////////////////////////////////////////////
// BEST PRACTICE: HAVE POINTERS POINT TO NULLPTR. NOT NULL AND NOT 0
//////////////////////////////////////////////////////////////////////
void exNullPtr(){
    A* ap;
    ap = nullptr; // don’t point at anything
    if(ap) { ap->foo(); } // foo won’t be called
}
// The type of nullptr is nullptr_t, which implicitly
// converts to any pointer type

// Old C/C++ code often uses 0 or the NULL
// macro to represent an empty pointer. 
// Don’t do this, as it breaks overloading 
int f3(char *){};
int f3(int){};
auto x = f3(0); // Which f was meant?
auto x = f3(0); // Calls f(int)
auto x = f3(nullptr); // Calls f(char *)

////////////////////////
// Pointer arithmetic
////////////////////////
// avoid it
// Arrays decay to a pointer to the 0th element
A *aap = new A[10];
// auto isequal = (*aap)[5] == *(aap + 5); // 5th elt of array 
// USE std::array and std::vector INSTEAD

////////////////////////////////////////////////////////////
// RELEASING MEMORY (DELETING ALLOCATED MEMORY HELD BY POINTER)
////////////////////////////////////////////////////////////

void exRawPtrLifecycle(){
    A* aptr = new A[10];
    // code...
    delete aptr; // Note: will be missed if code above throws exception
}