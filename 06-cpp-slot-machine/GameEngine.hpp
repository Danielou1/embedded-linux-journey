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
    void play();
};
