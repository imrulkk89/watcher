#include "ProcessManager.hpp"

ProcessManager::ProcessManager()
{
    // constructor
}

ProcessManager::~ProcessManager()
{
    // destructor
}

pid_t ProcessManager::spawnProcess(std::string command, std::vector<std::string> args /* = NULL */, bool isForeground /* = false */)
{
    // spawn a new process and get its pid
    // cmdArg = command + all args
    std::string cmdArg = command;

    // if args is not null then add args to cmdArg
    if (args.size() > 0)
    {
        for (int i = 0; i < args.size(); i++)
        {
            cmdArg += " ";

            // id args[i] contains spaces then add quotes
            if (args[i].find(" ") != std::string::npos)
            {
                cmdArg += "\"" + args[i] + "\"";
            }
            else
            {
                cmdArg += args[i];
            }
        }
    }


    // spawn a new process with boost::process
    boost::process::child c(cmdArg, boost::process::std_out > stdout, boost::process::std_err > stderr);
    if (c.running())
    {
        spdlog::get("process")->info("Spawned process with pid {} for {}", c.id(), command);
        // flush the log file
        spdlog::get("process")->flush();

        // detach the process
        c.detach();
        // push the pid to the vector
        this->processIds.push_back(c.id());
        return c.id();
    }
    else
    {
        spdlog::get("process")->error("Failed to spawn process for {}", command);
        // flush the logger
        spdlog::get("process")->flush();
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
        spdlog::get("process")->error("Process {} is not found", processName);
        // flush the logger
        spdlog::get("process")->flush();
        return -1;
    }

    // add the process id to the processIds vector
    processIds.push_back(pid);

    return pid;
}

// get the memory usage of the process with the given pid and resource type
// resource type: 0 = memory, 1 = cpu
double ProcessManager::getResourceUsages(pid_t pid, int resourceType) {
    std::vector<std::string> memCommand {"-c", "ps -p " + std::to_string(pid) + " -o rss | tail -1"};
    std::vector<std::string> cpuCommand {"-c", "ps -p " + std::to_string(pid) + " -o %cpu | tail -1"};
    
    boost::process::ipstream out;
    
    // in ideal case we should use boost::process::search_path("sh") but it doesn't work on this version of boost
    // so we use /usr/bin/sh instead which is the default path for sh on most linux distros
    boost::process::child c("/usr/bin/sh", resourceType == 0 ? memCommand : cpuCommand, boost::process::std_out > out);

    for (std::string line; c.running(), std::getline(out, line);) {
        return std::stod(line);
    }
    c.wait();

    return -1;
}