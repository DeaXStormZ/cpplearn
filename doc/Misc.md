# TODO

## [Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)

- C. 47 : Define and initialize member variables in the order of member declaration
- L. 23 : Keep the number of function arguments low
- ES. 50 : don't cast away const
- L. 11 : never transfer ownership by a raw pointer (use smart ptr/ return gsl.owner<T>)
- F. 21 : To return multiple out values, prefer tuple or struct (std::optional for 0 or 1 return value)
- Enum. 3 : Prefer class enum over plain enum
- L. 12 Declare a pointer that must not be null as not_null (`#include "gsl/gsl" gsl::not_null<Service*> ps = &s`)
- ES. Avoid lossy arithmetic conversion (use narrow_cast or narrow instead of static_cast to be explicit)

## Scope

## copy elision

## auto

## enum
 
manière 98 :
`enum value_place_request { FIRST, ANY, LAST, SECOND, THIRD, FOURTH, FIFTH };`
manière moderne :
`enum class value_place_request { first, any, last, second, third, fourth, fifth };`


## Operator overload

## volatile/mutable


## [friend](https://en.cppreference.com/w/cpp/language/friend)

The friend declaration appears in a class body
and grants a function or another class access to private and protected members of the class where the friend declaration appears.


## Macros

## Misc
TODO put this in the right places
  - avoid use of auto
  - new => crée un raw ptr en heap
  - jamais passer en arg des ptrs, utiliser via reference ou const ref; par contre en renvoyer c'est possible
  - mettre des const de partout
  - creer des obj sur la stack si possible. new crée sur la heap, donc éviter au max
TODO stack >> heap. faire des vecteurs d'objet, + rapide car prefetching. jamais de tri sur un vecteur d'obj. vecteur de ref de pointers dans ce cas, les ref de ptrs sont move. demander à Jordi notation constructeur pour limiter nb move et copy 
    // for (std::size_t i; i<10; i++) // utiliser size_t et non int pr iterer par index. /!\ index - 1 à 0 fait un modulo
    // rester en 32 pour faire des op sur les entiers, si en 16 le cpu peut pas et les implicit cast en 32
    // auto i{42ULL}

## [Noobie things](https://www.youtube.com/watch?v=i_wDa2AS_8w&ab_channel=mCoding)

- using namespace std
- std::endl instead of '\n' in for loops
- using c style array over std array
- using reinterpret_cast and C style cast
- using const_cast
- ! square bracket inserts elements in map if it doesn't exists
- ignoring const correctness (forgetting to flag parameters as const in functions)
- ! string literals lifetime = entire life of program
- ! use structure bindings
  ```cpp
  void loop_map_items() {
    std::unordered_map<std::string, std::string> colors = {
      {"RED", "#FF0000"},
      {"GREEN", "#00FF00"},
      {"BLUE", "#0000FF"},
    }
    for (const auto&[name, hex]: colors) {
      std::cout << "name: " << name ", hex: " << hex << "\n";
    }
  }
  ```
- multiple out parameters instead of struct
- not using constexpr to sacrifice compile time for runtime
- forgetting to mark destructor virtual in a class hierarchy
- thinking class members init in order of init list
- ! default vs value init : default contains garbage, value contains neutral element. almost always default initialize your values
- modifying container while looping over it. use a index loop here
- return std::move of a local. it breaks RVO
- ! move doesn't move something. it just casts to rvalue
- thinking evaluation is left to right : `"foo".replace(0, 3, "baz").replace(0, 3, "bar")̀` might return "bar" or "baz"
- unnecessary heap allocation (instead of stack). new creates objects on the heap
- using C style ptrs
- not using make_unique or make_shared
- any use of new or delete
- any manual resource management. look for a class that already does it (RAII)
- thinking raw ptrs are bad
- using shared_ptr when unique_ptr would do
- thinking shared_ptr is thread safe. only the reference counting is thread safe
- ! const applies to the thing at its left, of at its right if nothing at left 