// defining a ProcessManager class for *nix systems

#ifndef PROCESSMANAGER_HPP
#define PROCESSMANAGER_HPP

#include <string>
#include "spdlog/spdlog.h"

class ProcessManager
{
public:
    ProcessManager();
    ~ProcessManager();

    pid_t getProcessId(std::string);
};

#endif