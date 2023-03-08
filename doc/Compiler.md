# Compiler

## Optimizations

c.f. this great article : https://queue.acm.org/detail.cfm?id=3372264

- strength reduction : taking expensive operations and transforming them to use less expensive ones.

- inlining : 
the compiler replaces a call to a function with the body of that function. 
This removes the overhead of the call and often unlocks further optimizations, as the compiler can optimize the combined code as a single unit.

- [copy elision](https://en.cppreference.com/w/cpp/language/copy_elision) :
create an object directly where it has to be copied/moved, instead of copying or moving it effectively
RVO (return value optimization) and NRVO are variants of copy elision

- small object optimization :
put small objects on the stack instead of the heap, not described by standard, but done by most compilers.
e.g. for little std::string (10-20 char), lambdas with small capture. always pass refs or ptrs in the capture.