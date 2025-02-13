//////////////
// ATOMICS
//////////////

// C++ atomics

// Sometimes you just want a variable that you
// can read and update from multiple threads
// Using locks seems a little too complicated for that
// Especially because x86 has a built-in atomic increment
// Fortunately, C++ has a library of atomic types that can be shared between threads

// You can read an atomic with its load()
// method, write it with its store() method and
// (usually) increment or decrement it with ++ or --

// See DistributedCounter4 that uses atomics