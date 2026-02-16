#pragma once
#include "Reel.hpp"
#include "PayoutCalculator.hpp"
#include <vector>
#include <string>

class GameEngine {
private:
    Reel reel1, reel2, reel3;
    PayoutCalculator payout;
public:
    void play(); // Keep for legacy/CLI
    std::vector<std::string> spin();
    int getPayout(const std::vector<std::string>& result);
};
