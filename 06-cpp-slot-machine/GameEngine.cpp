#include "GameEngine.hpp"
#include <iostream>

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

std::vector<std::string> GameEngine::spin() {
    return {reel1.spin(), reel2.spin(), reel3.spin()};
}

int GameEngine::getPayout(const std::vector<std::string>& result) {
    return payout.calculate(result);
}
