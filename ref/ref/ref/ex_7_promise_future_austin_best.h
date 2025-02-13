#ifndef PROMISE_AND_FUTURE_H
#  define PROMISE_AND_FUTURE_H

#include <memory>
using std::unique_ptr;
using std::shared_ptr;
using std::make_shared;
using std::make_unique;
#include<mutex>
#include<condition_variable>
using std::mutex;
using std::condition_variable;
using std::unique_lock;

using std::exception_ptr;

namespace austins_promise_future {

	template <typename T>
	struct shareddata{
		mutex m;
		condition_variable cv;
		unique_ptr<T> dataPtr; // defaults to nullptr? hopefully.
		unique_ptr<exception_ptr> excepPtr; // defaults to nullptr? hopefully.
	};

	template <typename T>
	class Future {
	public:
		Future(shared_ptr<shareddata<T>> dataPtr) : dataPtr(dataPtr) {}
		
		T get() {
			// sleep until data available then fetch and return it
			unique_lock<mutex> lck(shareddataPtr->m); // acquire unique lock
			auto test = [&]() {
				auto hasValue = shareddataPtr->dataPtr != nullptr;
				auto hasException = shareddataPtr->excepPtr != nullptr;
				return hasValue || hasException; };
			dataPtr->cv.wait(lck, test);        // keep sleeping until data or exception available
			auto hasValue = shareddataPtr->dataPtr != nullptr;
			auto hasException = shareddataPtr->excepPtr != nullptr;
			if hasException{
				throw shareddataPtr->(*excepPtr);
			}
			else {
				return shareddataPtr->(*dataPtr);
			}

		};
	private:
		shared_ptr<shareddata<T>> shareddataPtr;

	};

	template <typename T>
	class Promise {
	public:
		Promise() {
			this->shareddataPtr = make_shared<shareddata<T>>();
		}

		Future<T> get_future() {
			return Future<T>(shareddataPtr);
		}

		auto set_value(T value) {
			unique_lock<mutex> lck(shareddataPtr->m); // acquire unique lock
			shareddataPtr->dataPtr = make_unique<T>(value);
		};

		auto set_exception(exception_ptr excepPtr) {
			unique_lock<mutex> lck(shareddataPtr->m); // acquire unique lock
			shareddataPtr->excepPtr = make_unique<T>(excepPtr);
		};
	private:
		shared_ptr<shareddata<T>> shareddataPtr; // default constructor creates
	};


}

#endif