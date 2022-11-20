#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <random>

static std::random_device rd;

// using Mersenne Twister 19937 generator
// reference: https://cplusplus.com/reference/random/mersenne_twister_engine/
static std::mt19937 gen(rd());

// generate a random number between min and max
int randomgen(int min, int max)
{
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

#endif