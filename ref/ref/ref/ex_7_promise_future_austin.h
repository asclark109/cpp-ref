#ifndef PROMISES_H
#  define PROMISES_H

#include <future>
#include <thread>
#include <mutex>

// simple helper class that "holds" the result of computation;
// Future and Promise have a shared_ptr to the Payload.
// Payload has a unique_ptr to the result of computation
template <class T>
struct Payload {
	std::unique_ptr<T> dataPtr;
	std::exception_ptr eptr;
};

// Future: capable of looking up the result of computation in a Payload;
// if Future::get() is called, Future::get() will block until the Payload 
// has a non-null data pointer field.
template <class T>
class Future {
public:
	Future(std::shared_ptr<std::mutex> mPtr_, std::shared_ptr<std::condition_variable> cvPtr_, std::shared_ptr<Payload<T>> payloadPtr_) 
		: mPtr(mPtr_), cvPtr(cvPtr_), payloadPtr(payloadPtr_) {};

	T get() {
		T data;
		std::unique_lock<std::mutex> lk(*mPtr);
		// wait until a result exists or an exception has been encountered (will block)
		cvPtr->wait(lk, [&] {
			return payloadPtr->dataPtr != nullptr || payloadPtr->eptr != nullptr;
		});

		// if an exception was encountered by Promise, rethrow it;
		// otherwise, a result is available, and it should be returned
		if (payloadPtr->eptr) {
			std::rethrow_exception(payloadPtr->eptr);
		}
		else { 
			return *(payloadPtr->dataPtr); // return copy of data
		}
	};
private:
	std::shared_ptr<std::mutex> mPtr; // Future shares the mutex with the Promise
	std::shared_ptr<std::condition_variable> cvPtr; // Future shares condition var with Promise so that Promise can wake up the thread sleeping from a Future::get() call
	std::shared_ptr<Payload<T>> payloadPtr; // Future shares the Payload with the Promise (so Promise can update the data, so Future can query the data)
};


// Promise: capable of storing data in a Payload variable. 
// Capable of creating Future objects that will have
// a shared_ptr to the same Payload, which they can query to obtain the data
template <class T>
class Promise {

public:
	Promise() {
		mPtr = std::make_shared<std::mutex>();
		cvPtr = std::make_shared<std::condition_variable>();
		payloadPtr = std::make_shared<Payload<T>>();
	};

	Future<T> get_future() {
		return Future(mPtr, cvPtr, payloadPtr);
	};

	// grants ability to a thread handling a Promise to communicate computational results to associated Future(s)
	void set_value(T val) { 
		{
			std::lock_guard<std::mutex> lk(*mPtr);
			payloadPtr->dataPtr = std::make_unique<T>(val);
		}
		cvPtr->notify_all();
	}

	// grants ability to a thread handling a Promise to communicate exceptions to associated Future(s)
	void set_exception(std::exception_ptr eptr) {
		{
			std::lock_guard<std::mutex> lk(*mPtr);
			payloadPtr->eptr = eptr;
		}
		cvPtr->notify_all();
	}

private:
	std::shared_ptr<std::mutex> mPtr; // Promise shares mutex with Future
	std::shared_ptr<std::condition_variable> cvPtr; // Promise shares condition var with Future
	std::shared_ptr<Payload<T>> payloadPtr; // Promise shares the Payload with the other Futures (so Promise can update the data, so Future can query the data)
	
};

#endif
