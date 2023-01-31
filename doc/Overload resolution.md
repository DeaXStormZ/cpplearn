# Overload Resolution

## overload vs override

- compile time polymorphism : 
  - function, method or constructor **overloading**
    multiple declarations w/ different signatures
  - operator overloading : invoke a different operation for given operator
  - invoking the correct function is base on the data type
- run time polymorphism
  - method **overriding**
    used w/ inheritance. same method name for base and derived class. needs virtual
  - invoke the correct method based on the object (run time type)

## definition

functions declarations are overloads of each other when
- they have the exact same name
- are visible from the same scope
- have a different set of parameter type
order of declaration is not meaningful

overload resolution : process of selecting the most appropriate overload at compile time,
only considering arguments to the call, and parameters type of the different function overloads.
if it is ambiguous, the compiler will raise an error.
template func or meth participate in the overload resolution process.
if 2 overloads are deemed equal, non-template function will be preferred

overload fails :
- only != return types
- only != default args
- 2 meth w/ same signature, one marked static

overload vs template:
prefer overload when the impl changes depending on the data type, else template
really avoid to mix both

name lookup : finding every function declaration in the scope (namespaces, argument dependent lookup, template argument deduction)
1) overload set put in list of candidates
2) remove all not viable candidates
  - too many arguments
  - fewer arguments, if not enough even w/ default arguments
  - data type or arguments can't be converted to match the declaration, even when considering implicit conversion
3) rank the remaining candidates
4) if only one has the higher rank, it wins
   rank depends on the category of conversions that have to be made to match the overload parameter types.
   looks at the arguments sequentially for ranking process
   exact match > lvalue transformation > qualification adjustments > numeric promotion > conversions > user conversion > ellipsis conversion
5) else tiebreakers are used
  - non-template > template
  - fewer conversion steps wins
6) if tiebreakers fail or no candidates, compiler error
7) resolution :
   - add or remove overload
   - mark a constructor explicit to avoid implicit conversion
   - template func can be eliminated through SFINAE
   - use explicit conversion before the call