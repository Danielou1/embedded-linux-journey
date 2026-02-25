/**
 * @file Reel.cpp
 * @author Danielou Mounsande
 * @brief Implements the Reel class for the slot machine.
 */
#include "Reel.hpp"
#include "RNG.hpp"

/**
 * @brief Constructs a new Reel object.
 * 
 * Initializes the reel with a predefined set of symbols:
 * Cherry, Lemon, Bell, Seven.
 */
Reel::Reel() {
    symbols = {"CHERRY", "LEMON", "DIAMOND", "7"};
}

/**
 * @brief Spins the reel to get a random symbol.
 * 
 * Uses the RNG class to generate a random index and select a symbol
 * from the symbols vector.
 * 
 * @return A string representing the randomly selected symbol.
 */
std::string Reel::spin() {
    RNG rng;
    int idx = rng.generate(0, symbols.size() - 1);
    return symbols[idx];
}
