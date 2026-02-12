# Makefile for the C++ Slot Machine project
#
# Usage:
#   make all  (to build for local x86 system)
#   make rpi  (to cross-compile for Raspberry Pi aarch64)
#   make clean (to remove build artifacts)

# --- Project Configuration ---
PROJECT_NAME = slot_machine
SRC_DIR = .
BUILD_DIR = build

# Source files (all .cpp files in SRC_DIR)
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Object files for native build (e.g., build/main.o)
OBJS_NATIVE = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Object files for RPi build (e.g., build/main_rpi.o) - distinct to avoid conflicts
OBJS_RPI = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%_rpi.o, $(SRCS))

# --- Compilers ---
# Native (x86) C++ compiler
CXX_NATIVE = g++
# Cross-compiler for Raspberry Pi (ARM 64-bit)
CXX_RPI = aarch64-linux-gnu-g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17

# --- Targets ---

.PHONY: all rpi clean

# Default target: build for local x86 system
all: $(BUILD_DIR) $(BUILD_DIR)/$(PROJECT_NAME)_x86

$(BUILD_DIR)/$(PROJECT_NAME)_x86: $(OBJS_NATIVE)
	@echo "Linking native (x86) executable..."
	$(CXX_NATIVE) $(CXXFLAGS) $(OBJS_NATIVE) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	@echo "Compiling $< for x86..."
	$(CXX_NATIVE) $(CXXFLAGS) -c $< -o $@

# Target for Raspberry Pi (aarch64) cross-compilation
rpi: $(BUILD_DIR) $(BUILD_DIR)/$(PROJECT_NAME)_rpi

$(BUILD_DIR)/$(PROJECT_NAME)_rpi: $(OBJS_RPI)
	@echo "Linking RPi (aarch64) executable..."
	$(CXX_RPI) $(CXXFLAGS) $(OBJS_RPI) -o $@

$(BUILD_DIR)/%_rpi.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	@echo "Compiling $< for RPi (aarch64)..."
	$(CXX_RPI) $(CXXFLAGS) -c $< -o $@

# Create build directory
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Clean up build artifacts
clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR)
