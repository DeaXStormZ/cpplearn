#include <iostream>
#include <vector>
#include <memory>

int main()
{
    auto v1 = std::vector<int>{1};
    std::cout << v1[0];
    v1.emplace_back(2);
    std::cout << v1[1];
}