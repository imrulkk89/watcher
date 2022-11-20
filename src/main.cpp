// #include "core/config/config.hpp"
// #include <iostream>

// #include "spdlog/spdlog.h"
// #include "service/unix/ProcessManager.hpp"

// #include <spdlog/spdlog.h>
// #include "spdlog/sinks/daily_file_sink.h"

#include "core/view/view.hpp"

using namespace std;

int main(){
    // get a view instance
    
    View *view = View::getInstance();

    // create a table
    vector<vector<string>> tableData;

    // add data to processData
    tableData.push_back({"process1", "1234", "100", "10", "running"});
    tableData.push_back({"process2", "1234", "100", "10", "running"});
    tableData.push_back({"process3", "1234", "100", "10", "running"});
    tableData.push_back({"process4", "1234", "100", "10", "running"});

    // render the table
    view->render(tableData);
}