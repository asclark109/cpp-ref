////////////
// LOCKS
////////////
// std::mutex   // The simplest way to protect shared data is with a 

//////////////
// DATA RACE
//////////////
// Accessing the same data from multiple threads without
// using synchronization like mutexes is called a data race
// error. Don’t do this!

// USE RAII TO ENSURE YOU NEVER FORGET TO UNLOCK LOCK
// ⚫ std::lock_guard (C++11 handy RAII ensures you never forget to unlock lock)
// ⚫ std::scoped_lock (C++17 can lock any number of locks without deadlocking)


//////////////////////////////////////////////////////////////
// MUTEX, LOCK_GUARD (RAII)...COARSE-GRAINED DATA STRUCTURES
//////////////////////////////////////////////////////////////
#include <mutex>
std::mutex m;             // creates muxtex...prevents concurrent access to the shared data structure
std::lock_guard guard(m); // locks mutex...when destroyed will unlock

// EXAMPLE: (coarse-grained data structure)
#include <list>
std::list<int> some_list; // accessed by multiple threads
std::mutex some_mutex;    // prevents concurrent access to the shared data structure

void add_to_list(int new_value) {
    // Since I am going to access the shared data struct, acquire the lock
    std::lock_guard guard(some_mutex);                                                //// ACQUIRE LOCK... CTAD deduces lock_guard<mutex>
    some_list.push_back(new_value);                                                   //// USE SCOPING {} WITH LOCK_GUARD INSTEAD OF MANUAL UNLOCK
    // Now it is safe to use some_list. lock_guard destructor 
    // releases lock at end of function
    /* ... */
}

bool list_contains(int value_to_find) {
    std::lock_guard guard(some_mutex); // Must lock to access some_list
    return std::find(some_list.begin(),some_list.end(),value_to_find) != some_list.end();
}

//////////////////////////////////////////////////////////////////
// SHARED MUTEX, SHARED_LOCK, UNIQUE_LOCK ("reader-writer" lock)
//////////////////////////////////////////////////////////////////
// A shared_mutex can be acquired either in shared
// ownership mode or unique ownership mode
#include <shared_mutex>
std::shared_mutex sm;                                               // CREATE MUTEX THAT CAN BE SHARED
std::shared_lock sl(sm);                                            // ACQUIRE the shared lock
std::unique_lock ul(sm);                                            // ACQUIRE the unique lock

// EXAMPLE: reader-writer lock
// Multiple threads can read from a data structure at the
// same time as long as no thread is modifying it.
// If a thread is modifying the data structure, it should
// acquire sole ownership of the object so no thread
// sees the data structure in a partially modified state
std::list<int> list1;
std::shared_mutex m1;
void add_to_list(int new_value) {
    std::unique_lock guard(m1);                                     // Unique writer access
    some_list.push_back(new_value);
}
bool list_contains(int value_to_find) {
    std::shared_lock guard(m1);                                     // Shared reader access
    return std::find(some_list.begin(),some_list.end(),value_to_find) != some_list.end();
}

////////////////////
// LOCK ORDERING
////////////////////
// to avoid deadlocks, you want to acquire locks in the same order
// lock A, lock B
//////////////////////////////////////////////
// BEST PRACTICE: DOCUMENT THE LOCK ORDERING
//////////////////////////////////////////////

////////////////////
// SCOPED_LOCK
////////////////////
// If attempting to lock down multiple data structures
// when there is no clear lock ordering (e.g. lock down
// two bank accounts to perform a transfer), a deadlock
// might occur. Use std::scoped_lock to prevent this.
account a1{};
account a2{};
std::scoped_lock lck(a1.m,a1.m);                                              // CREATE SCOPED_LOCK

// EXAMPLE: transfer between two bank accounts
typedef double currency_value;
class account {
    std::mutex m;
    currency_value balance;
public:
    friend void transfer(account& from,account& to, currency_value amount) {  // ACQUIRE SCOPED_LOCK (multiple mutexes)
        std::scoped_lock lck(from.m, to.m); // locks down two locks in deterministic ordering / won't deadlock
        from.balance -= amount;
        to.balance += amount;
    }
};

// EXAMPLES
// Implement a distributed counter with a thread local count in
// conformance with cache-conscious programming best practices in
// the lecture.
//
// Most of the complexity here is in managing the thread local counts
// as threads are created or destroyed. Study how we use various
// multithreading techniques to accurately and safely track these.
//
// Cache management here is poor. and it is a coarse grained impl
#include<mutex>
#include<shared_mutex>
#include<map>
#include<numeric>

namespace mpcs {
    class DistributedCounter {
    public:
        typedef long long value_type;

    private:
        value_type count;
        std::shared_mutex mutable mtx; // SHARED_MUTEX for reader-writer lock

    public:
        DistributedCounter() : count(0) {}

        void operator++() {
            std::unique_lock lock(mtx); // UNIQUE_LOCK to acquire write lock for shared_mutex
            ++count;
        }
        void operator++(int) {
            std::unique_lock lock(mtx); // UNIQUE_LOCK to acquire write lock for shared_mutex
            count++;
        }

        value_type get() const {        // LOGICALLY CONST
            std::shared_lock lock(mtx); // SHARED_LOCK to acquire read lock for shared_mutex
            return count;
        }
    };
}

//////////////////////////
// MUTABLE KEYWORD
//////////////////////////
// We would like DistributedCounter::get() to be
// const because it seems illogical that reading
// the current value modifies the object.

// But getting the reader lock will modify
// the state of the mtx member of the counter
// object.

// Since we don’t want consider changes to mtx
// to be changes to the state modeled by our
// counter, we label it mutable, which means
// that it can be modified even in const contexts

