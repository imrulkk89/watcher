#ifndef config_hpp // include guard to prevent multiple inclusion
#define config_hpp

// include other headers
#include <string>
#include <fstream>

// include json library from ../includes/json.hpp
// #include "../../includes/json.hpp"

// define a config class that will be used to read and write config files
class Config
{
public:
    Config();
    ~Config();
    void load();
    // void save();
    // void set(std::string key, std::string value);
    // std::string get(std::string key);
};

#endif