# Learn cpp

## Fundamentals

cf. [Vidéo](https://www.youtube.com/watch?v=1QT9HnCkz4I&ab_channel=CopperSpice)

### Data types

A data type is a classification identifyon gthe possible values for that type, and the operations which can be done on values of that type
- primitive types : `char, int, bool, double, float`. void = incomplete data type
- builtin data types : `lists, hash tables, complex numbers, ...`
- composite : derived from more than one primitive/builtin data type : `array, structure, class`
- user defined : `enum, class`
- abstract : any type w/o implementation `abstract class
- atomic : 
  - a) no component part can be accessed individually
  - b) data type encapsulating value whose access is granted not to cause data races
- pointer : `int *, char *, Foo *, ...`
- reference : `int &, char &, Foo &, ...`
- function pointer : useful to pass callback
  ```cpp
  bool (Foo::* myMethod) (int, int);
  Foo foo;
  bool data = (foo->*myMethod)(x, y);
  ``̀ 
- lambda : `[capture list](parameter list) -> returnType { body };`
  - capture list : outside variables available in the body, if they should be captured by value or reference (C++14 also by move)
  - return type is optional
  - /!\ scoping. watch dangling reference
  - to allow the captured values to be changed, the lambda has to be mutable

TODO https://www.youtube.com/watch?v=wkWtRDrjEH4&ab_channel=CopperSpice; https://www.youtube.com/watch?v=kRVjG3qb7RE&ab_channel=CopperSpice
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
- failing tu return value from a value-returning function


some ub are version dependent, eg. `int a = 3; a = ++a + 2;` is ub until C++11
some ub are version dependent, eg. `int a = 3; a = a++ + 2;` is ub until C++17
ub can be seen or not if compiler optimizations are enabled or not (/!\ debug mode)

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
    - plusieurs opérations possible via le cast
  - C++ cast : `<type>(var)`
    4 keywords : 
    - static_cast :
      - clarify implicit conversion : `float f = static_cast<float>(42);`
      - indicate intentional truncation : `uint8_t u = static_cast<uint8_t>(1.75f*f);`
      - cast between base and derived : ⚠️ pb si plusieurs classes héritent de la classe mère cf. [explication](https://youtu.be/2h2hdRqRIRk?list=PLHTh1InhhwT4TJaHBVWzvBOYhp27UO7mI&t=979)
      - cast between void* and T*
      - not infaillible
    - const_cast :
      - remove or add const qualifier from or to a variable (not really working as expected ? ask Jordi)
    - dynamic_cast :
      - require RTTI (Run Time Type information, can be disabled to save space)
      - see if To is in the same public inheritance tree as From
      - can only be a ref or ptr
      - From must be polymorphic
      - can be expensive
    - reintrepret_cast
      - ~C cast
      - useful for memory mapped functionality
      - should avoid to use it
      - Type aliasing : act of using memory of one type as if itt were another one when the memory layout of the 2 types are compatible, eg. for structs with same nb and type of attributes

![](img/cast.png)

⚠️ il ne faut jamais utiliser les cast de type C : `int32_t toto = (int32_t) my_float;`,
mais les static_cast : `int n = static_cast<int>(3.14);`

## [Values](https://en.cppreference.com/w/cpp/language/value_category)

Explanatory article : cf. [here](https://www.internalpointers.com/post/understanding-meaning-lvalues-and-rvalues-c)  
First of all, let's keep our heads away from any formal definition. In C++ an lvalue is something that points to a specific memory location. On the other hand, a rvalue is something that doesn't point anywhere. In general, rvalues are temporary and short lived, while lvalues live a longer life since they exist as variables. It's also fun to think of lvalues as containers and rvalues as things contained in the containers. Without a container, they would expire.

lvalue to rvalue conversion is performed  by many operators, eg. when doing `z = x op y`
can't convert rvalue to lvalue : `int& yref = 10;`
but can if using const, as it will automatically create a lvalue `const int& yref = 10;`

## 