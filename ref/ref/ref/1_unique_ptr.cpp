#ifndef EXUNIQUE_PTR_DYNAMIC_MEMORY_MNG_H
#  define EXUNIQUE_PTR_DYNAMIC_MEMORY_MNG_H

#include <iostream>

#include <memory>
using std::unique_ptr;
using std::make_unique;
using std::move;

void exUsage(){
    //////////////
    // CREATION
    //////////////
    unique_ptr<int>{};             // creates unique_ptr pointing to nullptr
    unique_ptr<int>(nullptr);      // creates unique_ptr pointing to nullptr
    unique_ptr<int> ptr1 = make_unique<int>(3); // CREATING unique_ptr
    unique_ptr      ptr2 = make_unique<int>(5); // CREATING unique_ptr (CTAD)
    
    //////////////
    // USE
    //////////////
    *ptr1; // == 3

    //////////////
    // GET RAW
    //////////////
    auto a = ptr1.get(); // get raw pointer

    //////////////
    // MOVE (transfer ownership)
    //////////////
    unique_ptr<int> ptr3 = move(ptr1); // dont use ptr1 anymore. ptr3 now owns the int
}


void exUniquePtr() {
    // Dynamic memory management

    // As with C, C++ programmers have to manage the lifetime
    // of objects explicitly (In contrast to garbage collected
    // languages like Java)

    // If memory is released too early, the program could crash
    // from trying to use an object that no longer exists in 
    // the computer’s memory

    // If memory is not released when it is no longer needed,
    // the program can run out of memory (a memory leak)

    // C++ has built-in commands to dynamically create and 
    // destroy objects, BUT YOU SHOULD NOT USE THEM!
    int* a = new int{4};  // new: creates object on heap and returns address of memory location
    delete a;             // delete: releases the memory of the thing stored at the address
    // They should be rarely called

    // Instead a “scoped ownership” model is used.
    // This is a special case of the most important idiom 
    // in C++, RAII!

    // In contrast to C, where memory management
    // is very time consuming and error-prone, C++
    // has lightweight abstractions that, when used
    // correctly, will automatically correctly
    // managed the lifetimes of the object in memory

    // The most common of these abstractions is 'unique_ptr'
    
    // Calling make_unique<T> creates an object in
    // memory on demand and returns a kind of
    // handle to the object of type unique_ptr<T>
    // that can be used to reference the object

    //////////////////////////
    // CREATE unique_ptr
    //////////////////////////
    // Create an int in memory and return an associated unique_ptr
    std::unique_ptr<int> ui = std::make_unique<int>(5);

    // unique_ptr Gives you access to the data in the object
    // When you need a reference to the object
    // managed by the unique_ptr, use the * operator
    int myInt = *ui;  // *ui returns an int...copied into myInt
    std::cout << *ui; // Prints 5

    //////////////////////////
    // UPDATING unique_ptr
    //////////////////////////
    // If you bind a unique_ptr to point to a new object,
    // it will free up the old one before it starts to
    // manage the new one
    auto ui = std::make_unique<int>(5); // *ui == 5
    ui = std::make_unique<int>(2);      // destroys 5 on the heap, now managing 2 on heap. *ui == 2
    std::cout << *ui;                   // prints 2

    ////////////////////////////////////////
    // TRANSFERING OWNERSHIP unique_ptr
    ////////////////////////////////////////
    // In our example program, we will need to
    // transfer ownership from one unique_ptr to another.
    // This is a little tricky. Assignment doesn’t work
    auto up1 = std::make_unique<int>(5);
    auto up2 = std::make_unique<int>(10);
    // up1 = up2; // Oops! Two “unique” owners; will throw exception
    // need to transfer ownership with move

    //////////////
    // MOVE 
    //////////////
    up2 = std::move(up1); // up2 is owner. Don’t use up1
    
    ////////////////////////////////////////////////////
    // GET RAW POINTER FROM SMART POINTER
    ////////////////////////////////////////////////////
    auto a = up2.get();
}

#endif