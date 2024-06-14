# Project 5.2: Interactive LED Control via UDP on ESP32

## Overview

Project 5.2 is about setting up a firmware utilizing the ESP32's capabilities for wireless communication. This project will guide you how to control RGB LEDs via UDP communications. The firmware is designed to respond to remote commands that adjust LED colors based on received inputs, providing an immediate visual presentation of the data on the TFT display. Previously, we set up a client on the computer, you can reuse the same client.cpp but you can also use Package Sender as a client.

## Material

1. TFT Screen
2. 330Ω resistors
3. RGB LED
4. ESP32

## Objective

1. Establish UDP communication: Implement a UDP server on the ESP32 that can receive color control commands from a remote client
2. Enhance Visual Interaction: Utilize an Adafruit ST7735 TFT display to provide feedback on the received commands and display the current state of the system
3. Dynamic LED Control: Develop a system where RGB LEDs change color based on the commands received via the UDP network.

## Hardware Assembly

<img src="https://raw.githubusercontent.com/matoanbach/Starter-Kit/main/pics/p5_2.jpeg" width="100%">

| Color | To ESP Pin |
| :---: | :--------: |
|  RED  |    P22     |
|  GND  |    GND     |
| GREEN |    P21     |
| BLUE  |    P19     |

## Network Diagram

<img src="https://raw.githubusercontent.com/matoanbach/Starter-Kit/main/pics/p5_21.jpeg" width="60%">

## Pseudocode for ESP32

```cpp
Declare necessary libraries and define pins

Initialize TFT display settings
Initialize WiFi as Access Point
Print IP Address and UDP port on TFT display
Set up UDP communication
Configure LED pins and perform initial LED blinking sequence

In the main loop:
  Check for incoming UDP packets
  If a packet is received:
    Read and display the packet content on the TFT display
    Convert the received string to an integer and set the LED color

Define setColor function:
  Calculate color intensities based on the input value
  Set the LED to the calculated color intensities
  Wait for 5 seconds before the next change
```

# Instruction

1. Download and install PackageSender
2. Visit this repo and download project5_2.ino
3. In project5_2.ino, you can change the name and password of the access point. Afterward, upload the code into the ESP32. If you don’t have a battery for the ESP32, then you can use your computer as a power souce for the ESP32.
4. he IP address of the ESP32 should be there on the TFT screen, so note it down because this will be used as an address that your message will be sent to.
5. pen PackSender and connect your computer with the name of your access point or “ESP32-Access-point” as default.
   In PackageSender, you need to write an integer value under ASCII section, you copy the address and the port displayed on TFT screen and then put them under address and port section. Because we set up the ESP32 to accept UDP packet, we should set it to UDP in PackageSender and then press send. To be more illustrative, an picture is provided below:

<img src="https://raw.githubusercontent.com/matoanbach/Starter-Kit/main/pics/p5_22.png" width="60%">

# What you should see

<img src="https://raw.githubusercontent.com/matoanbach/Starter-Kit/main/pics/p5_23.jpeg" width="60%">
