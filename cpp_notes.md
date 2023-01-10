

# C++ (Overview)

Common remarks on C++:
* complicated and difficult to learn
* unsafe (can scribble over memory and crash your program)
* incoherent mashup of every other programming language

These are all true; but still, C++:
* remains the language of choice
  * ahead of Java and in 3rd place on Tiobe Language Popularity index
* most of the advanced difficult features are for writing libraries. This can make writing applications in C++ easier
than in other languages

## C++ Standards

* 1979: "C with classes" invented by Bjarne Stroustrup
* 1998: the first standard
* 2011: C++11 standard..."a whole new language"
* 2017: C++17
  * medium-sized release containing library improvements: parallel algorithms, filesystem, string_view, optional, any, variant (tagged unions). Class Template Argument Deduction
* 2020: C++20
  * major release focused on Concepts, a major rearchitecture of templates and std::format, which makes formatting no longer suck
* 2023 (expected): C++23
  * Ranges and Modules will become useful
  * std::expected is a new paradigm for error handling

## C++ gaps

* no networking
* no thread pools
* asnychronous programming broken
* no sender-receiver
* no reflection (therefore no serialization, RPC, etc)
* way too many things still require unsafe code

## C++ safety

* C++ isn't safe
  * lets you access any memory location directly by its address ("pointers"), which by definition is unsafe
  * best known security CERTs are ascribed to unsafe memory usage in C and C++
* isn't as unsafe as people think either
  * modern C++ language and best practices vastly improve the situation
* still a long way to go

## C++ is not a standard

Some things are not mentioned in the C++ standard:
* bits in an integers
* DLLs
* whether characters are signed or unsigned
  * (signed int means e.g. ranges from -2147483648, 2147483647; unsigned 32-bit int ranges from 0,4294967295)
* common saying: "there are no interesting standards-compliant programs"

This reduces portability and is fragile; to combat the issue, if you need to rely on non-standardized behavior, try to rely on "implementation-defined" rather than "undefined" behavior so at least it is defined somewhere.

## C++ characteristics

* compiled
* multiparadigm (e.g. supports object-orientation)
* lightweight abstractions (supports low-level system programming and high-level abstractions)
* statically type safe and (largely) type inferenced
* Exceptions, Expected, and RAII

## C++ Compilation

* Java, Javscript use "Just in Time" (JIT) compilation
* C++ uses __"Ahead of Time"__ compilation (other examples: C, Rust, Swift)
  * may be less convenient because it means you must compile before running it
  * but the performance is faster because teh compiler can take its time to analyze the program in depth
  * enables metaprogramming for the compiler to control its code generation

## C++ use case

* C++ is a lightweight abstraction language that strikes a balance between being good for programmers (abstract) and good for the computer (i.e. low-memory, fast, low-level)
  * unlike almost any other language, C++ allows creation of powerful abstractions that are lightweight by having all the abstraction "compiled-away" during the build using __"`templates`"__. So, there is no performance penalty associated with using/creating abstractions.
* C++ offers low-level manipulation of code and data
  * no virtual machine, manual memory management, etc
* C++ offers abstraction through C++ generics, which use compile-time computation to generate optimal code

If you want code that is:
* good for the programmer (clear consistent, abstract, and extensible libraries)
* good for the computer (great time and space performance; low-level customizability)
Then C++ is most often the right language. Many programs don't need C++; i.e., it has no equivalent of scripting or notebooks for high-level programs.

https://www.youtube.com/watch?v=X4q1OM0voO0&list=PLRAV69dS1uWSR89FRQGZ6q9BR2b44Tr9N&index=1

Called "Golang" to avoid confusion caused by searching "Go" on search engines.

Features:
- Low Latency (if you are concerned about latency; adopted by twitch)
- Garbage Collection (if you want very fast and lots of support)
- GPU (if concerned about GPU power and utilization)
- Concurrency Support (built-in support)

# C++ Compilers

Common compilers for Windows:
* `Mingw`
* `MSVC`
* `clang llvm`

Common compilers for Linux:
* `GCC`
* `clang llvm`

to see what features each compiler supports, visit https://en.cppreference.com/w/cpp/compiler_support

For a windows machine, can go here to get `clang llvm` and `Mingw`: 

Can confirm installation successful at windows cmd: https://winlibs.com/
```
C:\Users\ascla>g++ --version
g++ (MinGW-W64 x86_64-ucrt-posix-seh, built by Brecht Sanders) 12.2.0
Copyright (C) 2022 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.


C:\Users\ascla>clang++ --version
(built by Brecht Sanders) clang version 15.0.6
Target: x86_64-w64-windows-gnu
Thread model: posix
InstalledDir: C:/mingw64/bin
```
For a windows machine, download microsoft visual studio to get the `MSVC compiler`. Can confirm installation by opening the newly installed "developer command prompt for VS 2019" and querying the compiler version:

```
**********************************************************************
** Visual Studio 2019 Developer Command Prompt v16.9.3
** Copyright (c) 2021 Microsoft Corporation
**********************************************************************

C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools>cl.exe
Microsoft (R) C/C++ Optimizing Compiler Version 19.28.29913 for x86
Copyright (C) Microsoft Corporation.  All rights reserved.

usage: cl [ option... ] filename... [ /link linkoption... ]
```

https://godbolt.org/ is a pretty good online compiler that allows you to compile and run C++ code with various compilers. you can also share code snippets with others.

# running compilers and program

gcc
```
g++ -std=c++20 vector_simple_demo.cpp -o vector_simple_demo && vector_simple_demo
```

# Basics

## First program

```c++
#include <iostream>

int main(){
    std::cout << "num1" << std::endl;
    std::cout << "num2" ;
    std::cout << "num3" << std::endl;
    return 0;
}
```

`include` statement copies in a bunch of code at the top of the file before compilation. Like an import statement. The `return 0` statement tells the operating system the program exited successfully.
`iostream` is a header file that contains functions for basic I/O operations.

## Comments

* `//` for single-line comments.
* `/*` and `*/` for multi-line comments ("block comments").
* can't nest comments

## Errors

* Compile time errors
  * occurs during compilation... (e.g. missing semi-colon); causes compilation to fail. this is good.
