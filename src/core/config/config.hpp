#ifndef config_hpp // include guard to prevent multiple inclusion
#define config_hpp

// include other headers
#include <string>
#include <fstream>

// include json library from ../../../include/json.hpp
#include "../../../include/json/json.hpp"

// define a config class that will be used to read and write config files
class Config
{
public:
    Config();
    ~Config();

    // a method to load the config file abd return a string vector of process names
    std::vector<std::string> load();
    char *getCommandByProcessName(std::string);
    char **getArgsByProcessName(std::string);
    bool isProcessForeground(std::string);
};

#endif