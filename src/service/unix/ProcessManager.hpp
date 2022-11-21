// defining a ProcessManager class for *nix systems

#ifndef PROCESSMANAGER_HPP
#define PROCESSMANAGER_HPP

#include <string>
#include "boost/process.hpp"
#include "spdlog/spdlog.h"

#include <iostream>

class ProcessManager
{
private:
    // a pid_t vector to store the process ids being monitored
    std::vector<pid_t> processIds;

public:
    ProcessManager();
    ~ProcessManager();

    pid_t getProcessId(std::string);
    pid_t spawnProcess(std::string, std::vector<std::string> = {}, bool = false);
    double getResourceUsages(pid_t, int);
};

#endif