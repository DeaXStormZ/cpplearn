#include <iostream>
#include <vector>
#include <memory>

template <class T>
struct Meeting {
};

template <class X>
struct Meeting<std::unique_ptr<X>> {
};
int main()
{
    Meeting<int> foo1; // T is int
    Meeting<std::unique_ptr<int>> v1; // X is int
    std::cout << "works\n";
    return 0;
}