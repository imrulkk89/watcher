#include "core/config/config.hpp"
#include <iostream>

#include "spdlog/spdlog.h"
#include "service/unix/ProcessManager.hpp"

#include <spdlog/spdlog.h>
#include "spdlog/sinks/daily_file_sink.h"

#include <tabulate/table.hpp>

using namespace std;
using namespace tabulate;

int main()
{
    // define loggers
    const auto processLog = spdlog::daily_logger_mt("process", "../logs/watcher.log", 0, 0);
    const auto configLog = spdlog::daily_logger_mt("config", "../logs/watcher.log", 0, 0);

    Config *config = new Config();
    ProcessManager *processManager = new ProcessManager();

    vector<string> processNames = config->load();

    // create a table
    Table processes;

    // add column headers
    processes.add_row({"Process Name", "PID", "MEM(kb)", "CPU(%)", "Status"});

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

            // add row to table
            processes.add_row({processNames[i], to_string(pid), to_string(mem), to_string(cpu), "running"});
        }
        else
        {
            // memory usage of the process
            int mem = (int)processManager->getResourceUsages(running_pid, 0);

            // cpu usage of the process
            int cpu = (int)processManager->getResourceUsages(running_pid, 1);

            // add row to table
            processes.add_row({processNames[i], to_string(running_pid), to_string(mem), to_string(cpu), "running"});
        }
    }

    // format table
    processes.format()
        .font_style({FontStyle::bold})
        .border_top("")
        .border_bottom("")
        .border_left("")
        .border_right("")
        .corner("");

    // format the first row
    processes[0].format()
        .font_color(Color::white)
        .font_background_color(Color::green)
        .font_align(FontAlign::center);

    // print table
    cout << processes << endl;

    while (true)
    {
    }
    return 0;
}
