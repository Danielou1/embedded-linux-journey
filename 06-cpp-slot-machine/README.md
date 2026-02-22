# Module 06: C++ OOP Project - Slot Machine

This module documents the development of a professional-grade Slot Machine engine, designed to showcase advanced C++ OOP skills and mastery of Embedded Linux cross-compilation workflows.

## 🎯 Objectives
- Implement a modular game engine using C++ Object-Oriented Programming.
- Integrate **SDL3** for hardware-accelerated rendering on embedded targets.
- Establish a robust **Cross-Compilation Pipeline** targeting ARM64 (Raspberry Pi).
- Implement **KMSDRM** support for "bare-metal" graphics without a window manager.

## 🛠️ Technical Stack
- **Language:** C++17
- **UI Library:** SDL3 (integrated via Git Submodule)
- **Target Architecture:** aarch64-linux-gnu (Raspberry Pi 4)
- **Graphics Backend:** KMSDRM / OpenGL ES 2.0
- **Build System:** Custom Makefile + CMake (for submodules)

## 🏗️ Project Structure
- `main.cpp`: Application entry point.
- `GameEngine.cpp/hpp`: Core game logic.
- `UI/SdlUi.cpp/hpp`: Graphics abstraction layer.
- `RNG.cpp/hpp`, `Reel.cpp/hpp`, `PayoutCalculator.cpp/hpp`: Modular engine components.
- `aarch64-toolchain.cmake`: CMake configuration for cross-compilation.
- `daten.txt`: Detailed technical log of the development process.
- All `.hpp` and `.cpp` files are now thoroughly documented with Doxygen comments.

## 📖 Code Documentation
The entire C++ codebase for this project has been meticulously documented using Doxygen.
-   **Purpose:** To provide clear explanations of classes, methods, and their functionalities.
-   **Content:** Every public API, class definition, method signature, and significant internal logic is accompanied by detailed Doxygen comments.
-   **Generation:** You can generate the full HTML documentation by running Doxygen in the project root after configuring `Doxyfile`. This will create an `html/` directory with an `index.html` entry point.

## 🚀 Build Instructions

### Native Build (x86_64)
```bash
make all
./build/slot_machine_x86
```

### Cross-Compilation (ARM64)
Ensure you have the arm64 toolchain and multi-arch libraries installed on your host.
```bash
make rpi
```
This command will:
1. Initialize/Build the SDL3 submodule for ARM64.
2. Link against system libraries (`libgbm`, `libdrm`).
3. Produce the `build/slot_machine_rpi` binary.

## 📊 Status
- ✅ C++ OOP Logic: **Complete**
- ✅ Cross-Compilation Pipeline: **Functional**
- ✅ SDL3 Static Linking: **Complete**
- ✅ Code Documentation (Doxygen): **Complete**
- ⏳ KMSDRM Runtime Initialization: **In Progress** (Binary compiled, driver verification ongoing on target).