* Runtime errors
  * logical error in your program; can cause a program to fail and crash
* Warnings
  * not serious enough to halt compilation; the compiler is telling you something about a problem that can be serious if not fixed soon. (division by 0 can actually be a warning)

## Functions

Functions have the following structure:
```c++
int addNumbers(int first, int second){
  int sum = first + second;
  return sum;
}

int main(int argc, char **argv)
{
  int first = 10;
  int second = 0;
  int sum;
  sum = addNumbers(first,second);
  std::cout << sum << std::endl;
  return 0;
}
```

## I/O

* `std::cout`: print data to console (terminal)
* `std::cin` read data from terminal
* `std::cerr` print errors to console
* `std::clog` print log messages to console

```c++
std::cout << "Hello World!" << std::endl;
std::cout << 12 << std::endl;
int age {21};
std::cout << "my age is " << age << std::endl;
// error
std::cerr << "std::cerr output: something went wrong " << age << std::endl;
// log
std::clog << "std::clog output: this is a log message " << std::endl;
```

### Output

```c++
std::cout << "Hello World!" << std::endl;
std::cout << 12 << std::endl;
int age {21};
std::cout << "my age is " << age << std::endl;
```

### Input

* use `std::cin` to get input from user
```c++
int age;
std::string name;

std::cout << "please enter your last name" << std::endl;
std::cin >> name;

std::cout << "please enter your age" << std::endl;
std::cin >> age;
```

* can chain getting input from user
```c++
int age;
std::string name;

std::cout << "please enter your last name and age, separated by spaced" << std::endl;
std::cin >> name >> age;
```

* can read a line of text from console like so
```c++
std::string full_name;
std::cout << "please enter your full name" << std::endl;
std::getline(std::cin, full_name);
```

### C++ program execution model

https://www.youtube.com/watch?v=8jLOx1hD3_o
jump to 02:49:57

### C++ Core Language vs Standard Library vs STL

* __Core Features__: core building block that makes up the C++ language; for example, how to define variables, the rules that make up how you can define and use functions, the rules about what you can and cannot do in C++, etc.. 
  * e.g. how functions are written, the built-in types
* __Standard Library__: a set of ready-to-use highly specialized components that we can use in our programs. e.g. `iostream`, `string`.
* __STL__: highly specialized part of the C++ standard library. collection of container types.

# Variables and Data Types

Common types
* `int`
* `double`
* `float`
* `char`
* `bool`
* `void` (represents a typeless type)
* `auto` (not a type; a keyword to deduce other types)

All data is stored in e.g. 32 bit wide (or 64 bit wide) registers. So the question is, how are ints, decimals, strings, etc represented in these registers.

a 32 bit wide register has 4 sections of 8 bits, which are called `bytes`.

## Number systems

Number systems transform data from forms readable to humans (e.g. `2`, `20.3`, `"Steve"`) into forms convenient for computers

* __base 10__:
  * `2371 = 2*10^3 + 3*10^2 + 7*10^1 + 1*10^0`
* __base 2 (binary)__:
  * `100101 = 1*2^5 + 0*10^4 + 0*2^3 + 1*2^2 + 0*2^1 + 1*2^0`

Generally, if we have `n` binary digits we can use to store 0's and 1's, then we can represent numbers from 0 all the way up to `2^n-1`.

For reference:
*  8 digits -> 1 byte  -> 0~255
* 16 digits -> 2 bytes -> 0~65535
* 32 digits -> 4 bytes -> 0~34359738367
* 64 digits -> 8 bytes -> 0~18446744073709551615

* __Hexadecimal system__: technique we use to shorten the length of a binary number. take a number and split it into groups of 4 bits:
  * 0000 -> 0 -> 0
  * 0001 -> 1 -> 1
  * 0010 -> 2 -> 2
  * 0011 -> 3 -> 3
  * 0100 -> 4 -> 4
  * 0101 -> 5 -> 5
  * 0110 -> 6 -> 6
  * 0111 -> 7 -> 7
  * 1000 -> 8 -> 8
  * 1001 -> 9 -> 9
  * 1010 -> 10 -> A
  * 1011 -> 11 -> B
  * 1100 -> 12 -> C
  * 1101 -> 13 -> D
  * 1110 -> 14 -> E
  * 1111 -> 15 -> F

Example: huge number in hexadecimal: `0x 6E30F13F`. We use `0x` in front to mean it is a hexadecimal number Each character represents 0-15 in base 10, which requires 4 bits in binary 0000-1111. So, rather than represent the large number as a 32 bit binary number, we can display it as a hexadecimal number and use fewer digits.

There also exists the seldom used __Octal system__, which groups numbers into 3 bits. Example: `0 15614170477`. `0` represents octal number system.

To represent numbers in C++ using various number systems, do it like so:
```c++
int num1 = 15; //15 in decimal
int num2 = 017; //15 in octal
int num3 = 0x0f; //15 in hexadecimal
int num4 = 0b00001111; //15 in binary - doable since C++14
```

In summary, hexadecimal system makes it a little easier for humans to handle streams of data with 1's and 0's. Octal system has the same goal but is seldom used anymore.

## basics

__variable__ a named piece of memory that you use to store specific types of data
* must start with lowercase letter or underscore
* are case sensitive


## braced variable initialization

initializing a variable has the form:
```c++
typename variable_name {intializer_value};
```

```c++
// compiler will put in garbage value
int elephant_count; // declare a variable
int elephant_count{}; // declares and initializes to 0
int elephant_count{10}; // declares and initializes to 10
int elephant_count{dog_count + cat_count}; // initializes with expression
int elephant_count{2.9}; // 2.9 is of type double, with wider range than int. will yield int.ERROR or WARNING
```

## functional variable initialization

```c++
int apple_count(5);
int orange_count(10);
int fruit_count (apple_count + orange_count);
int bad_initialization (doesnt_exist3 + doesnt_exist4);
// information loss. less safe than braced initializers.
int narrowing_conversion_functional (2.9); // implicit conversion; will happen silently. curly braces {} are preferred
```

## variable assignment initilization

```c++
int bike_count = 2;
int truck_count = 7;
int vehicle_count = bike_count + truck_count;
int narrowing_conversion_assignment = 2.9;
```

