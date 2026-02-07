# --- Default configuration (PC / x86) ---
CXX = g++
TARGET = security_check_pc

# --- Default rule (runs when you type 'make') ---
all:
	$(CXX) src/security_check.cpp -o $(TARGET)

# --- ARM rule (runs when you type 'make arm') ---
# Switches the compiler and output name for Raspberry Pi / ARM
arm: CXX = arm-linux-gnueabihf-g++
arm: TARGET = security_check_arm
arm: all

# --- Clean up generated files ---
clean:
	rm -f security_check_pc security_check_arm

