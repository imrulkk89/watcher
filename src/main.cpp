#include "core/config/config.hpp"
#include <iostream>

int main()
{
    Config *config = new Config();
    config->load();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}