## size of a type in memory

Query the size of a type in memory with
```c++
std::cout << "sizeof int : " << sizeof(int) << std::endl;
std::cout << "sizeof int : " << sizeof(truck_count) << std::endl;
```

## int

* typically occupies 4 bytes (32-bits) or more in memory

# Variables, Basic Data Types, basic I/O

There are two steps in variable creation. __declaration__ and __assignment__
* __declaration__: giving it a name and type
* __initialization__: giving it a value

* `int`: defines a numeric value holding whole numbers
* `float`: defines a numeric value with floating decimal points
* `bool`
* `string`: (double quotation marks `""`); not built in by default. include with `<string>`
* `char`: data type designed for the storage of a single character (single quotation marks `''`)

```c++
// integers (whole numbers)
int x; // declaration
x = 5; // assignment
int x,y; // multi line declaration
int y = 6;
int sum = x + y;
int days = 7.5; // leads to truncation

// double (number including decimal)
double price = 10.99;
double gpa = 2.5;

// char (single character)
char grade = 'A';
char initial = 'B';
char letters = 'BC'; // leads to overflow error. chars can only store one letter

// boolan (true or false)
bool student = true;
bool power = true;
bool forSale = true;

// string (object that represents a sequence of text)
std::string name = "bro";
std::string day = "friday";
std::string food = "pizza";

std::cout << "hello " << name << std::endl;
```

boilerplate handling multiple input from user may be errors:
```c++
int n, x;
cin >> n; // if n cannot be interpretted as an int there will be an error;
cout << n;
cin.clear(); // clears the failure from console input stream; however, does not remove the text error typed in to the console
cin.ignore(1000, '\n'); // (up to) 1000 characters to ignore; to ignore the characters typed in
cin >> x;
cout << x;
```

# Naming Conventions

variables:
* __camelCase__ is the preferred convention (`myJob`)
* __snake_case__ less accepted (`my_job`)

# `const` keyword

* `const` keyword specifies that a variable's value is constant
* tells the compiler to prevent anything from modifying it (read-only)
* frequently the variable is written in `ALL_CAPS`

```c++
int main (){
  const int LIGHT_SPEED = 300000000
  const double PI = 3.14159;
  double radius = 10;
  double circumference = 2 * pi * radius;
}
```

# Namespace

A __`Namespace`__ provides a solution for preventing name conflicts in large projects. Each entity needs a unique name. A namespace allows for identically named entitties as long as the namespaces are different.
* declarative region that provides a scope to the identifiers (the names of types, functions, variables, etc) inside it.

```c++
#include <iostream>

int main() {
  int x = 0;
  int x = 1; // leads to compile time error
}
```

creating and using namespaces
```c++
namespace first{ // creates a namespace
  int x = 1;
}

namespace second{ // creates a namespace
  int x = 2;
}

int main() {
  int x = 0;
  std::cout << first::x; // refer to x in the 'first' namespace
  std::cout << second::x; // refer to x in the 'first' namespace
}
```

using namespaces
```c++
namespace first{ // creates a namespace
  int x = 1;
}

namespace second{ // creates a namespace
  int x = 2;
}

int main() {
  using namespace first; // an entity without a namespace will be assumed to be in the 'first' namespace
  std::cout << x; // 1
  std::cout << second::x; // 2
}
```

some people include the statement `using namespace std` to save typing, but it is generally not recommended since the namespace includes many variables and you don't want to overwrite such variables.

# Typedef and Type-Aliases

__`Typedef`__: reserved keyword used to create an additional name (alias) for another data type. It is a new identifier for an existing type, and it helps with readability and reducing typos. Like a nickname

Example: you might have a really long data type like `std::vector<std::pair<std::string,int>>`, and you want to create an alias for it so it is easier to reference.

* create an alias with `typedef type newAliasName;`
* it is common to end the new alias name with `_t`
```c++
#include <iostream>
#include <vector>

typedef std::vector<std::pair<std::string,int>> pairlist_t;
typedef std::string text_t;
typedef int number_t;

int main() {
  text_t firstName = "bro"; // behaves exactly like a string
  number_t age = 21; // behaves exactly like a string
  return 0;
}
```

Instead of using _`typedef`_, it is recommended to use the `using` keyword:
* this is because it is more suitable for use in templates (later)
```c++
#include <iostream>
#include <vector>

using pairlist_t = std::vector<std::pair<std::string,int>>;
using text_t = std::string;
using number_t = int;

int main() {
  text_t firstName = "bro"; // behaves exactly like a string
  number_t age = 21; // behaves exactly like a string
  return 0;
}
```

# arithmetic operators

* `+ - * /`
* can use compound operators like `+=`, `-=`, `*=`, `/=`, `var--`, `--var`

```c++
#include <iostream>

int main(){
  int students = 20;
  std::cout << students;

  students = students + 2;
  students+=2;
  students++; // increment by 1

  students = students - 1;
  students-=1;
  students--; // decrement by 1

  students = students * 2;
  students*=2;

  students = students / 2;
  students/=2; // dividing integers leads to truncation

  int remainder = students % 3; // remainder when dividing by 3  
}
```

# Type conversion

type conversion is the conversion of a value of one data type to another
* implicit conversion is conversion that occurs automatically
* explicit conversion is conversion that is done by programmer

```c++
int main(){
  int x = 3.14; // implicit conversion; is 3;
  int x = (int) 3.14 // explicit type conversion; is 3;

  char x = 100; // implicitly convert 100 to char; ASCII table indicates this is 'd'
  char x = (char) 100; // explicit

  // why is this useful? may need to do inline type conversion
  int correct = 8;
  int questions = 10;
  double score = correct/(double)questions * 100;
  std::cout << score << "%";
}
```

# basic I/O

* use `cout` and  `<<` (insertion operator) to direct to std out.
* use `cin` and `>>` (extraction operator) to get from std in.

```c++
int main()
{
  std::string name;
  int age;

  // obtain string from user (no spaces)
  std::cout << "what's your name?: ";
  std::cin >> name;

  // obtain int from user
  std::cout << "what's your age?: ";
  std::cin >> age;

  // obtain strings from user (with spaces)
  std::getline(std::cin >> std::ws,name); // puts result into name
  // >> std::ws will remove any new line characters or white spaces before any user input

  std::cout << "hello " << name << ". you are " << age << " years old.";
}
```

