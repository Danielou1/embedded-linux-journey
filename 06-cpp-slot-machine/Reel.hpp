/**
 * @file Reel.hpp
 * @brief Logic for a single slot machine reel.
 * @author Danielou Mounsande
 */

#pragma once
#include <vector>
#include <string>

/**
 * @class Reel
 * @brief Manages a collection of symbols and the spinning mechanism.
 */
class Reel {
private:
    std::vector<std::string> symbols; /**< List of available symbols on this reel. */

public:
    /**
     * @brief Constructor initializing the reel with default symbols.
     */
    Reel();

    /**
     * @brief Simulates a spin of the reel.
     * @return A randomly selected symbol from the symbols list.
     */
    std::string spin();
};
