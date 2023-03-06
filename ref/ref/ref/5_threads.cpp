#include <iostream>
#include <thread>

////////////////
// THREADS
////////////////
// std::thread t(funcname);   // start a thread
// t.join();                  // Wait for that thread to complete

// Constructing an object of type std::thread
// immediately launches a new thread, running the
// function given as a constructor argument (in this
// case, hello_threads)

void hello_threads() {
    std::cout<<"Hello Concurrent World\n";
}

int exCreateThread(){
    // Print in a different thread
    std::thread t(hello_threads);
    t.join(); // Wait for that thread to complete
}

// Joining on the thread, waits until the thread completes
// Be sure to join all of your threads before ending the program
// unless it is a detached thread, which don’t need to be joined

////////////////////
// THREAD ARGUMENTS
////////////////////
// can add arguments to be passed to the
// new thread when you construct the std::thread object
int func(int x) {return x;};
void exThread(){
    // BASIC
    auto t = std::thread(func,3); // first arg is function. then variadic argument supply
    t.join();
    // BETTER: use jthread below
}

// EXAMPLE:
#include <vector>
#include <mutex>

std::mutex io_mutex;
void hello(std::string name) {
    std::lock_guard<std::mutex> guard(io_mutex);
    std::cout <<"Hello, " << name << std::endl;
}

int main(){ // No parens after thread function name:
    std::vector<std::string> names = { "John", "Paul"};
    std::vector<std::thread> threads;
    for(auto name : names) {
        threads.push_back(std::thread(hello, name));
    }
    // for(auto it = threads.begin(), it != threads.end(); it++) {
    //     it->join();
    // }
}

//////////////////////
// GOTCHA!
// Signatures of thread functions silently “change”
//////////////////////

// EXAMPLE
void f1(int &i) { i = 5; }
int main() {
    int i = 2;
    std::thread t(f1, i);
    t.join();
    std::cout << i << std::endl; // prints 2 :(...even though f takes a lvalue reference.
    return 0;
}

//////////////////////////////////////////////////////////////
// IF THREAD IS CALLING A FUNCTION TAKING ARGS BY REFERENCE
// NEED TO USE std::function OR std::ref TO FORWARD ARGUMENTS
// TO THREAD CORRECTLY; ELSE THREAD WILL GET A COPY
//////////////////////////////////////////////////////////////

////////////////
// REF WRAPPER
////////////////
#include <functional>

// EXAMPLE
void f2(int &i) { i = 5; }
int main() {
    int i = 2;
    std::thread t(f2, std::ref(i)); // GOOD. FUNCTION RECIEVES REF CORRECTLY
    t.join();
    std::cout << i << std::endl; // GOOD
    return 0;
}

//////////////////////
// GOTCHA!
// Careful passing references to functions run in threads
// 
//////////////////////
// Be very careful about passing pointers or references to local
// variables into thread functions unless you are sure the local
// variables won’t go away during thread execution
void h(int &i);
void bar();
void f3() {
    int i;
    std::thread t(h, std::ref(i));
    bar(); // What if bar throws an exception?
    t.join(); // This join is skipped. BAD!
} // h keeps running with a pointer
// to a variable that no longer exists
// Undefined (but certainly bad) behavior

//////////////////////
// SURROUND FUNCTION USING THREAD WITH TRY/CATCH
// OR USE A std::jthread
//////////////////////

////////////////
// EXCEPTIONS
////////////////
// When something goes wrong, throw an exception.
// This ensures that errors are never inadvertently ignored.

// an throw an exception (any type) with throw,
// But usually they should inherit from std::exception

// You can catch an exception within a try block with
// catch.
// If you don’t catch the exception, it is passed to the
// caller and then the caller’s caller, etc. until it is
// caught

// EXAMPLE
#include<iostream>
#include<stdexcept>
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


////////////////////////////////////////////////////////////
// USE JTHREADS INSTEAD OF THREADS TO GET EXCEPTION SAFETY
////////////////////////////////////////////////////////////
#include<thread>
size_t const reps{ 100'000'000 };
size_t const threadCount{ 10 };

size_t c{2};

void countALot() {
    for (size_t s = 0; s < reps; s++)
        c++;
}

// note this causes a data race...just exemplifying jthread use
int main() {
    std::vector<std::jthread> threads;
    { // CAN USE SCOPING AND MAKE USE OF RAII TO NOT HAVE TO JOIN THREADS
        for (size_t s = 0; s < threadCount; s++)
            threads.push_back(std::jthread(countALot));
    }
    // for (auto& thr : threads)
    //     thr.join();
    std::cout << "Count is " << c << std::endl;
    
    return 0;
}

// #include<chrono>
// auto start = std::chrono::high_resolution_clock::now();
// auto end = std::chrono::high_resolution_clock::now();
// cout << "Elapsed time is " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;