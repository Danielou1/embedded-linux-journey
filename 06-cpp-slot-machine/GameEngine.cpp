#include "GameEngine.hpp"
#include <iostream>

void GameEngine::play() {
    std::vector<std::string> result = {reel1.spin(), reel2.spin(), reel3.spin()};

    for(auto &s : result)
        std::cout << s << " ";
    std::cout << std::endl;

    int win = payout.calculate(result);
    if(win > 0)
        std::cout << "You win: " << win << " points!\n";
    else
        std::cout << "No win. Try again!\n";
}
