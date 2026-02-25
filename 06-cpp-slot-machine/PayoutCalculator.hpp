/**
 * @file PayoutCalculator.hpp
 * @brief Logic for calculating wins based on spin results.
 * @author Danielou Mounsande
 */

#pragma once
#include <vector>
#include <string>

/**
 * @class PayoutCalculator
 * @brief Logic engine to determine the payout amount for a given set of symbols.
 */
class PayoutCalculator {
public:
    /**
     * @brief Calculates the score based on the symbol combination.
     * @param result A vector containing the symbols resulting from a spin.
     * @return The payout amount (e.g., 100 for a jackpot, 20 for a pair).
     */
    int calculate(const std::vector<std::string>& result);
};
