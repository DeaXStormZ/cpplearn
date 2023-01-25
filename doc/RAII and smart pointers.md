## RAII and smart pointers

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
    - the destructor can be user defined `unique_ptr<Foo, ReleaseFooFunctor>̀` 
    - cannot copy
    - std::move() to transfer ownership to another unique_ptr :
    ```cpp
    auto name1 = make_unique<string>("foo");
    auto name2 = std::move(name1) // *name2 = "foo", *name1 = UB
    name2.release(); // returns the pointer, terminate ownership
    name2.reset(new std::string("bar")) // terminate the object, replace the ownership
    ```
    Uses :
    - containers can hold a unique_ptr<T> instead of T
    - we can have a unique ptr of a container => prevents copies
  - shared_ptr
    - container of raw ptr
    - reference count of ownership
    - obj referenced destroyed only when all copies of shared_ptr have been destroyed
    - thread safe, but make sure you use them right
    - create from an object using enable_shared_from_this
    - ⚠️ not really performant nor useful, avoid to use it
  - weak_ptr
    - created from existing shared_ptr
    - creation/destruction has no effect on shared_ptr count
    - after all copies of shared_prt have been destroyed, all weak_ptr copies become null ptr
    - cannot be dereferenced
    - can be turned back to shared_ptr (test if ptr is null b4 using it)
    - can be used to prevent circular references
    - useful methods
      - use_count : return the reference count
      - expired : verifies state
      - lock : return a handle w/ ownership (a shared_ptr)
  - auto_ptr : ⚠️ never use this. use unique_ptr instead

### Ownership

ownership : memory/value
owner can 
- update the data
- invalidate or move the data
- free the memory
ownership events :
- move an object
- pass an object as a function parameter
  - user code give ownership to lib : `Print(move(dev));`
  - ownership remains in, user code => func has to take reference : `void Print(unique_ptr<Device> &dev); Print(dev)`
- returning an object from a function


### RAII (Resource Acquisition Is Initialization)

technique to make sure that, when acquiring a ressource, ressource will be freed when the object is destroyed, and the destruction is guaranteed, even in case of errors 

Standard library
- string, vector - free memory on destructor
- jthread - rejoin on destructor
- unique_lock : exclusive mutex wrapper
- shared_lock : shared mutex wrapper
- lock_guard : ownership of a mutex in a scope
- scoped_lock : ownership of multiple mutex (avoid deadlocks)
- experimental::scope_exit : general purpose lock guard