# useful math functions

* `std::max()`
* `std::mix()`
* `pow()` from `<cmath>`
* `sqrt()` from `<cmath>`
* `abs()` from `<cmath>`
* `round()` from `<cmath>`
* `ceil()` from `<cmath>`
* `floor()` from `<cmath>`


```c++
#include <iostream>
#include <cmath>

int main()
{
  double x = 3;
  double y = 4;
  double smallest;
  double largest;
  double z;
  largest = std::max(x,y);
  smallest = std::min(x,y);
  z = pow(2,3); // 2^3
  z = sqrt(9); // 3
  z = abs(-3); // 3
  z = round(3.14); // 3
  z = ceil(3.14); // 4
  z = floor(3.14); // 3
}
```

# conditional logic 


## `if` statements

if statements have structure:
```c++
if(condition){
  statements..
}
```

if-else if-else statements have structure:
```c++
if(condition){
  statements..
}
else if(age < 0){
  statements..
}
else {
  statements..
}
```

```c++
if(age>=18){
  std::cout << "welcome to the site!";
}
else if (age < 0){
  std::cout << "you have not been born yet";
}
else {
  std::cout << "you are not old enough to enter!";
}
```

## `switch` statements

The switch statement shortens code involving many if statements
```c++
switch(month){
  case 1:
    std::cout << "it is january";
    break;
  case 2:
    std::cout << "it is feburary";
    break;
  //...
  default:
    std::cout << "Please enter in only numbers (1-12)";
}
```

```c++
char grade;

switch(grade){
  case 'A':
    std::cout << "you did well!";
    break;
  case 'B':
    std::cout << "you did good";
    break;
  //...
  default:
    std::cout << "Please only enter a letter grade (A-F)";
}
```

# Ternary Operator

__ternary operator__ shortened notation for an if-else statement
* has the form `condition ? expression1 : expression2;`

```c++
char grade = "A"
grade == "A" ? std::cout << "great job!" : std::cout << "do better."

// w bools
bool hungry = true;
hungry ? std::cout << "you are hungry" : std::cout << "you are full";

// can also do
std::cout << (hungry ? "you are hungry" : "you are full");
```

# Logical operators

* `&&`: and
* `||`: or
* `!`: not

```c++
if(temp > 0 && temp < 30){
  std::cout << "temperature is good!"
}
else {
  std::cout << "the temp is bad"
}
```

# Useful string methods

* `string.length()` 
* `string.size()` does same thing as length?
* `string.empty()` returns true if length of string is 0
* `string.clear()` 'empties' a string to the empty string
* `string.append("apple")` appends a string on the end of another string
* `string.at(idx)` reutrns the character at position in string
* `string.insert(idx,"apple")` inserts a string at a position in string
* `string.find("a")` finds the index of the first occurence of the substring
* `string.erase(0,3)` eliminates the characters between the first index (inclusive) and the last index (exclusive)
* when accessing a specific letter in a string with indexing, it must be a char
  * `char letter = myStr[2];`

```c++
std::string name;
std::cout << "enter your name: ";
std::getline(std::cin,name);

if (name.length() > 12){
  std::cout << "your name is too long";
}
```

# while loop

```c++
while(condition){
  // statements...
}
```

# do while loop

```c++
do {
  // statements...
}
while(condition);
```

# for loop

```c++
for(int i = 1; i <= 3; i++){
  std::cout << "happy new year!\n";
}

// can count by 2
for(int i = 1; i <= 3; i+=2){
  std::cout << "happy new year!\n";
}

// can count down
for(int i = 10; i >= 3; i--){
  std::cout << "happy new year!\n";
}
```

# break, continue

* `break` will break out of the nearest loop
* `continue` will skip the current iteration of nearest loop

# random numbers

for pseudo-random numbers, use `srand`
```c++
srand(time(NULL)); // uses current calendar time as the seed
int num = rand() % 6; // rand() generates number between [0, 32767]
// ^ gives number between 0 and 5
```

# user-defined functions

* has the form `returntype functionname(type arg,...){}`
```c++
void happyBirthday(){
  std::cout << "happy birthday!\n";
}
```

if the function is defined after the entrypoint function `main()`, there will be a compile-time error because the compiler works linearly through the program. To combat this, you can declare the function at the top of the file and then define it later.

```c++
#include <iostream>

void happyBirthday(std::string name); // function declaration

int main()
{
  std::string name = "bro";
  happyBirthday(name);
  return 0;
}

void happyBirthday(std::string name){ // function definition
  std::cout << "happy birthday " << name << "!\n";
}
```

# Return keyword

```c++

std::string concatStrings(std::string string1, std::string string2){
  return string1 + " " + string2;
}

int main(){
  std::string first = "bro";
  std::string last = "code";
  std::string fullName = concatStrings(first,last);
}
```

# function overloading

* this is when you have multiple functions with the same name but different parameters, and the compiler interprets at compilation based on types which function to call
* a function's __signature__ encompasses its function name and all its function arguments.

```c++
void bakePizza(){
  std::cout << "here is your pizza!\n";
}
void bakePizza(std::string topping1){
  std::cout << "here is your " << topping1 << " pizza!\n";
}
void bakePizza(std::string topping2, std::string topping2){
  std::cout << "here is your " << topping1 << ", " << topping2 << " pizza!\n";
}
```

# function scope

you should avoid using global variables, but you can make them by declaring them outside all the functions:
```c++

int myNum = 3; // a global variable; can be referenced in functions

void printNum();

int main()
{
  printNum();
  std::cout << myNum; 
  return 0;
}

void printNum(){
  std::cout << myNum;
}
```

avoid using global variables because
* they pollute the global namespace
* increase the complexity of code

when local and global variables with the same name exist, you can use the __scope resolution operator__ `::`
* precede the variable with `namespace::`
* to reference a global variable, precede the variable with just `::`

```c++
int x = 1 // global variable in global namespace

int main(){
  int x = 2; // local variable
  thermodynamics::x // refers to variable in 'thermodynamics' namespace
  ::x // refers to variable in global namespace; 1
  x // refers to local variable; 2
}
```

