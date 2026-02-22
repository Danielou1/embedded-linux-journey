/**
 * @file PayoutCalculator.hpp
 * @author Danielou Mounsande
 * @brief Defines the PayoutCalculator class for the slot machine.
 * 
 * This class is responsible for calculating the payout based on the
 * results of a spin.
 */
#pragma once
#include <vector>
#include <string>

/**
 * @class PayoutCalculator
 * @brief Calculates the payout for a given spin result.
 * 
 * It determines the winning amount based on the combination of symbols
 * obtained from the reels.
 */
class PayoutCalculator {
public:
    /**
     * @brief Calculates the payout based on the symbols.
     * @param result A constant reference to a vector of strings representing the symbols from each reel.
     * @return An integer representing the calculated payout amount. Returns 0 for no win.
     */
    int calculate(const std::vector<std::string>& result);
};
