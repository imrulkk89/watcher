#include "config.hpp"
#include <iostream>
#include "spdlog/spdlog.h"

using json = nlohmann::json;

Config::Config()
{
    // constructor
}

Config::~Config()
{
    // destructor
}

std::vector<std::string> Config::load()
{
    // load config file
    std::ifstream input("../config/watchdog.json");

    // check if file exists
    if (!input.good())
    {
        spdlog::error("core/config: configuration file is not found");
        exit(EXIT_FAILURE);
    }

    // parse json file
    json data = json::parse(input);

    // close file
    input.close();

    // get the size of data["processes"]
    int processCount = data["processes"].size();
    spdlog::info("core/config: found {} processes to watch", processCount);

    std::vector<std::string> processNames;
    for (int i = 0; i < processCount; i++)
    {
        processNames.push_back(data["processes"][i]["name"]);
    }

    return processNames;
}