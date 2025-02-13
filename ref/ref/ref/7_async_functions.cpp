////////////////////
// ASYNC FUNCTIONS
////////////////////

// it's nice that we can pass arguments to a thread (like we do to functions),
// but how can we get the thread to return a value back?

// we want to be able to use threads as “asynchronous functions”
////////////////////
// FUTURE; ASYNC
////////////////////
// C++11 defines a std::future class template that lets a thread return a
// value sometime in the future when it’s calculation is complete.
// One way to create a future is with std::async

////////////////////
// ASYNC
////////////////////
// As soon as you create an async function (and get a future), it starts
// running the function you passed it (usually) in a new thread
// 'get()' when you want to get the value produced by the function
// 'get()' will wait for the thread function to finish, then return the value
#include <future>
using std::future;
using std::async;
int func_returning_int(){return 1;};

void exAsync(){
    ////////////////////////////////////
    // CREATE ASYNC (returns future)
    ////////////////////////////////////
    future<int> f = async(func_returning_int);
    f.get(); // blocks until the other thread completes calculation
}

//////////////////////
// PROMISES, FUTURES
//////////////////////
// Promises and futures let you pass values between threads
// Kind of like a producer/consumer but you are just passing a
// single item, so you don’t need a queue

////////////////////////////////
// CREATE PROMISE, GET FUTURE
////////////////////////////////
// lets you pass a value from one thread to another
using std::future;
using std::promise;
promise<int> p;
future<int> fi = p.get_future();

// The producing thread stores the value in the promise
// PRODUCER THREAD
void exProducer(){
    // PRODUCER: assume he was given p
    // promise<int> p; 
    //////////////////////////
    // PROMISE.SETVALUE()
    //////////////////////////
    p.set_value(7);
}

void exConsumer(){
    // CONSUMER: assume he was given future
    // future<int> fi = p.get_future();
    // The consuming thread blocks, and then receives the value when 
    // it becomes available. 
    //////////////////////////
    // FUTURE.GET()
    //////////////////////////
    fi.get(); // continues execution until value is set by thread with promise
}


// EXAMPLE:
#include <future>
#include <iostream>
int calculate_the_answer_to_LtUaE();
void do_stuff();
void exPromise() {
    // Run calculation in a different thread
    std::future<int> the_answer = std::async(calculate_the_answer_to_LtUaE);
    do_stuff();
    std::cout <<"The answer to life, the universe and everything is "
        << the_answer.get()
        << std::endl;
}

// CHECK IF FUTURE HAS A VALUE
using namespace std::chrono_literals;
void exConsumer2(){
    fi.wait_for(std::chrono::seconds(0)) == std::future_status::ready; // evals to true if read
    // BETTER US A LITERAL
    fi.wait_for(0s) == std::future_status::ready; // evals to true if read
}

//////////////////////////////////////////////////
// WHAT IF ASYNCH FUNCTION THROWS AN EXCEPTION ?
//////////////////////////////////////////////////
// If the thread function in an async throws an
// exception instead of returning a value, then
// calling get() will throw the exception, just like
// the asynchronous function was a real
// function