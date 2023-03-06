//////////////////
// AUSTIN
//////////////////
#ifndef COUNTER_H
#  define COUNTER_H

#include<mutex>
#include<shared_mutex>
#include <functional>

template<typename F>
class Counter {

    F myFunc;
    bool shouldCount{ true }; // can be used to toggle on-off the counting

public:
    Counter(F myFunc) {
        this->myFunc = myFunc;
    }
    int count{ 0 };

    template<typename ... Args>
    requires std::invocable<F&, Args ...>
    auto operator()(Args &&... args) {
        if (shouldCount)
            count++;
        return myFunc(std::forward<Args>(args)...);
    }

    void toggleCounting() {
        shouldCount = !shouldCount;
    }
};

//////////////////
// AUSTIN
//////////////////
// a thread safe counter (uses reader-writer lock)
template<typename F>
class ThreadSafeCounter {

    F myFunc;
    int count{ 0 };
    std::shared_mutex mutable mtx;

public:
    ThreadSafeCounter(F myFunc) {
        this->myFunc = myFunc;
    }
    
    // NOTE: this code assumes myFunc is thread-safe
    // synchronization only occurs at incrementing counter
    // NOTE: we can easily make the function thread safe by 
    // having the execution of the function be wrapped inside
    // the lock/unlock block
    template<typename ... Args>
    requires std::invocable<F&, Args ...>
    auto operator()(Args &&... args) {
        std::unique_lock lock(mtx); 
        count++; 
        lock.unlock(); // synchronization only needed for incrementing counter
        return myFunc(std::forward<Args>(args)...);
    }

    auto getCount() {
        std::shared_lock lock(mtx);
        return count;
    }
};



#endif