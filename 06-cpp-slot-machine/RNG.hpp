/**
 * @file RNG.hpp
 * @author Danielou Mounsande
 * @brief Defines a Random Number Generator (RNG) utility class.
 * 
 * This class provides a simple interface for generating random numbers
 * within a specified range, using the Mersenne Twister algorithm.
 */
#pragma once
#include <random>

/**
 * @class RNG
 * @brief A wrapper for the Mersenne Twister random number generator.
 * 
 * This class encapsulates the std::mt19937 random number generator engine
 * to provide a convenient way to generate random integers.
 */
class RNG {
public:
    /**
     * @brief Constructs a new RNG object.
     * 
     * Seeds the Mersenne Twister engine with a random device.
     */
    RNG();

    /**
     * @brief Generates a random integer within a specified range.
     * @param min The minimum value of the range (inclusive).
     * @param max The maximum value of the range (inclusive).
     * @return An integer containing the randomly generated number.
     */
    int generate(int min, int max);

private:
    std::mt19937 mt; ///< The core Mersenne Twister engine.
};
