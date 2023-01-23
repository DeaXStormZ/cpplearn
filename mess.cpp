#include <iostream>
#include <vector>

struct C { int m; };
 
int main()
{
    int a = 42;
    auto l = [&a]() { std::cout << a; };
    a = 7;
    l();
}