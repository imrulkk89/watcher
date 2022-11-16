#include "ProcessManager.hpp"

ProcessManager::ProcessManager()
{
    // constructor
}

ProcessManager::~ProcessManager()
{
    // destructor
}

pid_t ProcessManager::getProcessId(std::string processName)
{
    // get process id with the given process name if it exists
    std::string command = "pidof -s " + processName;

    char buf[512];
    FILE *cmd_pipe = popen(&*command.begin(), "r");
    fgets(buf, 512, cmd_pipe);
    pid_t pid = strtoul(buf, NULL, 10);
    pclose(cmd_pipe);

    // if pid is 0, it means that the process is not found
    if (pid == 0)
    {
        spdlog::error("ProcessManager::getProcessId: process {} is not found", processName);
        return 0;
    }

    // log the process id
    spdlog::info("ProcessManager::getProcessId: process {} has pid {}", processName, pid);

    return pid;
}