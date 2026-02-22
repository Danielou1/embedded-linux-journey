/**
 * @file PayoutCalculator.cpp
 * @author Danielou Mounsande
 * @brief Implements the payout calculation logic.
 */
#include "PayoutCalculator.hpp"

/**
 * @brief Calculates the payout based on the symbols.
 * @param result A constant reference to a vector of strings representing the symbols from each reel.
 * @return An integer representing the calculated payout amount.
 * 
 * This is a simple implementation:
 * - 3 identical symbols: 100 points
 * - 2 identical symbols: 20 points
 * - Otherwise: 0 points
 */
int PayoutCalculator::calculate(const std::vector<std::string>& result) {
    if (result[0] == result[1] && result[1] == result[2]) {
        return 100;
    } else if (result[0] == result[1] || result[1] == result[2] || result[0] == result[2]) {
        return 20;
    } else {
        return 0;
    }
}
