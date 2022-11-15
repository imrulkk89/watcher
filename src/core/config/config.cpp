#include "config.hpp"
#include <iostream>

// using json = nlohmann::json;

Config::Config()
{
    // constructor
}

Config::~Config()
{
    // destructor
}

void Config::load()
{
    // load config file
    // std::ifstream file("config/global.conf");
    // json data = json::parse(file);
    // file.close();
    // set config values
    std::cout << "data" << std::endl;
}
