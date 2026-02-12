#pragma once
#include <random>

class RNG {
public:
    RNG();
    int generate(int min, int max); // retourne un entier entre min et max
private:
    std::mt19937 mt;
};
