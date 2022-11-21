/* This is a sample process named after beloved Star Trek character spock
   This process will print a message every 1 to 10 seconds
*/

#include <iostream>
#include <chrono>
#include <thread>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/daily_file_sink.h"

#include "utils/utils.hpp"

using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;

using namespace spdlog;

int main(int argc, char** argv)
{   // a logger with a daily file sink that rotates on 00:00
    auto logger = spdlog::daily_logger_mt("spock", "../logs/spock.log", 2, 30);

    std::string message = "Live long and prosper 🖖";

    // if argument is passed, use it as a message
    if (argc > 1)
    {
        message = argv[1];
    }

    while (true)
    {
        // log a message
        logger->info(message);
        // flush the logger
        logger->flush();
        // generate a random number between 1 and 10
        int random = randomgen(1, 10);
        // sleep for random seconds
        sleep_for(random * 1s);
    }
    return 0;
}