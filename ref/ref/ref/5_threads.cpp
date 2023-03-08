#include <iostream>
#include <thread>

////////////////
// THREADS
////////////////
// auto t = std::thread t(funcname, arg1, arg2,...);        // (1) start a thread
// use std::ref if you need the arg to go in by reference
// t.join();                                                // (2) Wait for that thread to complete

//////////////////////
// CREATION, JOINING
//////////////////////
// Constructing an object of type std::thread
// immediately launches a new thread, running the
// function given as a constructor argument (in this
// case, hello_threads)
void func1(int x, int const & y) {};
int exCreateThread(){
    int i{1};
    int j{3};

    auto t = std::thread(func1,i,std::ref(j));   //// CREATE new thread to run func1. USE std::ref to pass by reference
    t.join();                                    //// JOIN thread...blocks until thread completes
}

// Joining on the thread, waits until the thread completes
// Be sure to join all of your threads before ending the program
// unless it is a detached thread, which don’t need to be joined

//////////////////////
// (multiple)
//////////////////////
// EXAMPLE: locks
#include <vector>
#include <mutex>
#include <string>
using std::vector;
using std::thread;
using std::string;

std::mutex io_mutex;
void hello(std::string name) {
    std::lock_guard<std::mutex> guard(io_mutex);
    std::cout <<"Hello, " << name << std::endl;
}

int main(){ // No parens after thread function name:
    vector<string> names = { "John", "Paul"};
    vector<thread> threads;
    for(auto name : names) {                                            //// CREATE MULTIPLE
        threads.push_back(thread(hello, name));
    }
    // for(auto it = threads.begin(), it != threads.end(); it++) {      //// JOIN MULTIPLE
    //     it->join();
    // }
}

////////////////////
// THREAD ARGUMENTS
////////////////////
// can add arguments to be passed to the
// new thread when you construct the std::thread object
int func(int x) {return x;};
void exThread(){
    auto t = std::thread(func,3); // first arg is function. then variadic argument supply
    t.join();
}


//////////////////////////////////////////////////////
// GOTCHA!
// Signatures of thread functions silently “change”
//////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////
// GOTCHA!
// Careful passing references to functions run in threads
//////////////////////////////////////////////////////////
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
} 
// h keeps running with a pointer
// to a variable that no longer exists
// Undefined (but certainly bad) behavior

////////////////////////////////////////////////////////
// SURROUND FUNCTION USING THREAD WITH TRY/CATCH
// OR USE A std::jthread
////////////////////////////////////////////////////////

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
    {                                                               // CREATE JTHREAD...USE SCOPING TO MAKE USE OF RAII...DO NOT HAVE TO JOIN THREADS THEN
        for (size_t s = 0; s < threadCount; s++)
            threads.push_back(std::jthread(countALot));
    }
    // for (auto& thr : threads)
    //     thr.join();
    std::cout << "Count is " << c << std::endl;
    
    return 0;
}