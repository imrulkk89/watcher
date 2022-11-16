#include "core/config/config.hpp"
#include <iostream>

#include "spdlog/spdlog.h"
#include "service/unix/ProcessManager.hpp"

int main()
{
    spdlog::info("Hello, {}!", "World");
    Config *config = new Config();
    config->load();

    ProcessManager *processManager = new ProcessManager();
    pid_t pid = processManager->getProcessId("firefox");
    std::cout << pid << std::endl;

    pid_t pid2 = processManager->getProcessId("yakuake");
    std::cout << pid2 << std::endl;

    return 0;
}