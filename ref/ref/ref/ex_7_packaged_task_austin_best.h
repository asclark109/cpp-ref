#ifndef PACKAGED_TASK_H
#  define PACKAGED_TASK_H

#include <memory>
using std::unique_ptr;
using std::make_unique;
#include <future>
using std::future;
using std::promise;
using std::function;
using std::forward;

template<typename T>
struct packaged_task;

template <typename R, typename ...Args>
class packaged_task<R(Args...)> {

public:
	template<typename Callable>
	packaged_task(Callable && func) : callable(forward<Callable>(func)) {};  // bind the lambas,function,functor, etc to a std::function

	future<R> get_future() {
		return p.get_future();
	}

	void operator()(Args... args) {
		try {
			p.set_value(callable(std::forward<Args>(args)...));
		}
		catch (...) {
			p.set_exception(std::current_exception());
		}
	}
		
private:
	promise<R> p;
	function<R(Args...)> callable;
};

#endif