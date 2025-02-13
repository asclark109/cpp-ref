#include <string>
using std::string;

#include <ostream>

#include <memory>
using std::move;

namespace class_template {

// class  == default private members (fields and functions) 
// struct == default public  members (fields and functions) 

class BigClass { 
    // BigClass() {}         // default constructor (no arg constructor)
                             // implicitly generated (unless you specify a constructor)
                             // primitive fields will have garbage values unless they
                             // have defaults specified.

                             // NEVER MAKE A CONSTRUCTOR VIRTUAL!

    BigClass() = default;    // DEFAULT CONSTRUCTOR 
                             // get constructor the compiler would declare
                             // had you not given any constructors

                             // NEVER have a virtual constructor

    BigClass() = delete;     // DELETE keyword: can remove from a class

    // if constructor implemented; default constructor deleted
    // if copy constructor implemented; default copy constructor deleted
    // if copy assignment, move, move assignment, or destructor implemented, default copy constructor is deleted (assume default copy impl--copy all members--not safe)
    // if copy, copy-assign, or destructor implemented, move constructor is deleted (assumes moving impl--move all members--not safe)

    BigClass(int const & i) : i(i) {d=2.0;} ;  // CONSTRUCTOR: 
                                               // implemented constructor
                                               // adding one causes compiler
                                               // not to generate default constructor
    BigClass(int const &i, double const &d, double const &j) : i(i), d(d), j(j) {}
                                               // AGGREGATE CONSTRUCTOR:
                                               // If a class is a simple data structure
                                               // with public members, c++
                                               // considers that to be an aggregate
                                               // and generates a constructor that
                                               // takes that takes an initializer 
                                               // (simplification). invoke like so:
                                               // BigClass b = {1, 2.3, 3.4};
                                               // BigClass b = {.i=1, .d=2.3, .j=3.4};

    ~BigClass() = default;   // DESTRUCTOR: 
                             // wont usually need to write if you use RAII

    ////////////////////////////////////////////////////
    // BEST PRACTICES: Classes that are meant to be
    // inherited from should have a virtual destructor
    // (virtual by default unless you custom implement destructor
    ////////////////////////////////////////////////////

    ////////////////////////////////////////////////////
    // BEST PRACTICES: DESTRUCTORS SHOULD BE LABELED NOTHROW
    ////////////////////////////////////////////////////

    BigClass(BigClass const & s): i(s.i), d(s.d) {}; // COPY CONSTRUCTOR:
                                                     // implicitly generated
                                                     // copies all base classes and
                                                     // member like so, unless you
                                                     // implement your own in a
                                                     // custom way.

    BigClass & operator=(BigClass const & s) { 
        this->i=s.i;
        this->d=s.d;
        return *this;
    }; 
                                                    // COPY-ASSGINMENT CONSTRUCTOR:
                                                    // implicitly generated
                                                    // copies all base classes and
                                                    // members like so, unless you
                                                    // implement your own in a
                                                    // custom way.

    BigClass(BigClass && s) : i(move(s.i)), d(move(s.i)) {};
                                        // MOVE CONSTRUCTOR: 
                                        // for more efficient copying 
                                        // (or because you want to
                                        // not make an object copyable)
                                        // -- if you don't define your own
                                        // default, copy, or move constructor
                                        // (if all have default behavior)
                                        // compiler generates default move;
                                        // -- compiler generates a move constructor
                                        // moving all members and base classes.
                                        // -- compiler will use copy when it can't
                                        // move

    BigClass& operator=(BigClass && s) { i=move(s.i); d=move(s.i); return *this;};
                                        // MOVE ASSIGNMENT CONSTRUCTOR
                                        
    explicit BigClass(int i){}; // EXPLICIT keyword!

                                // controls unwanted implicit type conversions
                                // can only be used in declarations of constructors
                                // within a class declaration.

                                // e.g. normally say a function takes a BigClass
                                // object. if you pass an int, the compiler notices
                                // it can use a constructor BigClass(int i) to
                                // perform an implicit type conversion of int to
                                // BigClass. However a compiler limits itself to
                                // only being allowed to do 1 type conversion

                                // IF HOWEVER, explicit is used with this type
                                // conversion constructor, then this prevents the
                                // compiler from using the constructor for an
                                // implicit type conversion. 

    operator int() {return i;}    // TYPE CONVERSION OPERATOR:
                                  // can be used to describe how to convert
                                  // a Class to another type. 
                                  // int i = BigClass();

                                  // max of 2 user-defined
                                  // conversions will be implicitly composed:
                                  // struct A { A(int); }
                                  // A a = BigClass();    // ILL-FORMED

    double operator()(double x) const {  // FUNCTORS: overloading the operator()
        return x*x;                      // makes the class invocable
    }

    int negateNCast(double x) const {   // STATIC_CAST: mostly used to control
        return static_cast<int>(x);     // and confirm the validity of type casting
    }                                   // at compile time. static_cast works on
                                        // objects of custom classes by using the
                                        // type conversion operators defined in
                                        // the class. use DYNAMIC_CAST for polymorphism
                                        // related casting (e.g. downcasting)

    virtual void mymethod();            // mark a method virtual if you want subclasses to override it

    // virtual void superClassMethod() override final;    // use OVERRIDE to communicate you
                                                          // are intending to override a super class method
                                                          // use FINAL to communicate you do not
                                                          // want subclasses to be able to 
                                                          // override this.

    static size_t memUsed() {     // STATIC METHOD:
        return sizeof(BigClass);  // class member to be shared by all objects 
    }                             // of a class. invoke static method like:
                                  // BigClass::memUsed(); 

    static int objcount;    // STATIC FIELD:
                            // intitializing static class members
                            // Warning: For technical reasons, you may have to 
                            // initialize static data members with class types in 
                            // a separate .cpp file. This is so its memory is only
                            // allocated once, not every time the header is included
                            // in BigClass.h:
                            //    struct BigClass { static int objcount; };
                            // in BigClass.cpp:
                            //    int BigClass::objcount(1);

    // FRIEND: use the friend keyword and the name of a non-member function 
	// or other class to grant it access to the private and protected
	// members of your class. 
    // grant ostream's operator << friend level access to this class. Helpful
    // with overriding std template library classes's functions:
	friend std::ostream &operator<<(std::ostream &, BigClass bc); // FRIEND
    // here, it is then typical to define the implementation of the method out
    // side scope of the class. (see below)
	

    int i;                // private field
    double d;             // private field

    int j{0};         // field will be initialized with value when struct made.
};

// INLINE keyword: suggestion to the compiler that an inline expansion can be performed
// inlining generally increases program size, but if the function is small then it
// might actually shorten the code by removing call-linkage overhead. also could
// improves execution time. increases coupling with other modules by requiring 
// recompilation when the implementation changes.
inline std::ostream& operator<<(std::ostream &os, BigClass bc) { // INLINE METHOD
    os << bc.i;
	return os;
}

// DEFINE SYMMETRIC BINARY OPERATIONS OUTSIDE THE CLASS SO THAT
// OPERANDS ARE TREATED EQUALLY (E.G. wrt implicit type cast 
// behavior)
BigClass operator+(const BigClass &s1, const BigClass &s2);

};