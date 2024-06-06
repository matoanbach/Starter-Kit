# Project 4: Real-Time Sensor Data Visualization on TFT display

## Overview

Project 5.1 aims to create an integrated system using the ESP32 microcontroller along with the Adafruit MPU6050 sensor and an Adafruit ST7735 TFT display. This project focuses on capturing real-time motion data and displaying it on a TFT display.

## Material

1. IMU sensor
2. TFT Screen
3. ESP32

## Objectives

1. Sensor Data Acquisition: Utilize the Adafruit MPU6050 to gather real-time accelerometer, gyroscope, and temperature data.
2. Data Visualisation: Implement a graphical interface on the Adafruit ST7735 TFT display to show sensor data

## Hardware Assembly

<img src="https://raw.githubusercontent.com/matoanbach/Starter-Kit/main/pics/p4.png">

## Pin Connection

|  LCD Pin   | Description | To ESP Pin |
| :--------: | :---------: | :--------: |
|  1 – GND   |    Reset    |    GND     |
| 2 – VCC_IN | Chip Select |     5V     |
|  3 – SDA   |  Data/Cmd   |    P21     |
|  4 – SCL   | MOSI Slave  |    P22     |

## Pseudocode

```cpp
Include necessary libraries for MPU6050 and TFT display

Define TFT display pins

Initialize MPU6050 sensor object
Initialize TFT display object with specified pins

Function setup:
    Initialize TFT display with black background, white text color, size 1 text
    Initialize serial communication at 115200 baud rate
    Start MPU6050 sensor
    Configure MPU6050 settings for accelerometer, gyro, and bandwidth
    Print a blank line to Serial
    Wait for 100 milliseconds

Function loop:
    Clear the TFT display and reset cursor to top-left
    Declare sensor event variables for acceleration, gyro, and temperature
    Retrieve sensor data from MPU6050

    Display "Acceleration" label and values for X, Y, Z on TFT display
    Display a separator line
    Display "Rotation" label and values for X, Y, Z on TFT display
    Display a separator line
    Display "Temperature" label and value on TFT display
    Display a separator line
    Wait for 100 milliseconds
```

# What you should see

<img src="https://raw.githubusercontent.com/matoanbach/Starter-Kit/main/pics/p4_1.jpeg">
