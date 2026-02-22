/**
 * @file Reel.hpp
 * @author Danielou Mounsande
 * @brief Defines the Reel class for the slot machine.
 * 
 * This class represents a single reel in the slot machine, which contains
 * a collection of symbols and can be spun to yield a random symbol.
 */
#pragma once
#include <vector>
#include <string>

/**
 * @class Reel
 * @brief Represents a single slot machine reel.
 * 
 * A reel has a list of symbols. Spinning the reel randomly selects one
 * of these symbols.
 */
class Reel {
private:
    std::vector<std::string> symbols; ///< The collection of symbols on this reel.

public:
    /**
     * @brief Constructs a new Reel object.
     * 
     * Initializes the reel with a predefined set of symbols.
     */
    Reel();

    /**
     * @brief Spins the reel to get a random symbol.
     * @return A string representing the randomly selected symbol.
     */
    std::string spin();
};
