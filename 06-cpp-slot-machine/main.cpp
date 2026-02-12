#include "GameEngine.hpp"
#include <iostream>

int main() {
    GameEngine game;
    char choice;
    do {
        game.play();
        std::cout << "Play again? (y/n): ";
        std::cin >> choice;
    } while(choice == 'y' || choice == 'Y');
    return 0;
}
