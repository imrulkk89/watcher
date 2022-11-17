#include "core/config/config.hpp"
#include <iostream>

#include "spdlog/spdlog.h"
#include "service/unix/ProcessManager.hpp"

using namespace std;

int main()
{
    Config *config = new Config();
    vector<string> processNames = config->load();

    // print the process names
    for (int i = 0; i < processNames.size(); i++)
    {
        cout << processNames[i] << endl;
    }

    // ProcessManager *processManager = new ProcessManager();
    // pid_t pid = processManager->getProcessId("firefox");
    // pid_t pid2 = processManager->getProcessId("yakuake");
    // pid_t pid = processManager->spawnProcess("/home/nsssayom/Dev/medCX/watcher/build/bin/uhura", NULL, true);
    // while (true)
    // {
    //     spdlog::info("ProcessManager::main: main loop");
    //     // sleep for 1 second
    //     sleep(1);
    // }
    return 0;
}