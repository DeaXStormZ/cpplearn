# TODO

## Scope

## auto

## Operator overload

## Headers (.h)

dans header
mettre template definition
mettre functions inline 
ifndef ...
define ...
include uniquement ce qui est utile ds le header


## Heap/stack

## Classes

## Macros

## STD

vector: cf. [guide](https://code.probayes.net/probayes/devops/code-community-kb/-/wikis/guide/cpp/astuces/std::vector)

## Misc
TODO put this in the right places
  - avoid use of auto
  - new => crée un raw ptr
  - jamais passer en arg des ptrs, utiliser via reference ou const ref; par contre en renvoyer c'est possible
  - mettre des const de partout
  - creer des obj sur la stack si possible. new crée sur la heap, donc éviter au max
TODO stack >> heap. faire des vecteurs d'objet, + rapide car prefetching. jamais de tri sur un vecteur d'obj. vecteur de ref de pointers dans ce cas, les ref de ptrs sont move. demander à Jordi notation constructeur pour limiter nb move et copy 
    // for (std::size_t i; i<10; i++) // utiliser size_t et non int pr iterer par index. /!\ index - 1 à 0 fait un modulo
    // rester en 32 pour faire des op sur les entiers, si en 16 le cpu peut pas et les implicit cast en 32
    // uint_64_t i{42ULL}

## [Noobie things](https://www.youtube.com/watch?v=i_wDa2AS_8w&ab_channel=mCoding)

- using namespace std
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