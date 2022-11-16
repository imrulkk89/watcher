#include "config.hpp"
#include <iostream>

using json = nlohmann::json;

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
    std::ifstream input("../config/watchdog.conf");

    // check if file exists
    if (!input.good())
    {
        std::cout << "configuration file is not found" << std::endl;
        return;
    }

    // parse json file
    json data = json::parse(input);

    // close file
    input.close();

    // get the size of data["processes"]
    int size = data["processes"].size();

    // print the size of data["processes"]
    std::cout << size << std::endl;
}