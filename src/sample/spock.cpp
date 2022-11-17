/* This is a sample process named after beloved Star Trek character Spock 🖖
   This process will print a message every 1 to 10 seconds
*/

#include <iostream>
#include <chrono>
#include <thread>

#include "spdlog/spdlog.h"

using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;

using namespace spdlog;

// main with argc and argv
int main(int argc, char **argv)
{
    while (true)
    {
        std::string message = "Spock: Live long and prosper";

        // if there are argument, overwrite the default message
        if (argc > 1)
        {
            message = argv[1];
        }

        info("Spock: {}", message);
        // generate a random number between 1 and 10
        int random = rand() % 10 + 1;
        // sleep for random seconds
        sleep_for(random * 1s);
    }
    return 0;
}