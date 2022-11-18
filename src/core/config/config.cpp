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

json Config::readConfigFile()
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

    return data;
}

std::vector<std::string> Config::load()
{
    json data = this->readConfigFile();

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

std::string Config::getCommandByProcessName(std::string processName)
{
    // parse json file
    json data = this->readConfigFile();

    // get the size of data["processes"]
    int processCount = data["processes"].size();
    spdlog::info("core/config: found {} processes to watch", processCount);

    for (int i = 0; i < processCount; i++)
    {
        if (data["processes"][i]["name"] == processName)
        {
            return data["processes"][i]["command"];
        }
    }

    return "";
}

char **Config::getArgsByProcessName(std::string processName)
{
    // parse json file
    json data = this->readConfigFile();

    // get the size of data["processes"]
    int processCount = data["processes"].size();
    spdlog::info("core/config: found {} processes to watch", processCount);

    for (int i = 0; i < processCount; i++)
    {
        if (data["processes"][i]["name"] == processName)
        {
            // typecast json array to char**
            return (char **)data["processes"][i]["args"].get<std::vector<std::string>>().data();
        }
    }

    return NULL;
}

bool Config::isProcessForeground(std::string processName)
{
    // parse json file
    json data = this->readConfigFile();

    // get the size of data["processes"]
    int processCount = data["processes"].size();
    spdlog::info("core/config: found {} processes to watch", processCount);

    for (int i = 0; i < processCount; i++)
    {
        if (data["processes"][i]["name"] == processName)
        {
            // if data["processes"][i]["foreground"] exists, return it
            if (data["processes"][i].find("foreground") != data["processes"][i].end())
            {
                return data["processes"][i]["foreground"];
            }
        }
    }

    return false;
}