#ifndef ASYNCH_H
#  define ASYNCH_H

#include <future>
using std::packaged_task;
using std::future;

#include <thread>
using std::thread;

template<typename Func, typename ...Args>
auto my_async(Func f, Args&&... args) { 
	packaged_task pt{f};
	future ft = pt.get_future();
	thread([pt = std::move(pt), ...args = std::forward<Args>(args)]() mutable {
		pt(args...);
	}).detach();
	return ft;

}
#endif