#include "RNG.hpp"
#include <chrono>

RNG::RNG() {
    mt.seed(std::chrono::steady_clock::now().time_since_epoch().count());
}

int RNG::generate(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}
