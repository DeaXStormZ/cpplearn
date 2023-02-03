# Exceptions

## Problems
- extreme perf overhead in failure case (*100 cpu of anything else)
- make it harder to reason about functions (can use noexcept)
- rely on dynamic memory
- make binary executable size grow

## how it works ?
- try/catch : when the func throws : stack unwinding
  - objects on the stack are destroyed
  - destruction happens in reverse order of construction
- unhandled exceptions result in a call to std::terminate()
  - no stack unwinding
  - no destructors are called
  - ressources are potentially leaked
- catch specific exception handler > catch all handler > no catch handler

## When
- to use them
  - for errors that occur rarely
  - for exceptional cases that cannot be dealt with locally
    - file not found
    - can't find key in map
  - for operators and constructors
- not to use them
  - for error that occur frequently
  - for function that are expected to fail for some inputs : instead return std::optional/boost::outcome from function
  - if you have to guarantee certain response time, even in the error cases
  - for things that shouldn't happen (UB)

## How to use exceptions
- Build on the std::exceptions hierarchy
- Throw by rvalue `throw std::runtime_error("Error message");`
- catch by reference, **not by value as it can slice the exception** `catch(std:: exception const &ex)`

## Exception Safety Guarantees
- Basic : all functions should at least provide that
  - Invariants are preserved (states can have changed)
  - No ressources are leaked
- Strong (extends basic)
  - No state changes (commit or rollback)
  - Not always possible (socket, streams...) nor reasonable perfomance-wise
- No-Throw
  - The operation cannot fail (noexcept)

## How to write exception safe code
- RAII
- temporary move idiom

Functions that should not fail
- std::move (an every other move)
- swap
- destructor. implicitly marked noexcept

noexcept
- makes the promise to never throw know by user
- slightly faster code
- if a noexcept excepts, terminate is called
- a noexcept can't be taken back (as users will rely on it to be noexcept)
- only mark few functions noexcept

Deal with failing cleanup functions
- std::ofstream ignores failures during closing files
- for handling the error case differently, writ ur own raii class

## How to refactor non exception safe code
- Iron law of legacy refactoring : existing contract cannot be broken
- reimplement old func using new ones, but don't break legacy contracts 