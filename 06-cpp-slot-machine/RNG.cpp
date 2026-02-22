/**
 * @file RNG.cpp
 * @author Danielou Mounsande
 * @brief Implements the Random Number Generator (RNG) utility class.
 */
#include "RNG.hpp"
#include <chrono>

/**
 * @brief Constructs a new RNG object.
 * 
 * Seeds the Mersenne Twister engine using the current time from a steady clock,
 * ensuring a different sequence of random numbers on each program run.
 */
RNG::RNG() {
    mt.seed(std::chrono::steady_clock::now().time_since_epoch().count());
}

/**
 * @brief Generates a random integer within a specified range.
 * @param min The minimum value of the range (inclusive).
 * @param max The maximum value of the range (inclusive).
 * @return A randomly generated integer within the specified range.
 */
int RNG::generate(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}
