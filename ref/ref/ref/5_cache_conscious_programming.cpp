////////////////////////////////
// CACHE-CONSCIOUS PROGRAMMING
////////////////////////////////
// Accessing main memory can take a processors
// hundreds of cycles

// Therefore, processors use high-speed caches to
// maintain local copies of data

// If another processor needs to read/write that memory,
// it needs to force other processors to flush or invalidate
// any cached copies of the memory

// Since every thread reads and writes the
// counter on every increment, caching is
// useless because each processor’s cached
// value might be out-of-date

// When it modifies the counter, the computer’s
// cache coherence protocol tells all other cores
// to discard their cached counter value

////////////////////////////////////////////////////////////////////
// IMPROVE COARSE-GRAINED IMPL (LESSEN CONTENTION):
// SEPARATE THE DATA STRUCTURE INTO SECTIONS SO THAT EACH 
// THREAD HAS ITS OWN SECTION TO MANIPULATE
////////////////////////////////////////////////////////////////////

// DistributedCounter2 attempts to fix this by hashing each
// thread to a different counter

// This gives some speedup
// But it is inconsistent and not as fast as we might hope

// DistributedCounter2.h
// Create multiple "sub-counters" so that different threads are unlikely
// to use the same sub-counter, reducing contention compared to DistributedCounter1
#include<atomic>
#include<mutex>
#include<shared_mutex>
#include<map>
#include<numeric>
#include<utility>
#include<vector>
namespace mpcs {
    class DistributedCounter {
        typedef size_t value_type;

        struct bucket {
            std::shared_mutex sm;
            value_type count;
        };

        static size_t const buckets{ 128 };     // create the buckets that'll be shared accross counters
        std::vector<bucket> counts{ buckets };  // vector of buckets of size 128

    public:
    
        void operator++() {
            size_t index = std::hash<std::thread::id>()(std::this_thread::get_id()) % buckets; // get our thread hash number
            std::unique_lock ul(counts[index].sm);  // acquire unique lock on our bucket
            counts[index].count++; // increment our bucket
        }

        void operator++(int) {
            ++*this;
        }

        value_type get() {
            return std::accumulate(counts.begin(), counts.end(), (value_type)0, 
                [](auto acc, auto &x) { std::shared_lock sl(x.sm); return acc + x.count; });
        }
    };
}


// What happened?

// When data is moved from main memory to cache,
// enough data is always moved to fill a “cache line.”

// The size of a cache line varies by processor and needs to be
// looked up in the processor datasheet. A typical size would be 32
// bytes, but it varies greatly.

// As a result, if two processors are modifying data within
// 32 bytes, they are constantly forcing each other to
// invalidate their cache (“false sharing”)

// (DistributedCounter2):
// Even though it uses multiple subcounters, since they
// are stored in an array, many of them end up in the
// same cache line, which means updating a counter
// on one thread means that all of the other threads will
// have to reload their counters from main memory
// since they are in the same cache line

// This is very slow. Maybe 100x slower than accessing cache memory

//////////////////////
// FALSE SHARING
//////////////////////
// This kind of coupling of seemingly independent
// variables because they reside on the same cache
// line is known as false sharing

////////////////////////////////////////////////////////////
// ELIMINATE FALSE SHARING BY ADDING PADDING TO PUT ELEMENTS IN 
// SEPARATE CACHE LINES
////////////////////////////////////////////////////////////
// DistributedCounter4.h
// Add padding to avoid false sharing
#include<mutex>
#include<shared_mutex>
#include<map>
#include<numeric>
#include<utility>
#include<vector>
namespace mpcs {
	class DistributedCounter {
		typedef size_t value_type;

		struct bucket {
			std::shared_mutex sm;
			value_type count;
			char padding[256]; // increases the size of the struct to get it on separate cache line
		};

		static size_t const buckets{ 128 };
		std::vector<bucket> counts{ buckets };

	public:

		void operator++() {
			size_t index = std::hash<std::thread::id>()(std::this_thread::get_id()) % buckets;
			std::unique_lock ul(counts[index].sm);
			counts[index].count++;
		}

		void operator++(int) {
			++*this;
		}

		value_type get() {
			return std::accumulate(counts.begin(), counts.end(), (value_type)0,
				[](auto acc, auto &x) { std::shared_lock sl(x.sm); return acc + x.count; });
		}
	};
}

////////////////////////
// PORTABLE PADDING
////////////////////////
// C++17 introduces a portable approach
// If you keep objects further than std::hardware_destructive_interference_size,
// they “should” (i.e., implementation-defined) end up on different cache lines
// If you keep objects closer than std::hardware_constructive_interference_size, they
// “should” end up on the same cache line

////////////////////////////////////////////////////////////////////////////
//// Cache-conscious programming (Adapted from Herlihy&Shavit p. 477)
////////////////////////////////////////////////////////////////////////////

// (1) Objects or fields that are accessed independently 
//     should be aligned and padded so they end up on 
//     different cache lines.

// (2) Keep read-only data separate from data that is modified frequently.

// (3) When possible, split an object into thread-local pieces. For example, a counter
//     used for statistics could be split into an array of counters, one per thread, each
//     one residing on a different cache line. While a shared counter would cause
//     invalidation traffic, the split counter allows each thread to update its own replica
//     without causing cache coherence traffic.

// (4) If a lock protects data that is frequently modified, then keep the lock and the
//     data on distinct cache lines, so that threads trying to acquire the lock do not
//     interfere with the lock-holder’s access to the data.

// (5) If a lock protects data that is frequently uncontended, then try to keep the lock
//     and the data on the same cache lines, so that acquiring the lock will also load
//     some of the data into the cache.

// (6) If a class or struct contains a large chunk of data whose size is divisible by a
//     high power of two, consider separating it out of the class and holding it with an
//     unique_ptr to avoid the Ghostscript problem from the previous slide (see lec 5)

// (7) Use a profiling tool like VTune to identify where your cache bottlenecks are