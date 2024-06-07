# Project 3: Calibrating and Measuring an Object

## Overview

Project 3 is to design a weight measurement system using the HX711 load cell amplifier, strain gauge and an ESP32 microcontroller. The challenge is to set up a system used to calibrate and measure an object with a known weight, and displaying the readings on TFT screen.

## Material

1. Strain Gauge
2. HX711 Amplifier
3. TFT Screen
4. ESP32

## Objectives

1. Calibration of Load Cell: calibrate the HX711 load cell amplifier with a known weight to ensure accurate measurements.
2. Weight Measurement: Use the calibrated value to measure the weight of an object and display it on a TFT screen.

## Hardware Assembly

<img src="https://raw.githubusercontent.com/matoanbach/Starter-Kit/main/pics/p3.png">

## Pseudocode

### Calibrating weight

```cpp
Include the HX711 library

Define pins for HX711 data and clock

Initialize HX711 scale object

Setup:
  Begin serial communication at 57600 baud rate
  Start the HX711 with defined pins

Loop:
  If the scale is ready:
    Reset any previous scale settings
    Print "Tare... remove any weights from the scale."
    Wait 5 seconds
    Zero the scale (tare it)
    Print "Tare done..."
    Prompt to place a known weight
    Wait 5 seconds
    Measure the weight and take 10 readings for accuracy
    Print the measured weight
  If the scale is not ready:
    Print "HX711 not found."
  Wait 1 second before the next loop iteration

```

### Measuring weight

```cpp
Include necessary libraries for the HX711 load cell and Adafruit ST7735 TFT display

Define pins for the TFT display and HX711 load cell

Initialize HX711 scale and Adafruit ST7735 display objects

Setup:
  Begin serial communication at 115200 baud
  Initialize the TFT display with specific settings (black background, white text)
  Configure the TFT display for text display (set text color, size, and initial cursor position)
  Initialize the HX711 scale, set the calibration factor, and tare the scale

Loop:
  Clear the TFT display and reset cursor position
  Read the current weight from the HX711 scale
  Display the current weight on the TFT display formatted to five decimal places with the unit "kg"
  Pause for 1 second before refreshing the display

```

## Instruction

### Calibrating an object

Every calibration factor might be different, so this step can't be skipped.

1. Prepare an object with a known weight. Because I used a 5kg strain gauge, I personally used a canadian penny with a weight of ~2.35g.
2. Use calibrating code that you wrote or you can download project3_calibrating from this repository.
3. After uploading, open your Serial Monitor at a baud rate of 115200 and the press RESET button on the ESP32
4. Follow the instructions on the Serial Monitor, it should look like the picture below:

<img src="https://raw.githubusercontent.com/matoanbach/Starter-Kit/main/pics/p3_1.png">

5. Calculate your calibration factor using this equation:

```console
calibration factor: (reading) / (known weight)
```

6. In my case, the loonie is around 6.27g so I got a result of ~433.33. So my calibration factor should be around 1174. Save this number for later use when we measure pennies.

### Measuring the weight of an object

1. Use your code that you wrote to measure an object or you can download and unload project3.ino into the ESP32.
2. Hold the strain gauge up like I did below and then press RESET, the weight displayed on the screen should be close to 0.
<div>
   <img src="https://raw.githubusercontent.com/matoanbach/Starter-Kit/main/pics/p3_12.png" width="50%">
   <img src="https://raw.githubusercontent.com/matoanbach/Starter-Kit/main/pics/p3_13.jpeg" width="50%">
</div>

3. Put a penny (or your preferred object) on the strain gauge like I did below.

   <img src="https://raw.githubusercontent.com/matoanbach/Starter-Kit/main/pics/p3_14.png" width="50%">

4. The weight should be displayed on the TFT screen like below.

   <img src="https://raw.githubusercontent.com/matoanbach/Starter-Kit/main/pics/p3_15.jpeg" width="50%">

