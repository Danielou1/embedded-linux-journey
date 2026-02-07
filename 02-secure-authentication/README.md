# 02 – Secure Embedded Authentication

This module demonstrates a **secure authentication system** for embedded Linux devices.
It is part of the **Embedded Linux Journey** and illustrates best practices for password security and cross-platform compilation.

---

## 🔹 Objective

- Learn how to secure embedded systems by **avoiding plain-text passwords**.
- Implement a simple but effective **hash-based authentication** (djb2).
- Practice **cross-compilation for x86 and ARM architectures** (Raspberry Pi).

---

## 🛠️ Features

- **Zero Trace**: The secret password is never stored in the binary.
- **Hashing**: Uses the djb2 algorithm to convert passwords into unique numeric hashes.
- **Cross-Platform Ready**: Can be compiled and executed on x86 or ARM systems.
- **Makefile Included**: Simplifies compilation for both PC and Raspberry Pi.

---

## 💻 How to Build & Run

### Requirements

- Linux (or WSL on Windows)
- g++ compiler
- ARM cross-compiler (for Raspberry Pi, e.g. `arm-linux-gnueabihf-g++`)

### Compile using Makefile

From the **module folder** (`02-secure-authentication`):

```bash
# Compile for PC / x86
make

# Compile for Raspberry Pi / ARM
make arm
> The Makefile automatically handles cross-compilation and output names.

---

## 💻 Run

### PC executable:

```bash
./security_check_pc
Raspberry Pi / ARM executable:
./security_check_arm
The program prompts for a key, hashes the input, and compares it with the stored secret hash:

[OK] Access granted.      # if correct
[ALERT] Invalid key!      # if incorrect


Note: In an actual embedded system, input could come from UART, a keypad, or other secure channels.

📝 How It Works

The user input is read from stdin.

The input string is processed by the djb2 hash function.

The resulting hash is compared to a precomputed secret hash stored in the code.

If the hash matches, access is granted; otherwise, access is denied.
📌 Learning Outcomes

By completing this module, you will understand:

Basic principles of hash-based authentication

How to avoid storing sensitive information in binaries

Cross-compilation workflows for ARM devices

Writing clean, documented C++ code for embedded applications
