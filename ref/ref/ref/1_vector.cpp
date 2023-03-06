#ifndef EXVECTOR_H
#  define EXVECTOR_H

#include <vector>
#include <iostream>

void exVECTOR() {
    /*
    The vector container in C++ is in fact a class
    template, so the compiler can build a version
    optimized for each class

    Vectors are sequence containers representing arrays that can change in size
    kind of like wrapping an array in a container

    when you remove a lot of elements from a vector, you could be using a lot of
    space in memory, so periodically or situationally use shrink_to_fit()
	*/

    // CREATE
    std::vector<int> v1 = { 1, 2, 3}; // type can be specified
    std::vector v2 = {1, 2, 3}; // or deduced also vector<int>

    std::cout << v1[1]; // 2
    v1.front(); // 1
    v1.back(); // 3
    v1.size(); // 3
    v1.capacity(); // 4 for now; how many elements it can currently hold; size == numu elements its actually holding
    v1.push_back(9); // adding to the end of the vector; this will increase the capacity from 4 to 8
    v1.push_back(9);
    v1.push_back(9);
    v1.push_back(9); // now vector is of size 8; capacity is 8;
    v1.push_back(9); // when the 9th element added, it doubles the size of the vector
    v1.pop_back(); // removes element from back of vector, and returns the elem removed
    // if we pop a lot of elements off, it will reduce the size but capacity will stay the same.
    // to decrease the capacity of the vector so that space can be freed:
    v1.shrink_to_fit(); // capacity will now shrink to the size of the vector
    
    // INSERT, ERASE
    v1.insert(v1.begin(), 5); // insert at front
    v1.insert(v1.begin() + 1, 5); // insert at 2nd spot
    v1.erase(v1.begin()); // erase element at first position.

    // LOOPS
    for (int i = 0; i < v1.size(); ++i){
        std::cout << v1[i] << std::endl;
    }

    for (auto itr = v1.begin(); itr != v1.end(); ++itr){
        std::cout << *itr << std::endl; // iterates over elements
    }
    
    for(auto i : v1)
        std::cout << i << ' '; // Prints 1 2 3
	
}

#endif