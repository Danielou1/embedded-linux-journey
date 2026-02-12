import RPi.GPIO as GPIO
import time

# Use GPIO numbering (BCM) instead of physical pin numbering (BOARD)
# BCM refers to the "Broadcom SOC channel" numbers, which are the ones used in datasheets.
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

# --- Configuration ---
# We will use GPIO pin 17. On most Raspberry Pi boards (including the Pi 4),
# GPIO 17 corresponds to physical pin 11.
LED_PIN = 17

# --- Setup ---
# Set up the GPIO pin as an output. This means we can send a signal (voltage) out of this pin.
GPIO.setup(LED_PIN, GPIO.OUT, initial=GPIO.LOW)

print(f"LED Blinker started on GPIO {LED_PIN} (Physical Pin 11).")
print("Press Ctrl+C to exit.")

# --- Main Loop ---
try:
    # This loop will run forever until the user interrupts it.
    while True:
        print("LED ON")
        GPIO.output(LED_PIN, GPIO.HIGH) # Set the pin to HIGH (3.3V), turning the LED ON
        time.sleep(1)                   # Wait for 1 second

        print("LED OFF")
        GPIO.output(LED_PIN, GPIO.LOW)  # Set the pin to LOW (0V), turning the LED OFF
        time.sleep(1)                   # Wait for 1 second

except KeyboardInterrupt:
    # This block will run when the user presses Ctrl+C on the keyboard.
    print("Exiting program.")

finally:
    # This block is crucial for embedded programming.
    # It ensures that no matter how the program exits (normally or via an error),
    # the GPIO pins are "cleaned up" and reset to their default state (input).
    # This prevents issues where a pin might be left in an active state.
    GPIO.cleanup()
    print("GPIO cleanup complete. Goodbye!")