# arrays

data structure that can hold multiple values, which can be accessed with an index
* can declare and initialize with starting values
* can declare (must define size) and then define values later.
* NOTE: when an array is passed to a function, you only need to pass the name of the array, but it "decays" into a pointer; the function e.g. no longer knows the size of the array, so it should be passed as an additional argument so that the function can e.g. iterate over the array
* downside of an array is that they are statically sized
* declare/intialize like:
  * `type arr[size];` (`int arr[3];`)
  * `type arr[] = literalarray;` (`int arr[] = {2,3,4};`)
* getting the size of an array is not so trivial
  * to get the size, use `sizeof()`, which returns the bytes taken up by array
    * `size = sizeof(arr)/sizeof(arr[0]);`
    * `size = sizeof(arr)/sizeof(elemtype);`

```c++
std::string cars[] = {"corvette", "mustang", "camry"};
std::cout << cars << "\n"; // prints 0xf4bddff630. the memory address
std::cout << cars[0]; // prints "corvette"
cars[0] = "camaro";

// declare first, initialize values later, but must include size
std::string cars[3]; // sets size to 3
```

# sizeof() operator

`sizeof()` returns the size in bytes of a: variable, data type, class, object, etc.

* `char` typically occupied by 1 byte of memory
* can determine the size of an array with:
```c++
char grades[] = {'A','B','C','D','F'};
std::cout << sizeof(grades)/sizeof(char); // prints out 5
```

# iterate over an array (`sizeof()`)

using `sizeof()`
```c++
char grades[] = {'A','B','C','D','F'};

for(int i = 0; i < sizeof(grades)/sizeof(char); i++){
  std::cout << grades[i] << '\n';
}
```

# for each loop

* less syntax, but less flexible version of the for-loop
```c++
char lettergrades[] = {'A','B','C','D','F'};
for(char letter : lettergrades) {
  std::cout << student << '\n';
}

int grades[] = {65,72,81,93};
for(int grade : grades) {
  std::cout << grade << '\n';
}
```

# `fill()`

`fill()` fills a range of elements with a specified value
* usage `fill(begin, end, value)`
  * `begin` beginning address of a data structure
  * `end` ending address of a data structure

```c++
const int SIZE = 100;
std::string foods[SIZE];
fill(foods, foods + SIZE/2, "pizza"); // fill first half with pizza
fill(foods + SIZE/2, foods + SIZE, "burger"); // second half with burger
```

# multi-dimensional array

* declared with `type name[rowSize][colSize];`
* `rowSize` optional
```c++
std::string cars[3][3]; // row size, column size
std::string cars[][3];
std::string cars[][3] = {{"mustang", "escape","f-150"},
  {"corvettee", "equinox","silverado"},
  {"challenger", "durango","ram 1500"}};

int rows = sizeof(cars)/sizeof(cars[0]);
int columns = sizeof(cars[0])/sizeof(cars[0][0]);

// iterates over inner arrays (will print the memory addresses)
for(int i = 0; i < rows; i++){
  std::cout << cars[i] << '\n';
  // 0xf4861ffa90
  // 0xf4861ffaf0
  // 0xf4861ffb50
  for(int j = 0; j < columns; j++){
    std::cout << cars[i][j] << " ";
  }
}

// e.g.
std::string questions[] = {"1. askdfajlsdk?",
  "2. askdfajlsdk?",
  "3. askdfajlsdk?",
  "4. askdfajlsdk?"};

std::string options[][4] = {
  {"A. dfs", "B. asd", "C. fds", "D. dfs"},
  {"A. dfs", "B. asd", "C. fds", "D. dfs"},
  {"A. dfs", "B. asd", "C. fds", "D. dfs"},
  {"A. dfs", "B. asd", "C. fds", "D. dfs"}
};
```

# Memory Address

__memory address__: location in memory where data is stored
* can be accessed wtih `&` (address-of operator)

```c++
std::string name = "bro";
int age = 21;
bool student = true;

std::cout << &name << '\n';    // 0xbd8a1ff600 --> 814066169344
std::cout << &age << '\n';     // 0xbd8a1ff5fc --> 814066169340 (gap of 4 memory addresses w/ above)
std::cout << &student << '\n'; // 0xbd8a1ff5fb --> 814066169339 (gap of 1 memory address w/ above; bool only take up one byte of memory)
```
* integers (`int`) takeup 4 bytes of memory typically
* booleans (`bool`) takeup 1 byte of memory

# pass by value, pass by reference

* always try to pass by reference unless you have a good reason to pass by value.

```c++
int main()
{
  std::string x = "kool-aid";
  std::string y = "water";
  swap(x,y); // will make copies of the two above strings (passed by value).
  // the values of x and y in this scope have not been swapped. 
  swapPtr(x,y); // will make copies of the addresses (passed by reference).
  // the values of x and y in this scope have HAVE been swapped. 
  
}

void swap(std::string x, std::string y){
  std::string temp;
  temp = x;
  x = y;
  y = temp;
}

void swapPtr(std::string &x, std::string &y){
  std::string temp;
  temp = x;
  x = y;
  y = temp;
}

```

# `const` keyword

* `const` in a variable declaration ensures that the variable will not be mutated (read-only)
* can precede function parameters with the `const` to ensure the body of the function does not mutate the function arguments:
```c++

void printInfo(std::string name, int age); // add const keywords to display intent

void printInfo(std::string name, int age){
  name = " " // programmer can do this, which we may not want
  age = 0; // programmer can do this, which we may not want
  std::cout << name << '\n';
  std::cout << age << '\n';
}

void printInfo(const std::string name, const int age); // add const keywords to display intent

void printInfo(const std::string name, const int age){
  name = " " // will throw error
  age = 0; // will throw error
  std::cout << name << '\n';
  std::cout << age << '\n';
}
```

* it is a VERY good idea to add const keywords to function parameters if the parameters are pointers to objects; this helps ensure a function does not mutate an object that belongs in the calling scope.
```c++
void printInfo(const std::string &name, const int &age); // add const keywords to display intent

void printInfo(const std::string &name, const int &age){
  std::cout << name << '\n';
  std::cout << age << '\n';
}
```

