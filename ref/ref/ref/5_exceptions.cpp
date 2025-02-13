
////////////////
// EXCEPTIONS
////////////////
// When something goes wrong, throw an exception.
// This ensures that errors are never inadvertently ignored.

// an throw an exception (any type) with throw,
// But usually they should inherit from std::exception

//////////////////////
// THROW EXCEPTION
//////////////////////
#include<stdexcept>
void throwExcep(){
    throw std::runtime_error("Demo exception");
}

//////////////////////////////////
// TRY - CATCH
//////////////////////////////////
// You can catch an exception within a try block with catch.
// If you don’t catch the exception, it is passed to the
// caller and then the caller’s caller, etc. until it is caught
void catchExcep(){
    try {
        {
            throw std::runtime_error("this is an exception");   // THROW
        }
    } catch (std::exception &e) {
        std::cout << e.what();                                  // CATCH
    }
}
    
// EXAMPLE
#include<iostream>
struct A {
    A() { 
        throw std::runtime_error("Demo exception");
        std::cout << "Creating an A"; 
    }
    ~A() { std::cout << "Destroying an A"; }
};

int main()
{
    try {
        A a;
        {
            A &a2 = a;
        }
        std::cout << "out of inner scope";
    } catch (std::exception &e) {
        std::cout << e.what();
    }
    return 0;
}

////////////////////////////////////////////////////////
// EXCEPTIONS CAN BREAK RESOURCE MANAGEMENT SO USE RAII
////////////////////////////////////////////////////////
void f4() {
    // code_to_create_resources;
    // g(); // May thrown an exception
    // code_to_release_resources;
}
// RAII uses automatic duration objects to manage the
// lifetimes of dynamic duration resources
// RAII just means that we ensure that an automatic 
// object’s destructor performs any needed cleanup

// EXAMPLE
struct X{};
void g(){};

void f5() {
    auto x = std::make_unique<X>();
    g(); // No resource leak even if g throws
}

// to have the RAII object leave scope
std::unique_ptr<X> f6() {
    auto x = std::make_unique<X>();
    g();
    return move(x); // Transfer ownership to caller
}

// example RAII objects:
// unique_ptr
// shared_ptr
// jthread
// lock_guard
// scoped_lock
// unique_lock
// shared_lock

// CODE TO BE EXCEPTION SAFE:
void f7(){
    auto a = std::make_unique<X>();
    // code to work with a
}

// to get it to leave scope
std::unique_ptr<X> f8(){
    auto a = std::make_unique<X>();
    // code to work with a
    return move(a);
}
