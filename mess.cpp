#include <iostream>
#include <vector>
#include <memory>

int main()
{
    auto name1 = std::make_unique<std::string>("foo");
    auto name2 = std::move(name1);
    std::cout << *name2;  
    std::cout << *name1;  
}