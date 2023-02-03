# Object Oriented Programming

## Key ideas

Class : encapsulation of members
- class
- struct
- union

Inheritance : don't inherit for code reuse. Inherit when you want to express a logical structure
the access specifier of the inherited class and the access specifier of the inheritance must be considered :
```cpp
class Account{
    public: int pub;
    protected: int pro;
    private: int pri;
}

class PubAccount: public Account {
    public: PubAccount(){ pub + pro; } // public + protected
}
class ProAccount: protected Account {
    public: ProAccount(){ pub + pro; } // protected + protected
}
class PriAccount: private Account {
    public: PriAccount(){ pub + pro; } // private + private
}
```
struct vs class : 
- struct all is public by default, class all is private by default
- deriving a class is private by default, using a struct derives public
- prefer struct for data structure, class when you need encapsulation and internal data processing

Polymorphism : involves pointer indirection
The separation of interface and impl is crucial

## Early and late binding

Virtuality : distinguish between the static and the dynamic type of an object
it requires
- a virtual member function
- a pointer or reference
Rules : 
- Constructor cannot be virtual. Desturctor can
- a virtual member function stays virtual in the class hierarchy
- the overriding member function must be identical to the overridden virtual func (parameters, return type, const qualifiers)
- Pure virtual member functions suppress the instanciation of a class, and can have default implementation
  ```cpp
  struct Window {
    virtual void show() = 0; 
  };
  void Window::show() { // default implementation };
  ```

override : an override declared function expresses that this function overrides a virtual function of a base class
final : this function overrides a virtual membered, and cannot be overriden -> useful for compiler.
both are equivalent : `void func() final`; `virtual void func() final override`

Template method : behavioral pattern, e.g. calls same steps.

Destructor : define it if a class needs an explicit action at object destruction
a base class destructor should either be :
- public and virtual : base class ptr or ref can destroy instances of derived class
- protected and non-virtual : cannot
destructor should not fail, mark them noexcept

## Interfaces

Liskov substitution principle : objects of a superclass should be replaceable with objects of its subclasses without breaking the application. in cpp, need to use public inheritance

Inheritance
- interface : public inheritance
- implementation : private inheritance. useful for adapter

Covariant return type : allows overriding member function to return a subtype of the return type of the overridden function 
```cpp
class Base {
public:
    virtual Base* clone() const
    {
        return new Base(this);
    }
};

class Derived : public Base {
public:
    virtual Derived* clone() const
    {
        return new Derived(this);
    }
};
```

Duck typing : don't ask for permission, ask for forgiveness
If it walks like a duck and it quacks like a duck, then it must be a duck
["Substitution Failure Is Not An Error"](https://en.cppreference.com/w/cpp/language/sfinae)
This rule applies during overload resolution of function templates: When substituting the explicitly specified or deduced type for the template parameter fails, the specialization is discarded from the overload set instead of causing a compile error.

- Interface design : contract driven design `void swim(const Duck* duck)`
- Duck typing : behavioral driven design `template <typename Duck> void swim(Duck duck);`

## Traps

virtual in constructor/destructor
/!\ don't call virtual functions in constructor and destructors
- pure virtual : UB
- virtual : virtual call mech is disabled, bc you only get the static type
constructed from inside out, destructed from outside in

slicing
copies of derived class are base class (so you lose specification)
need to implement a clone method instead (this is called virtual construction)

shadowing
function from derived class with same name but different parameter type are called (with narrowing conversion) even if function with exact same parameter type are in the base class. use ̀`using Base::func` to avoid this.
```cpp
struct Base {
    void func (double d) {} 
}
struct Derived {
    void func(int i) {}
    using Base::func // w/o this, call to Derived::func with a float would cause narrowing conversion instead of calling Base::func
}
```

## Designing classes

Guidelines :
- design classes for easy changes and extensions
- spend time to find good names for all entities
- don't put everything into one class. separate concerns. delegate to services
- design classes to be testable
design principles
- SRP (single responsibility principle) : separate concerns to isolate and simplify change
- OCP (open closed principle) : prefer design that simplify the extension by type or operations.
  open for extension, closed for modification
- DRY (don't repeat yourself)
[design patterns](https://fr.wikipedia.org/wiki/Patron_de_conception)
- strategy design pattern => dependency injection, passing unique_ptr ownership to the class (modern cpp, pass std::function/use template)
- template method design pattern (not referencing to c++ templates) : define algorithm w/ steps (virtual method). concrete class has to implement the steps. also w/ 1 single space : public write, private doWrite. NVI : non virtual interface idiom
design for testability : how to test a private member
- move the member into a private namespace
- or ito another class (as a separate service)

Implementation guidelines
```cpp
class Widget {
    // default operations. C.20: rule of 0 : if you can avoid defining default operations, do.
    public:
        Widget(); // default constructor
        Widget(Widget const& other); // copy constructor
        Widget& operator=(Widget const& other); // copy assignment operator
        Widget(Widget && other) noexcept; // move constructor
        Widget& operator=(Widget && other) noexcept; // move assignment operator
        ~Widget(); // destructor

        ~Widget(){delete ptr;}; // C.33: if a class has an owning pointer member, define a destructor

    private:
        int i;
        std::string s;
        Resource* ptr; // C.32: if a class has a raw ptr or reference, consider whether it might be owning
        // R.3 a raw ptr is non owning (if we want an owning ptr, use unique_ptr instead)
        // R.1 Manage resources using RAII
        std::unique_ptr<Resource> uptr; // copy and move wont work anymore, have to reimplement them
        // C.21 : rule of 5 : if you define or =delete any default operation, define or =delete the all
}
```
strive for rule of 0, but if it cannot be achieved, strive for rule of 5