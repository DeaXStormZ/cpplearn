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

## Variadic templates

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