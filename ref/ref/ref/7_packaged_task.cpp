<<<<<<< HEAD

// ASYNC is good if you just want to run a function on a
// new thread to get a return value,

// if you want to asynchronously run a function
// on a specific existing thread, like a UI thread,
// you want a packaged_task.

//////////////////////////////////////
// PACKAGED_TASK std::packaged_task
//////////////////////////////////////
// If I had said in one thread
#include <future>
using std::packaged_task;
using std::future;

void f(){};
packaged_task<int(double)> pt{f};
future<int> fi = pt.get_future();
// Then I could run pt in any other thread
// And the value will become available in fi
void exExecutePackagedTask(){
    pt(3.6);
}

//////////////////////////////
// IMPORTANT TO KNOW
//////////////////////////////
// If you get a future from a promise, it is “nonblocking”
// -- Destroying the future does not wait for the thread to complete
// -- If you call async, it returns a “blocking future”. Its destructor will join the thread
#include <future>
using std::async;
void f1();
void g1();
// The following code runs in parallel
auto a = async(f1);
auto b = async(g1);
// NO PARALLELISM!
async(f1); // future returned from async is not stored anywhere, 
           // so its destructor is called after 1st line, so it will
           // wait for the thread running f1 to finish before advancing
           // to the next line to launch g.
async(g1);

// EXAMPLE PARALLEL ACCUMULATE
// async_accumulate_function.h
#include <numeric>
namespace mpcs51044 {
    template<class T> 
    T accumulate_future_value(T t, std::future<T> &f) {
        return t + f.get();
    }

    template<typename Iterator,typename T>
    T async_accumulate(Iterator first,Iterator last,T init) {
        unsigned long const length = std::distance(first,last);
        if(!length)
            return init;
        unsigned long const min_per_thread=25;
        unsigned long const max_threads = (length+min_per_thread-1)/min_per_thread;

        // hardware_concurrency may return 0 if it doesn't choose to answer
        unsigned long const hardware_threads = std::thread::hardware_concurrency();
        unsigned long const num_threads = std::min(hardware_threads!=0?hardware_threads:2,max_threads);
        unsigned long const block_size = length/num_threads;
        std::vector<std::future<T>> futures(num_threads-1);
        Iterator block_start=first;

        for(unsigned long i=0; i<(num_threads-1); ++i) {
            Iterator block_end = block_start;
            std::advance(block_end,block_size);
            futures[i] = std::async(
                std::accumulate<Iterator,T>,
                // next line for MSVC 2010, instead of the above:
                //static_cast<T (*)(Iterator, Iterator, T)>(std::accumulate<Iterator,T>),
                block_start,
                block_end,
                T{});
            block_start = block_end;
        }
        return std::accumulate(
            futures.begin(),
            futures.end(),
            std::accumulate(block_start, last, T()),
            [](auto &acc, auto &next) { return acc + next.get();  }
        );
    }
=======

// ASYNC is good if you just want to run a function on a
// new thread to get a return value,

// if you want to asynchronously run a function
// on a specific existing thread, like a UI thread,
// you want a packaged_task.

//////////////////////////////////////
// PACKAGED_TASK std::packaged_task
//////////////////////////////////////
// If I had said in one thread
#include <future>
using std::packaged_task;
using std::future;

void f(){};

//////////////////////////////
// CREATE PACKAGED_TASK
//////////////////////////////
packaged_task<int(double)> pt{f};
future<int> fi = pt.get_future();
// Then I could run pt in any other thread
// And the value will become available in fi
void exExecutePackagedTask(){
    pt(3.6);
}

//////////////////////////////
// IMPORTANT TO KNOW
//////////////////////////////
// If you get a future from a promise, it is “nonblocking”
// -- Destroying the future does not wait for the thread to complete
// -- If you call async, it returns a “blocking future”. Its destructor will join the thread
#include <future>
using std::async;
void f1();
void g1();
// The following code runs in parallel
auto a = async(f1);
auto b = async(g1);
// NO PARALLELISM!
async(f1); // future returned from async is not stored anywhere, 
           // so its destructor is called after 1st line, so it will
           // wait for the thread running f1 to finish before advancing
           // to the next line to launch g.
async(g1);

// EXAMPLE PARALLEL ACCUMULATE
// async_accumulate_function.h
#include <numeric>
namespace mpcs51044 {
    template<class T> 
    T accumulate_future_value(T t, std::future<T> &f) {
        return t + f.get();
    }

    template<typename Iterator,typename T>
    T async_accumulate(Iterator first,Iterator last,T init) {
        unsigned long const length = std::distance(first,last);
        if(!length)
            return init;
        unsigned long const min_per_thread=25;
        unsigned long const max_threads = (length+min_per_thread-1)/min_per_thread;

        // hardware_concurrency may return 0 if it doesn't choose to answer
        unsigned long const hardware_threads = std::thread::hardware_concurrency();
        unsigned long const num_threads = std::min(hardware_threads!=0?hardware_threads:2,max_threads);
        unsigned long const block_size = length/num_threads;
        std::vector<std::future<T>> futures(num_threads-1);
        Iterator block_start=first;

        for(unsigned long i=0; i<(num_threads-1); ++i) {
            Iterator block_end = block_start;
            std::advance(block_end,block_size);
            futures[i] = std::async(
                std::accumulate<Iterator,T>,
                // next line for MSVC 2010, instead of the above:
                //static_cast<T (*)(Iterator, Iterator, T)>(std::accumulate<Iterator,T>),
                block_start,
                block_end,
                T{});
            block_start = block_end;
        }
        return std::accumulate(
            futures.begin(),
            futures.end(),
            std::accumulate(block_start, last, T()),
            [](auto &acc, auto &next) { return acc + next.get();  }
        );
    }
>>>>>>> daaac18b9a6fa6ae774efaf9b921fe69fc86d677
}