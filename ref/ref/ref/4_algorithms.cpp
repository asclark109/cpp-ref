#ifndef EXALGORITHMS_H
#  define EXALGORITHMS_H

#include<string>
#include<iostream>
#include<vector>
#include<memory>
#include<algorithm>

//Check if all/any/none of the items in a container (or range) have a certain property
// -- all_of
// -- any_of
// -- none_of

auto getData() {
    std::vector<int> nums = {1,2,3,4,5,6};
    return nums;
}

void exALGORITHMS() {
    // -- copy_n
    std::vector<int> v = getData();
    copy_n(v.begin(), 5,std::ostream_iterator<int>(std::cout, "\n"));

    // -- find_if_not
    std::vector<int> v = { 1, 3, 5, 6, 7}; // Print first elt that is not odd
    std::cout << *find_if_not(v.begin(), v.end(), [](int i) { return i%2 == 1; });  

    // -- partition_copy
    std::vector<int> primes;
    std::vector<int> composites;
    std::vector<int> data = getData();
    extern bool is_prime(int i);
    partition_copy(data.begin(), data.end(), back_inserter(primes), back_inserter(composites), is_prime);

    // -- minmax
    // -- minmax_element
    // Gets both the biggest and smallest items in the range

    // -- is_heap
    // -- is_heap_until
    // -- is_sorted
    // -- is_sorted_until
    // -- partial_copy

    ////////////////////////
    // Parallel algorithms
    ////////////////////////
    // While we haven’t discussed threading yet, many
    // standard library algorithms can run in parallel
    // Just pass them a parallel execution policy as a first argument
    // sort(execution::par_unseq, v.begin(), v.end());
    // This does a parallel sort that can even (in principle) take advantage of GPUs
    // https://devblogs.microsoft.com/cppblog/using-c17-parallel-algorithms-for-better-performance/

    // C++ algorithms seem pretty powerful, what’s wrong?
    // - They have several problems that are becoming increasingly problematic
    //   as functional programming becomes more popular
    // - They can’t be composed
    //    - In our transform then accumulate problem, we had to
    //      awkwardly create an (irrelevant) intermediate vector
    //      instead of just chaining
    //    - They can’t work on infinite streams (it would take
    //      forever to create the intermediate vector)
    //    - The notation is cumbersome
    //      Why do I have to say sort(v.begin(), v.end()) instead of sort(v)?

    ////////////////////////
    // RANGES
    ////////////////////////
    // Ranges are a work in process replacement for the
    // C++ standard library algorithms that are
    // - Composable so you can feed one algorithm into another
    // - Work directly on ranges rather than iterator pairs for natural usage
    // - Lazy for efficiency because you don’t have to create
    //   intermediate containers holding all of the elements from
    //   each step
    // - Fully conceptized for improved safety and error messages
    // https://godbolt.org/z/PmtJRa
    // https://godbolt.org/z/RgHwaR
    // A limited amount of ranges got into C++20


}


#endif