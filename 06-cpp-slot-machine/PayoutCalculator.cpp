#include "PayoutCalculator.hpp"

int PayoutCalculator::calculate(const std::vector<std::string>& result) {
    // Exemple simple : 3 identiques → 100, 2 identiques → 20, else 0
    if (result[0] == result[1] && result[1] == result[2])
        return 100;
    else if (result[0] == result[1] || result[1] == result[2] || result[0] == result[2])
        return 20;
    else
        return 0;
}
