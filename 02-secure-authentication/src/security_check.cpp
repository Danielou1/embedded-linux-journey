/**
 * ============================================================================
 * Module: Secure Embedded Authentication
 * Filename: security_check.cpp
 * Description:
 *   Implements a secure authentication system for embedded Linux devices.
 *   The password is never stored in plain text; only its hash is saved.
 *   Hash algorithm: djb2
 *
 * Author: Danielou Mounsande
 * Date: 2025-02-07
 *
 * Target Platforms: x86 / ARM (Raspberry Pi)
 * Build: g++ -o security_check security_check.cpp
 * ============================================================================
 */

#include <iostream>
#include <string>

using namespace std;

/**
 * --------------------------------------------------------------------------
 * Function: calculate_hash
 * Description:
 *   Converts any input string into a unique numeric hash.
 *   The secret password itself is never stored.
 *
 * Parameters:
 *   const string& input - the string to hash
 *
 * Returns:
 *   unsigned long - resulting hash value
 * --------------------------------------------------------------------------
 */
unsigned long calculate_hash(const string &input) {
    unsigned long hash = 5381; // initial value recommended by djb2
    for (char c : input) {
        hash = ((hash << 5) + hash) + static_cast<unsigned long>(c); // hash * 33 + c
    }
    return hash;
}

/**
 * --------------------------------------------------------------------------
 * Main function
 * Description:
 *   Demonstrates a simple authentication flow. The user is prompted to enter
 *   a key. The entered value is hashed and compared with the precomputed hash.
 *
 * Notes:
 *   In a real embedded system, input could come from UART, a keypad, or secure storage.
 * --------------------------------------------------------------------------
 */
int main() {
    // Precomputed hash of the secret password
    const unsigned long SECRET_HASH = 8245147252682851653;

    cout << "--- LINUX SECURE SYSTEM ---" << endl;
    cout << "Enter the key: ";

    string user_input;
    cin >> user_input;

    // Compare user input hash with the stored secret hash
    if (calculate_hash(user_input) == SECRET_HASH) {
        cout << "[OK] Access granted." << endl;
        // Additional actions (GPIO, secure functions) can be added here
    } else {
        cout << "[ALERT] Invalid key!" << endl;
    }

    return 0;
}

