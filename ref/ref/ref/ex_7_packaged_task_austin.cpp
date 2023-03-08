#ifndef PROMISE_H
#  define PROMISE_H

#include <future>
#include <thread>

template <class R, class...Args>
class BasicPackagedTask {};

template <class R, class...Args>
class BasicPackagedTask<R(Args...)> {
public:

	BasicPackagedTask(R(*fptr)(Args...)) {
		this->prom = std::promise<R>{};
		this->fptr = fptr;
	}

	std::future<R> get_future() { return prom.get_future(); };

	virtual void operator()(Args&&... args) {
		prom.set_value((*fptr)(std::forward<Args>(args)...));
	}
	
private:
	R (*fptr)(Args...);
	std::promise<R> prom;
};

#endif
