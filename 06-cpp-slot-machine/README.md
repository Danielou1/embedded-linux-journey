# Module 06: C++ OOP Project - Slot Machine

This module focuses on developing a robust, object-oriented slot machine application in C++. The project is designed to demonstrate key skills in software architecture, C++ programming, and cross-platform development targeting an Embedded Linux environment (Raspberry Pi).

## 🎯 Objectives

-   Implement an object-oriented design for the slot machine logic (GameEngine, Reel, PayoutCalculator, RNG).
-   Separate game logic from the user interface (initially console-based, later SDL2).
-   Master the cross-compilation workflow from a development host (WSL/x86) to an ARM-based target (Raspberry Pi).
-   Gain experience with `Makefile` configuration for complex C++ projects.

## 🛠️ Implementation Details

The project follows a modular structure:

-   `main.cpp`: Entry point of the application.
-   `GameEngine.hpp`/`GameEngine.cpp`: Orchestrates game flow, spins reels, and calculates payouts.
-   `Reel.hpp`/`Reel.cpp`: Represents a single slot reel, managing symbols and spin logic.
-   `PayoutCalculator.hpp`/`PayoutCalculator.cpp`: Determines winnings based on spin results.
-   `RNG.hpp`/`RNG.cpp`: Provides random number generation, essential for the game's mechanics.
-   `UI/`: Directory reserved for future graphical user interface (SDL2) components.

### Compilation

A custom `Makefile` is provided to manage the build process:

-   **Native Build (x86):** Compiles the project for your local WSL environment.
    ```bash
    make all
    ./build/slot_machine_x86
    ```
-   **Cross-Compilation (Raspberry Pi - aarch64):** Compiles the project for the Raspberry Pi.
    ```bash
    make rpi
    ```
    The resulting executable `build/slot_machine_rpi` can then be transferred to your Raspberry Pi and run.

-   **Clean Build Artifacts:**
    ```bash
    make clean
    ```

## 🚀 Next Steps

1.  Populate the C++ source and header files with the provided code.
2.  Test native compilation and execution.
3.  Set up `scp` for easy transfer to the Raspberry Pi.
4.  Test cross-compilation and remote execution.
5.  Proceed with the SDL2 integration.
