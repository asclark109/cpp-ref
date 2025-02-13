//////////////
// POINTERS
//////////////
// Pointers are a low-level way to refer to a
// (typed) location in physical memory

// For the most part, one should use references
// and higher-level lightweight abstractions like
// unique_ptr

//////////////////////////////////////////////////////////////////////
// USE RAW POINTERS SELDOMLY!!! INSTEAD USE REFERENCES OR UNIQUE_PTR
//////////////////////////////////////////////////////////////////////

// When pointers?
// A reference always refers to the same object but doesn’t own it 
// and cannot be “unbound”

// A unique_ptr can change what object it manages, and can be unset
// (not managing any object), but always owns any object it manages

// What if we want to be unsettable/rebindable but not own the object?

// C++ forces pointers on you in a number of cases
// (1) 'this' is a pointer
//      Although it’s generally better to use the reference *this
// (2)  uses “pointers to pointers” to pass command line arguments. Yuck!
int main(int argc, char **argv) {}
// (3)  Low-level programming. C++ is a systems programming language
//      You may need to access memory directly.
//      
//      For example, a temperature sensor external to the
//      program may write the current temperature into a
//      particular memory location, and your program
//      needs to read the value at that know memory
//      location

// (4)  Advanced memory management

//      Nearly all memory management can be
//      handled with unique_ptr and shared_ptr,
//      But occasionally there are situations they
//      don’t cover. For example, managing the lifetime
//      of nodes in a doubly linked list has shared ownership
//      but using shared_ptr would be too inefficient
