/**
 * @file GameEngine.hpp
 * @brief Main orchestrator for the slot machine game logic.
 * @author Danielou Mounsande
 */

#pragma once
#include "Reel.hpp"
#include "PayoutCalculator.hpp"
#include <vector>
#include <string>

/**
 * @class GameEngine
 * @brief Coordinates reels and payout calculations.
 * 
 * This class acts as the bridge between the individual components of the game,
 * handling the spin process and evaluating the results.
 */
class GameEngine {
private:
    Reel reel1;            /**< First reel. */
    Reel reel2;            /**< Second reel. */
    Reel reel3;            /**< Third reel. */
    PayoutCalculator payout; /**< Payout calculation logic. */

public:
    /**
     * @brief Legacy CLI play function for terminal-based testing.
     */
    void play();

    /**
     * @brief Executes a spin on all three reels.
     * @return A vector of strings representing the three winning symbols.
     */
    std::vector<std::string> spin();

    /**
     * @brief Retrieves the payout for a specific spin result.
     * @param result The symbols to evaluate.
     * @return The calculated score.
     */
    int getPayout(const std::vector<std::string>& result);
};
