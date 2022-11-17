// defining a ProcessManager class for *nix systems

#ifndef PROCESSMANAGER_HPP
#define PROCESSMANAGER_HPP

#include <string>
#include "spdlog/spdlog.h"

#include "boost/process.hpp"

class ProcessManager
{
private:
    // a pid_t vector to store the process ids being monitored
    std::vector<pid_t> processIds;

public:
    ProcessManager();
    ~ProcessManager();

    pid_t getProcessId(std::string);
    pid_t spawnProcess(std::string, char ** = NULL, bool = false);
};

#endif