* `const` keyword is useful for __references__ (so no one can change the value at that reference)
* `const` keyword is useful for __pointers__ (so no one can change the address of where a pointer is pointing to)

# references

* __Reference__: is kind of an "operator" that can "calculate/find" memory address of a variable

* __alias__: name that refers to a previously defined type
* __reference__: reference datatype that is less powerful but safer than the pointer type inherited from C
  * `int a = 2; int &b = a;` ("b is a reference to a")
    * if we modify `b`, we will also modify `a`; if we modify `a`, we will also modify `b`
  * `int a = 2; int b = a;`
    * this will make a copy of whatever `a` is storing and it will store that in the variable `b`

```c++
int a = 2;  // a --> [   2   ]
int &b = a; // b points to a: b --> [   2   ]
int &c = b; // c points to a: c --> [   2   ]
```

* to access the memory address that these references are pointing to:
```c++
int a = 2;  // a --> [   2   ]
int &b = a; // b points to a: b --> [   2   ]
&a // 0x61feb8
&b // 0x61feb8

int a = 2;  // a --> [   2   ] 
int b = a;  // b --> [   2   ] (copy)
&a // 0x61feb8
&b // 0x61febc
```

* to create a reference, you MUST initialize it
  * `bool &y` illegal; must declare and initialize at the same time
  * `bool &y = x;` legal
  * can't initialize with null: `bool &y = NULL`

# pointers

__pointer__: variable that stores a memory address of another variable
* sometimes, it's easier to work with an address
* `&` address-of operator (returns the memory address to which a reference refers to)
* `*` dereference operator (returns the value at the memory address)

* so, _we save the address found by "address-of" operator in a special type of variable called a pointer_.
* create a pointer with `type *ptrname`
  * `int *z = &x;` 
    * use the "address-of" operator to get the memory address and we store it in a pointer variable.


```c++
std::string name = "bro";
std::string *pName = &name;
std::cout << pName << '\n'; // 0xb15fbff760
std::cout << *pName << '\n'; // accesses the value at the address stored in the pointer; "bro"

int age = 21;
int *pAge = &age;
std::cout << *pAge << '\n'; // accesses the value at the address that's stored within the pointer; "21"

// array of strings
std::string freePizzas[5] = {"p1","p2","p3","p4","p5"};
std::string *pFreePizzas = freePizzas; // don't need to use the address-of operator because freePizzas is already a pointer
```

# null pointers

`Null` value is a special value that means something has no value
* when a pointer is holder a null value, that pointer is not pointer to anything ("null pointer")
* `nullptr` keyword that represents a null pointer literal
* null pointers are helpful when determining if an address was successfully assigned to a pointer
* when using pointers, be careful your code isn't dereferencing null or pointing to free memory;
this will cause undefined behavior

* if we create a pointer but don't assign it a value, we don't know where it points to. for good practice it would be good to know it doesn't point anywhere:
```c++
int *pointer = nullptr;
// ...
int x = 123;
pointer = &x;
```

* dereferencing a null pointer can lead to undefined behavior:
```c++
int *pointer = nullptr;
*pointer; // attempting to dereference a null pointer
```

* you can check to see if a pointer
```c++
int *pointer = nullptr;
int x = 123;
pointer = &x;
if(pointer == nullptr){
  std::cout << "address was not assigned"
}
else {
  std::cout << "address was assigned!"
  std::cout << *pointer
}
```

# dynamic memory

__dynamic memory__ is memory that is allocated after the program is already compiled and running
* use the `new` operator to allocate memory in the heap rather than the stack
* useful when we don't know howm uch memory we will need. makes programs more flexible.
* to create a variable to be stored on the heap, use the expression `new datatype`
  * `new` will return an address
* whenever you use the `new` operator, it is expected you also use the `delete` operator to remove that space (which frees up the memory at this address); if you do not
  * to delete (free up memory from) an array, use `delete[] arrayName`

dynamic memory is allocated on the __heap__, rather than the __stack__.

```c++
int main () {
  int *pNum = NULL; // common practice when initializing a pointer and not ready to assing a value
  pNum = new int; // new operator will allocate enough space on the heap for 1 int and return the address
  *pNum = 21;

  std::cout << "address: " << pNum << "\n"; //0x217247119b0
  std::cout << "value: " << *pNum << "\n"; //21

  delete pNum; // HIGHLY ENCOURAGED, FROWNED UPON IF YOU DO NOT DO THIS

  // other ex:
  char *pGrades = NULL;
  int size;
  std::cout << "how many grades to enter in?: ";
  std::cin >> size;
  pGrades = new char[size];
  for (int i = 0; i < size; i++){
    std::cout << "Enter grade #" << i + 1 << ": ";
    std::cin >> pGrades[i]
  }
  for (int i = 0; i < size; i++){ // display
    std::cout << pGrades[i] << " ";
  }
  
  delete[] pGrades;
}
```

# function templates

`function templates` describe what a function looks like
* allows you to generate as many overloaded functions as needed, each using different data types

example: you may want a function you can apply to many different data types. It would be cumbersome to write each function signature needed.
```c++
int max(int x, int y){
  return (x>y) ? x : y;
}

double max(double x, double y){
  return (x>y) ? x : y;
}

int main(){
  std::cout << max(1,2) << '\n';
  return 0;
}
```

This is remedied with a function template. In `C++20`:
```c++
auto max(auto x, auto y){
  return (x>y) ? x : y;
}

int main(){
  std::cout << max(1,2) << '\n';
  return 0;
}
```

In older C++ verisons:
```c++
template <typename T> // template parameter declaration
T max(T x, T y){ // function template definition: will work with many data types
  return (x>y) ? x : y;
}

int main(){
  std::cout << max(1,2) << '\n';
  return 0;
}
```

* Note: problem with the above code is that it only works with two parameters of the same data type. what if you wanted to mix and match types--like find the max of an integer or double?
```c++
template <typename T, typename U> // template parameter declaration (T, U, X, ...)
T max(T x, U y){ // function template definition: will work with many data types
  return (x>y) ? x : y;
}

int main(){
  std::cout << max(1,2) << '\n';
  return 0;
}
```

