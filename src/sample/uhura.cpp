/* This is a sample process named after beloved Star Trek character Uhura
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

int main()
{
    // a logger with a daily file sink that rotates on 00:00
    auto logger = spdlog::daily_logger_mt("uhura", "../logs/uhura.log", 2, 30);
    while (true)
    {
        // log a message
        logger->info("Uhura reporting for duty!");
        // flush the logger
        logger->flush();
        // info("Uhura: Oh, On The Starship Enterprise, There's Someone Who's In Satan's Guise.");
        // generate a random number between 1 and 10
        int random = randomgen(1, 10);
        // sleep for random seconds
        sleep_for(random * 1s);
    }
    return 0;
}