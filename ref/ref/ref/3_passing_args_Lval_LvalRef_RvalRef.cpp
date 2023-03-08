
#include <iostream>

void funcLValue(        int i) { std::cout<<"called funcLValue";};
void funcLValueRef(     int & i) { std::cout<<"called funcLValueRef";};
void funcRValueRef(     int && i) { std::cout<<"called funcRValueRef";};
void funcLValueConstRef(int const & i) {  std::cout<<"called funcLValueConstRef";};

void exInvocations(){
    ////////////////////////////
    // FUNC ACCEPTING L VALUE
    ////////////////////////////
    // (1a) passing an L value
    int i{2};
    funcLValue(i); // legal. makes a local copy of the int that i holds in storage (i owns the storage)
    // (1b) passing an L value reference
    int& j = i;
    funcLValue(j); // legal. makes a local copy of the int that j refers to (refers to the int whose storage is managed by i)
    // (1c) passing an R value
    funcLValue(1); // legal. makes a local copy of a temporary expression (Rvalue) "1"

    ////////////////////////////
    // FUNC ACCEPTING L VALUE REFERENCE
    ////////////////////////////
    // (2a) passing an L value
    int i{2};
    funcLValueRef(i); // legal. makes a local reference variable that refers to the original int i in caller scope
    // (2b) passing an L value reference
    int& j = i;
    funcLValueRef(j); // legal. makes a local reference variable that refers to the same underlying int that j was referring to
    // (2c) passing an R value
    // funcLValueRef(1); // ILLEGAL. we can't make a reference variable to something that doesn't have its own storage (i.e. an "Rvalue"/"temporary")?

    ////////////////////////////
    // FUNC ACCEPTING R VALUE REFERENCE
    ////////////////////////////
    // (3a) passing an L value
    int i{2};
    // funcRValueRef(i); // ILLEGAL. function only knows how to work with objects it can "raid for parts"
    // (3b) passing an L value reference
    int& j = i;
    // funcRValueRef(j); // ILLEGAL. function only knows how to work with objects it can "raid for parts"
    // (3c) passing an R value
    funcRValueRef(1);       // legal. 1 is a temporary / R value
    funcRValueRef(std::move(i)); // legal. using move gives us a temporary / R value reference...signals we are allowing i to be raided for parts...function accepts things it can raid for parts. makes more sense if i is an object.

    ////////////////////////////////////////////////
    // FUNC ACCEPTING REFERENCE TO A CONST L VALUE
    ////////////////////////////////////////////////
    // (4a) passing an L value
    int i{2};
    funcLValueConstRef(i); // legal. same as (2a). working with a reference to an int it wont change
    // (4b) passing an L value reference
    int& j = i;
    funcLValueConstRef(j); // legal. same as (2b). working with a reference to an int it wont change
    // (4c) passing an R value
    funcLValueConstRef(1); // LEGAL. weird case. since the function works with a reference to an int that it won't modify
                           // then hypothetically it means the function could work with a temporary since it has no intension
                           // of modifying the temporary, which would require that the temporary have its own storage, which it doesn't
}