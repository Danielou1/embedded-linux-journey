/**
 * @file main.cpp
 * @brief Entry point for the Slot Machine RPi application.
 * @author Danielou Mounsande
 * @date 2026
 */

#include "UI/SdlUi.hpp"

/**
 * @brief Main function.
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return 0 on success.
 */
int main(int argc, char* argv[]) {
    // Suppress unused parameter warnings
    (void)argc;
    (void)argv;
    
    SdlUi ui;
    ui.run();

    return 0;
}
