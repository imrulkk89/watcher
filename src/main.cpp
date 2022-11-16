#include "core/config/config.hpp"
#include <iostream>

#include "spdlog/spdlog.h"

int main()
{
    spdlog::info("Hello, {}!", "World");
    Config *config = new Config();
    config->load();
    return 0;
}