There's still one more problem, the return type is conditional (either returns type `T` or `U`);
* using the keyword `auto`, the compiler will deduce what the return type should be.

# struct

__`struct`__ a structure that groups related variables under one name
* can contain many different data types (string, int, bool, double,...)
* variables in a struct are known as _"members"_
* members can be accessed with `.`-- the _"Class Member Access Operator"_
* made with form: `struct student{}`

```c++
// create a struct with 3 members
struct student{
  std::string name;
  double gpa;
  bool enrolled = true; // set a default value; then you won't need to explicitly state that
}; // end struct with semi-colon!

int main()
{
  student student1; // declare
  student1.name = "Spongebob";
  student1.gpa = 3.2;
  student1.enrolled = true;

  student student2;
  student1.name = "Patrick";
  student1.gpa = 2.1;
  student1.enrolled = true;

  student student3;
  student1.name = "Squidward";
  student1.gpa = 1.5;
  student1.enrolled = false;
}
```

# passing structs as arguments

* structs are passed by value, rather than by reference
* if you pass a struct as an argument, you create a copy of the original struct.
* if instead the parameter to the function is a pointer to a struct, then, you only create a copy of the address

```c++
struct Car{
std::string model;
int year
std::string color;
};

void printCar(Car &car);
void paintCar(Car &car);

int main(){
  Car car1;
  Car car2;

  car1.model = "mustang";
  car1.year = 2023;
  car1.color = "red";
  car2.model = "corvette";
  car2.year = 2024;
  car2.color = "blue";

  return 0;
}

void printCar(Car &car){
  std::cout << car.model << '\n';
  std::cout << car.year << '\n';
  std::cout << car.color << '\n';
}

void paintCar(Car &car, std::string color){
  car.color = color;
}
```

# enums

__enums__: user-defined data type that consists of paired named-integer constants
* good if you have a set of potential options
* declare enums at the top of the program with the `enum` keyword
* if you don't assign values manually to enums, then implicitly 0,1,2,... will be assigned

```c++
enum Day {sunday = 0, monday = 1, tuesday = 2, wednesday = 3,
  thursday = 4, friday = 5, saturday = 6};

int main(){
  switch(today){
    case sunday: std::cout << "it is sunday!\n";
      break;
    default: std::cout << "it is NOT sunday!\n";
      break;
  }
}
```

# Object-Oriented Programming

* `class` is similar but different than a `struct`
* objects can perform methods (invoke with `object.method()`)
* any methods or attributes defined without a `public` or `private` header are `private` by default
* can also use the `protected` keyword (like private, but CAN be accessed by a subclass; allows subclass to be able to access parent class variable)

```c++
class Human{
  public: // public access modifier. publically accessible attributes and methods here
    std::string name; // declared public attribute
    std::string occupation;
    int age = 21; // can define default attribute

    // public methods
    void eat(){
      std::cout << "This person is eating";
    }
    void drink(){
      std::cout << "This person is drinking";
    }
    void sleep(){
      std::cout << "This person is sleeping";
    }
}

int main(){
  // create (instantiate) a human
  Human human1;
  human1.name = "Rick";
  human1.occupation = "scientist";
  human1.age = 70;
}
```

# Constructor

__Constructor__: special method that is automatically called when an object is instantiated
* useful for assigning values to attributes as arguments
* behind the scenes there exists a constructor if you have not defined one, but you can manually create your own
* constructor has the same name as the class

```c++
class Student{
  public:
    std::string name;
    int age;
    double gpa;

  Student(std::string name, int age, double gpa){ // constructor
    this->name = name; // only need 'this->' if the attribute names are 
    this->age = age;   // the same as the parameter names for constructor
    this->gpa = gpa;
  }

  // OR
  Student(std::string x, int y, double z){ // constructor
    name = x;
    age = y;
    gpa = z;
  }
}

int main(){
  Student student1("Sponge",25,3.2);
  std::cout << student1.name << '\n';
}fs
```

# Overloading Constructors

can have multiple constructors with the same name but different parameters
* allows for varying arguments when instantiating an object

```c++
class Pizza{
  public:
    std::string topping1;
    std::string topping2;

  Pizza(){

  }

  Pizza(std::string topping1){
    this->topping1 = topping1;
  }

  Pizza(std::string topping1, std::string topping1){
    this->topping1 = topping1;
    this->topping2 = topping2;
  }
}

int main() {
  Pizza pizza1("pepperoni");
  Pizza pizza2("mushrooms","peppers");
  Pizza pizza2;
}

```

# Getters, Setters

* allows you to make a private attribute readable and writeable

```c++
class Stove {
  private:
    int temperature = 0; // private; not directly accessible outside class

  public:

    Stove(int temp){
      setTemperature(temp);
    }

    int getTemperature(){
      return temperature;
    }

    void setTemperature(int temp){
      if(temp<0){
        this->temperature = 0;
      }
      else {
        this->temperature = temp;
      }
    }  
}

int main() {
  Stove stove;
  // stove.temperature = 10000;
  stove.getTemperature();
}
```

# inheritance

```c++
class Animal{
  public:
    bool alive = true;

    void eat(){
      std::cou  t << "this animal is eating\n";
    }
}

class Dog : public Animal {
  public:
    void bark{
      std::cout << "woof!\n";
    }
}

class Cat : public Animal {
  public:
    void meow{
      std::cout << "meow!\n";
    }
}

int main() {
  Dog dog;
  Cat dog;
  std::cout << dog.alive;
  dog.bark();
  cat.meow();
  return 0;
}
```

calling super class constructor within subclass constructor
```c++
class Employee {
  private:
    string Name;
    string Company;
    int Age;

  public:
    Employee(string Name, string Company, int Age){
      this->Name = Name;
      this->Company = Company;
      this->Age = Age;
    }

    void IntroduceYourself() {
      std::cout << "my name is " << Name << std::endl;
    }

    void AskForPromotion() {
      std::cout << "may I have a promotion?" << std::endl;
    }
}

// inheritence is private by default
class Developer : Employee { // this causes inheritence but public methods of Employee are now private
  public:
    string FavLanguage;

    Developer(string Name, string Company, int Age, string FavLanguage)
      :Employee(Name, Company, Age)
    {
      this->FavLanguage=FavLanguage;
    }
}

class Developer : public Employee { // this allows client code to access public methods/properties of Employee
  public:
    string FavLanguage;

    Developer(string Name, string Company, int Age, string FavLanguage)
      :Employee(Name, Company, Age)
    {
      this->FavLanguage=FavLanguage;
    }
}
```

