/* This is a sample process named after beloved Star Trek character Jean-Luck Picard
   This process will print a message every 1 to 10 seconds
*/

#include <iostream>
#include <chrono>
#include <thread>

#include "spdlog/spdlog.h"

#include "utils/utils.hpp"

using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;

using namespace spdlog;

int main()
{
    while (true)
    {
        info("Picard: It is possible to commit no mistakes and still lose.That is not weakness, that is life.");
        // generate a random number between 1 and 10
        int random = randomgen(1, 10);
        // sleep for random seconds
        sleep_for(random * 1s);
    }
    return 0;
}