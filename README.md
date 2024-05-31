# Introduction:

The ESP32 is an affordable, low-power system on a chip micro-controller that integrates Wi-Fi and dual-mode Bluetooth, making it suitable for many fascinating projects.

This repository serves as a collection of solutions and guides for embarking on ESP32-related projects. Here, we will go from basic to intermediate levels, enabling our computers to interact with the ESP32 via an access point. To start, you'll need to learn how to install the necessary libraries for sensors, screens, and the ESP32 itself. I've outlined the essential methods and libraries required, so I encourage you to review this information to gain a solid understanding before you begin assembling hardware and writing firmware. Each project is attached with its own documentation and solutions. For the best learning experience, try to tackle the challenges independently before referring to the solutions provided.

# Table of content

- [Bill of Material](#project)
- [About Us](#about-us)
- [Projects](#project)
- [Instruction](#instructions)

# About Us

Canada Robotix is your source for Raspberry Pi, Arduino, Adafruit, SparkFun, Pololu, and a lot more. We are here to make your DIY electronics and robotics project possible. We Love Robotics!

# Project

- [PROJECT 1:]()
- [PROJECT 2:]()
- [PROJECT 3:]()
- [PROJECT 4:]()
- [PROJECT 5:]()
- [PROJECT 6:]()

# Bill of Material

|   Description   |            P/N            |   Property    |           Note            | Quantity | Price |
| :-------------: | :-----------------------: | :-----------: | :-----------------------: | :------: | :---: |
| ESP32 Dev board |       ESP-WROOM 32        |    Module     |        3.3V Module        |    1     |       |
|  1.8” TFT LCD   |          ST7735           |   Coloured    |         5V Module         |    1     |       |
|   Bread board   |            N/A            |   Standard    |         Half Size         |    1     |       |
| RGB LED module  |         COM-11120         |   Coloured    |     Diffused 10mm LED     |    1     |       |
|      Wires      |            N/A            |               | Pin wires for connections |          |       |
|    USB Cable    |            N/A            |   MicroUSB    |            N/A            |    1     |       |
|   IMU sensors   | MPU6050, HMC5883L, BMP180 |    Module     |        10 DoF IMU         |    1     |       |
|    Amplifier    |           HX711           |    Module     |    Load cell amplifier    |    1     |       |
|  Strain gauge   |          YZC-131          | 5kg load cell |            N/A            |    1     |       |
|     Battery     |            N/A            |      N/A      |     3.7V LIPO battery     |    1     |       |
| Battery Charger |            N/A            |      N/A      |            N/A            |    1     |       |
|    Resistors    |            N/A            |     330Ω      |        For RGB LED        |    3     |       |

# Instructions:

## Library installation

For this starter kit, we are going to use many libraries, so we better know how to install library into our Arduino IDE.

To install a library (e.g: Adafruit_GFX.h):

<ol>
    <li>Search for adafruit_gfx.h arduino library</li>
    <li>Download the latest version (the file downloaded should be a zip file)</li>
    <li>Open Arduino IDE</li>
    <li>Go to <code>Sketch</code> > Include <code>Library</code> > <code>Add .ZIP Library</code></li>
    <li>Select Adafruit_GFX file that you just downloaded</li>
</ol>

## Library interface

Now let's walk through some methods (functions) that we are going to use in each library.

### TFT screen: <code>Adafruit_GFX.h</code>, <code>Adafruit_ST7735.h</code>, <code>SPI.h</code>

```cpp
Adafruit_ST7735::Adafruit_ST7735(<error-type> cs, <error-type> dc, <error-type> mosi, <error-type> sclk, <error-type> rst)
+4 overloads

Instantiate Adafruit ST7735 driver with software SPI

Parameters:
cs – Chip select pin #
dc – Data/Command pin #
mosi – SPI MOSI pin #
sclk – SPI Clock pin #
rst – Reset pin # (optional, pass -1 if unused)
```
