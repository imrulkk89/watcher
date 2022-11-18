#include "core/config/config.hpp"
#include <iostream>

#include "spdlog/spdlog.h"
#include "service/unix/ProcessManager.hpp"

#include <tabulate/table.hpp>

using namespace std;
using namespace tabulate;

int main()
{
    Config *config = new Config();
    ProcessManager *processManager = new ProcessManager();

    vector<string> processNames = config->load();

    // loop through process names
    for (int i = 0; i < processNames.size(); i++)
    {
        // check if process is running
        if (processManager->getProcessId(processNames[i]) == -1)
        {
            // if not, spawn it
            processManager->spawnProcess(
                config->getCommandByProcessName(processNames[i]),
                config->getArgsByProcessName(processNames[i]),
                /* config->isProcessForeground(processNames[i]) */
                false);
        }
    }

    // create a table
    Table processes;

    // add column headers
    processes.add_row({"Process Name", "PID", "Status"});
    processes.add_row({"------------", "---", "------"});
    processes.add_row({"------------", "---", "------"});

    while (true)
    {
    }
    return 0;
}