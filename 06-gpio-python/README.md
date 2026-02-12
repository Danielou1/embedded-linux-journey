# 06 - GPIO Control with Python

This project is the first step into practical embedded Linux on the Raspberry Pi.

## Objective

The goal is to control a General-Purpose Input/Output (GPIO) pin to make an LED blink. This is the "Hello, World!" of hardware programming and confirms that our development environment and hardware setup are working correctly.

## Concepts Learned

- **GPIO:** What are GPIOs and how to interact with them.
- **RPi.GPIO library:** The standard Python library for controlling GPIOs on a Raspberry Pi.
- **Pin Numbering:** Understanding the difference between BCM and BOARD numbering schemes.
- **Remote Execution:** Writing code on a host machine and executing it on a target device.
- **File Transfer:** Using `scp` to transfer files over SSH.

## Hardware Required

- Raspberry Pi 4
- Breadboard
- 1x LED (any color)
- 1x Resistor (220Ω to 330Ω)
- Jumper wires
