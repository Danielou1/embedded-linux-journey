/**
 * @file GameEngine.cpp
 * @author Danielou Mounsande
 * @brief Implements the main logic for the slot machine game.
 */
#include "GameEngine.hpp"
#include <iostream>

/**
 * @brief Runs a simple command-line version of the game.
 * @deprecated This method is for legacy command-line interface and testing.
 * 
 * It spins the reels, prints the result to the console, and displays
 * any winnings.
 */
void GameEngine::play() {
    std::vector<std::string> result = spin();

    for(auto &s : result)
        std::cout << s << " ";
    std::cout << std::endl;

    int win = getPayout(result);
    if(win > 0)
        std::cout << "You win: " << win << " points!\n";
    else
        std::cout << "No win. Try again!\n";
}

/**
 * @brief Spins all three reels.
 * @return A vector of strings containing one symbol from each reel.
 */
std::vector<std::string> GameEngine::spin() {
    return {reel1.spin(), reel2.spin(), reel3.spin()};
}

/**
 * @brief Calculates the payout for a given spin result.
 * @param result A constant reference to a vector of strings representing the symbols.
 * @return The integer value of the payout.
 */
int GameEngine::getPayout(const std::vector<std::string>& result) {
    return payout.calculate(result);
}
