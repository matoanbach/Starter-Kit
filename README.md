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

void Adafruit_ST7735::initR(<error-type> options = 0)
    Initialization code common to all ST7735R displays
    Parameters:
    options – Tab color from adafruit purchase

virtual void GFXcanvas1::fillScreen(<error-type> color)
    Fill the framebuffer completely with one color
    Parameters:
    color – Binary (on or off) color to fill with

inline void Adafruit_GFX::setTextColor(<error-type> c)
    Set text font color with transparant background
    Parameters:
    c – 16-bit 5-6-5 Color to draw text with
    Note:
    For 'transparent' background, background and foreground are set to same color rather than using a separate flag.

void Adafruit_GFX::setTextSize(<error-type> s)
    Set text 'magnification' size. Each increase in s makes 1 pixel that much bigger.
    Parameters:
    s – Desired text size. 1 is default 6x8, 2 is 12x16, 3 is 18x24, etc

inline void Adafruit_GFX::setCursor(<error-type> x, <error-type> y)
    Set text cursor location
    Parameters:
    x – X coordinate in pixels
    y – Y coordinate in pixels

void println(const char[])
    Print a one line including "/n"
    Parameters:
    const char *

```

### MPU Sensors: <code>Adafruit_MPU6050.h</code>, <code>Adafruit_Sensor.h</code>, <code>Wire.h</code>

```h
/* Sensor event (36 bytes) */
/** struct sensor_event_s is used to provide a single sensor event in a common
 * format. */
typedef struct {
  int32_t version;   /**< must be sizeof(struct sensors_event_t) */
  int32_t sensor_id; /**< unique sensor identifier */
  int32_t type;      /**< sensor type */
  int32_t reserved0; /**< reserved */
  int32_t timestamp; /**< time is in milliseconds */
  union {
    float data[4];              ///< Raw data */
    sensors_vec_t acceleration; /**< acceleration values are in meter per second
                                   per second (m/s^2) */
    sensors_vec_t
        magnetic; /**< magnetic vector values are in micro-Tesla (uT) */
    sensors_vec_t orientation; /**< orientation values are in degrees */
    sensors_vec_t gyro;        /**< gyroscope values are in rad/s */
    float temperature; /**< temperature is in degrees centigrade (Celsius) */
    float distance;    /**< distance in centimeters */
    float light;       /**< light in SI lux units */
    float pressure;    /**< pressure in hectopascal (hPa) */
    float relative_humidity; /**< relative humidity in percent */
    float current;           /**< current in milliamps (mA) */
    float voltage;           /**< voltage in volts (V) */
    float tvoc;              /**< Total Volatile Organic Compounds, in ppb */
    float voc_index; /**< VOC (Volatile Organic Compound) index where 100 is
                          normal (unitless) */
    float nox_index; /**< NOx (Nitrogen Oxides) index where 100 is normal
                          (unitless) */
    float CO2;       /**< Measured CO2 in parts per million (ppm) */
    float eCO2;      /**< equivalent/estimated CO2 in parts per million (ppm
                        estimated from some other measurement) */
    float pm10_std;  /**< Standard Particulate Matter <=1.0 in parts per million
                        (ppm) */
    float pm25_std;  /**< Standard Particulate Matter <=2.5 in parts per million
                        (ppm) */
    float pm100_std; /**< Standard Particulate Matter <=10.0 in parts per
                        million (ppm) */
    float pm10_env;  /**< Environmental Particulate Matter <=1.0 in parts per
                        million (ppm) */
    float pm25_env;  /**< Environmental Particulate Matter <=2.5 in parts per
                        million (ppm) */
    float pm100_env; /**< Environmental Particulate Matter <=10.0 in parts per
                        million (ppm) */
    float gas_resistance;   /**< Proportional to the amount of VOC particles in
                               the air (Ohms) */
    float unitless_percent; /**<Percentage, unit-less (%) */
    sensors_color_t color;  /**< color in RGB component values */
    float altitude; /**< Distance between a reference datum and a point or
                       object, in meters. */
  };                ///< Union for the wide ranges of data we can carry
} sensors_event_t;
```
