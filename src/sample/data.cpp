/* This is a sample process named after beloved Star Trek character Data
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

int main()
{
    while (true)
    {
        info("Data: This is just a thing… and things can be replaced. Lives cannot.");
        // generate a random number between 1 and 10
        int random = rand() % 10 + 1;
        // sleep for random seconds
        sleep_for(random * 1s);
    }
    return 0;
}