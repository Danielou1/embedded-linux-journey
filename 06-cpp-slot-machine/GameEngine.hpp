/**
 * @file GameEngine.hpp
 * @author Danielou Mounsande
 * @brief Defines the main logic for the slot machine game.
 * 
 * This class orchestrates the game flow, including spinning the reels
 * and calculating the payout based on the result.
 */
#pragma once
#include "Reel.hpp"
#include "PayoutCalculator.hpp"
#include <vector>
#include <string>

/**
 * @class GameEngine
 * @brief Manages the core gameplay of the slot machine.
 * 
 * This class holds the reels, initiates a spin, and uses a PayoutCalculator
 * to determine the win amount.
 */
class GameEngine {
private:
    Reel reel1, reel2, reel3;  ///< The three reels of the slot machine.
    PayoutCalculator payout;   ///< The calculator for determining payouts.

public:
    /**
     * @brief Runs a simple command-line version of the game.
     * @deprecated This method is for legacy command-line interface and testing.
     */
    void play();

    /**
     * @brief Spins all the reels and returns the symbols.
     * @return A vector of strings representing the symbol from each reel.
     */
    std::vector<std::string> spin();

    /**
     * @brief Calculates the payout for a given spin result.
     * @param result A vector of strings representing the symbols from a spin.
     * @return The integer value of the payout.
     */
    int getPayout(const std::vector<std::string>& result);
};
