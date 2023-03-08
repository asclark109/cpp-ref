//////////////////////////////
// INTER-THREAD COMMUNICATION
//////////////////////////////

// Sometimes locks aren’t what you want

//////////////////////////////
// PRODUCER-CONSUMER
//////////////////////////////
// Suppose we are trying to implement a “producer/consumer” design pattern
// Think of this as a supply chain
// Some threads produce work items that are consumed by otherthreads
// Incredibly common in multi-threaded programs

// Typically the producers put work onto a queue, and the consumers take them off
// ⚫ Locks can allow thread-safe access to the queue
// ⚫ But what happens if there is no work at the moment?
// ⚫ The consumer thread needs to go to sleep and wake up when there is work to do
// ⚫ Rather than a lock, you’d like to wait for an “event” stating that the queue has become non-empty

////////////////////
// UNIQUE_LOCK
////////////////////
// std::unique_lock // a richer version of lock_guard

//////////////////////
// CONDITION_VARIABLE
//////////////////////
// std::condition_variable // “wakes up” waiting threads
// cv.notify_one(); // Wakes one waiter; No guarantees which one
// cv.notify_all(); // Wakes all waiters
#include<mutex>
#include<condition_variable>
using std::unique_lock;
using std::condition_variable;
using std::mutex;

// USAGE
bool test(){
    return true;
};

void exCv(){
    // USING A CONDITION VARIABLE
    mutex m; // assume mutex, cv is shared by all producers and consumers
    std::condition_variable cv;
    // CONSUMER CODE
    unique_lock<mutex> lck(m);   // acquire unique lock
    cv.wait(lck, test);          // run test() if evaluates to true, proceeds; 
                                 // otherwise, relases lock and sleeps.
                                 // when it wakes back up it tries to acquire lock
    // CODE IN OTHER THREAD
}

void exProducer(){
    mutex m; // assume mutex, cv is shared by all producers and consumers
    std::condition_variable cv;
    // PRODUCER CODE
    // do stuff...
    unique_lock<mutex> lck(m);   // acquire unique lock
    // do stuff...
    // when some interesting event happens
    cv.notify_one(); // Wakes one waiter; No guarantees which one
    cv.notify_all(); // Wakes all waiters
}

// EXAMPLE: PRODUCER_CONSUMER FROM C++ CONCURRENCY IN ACTION
// later example problem
#include <queue>
#include <memory>
using std::queue;
using std::lock_guard;
using std::move;
typedef int data_chunk;
mutex m;
queue<data_chunk> data_queue;
condition_variable cond;

bool more_data_to_prepare();
int prepare_data();
void process(data_chunk data);
bool is_last_chunk(data_chunk data);

void data_preparation_thread() {
    while(more_data_to_prepare()) {
        data_chunk const data=prepare_data();
        lock_guard lk(m);
        data_queue.push(data);
        cond.notify_one();
    }
}

void data_processing_thread() {
    while(true) {
        data_chunk data;
        {
            unique_lock<mutex> lk(m);
            cond.wait(lk,[]{return !data_queue.empty();});
            data=move(data_queue.front());
            data_queue.pop();
        }
        process(data);
        if(is_last_chunk(data))
            break;
    }
}