#pragma once
#include <vector>
#include <string>

class Reel {
private:
    std::vector<std::string> symbols;
public:
    Reel();
    std::string spin();
};
