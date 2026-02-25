/**
 * @file RNG.hpp
 * @brief Random Number Generator for the Slot Machine.
 * @author Danielou Mounsande
 * @date 2026
 */

#pragma once
#include <random>

/**
 * @class RNG
 * @brief Provides a robust pseudo-random number generation system.
 * 
 * Uses the Mersenne Twister engine (std::mt19937) to ensure high-quality 
 * randomness for the slot machine spins.
 */
class RNG {
public:
    /**
     * @brief Constructor that seeds the generator using the current system time.
     */
    RNG();

    /**
     * @brief Generates a random integer within a specified range.
     * @param min The minimum inclusive value.
     * @param max The maximum inclusive value.
     * @return A random integer between min and max.
     */
    int generate(int min, int max);

private:
    std::mt19937 mt; /**< Mersenne Twister 19937 generator engine. */
};
