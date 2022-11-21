#include "core/config/config.hpp"
#include <iostream>

#include "spdlog/spdlog.h"
#include "service/unix/ProcessManager.hpp"

#include <spdlog/spdlog.h>
#include "spdlog/sinks/daily_file_sink.h"

#include "core/view/view.hpp"

using namespace std;
using namespace tabulate;

void loop()
{
    while (true)
    {
        Config *config = new Config();
        ProcessManager *processManager = new ProcessManager();
        vector<string> processNames = config->load();

        // get a view instance
        View *view = View::getInstance();
        // create a tableData
        vector<vector<string>> tableData;

        // loop through process names
        for (int i = 0; i < processNames.size(); i++)
        {
            // check if process is running
            pid_t running_pid = processManager->getProcessId(processNames[i]);
            if (running_pid < 0)
            {
                // if not, spawn it
                pid_t pid = processManager->spawnProcess(
                    config->getCommandByProcessName(processNames[i]),
                    config->getArgsByProcessName(processNames[i]),
                    /* config->isProcessForeground(processNames[i]) */
                    false);

                // memory usage of the process
                int mem = (int)processManager->getResourceUsages(pid, 0);

                // cpu usage of the process
                int cpu = (int)processManager->getResourceUsages(pid, 1);

                // add data to tableData
                tableData.push_back({processNames[i], to_string(pid), to_string(mem), to_string(cpu), "running"});
            }
            else
            {
                // memory usage of the process
                int mem = (int)processManager->getResourceUsages(running_pid, 0);

                // cpu usage of the process
                int cpu = (int)processManager->getResourceUsages(running_pid, 1);

                tableData.push_back({processNames[i], to_string(running_pid), to_string(mem), to_string(cpu), "running"});
            }
        }

        // render the table
        view->render(tableData);

        // wait for 500ms
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main()
{
    // create a logger
    auto logger = spdlog::daily_logger_mt("config", "../logs/watcher.log", 0, 0);
    auto logger2 = spdlog::daily_logger_mt("process", "../logs/watcher.log", 0, 0);

    loop();
}