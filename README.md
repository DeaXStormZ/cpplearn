# Learn cpp

# Fundamentals

## Data types

cf. [Video](https://www.youtube.com/watch?v=1QT9HnCkz4I&ab_channel=CopperSpice)

A data type is a classification identifying the possible values for that type, and the operations which can be done on values of that type
- primitive types : `char, int, bool, double, float`. void = incomplete data type
- builtin data types : `lists, hash tables, complex numbers, ...`
- composite : derived from more than one primitive/builtin data type : `array, structure, class`
- user defined : `enum, class`
- abstract : any type w/o implementation `abstract class
- atomic : 
  - a) no component part can be accessed individually
  - b) data type encapsulating value whose access is granted not to cause data races
- pointer : `int *, char *, Foo *, ...`
- reference : `int &, char &, Foo &, ...`. cf. Value Categories for lvalue and rvalue references
- function pointer : useful to pass callback
  ```cpp
  bool (Foo::* myMethod) (int, int);
  Foo foo;
  bool data = (foo->*myMethod)(x, y);
  ``̀ 
- lambda : `[capture list](parameter list) -> returnType { body };`
  - capture list : outside variables available in the body, if they should be captured by value or reference (C++14 also by move)
  - return type is optional
  - ⚠️ scoping. watch dangling reference
  - to allow the captured values to be changed, the lambda has to be mutable

### [Values](https://en.cppreference.com/w/cpp/language/value_category)

cf. [Video](https://www.youtube.com/watch?v=wkWtRDrjEH4&ab_channel=CopperSpice)

## Value Categories :
Explanatory article : cf. [here](https://www.internalpointers.com/post/understanding-meaning-lvalues-and-rvalues-c)  
First of all, let's keep our heads away from any formal definition. In C++ an lvalue is something that points to a specific memory location. On the other hand, a rvalue is something that doesn't point anywhere. In general, rvalues are temporary and short lived, while lvalues live a longer life since they exist as variables. It's also fun to think of lvalues as containers and rvalues as things contained in the containers. Without a container, they would expire.

lvalue : 
- typically has a name
- lifetime persist beyond current statement
- must be able to use & on it
rvalue :
- typically has no name
- lifetime usually ends with the current statement
- may not be able to access address
glvalue : (generalized lvalue)
- lvalue or xvalue
prvalue : (pure rvalue)
xvalue : (expiring value)

parameter passing :
- pass by value : called function will get a copy of the passed data
   `void func(int x); func(y); func(42);` 
- pass by lvalue reference : called func can can modify caller's data, caller can see the changes
  `void func(int &x); func(y); func(42); // func(42) is illegal` 
- pass by const reference : called func can not modify the data
  `void func(const int &x); func(y); func(42);` 
- pass by rvalue reference : called function can modify caller's data, caller cannot see the changes
  `void func(const int &&x); func(y); // func(y) is illegal func(42);`

Example
```cpp
Foo && var1 = Foo{}; // var1 is rvalue reference
auto && var2 = var1; // deduced type. type of declaration called 'forwarding reference'. var2 is really a lvalue reference
```

lvalue to rvalue conversion is performed  by many operators, eg. when doing `z = x op y`
can't convert rvalue to lvalue : `int& yref = 10;`
but can if using const, as it will automatically create a lvalue `const int& yref = 10;`

### Const qualifier

const : promise not to change
constexpr : constant known at compile time
- const variable : `const int var`
- const reference : `const int &var`
- const pointer : `char *const var`
- pointer to const : `const char *var`
- const methods : `void someMethod() const` : someMethod will no change `this`

## Move semantics, perfect forwarding

cf. [Vidéo](https://www.youtube.com/watch?v=kRVjG3qb7RE&ab_channel=CopperSpice)

### Semantics

- value (copy)
  - intended to be copied
  - must use asignment operator to modify the value
  - immutability of the object
  ```cpp
  QString str = "hello world";
  str = str.left(5);
  ```
- move
  - based on rvalue reference
  - when a caller passes rvalue, the called function can steal the data
  - instead of copying, data is moved to another object
  - original object is a zombie, and should *never* be accessed after the move operation
- reference (pointer)
  - value large, copy slow
  - if 2 obj refer to same value, modifying one obj will change the value of the other obj
  - most basic example : raw pointers

Pb w/ raw pointers : complicated to track who owns the object, so to know when to deallocate it safely

### Smart Pointers (C++11)

Smart pointers
- a data type which simulate a ptr
- provide some form of automatic mem management
- prevent most mem leaks, by making deallocation automatic
- eliminates dangling pointers by waiting to destroy an object until it is no longer in use

3 types, all are containers for a raw ptr :
  - unique_ptr
    - `unique_ptr<int> num_ptr = make_unique<int>(42);`
    - the destructor will delete the obj when the pointer goes out of scope
    - cannot copy
    - std::move() to transfer ownership to another unique_ptr :
    ```cpp
    auto name1 = make_unique<string>("foo");
    auto name2 = std::move(name1) // *name2 = "foo", *name1 = UB
    name2.release(); // returns the pointer, terminate ownership
    name2.reset(new std::string("bar")) // terminate the object, replace the ownership
    ```
  - shared_ptr
    - container of raw ptr
    - reference count of ownership
    - obj referenced destroyed only when all copies of shared_ptr have been destroyed
    - ⚠️ not really performant nor useful, avoid to use it 
  - weak_ptr
    - created from existing shared_ptr
    - creation/destruction has no effect on shared_ptr count
    - after all copies of shared_prt have been destroyed, all weak_ptr copies become null ptr
    - cannot be dereferenced
    - can be turned back to shared_ptr (test if ptr is null b4 using it)
  - auto_ptr : ⚠️ never use this. use unique_ptr instead

### RAII

ownership : memory/value
owner can 
- update the data
- invalidate or move the data
- free the memory

TODO https://youtu.be/07rJOzFRs6M?list=PLHTh1InhhwT4TJaHBVWzvBOYhp27UO7mI&t=620


### Templates

- utilized at compile time to generate a class, function, method or variable based on one or more data types
- designed w/o knowing the precise data type
- most of the cost is paid at compile time
- very powerful tool for generic programming
- templates are used when multiple variations of the same construct are needed for a variety of different data types
- template instanciated at compile time
- none of the info used to instantiate a template can be provided at runtime
Examples
- Template class w/ specialized method
```cpp
template <class T> // "class" or "typename"
class Widget {
  public:
    void setName(){};
}

template <> // required, templated class
void Widget<int>::setName(){} // specialization of a member

// call to Widget.setName with an int will call specialization. call w/ other type will call base method 
```
- Template class w/ templated method
```cpp
template <class T>
class Widget {
  public:
    template<class M>
    void setName(M data){};
}

template <class T>
template <class M>
void Widget<T>::setName(M data)
```
- Template class w/ class partial specialization. works for class, not templated functions or methods as they must be fully specialized
```cpp
template <class T>
class Widget {
}

template <class X>
class Widget<std::vector<X>> {
}

Widget<int> foo1; // T is int
Widget<std::vector<int>> v1; // X is int
```
- forwarding


## forwarding

```cpp
Widget w;
showWidget(std::move(w))

void showWidget(Widget &&arg) {
  nextTask(std::move(arg)) // instead of nextTask(arg) to avoid copy, forward same value category
}
```
- forwarding reference : `std::move()`
reference collapsing => compiler may interpret && T or auto && as single &, so you end up with lvalue reference instead of rvalue reference
- perfect forwarding : `std::forward()`
refers to a template func or method which passers args to another func or method preserving the const qualifier and value category
Dependent of compiler to deduce correct value category

Variadic template : can take a variable nb of args
`template<typename ... Ts> class Widget;`
ellipsis
- left of name of a param : declares a param pack, binding 0 or more args to the variadic template parameter
- right of an argument : unpack the param pack into separate args `template<typename ... Ts> void makeWidget(Ts ... Vs) { someFunc(Vs...); }`
Example (cf. [link](https://learn.microsoft.com/fr-fr/cpp/cpp/ellipses-and-variadic-templates?view=msvc-170))
```cpp
#include <iostream>

using namespace std;

void print() {
    cout << endl;
}

template <typename T> void print(const T& t) {
    cout << t << endl;
}

template <typename First, typename... Rest> void print(const First& first, const Rest&... rest) {
    cout << first << ", ";
    print(rest...); // recursive call using pack expansion syntax
}

int main()
{
    print(); // calls first overload, outputting only a newline
    print(1); // calls second overload

    // these call the third overload, the variadic template,
    // which uses recursion as needed.
    print(10, 20);
    print(100, 200, 300);
    print("first", 2, "third", 3.14159);
}
```
## RAII and smart pointers

## Scope

TODO

## auto

TODO

## Operators

![](img/operators.png)

## [Undefined behaviour](https://en.cppreference.com/w/cpp/language/ub)

cf. https://blog.regehr.org/archives/213

A correct program must be free of undefined behavior
- defined behavior : code w/ precise meaning. deterministic
- implementation defined behavior : `size(int) < size(long)` depends on platform/compiler
- unspecified behavior : code which can have multiple meanings. compiler can chose one randomly. `"abc" == "abc"̀`
- undefined behavior : code which has no meaning
The good thing — the only good thing! — about undefined behavior in C/C++ is that it simplifies the compiler’s job

Most known undefined behaviors :
- Out of Bounds Array/vector Accesses : `int arr[1] = {42}; int a = arr[1];`
- Dereferencing a NULL Pointer : `int *a = nullptr; cout << *a;`
- Use of an uninitialized variable : `bool b; if(b) {...}`
- Signed integer overflow : `int a = INT_MAX + 1;` 
- Oversized Shift Amounts :  `int a = (1 << 32);`
- Violating Type Rules : It is undefined behavior to cast an int* to a float* and dereference it (accessing the "int" as if it were a "float")
- infinite loop w/o die effect
- modifying const
- any race condition
- use after free
- accessing inactive member of an union
- failing to return value from a value-returning function


some ub are version dependent, eg. `int a = 3; a = ++a + 2;` is ub until C++11
some ub are version dependent, eg. `int a = 3; a = a++ + 2;` is ub until C++17
ub can be seen or not if compiler optimizations are enabled or not (⚠️ debug mode)

Resolving ub
- tools : address, memory, ub, thread sanitizers
- code review
- compiler warnings
- build code w/ != compilers
- test corner cases
- treat ub as critical bug
- create an interface to sanitize data
## [Pointers](https://en.cppreference.com/w/cpp/language/pointer)

```cpp
int n;
int* np = &n; // pointer to int

int a[2];
int* p1 = a; // pointer to the first element a[0] (an int) of the array a
int (*ap)[2] = &a; // pointer to array of int
struct C
{
    int x, y;
} c;
 
int* px = &c.x;   // value of px is "pointer to c.x"
int* pxe= px + 1; // value of pxe is "pointer past the end of c.x"

void f(int);
void (*p1)(int) = &f;
void (*p2)(int) = f; // same as &f

int *a = nullptr; // null pointer
```

## Conversions

`In all cases, it would be better if the cast - new or old - could be eliminated`

TLDR :
⚠️ never use type C cast : `int32_t toto = (int32_t) my_float;`,
use static_cast instead : `int n = static_cast<int>(3.14);`

- [Implicit type conversion](https://en.cppreference.com/w/c/language/conversion)
  - at assignment, automatic cast may be performed : float <-> double <-> int <-> char
  - Arithmetic type conversion : 
    `uint8_t a = 10; uint8_t b = 50; // a + b est de type int et non uint8_t ` 
  - Sign conversion
  - User conversion
- [Explicit type conversion](https://en.cppreference.com/w/cpp/language/explicit_cast) aka cast
  - C cast : `(type) var;`
    - change the meaning of the bytes
    - can fail to compile
    - can cause undefined behavior
    - function ptrs are types, can cast em
    - multiple possible operations via cast
  - C++ cast : `<type>(var)`
    4 keywords : 
    - static_cast :
      - clarify implicit conversion : `float f = static_cast<float>(42);`
      - indicate intentional truncation : `uint8_t u = static_cast<uint8_t>(1.75f*f);`
      - cast between base and derived : ⚠️ issue if multiple classes derive from base cf. [explication](https://youtu.be/2h2hdRqRIRk?list=PLHTh1InhhwT4TJaHBVWzvBOYhp27UO7mI&t=979)
      - cast between void* and T*
      - not infaillible
      - known at compile time
    - dynamic_cast :
      - require RTTI (Run Time Type information, can be disabled to save space)
      - see if To is in the same public inheritance tree as From
      - can only be a ref or ptr
      - From must be polymorphic
      - can be expensive
    - const_cast :
      - remove or add const qualifier from or to a variable (not really working as expected ?)
      - ⚠️ shouldn't be used, if so it is most likely that code is badly designed
    - reintrepret_cast
      - ~C cast
      - useful for memory mapped functionality
      - Type aliasing : act of using memory of one type as if itt were another one when the memory layout of the 2 types are compatible, eg. for structs with same nb and type of attributes
      - ⚠️ should avoid to use it

![](img/cast.png)


## Misc
TODO put this in the right places
  - avoid use of auto
  - new => crée un raw ptr
  - jamais passer en arg des ptrs, utiliser via reference ou const ref; par contre en renvoyer c'est possible
  - mettre des const de partout
  - creer des obj sur la stack si possible. new crée sur la heap, donc éviter au max
TODO RAII. stack >> heap. faire des vecteurs d'objet, + rapide car prefetching. jamais de tri sur un vecteur d'obj. vecteur de ref de pointers dans ce cas, les ref de ptrs sont move. demander à Jordi notation constructeur pour limiter nb move et copy 