#include "ProcessManager.hpp"

ProcessManager::ProcessManager()
{
    // constructor
}

ProcessManager::~ProcessManager()
{
    // destructor
}

pid_t ProcessManager::spawnProcess(std::string command, char **args /* = NULL */, bool isForeground /* = false */)
{
    // spawn a new process and get its pid
    // pid_t pid = std::system(command.c_str());
    // spdlog::info("Spawned process with pid: {}", pid);
    // return pid;

    // cmdArg = command + all args
    std::string cmdArg = "";
    if (args != NULL)
    {
        for (int i = 0; args[i] != NULL; i++)
        {
            cmdArg += args[i];
            cmdArg += " ";
        }
    }
    else
    {
        cmdArg = command;
    }

    // spawn a new process with boost::process
    boost::process::child c(cmdArg, boost::process::std_out > stdout, boost::process::std_err > stderr);
    if (c.running())
    {
        spdlog::info("Spawned process with pid: {}", c.id());
        // detach the process
        c.detach();
        // push the pid to the vector
        processIds.push_back(c.id());
        return c.id();
    }
    else
    {
        spdlog::error("Failed to spawn process");
        return -1;
    }
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
    // add the process id to the processIds vector
    processIds.push_back(pid);

    return pid;
}