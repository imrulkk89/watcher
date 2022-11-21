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
        spdlog::get("config")->error("core/config: configuration file is not found");
        spdlog::get("config")->flush();
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

    spdlog::get("config")->info("found {} processes to watch", processCount);
    spdlog::get("config")->flush();

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
    for (int i = 0; i < processCount; i++)
    {
        if (data["processes"][i]["name"] == processName)
        {
            return data["processes"][i]["command"];
        }
    }

    return "";
}

std::vector<std::string> Config::getArgsByProcessName(std::string processName)
{
    // parse json file
    json data = this->readConfigFile();

    // get the size of data["processes"]
    int processCount = data["processes"].size();

    for (int i = 0; i < processCount; i++)
    {
        if (data["processes"][i]["name"] == processName)
        {
            // typecast json array to char**
            // char** argv = (char **)data["processes"][i]["args"].get<std::vector<std::string>>().data();

            // get the data["processes"][i]["args"] array
            json args = data["processes"][i]["args"];

            // typecast json array to std::vector<std::string>
            std::vector<std::string> argv = args.get<std::vector<std::string>>();

            // if there is no args, return an empty vector
            if (argv.size() == 0)
            {
                return {};
            }
            
            // get a string with all arguments
            std::string argsString = "";
            for (int i = 0; i < argv.size(); i++)
            {
                argsString += argv[i] + " ";
            }
            
            spdlog::get("config")->info("found arguments {} for process {}", argsString, processName);
            spdlog::get("config")->flush();

            return argv;
        }
    }

    return {};
}

bool Config::isProcessForeground(std::string processName)
{
    // parse json file
    json data = this->readConfigFile();

    // get the size of data["processes"]
    int processCount = data["processes"].size();

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