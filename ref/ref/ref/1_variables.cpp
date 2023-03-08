#ifndef EXVARIABLES_H
#  define EXVARIABLES_H

void exVARIABLES() {
    //////////////////////
    // SIMPLE VARIABLES
    //////////////////////
    int i = 5;

	/*
    When the program creates the variable i at
    runtime, it allocates some memory (usually on the stack)
    to hold i’s data
    
    Any expressions in the code involving i will use the data there
    */

    ////////////////////////////
    // COPYING and ASSIGNMENT
    ////////////////////////////
    // In an assignment, the object is copied
    int i = 3; 
    int j = i;  // copied!
    i = 5;      // j == 3, i == 5
    // In this example, both i and j have their own storage
    // associated with them in the running program

    ////////////////////////////
    // REFERENCES
    ////////////////////////////
    int i = 3;
    int &j = i;  // creates a reference!
    i = 5;       // j == 5, i == 5

    // The only difference between references and values
    // is that the value has its own copy of the data, and
    // the reference reuses the object it is initialized with
    // as its storage without making a copy

    // i is a variable of type int and has its own storage

    // j is of type int& (“int reference”), and does not have any
    // new storage associated with it. It just treats i’s storage as
    // its own
    
    ////////////////////////////
    // WARNING ABOUT REFERENCES
    ////////////////////////////
    // If multiple variables are referring to the same
    // object, you have to be careful that the object
    // still exists when you use it
    
    int &j = f(); // f returns a reference to f’s i,
    // so the int& j also uses that as its storage
    // However, the storage for f’s i is released when
    // f is done running, so j has bound itself to a
    // no longer existing object!
    
}

int &f() { // f is a function returning an int&
    int i = 3;
    return i;
}

#endif