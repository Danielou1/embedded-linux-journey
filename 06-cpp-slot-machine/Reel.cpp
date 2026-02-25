#include "Reel.hpp"
#include "RNG.hpp"

Reel::Reel() {
    symbols = {"CHERRY", "LEMON", "DIAMOND", "7"};
}

std::string Reel::spin() {
    RNG rng;
    int idx = rng.generate(0, symbols.size() - 1);
    return symbols[idx];
}
