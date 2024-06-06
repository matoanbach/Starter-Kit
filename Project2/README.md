# Project 2: "Hello" on Screen

## Overview

In this project, we will integrate a TFT LCD display with ESP32 using specialized libraries to manage graphics and display some strings to the screen. You should attempt to write code using pseudocode and library methods I provided. 

## Material

1. TFT Screen
2. ESP32

## Objective

1. Interface with a TFT Display: Understand the wiring and software configuration needed to drive an Adafruit ST7735 TFT display using an ESP32 microcontroller.
2. Implement Basic Graphics Programming: Use the Adafruit GFX library to display text and manage simple graphics.

## Hardware Assembly

<img src="https://raw.githubusercontent.com/matoanbach/Starter-Kit/main/pics/p2.png">

### Pin Connection

| LCD Pin | Description | To ESP Pin |
| :-----: | :---------: | :--------: |
| 1 – RST |    Reset    |    P27     |
| 2 – CS  | Chip Select |     P5     |
| 3 – D/C |  Data/Cmd   |    P32     |
| 4 – DIN | MOSI Slave  |    P23     |
| 5 – CLK |    Clock    |    P18     |
| 6 – VCC |    Power    |     5V     |
| 7 – BL  |  Backlight  |     5V     |
| 8 – GND | Ground (0V) |    GND     |

## Pseudocode:

```cpp
Include Adafruit_GFX and Adafruit_ST7735 libraries for display control
Include SPI library for communication
Define pin connections for TFT display

Create TFT display object with specified control pins

Function setup:
    Initialize the TFT display with specific configuration
    Clear the display screen to black
    Set text color to white
    Set text size to normal
    Set cursor position to top-left corner of the display
    Display "Hello World" on the screen
    Wait for 5 seconds

Function loop:
    Do nothing (endless loop)
```

## What you should see

<img src="https://raw.githubusercontent.com/matoanbach/Starter-Kit/main/pics/p2_1.jpeg">