# Abstract Classes (Interfaces)

* To create a contract that ensures a class will have a method, make an Abstract class
* c++ does not have an `interface` like Java and C# does. The equivalent mechanism is done by making an abstract class
* force a subclass to implement a function by making it a virtual function with the `virtual` keyword
  * adding the `virtual` keyword to a function makes that function a pure virtual function, and it makes that class abstract 
* when a virtual function is invoked, it will check for implementation of the function in derived classes; if there exists one, execute that. Otherwise, execute this. Like an abstract method in java.

```c++
class AbstractEmployee { // IEmployee is another naming option
  virtual void AskForPromotion()=0; // make the method obligatory by making it a pure virtual function
}

class Employee: AbstractEmployee { // Employee has now signed the AbstractEmployee contract
  private:
    string Name;
    string Company;
    int Age;

  public:
    void IntroduceYourself() {
      std::cout << "my name is " << Name << std::endl;
    }

    void AskForPromotion() {
      std::cout << "may I have a promotion?" << std::endl;
    }

    virtual void Work() { // when a virtual func is invoked, it will check for implementation of this function in derived classes; if yes, execute that. Otherwise, execute this
      std::cout << " is checking email, task backlog, performing tasks...";
    }
}
```

# Polymorphism

```c++

Developer d = Developer("austin","youtube",27,"C++");
Teacher t = Developer("saldina","youtube",35,"history");
Employee *e1 = &d // pointer to an employee, the base class
Employee *e2 = &t // pointer to an employee, the base class

e1->Work(); // -> is used when you want to access members using a pointer
e2->Work();
```

# Vectors

* __Vectors__ are sequence containers representing arrays that can change in size
  * kind of like wrapping an array in a container
* be aware: when you remove a lot of elements from a vector, you could be using a lot of space in memory, so periodically or situationally use `shrink_to_fit()`

```c++
#include <iostream>
#include <vector>

int main() {
  vector<int> v1 = {1,2,3}; // create like an array
  v1[1] // 2
  v1.front() // 1
  v1.back() // 3
  v1.size() // 3
  v1.capacity() // 4 for now; how many elements it can currently hold; size == numu elements its actually holding
  v1.push_back(9) // adding to the end of the vector; this will increase the capacity from 4 to 8
  v1.push_back(9)
  v1.push_back(9)
  v1.push_back(9) // now vector is of size 8; capacity is 8;
  v1.push_back(9) // when the 9th element added, it doubles the size of the vector
  v1.pop_back() // removes element from back of vector, and returns the elem removed
  // if we pop a lot of elements off, it will reduce the size but capacity will stay the same.
  // to decrease the capacity of the vector so that space can be freed:
  v1.shrink_to_fit() // capacity will now shrink to the size of the vector

  // insert, erase
  v1.insert(v1.begin(),5) // insert at front
  v1.insert(v1.begin()+1,5) // insert at 2nd spot
  v1.erase(v1.begin()) // erase element at first position.

  // iteration
  for (int i = 0; i < v1.size(); ++i){
    cout << v1[i] << endl;
  }

  for (auto itr = v1.begin(); itr != v1.end(); ++itr){
    cout << *itr << edl; // iterates over elements
  }

}
```

# C++ program structure

Every c++ program MUST have the `int main()` entrypoint function

# Tuple

* like an array, but the elements do not need to be the same type
* ordered collection of elements
* initialize empty tuple: `tuple <type1,type2,...> varname;`
* initialize w/ values: `tuple <type1,type2,...> varname(val1,val2,...);`
* use `get` to access elements: `get<idx>(varname)`
* use `get` to set elements: `get<idx>(varname) = newVal`
* use `make_tuple()` to make a tuple later in code
* can have 2 tuples swap contents with `swap()`; must have same tuple type
* can decompose a tuple with `tie()` to put contents into variables
* can concatenate tuples with `tuple_cat()`

```c++
#include <tuple>

int main(){
  // initialize empty tuple
  tuple <int, string> person;  // says first item is int, second is string,

  // initialize wtih values
  tuple <int, string> person(20, "Tim");

  // access values
  get<0>(person) // get 1st item
  get<1>(person) // get 2nd item

  // set values
  get<1>(person) = "billy";

  // declare and then initialize with values
  tuple <int, char, bool, float> thing; // declare
  thing = make_tuple(20, 'h', true, 24.3); // initialize

  // can do in one line
  tuple <int, char, bool, float> thing = make_tuple(20, 'h', true, 24.3); // initialize and init
  
  // what happens when you declare but don't initialize a tuple?
  tuple <int, char, bool, float> thing; // declare
  // attempting to access will return 0's

  // can swap the contents of tuples
  tuple <int, int> t1 = make_tuple(1,2);
  tuple <int, int> t2 = make_tuple(3,4);
  t1.swap(t2) // will swap the contents

  // can decompose a tuple
  tuple <int, int> t1 = make_tuple(1,2);
  int x,y;
  tie(x,y) = t1;
  // now x, y hold 1, 2

  // can concatenate tuples
  tuple <int, char> t1(20, 'T');
  tuple <char, string> t2('R', "Hello World");
  tuple <int,char,char,string> t3 = tuple_cat(t1,t2);
  // can use auto to have the compiler figure out for you the appropriate type
  auto t3 = tuple_cat(t1,t2);
}
```

# Maps

* associative data structure for key->value mappings
* create a map literal: `map<keytype, valtype> varname = {{k1,v1}{k2,v2},...};`

```c++
#include <map>

int main()
{
  // create map literal
  map<char, int> mp = {
    {'T', 7},
    {'S', 8}
    {'a', 4}
  };

  // insert
  mp['u'] = 9;
  mp.insert(pair<char,int>('j',5)); // create a pair with pair<char,int>('j',5)

  // indexing a key that is not in the map returns 0!
  // must explicitly check if key exists in map

}
```