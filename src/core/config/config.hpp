#ifndef config_hpp // include guard to prevent multiple inclusion
#define config_hpp

// include other headers
#include <string>
#include <fstream>

// #include "../../../include/json/json.hpp"
#include "json/json.hpp"

using json = nlohmann::json;
// define a config class that will be used to read and write config files
class Config
{
private:
    json readConfigFile();

public:
    Config();
    ~Config();

    // a method to load the config file abd return a string vector of process names
    std::vector<std::string> load();
    std::string getCommandByProcessName(std::string);
    char **getArgsByProcessName(std::string);
    bool isProcessForeground(std::string);
};

#endif