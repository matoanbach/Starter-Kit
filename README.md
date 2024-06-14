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

- [PROJECT 1:](https://github.com/matoanbach/Starter-Kit/tree/main/Project1)
- [PROJECT 2:](https://github.com/matoanbach/Starter-Kit/tree/main/Project2)
- [PROJECT 3:](https://github.com/matoanbach/Starter-Kit/tree/main/Project3)
- [PROJECT 4:](https://github.com/matoanbach/Starter-Kit/tree/main/Project4)
- [PROJECT 5:](https://github.com/matoanbach/Starter-Kit/tree/main/Project5)
- [PROJECT 6:](https://github.com/matoanbach/Starter-Kit/tree/main/Project6)

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
Adafruit_ST7735::Adafruit_ST7735(
    <error-type> cs, 
    <error-type> dc, 
    <error-type> mosi, 
    <error-type> sclk, 
    <error-type> rst
)
Description:
    Instantiate Adafruit ST7735 driver with software SPI
Parameters:
    cs – Chip select pin #
    dc – Data/Command pin #
    mosi – SPI MOSI pin #
    sclk – SPI Clock pin #
    rst – Reset pin # (optional, pass -1 if unused)
```

```cpp
void Adafruit_ST7735::initR(<error-type> options = 0)
Description:
    Initialization code common to all ST7735R displays
Parameters:
    options – Tab color from adafruit purchase
```

```cpp
virtual void GFXcanvas1::fillScreen(<error-type> color)
Description:
    Fill the framebuffer completely with one color
Parameters:
    color – Binary (on or off) color to fill with
```

```cpp
inline void Adafruit_GFX::setTextColor(<error-type> c)
Description:
    Set text font color with transparant background
Parameters:
    c – 16-bit 5-6-5 Color to draw text with
Note:
    For 'transparent' background, background and foreground are set to same color rather than using a separate flag.
```

```cpp
void Adafruit_GFX::setTextSize(<error-type> s)
Description:
    Set text 'magnification' size. Each increase in s makes 1 pixel that much bigger.
Parameters:
    s – Desired text size. 1 is default 6x8, 2 is 12x16, 3 is 18x24, etc
```

```cpp
inline void Adafruit_GFX::setCursor(<error-type> x, <error-type> y)
Description:
    Set text cursor location
Parameters:
    x – X coordinate in pixels
    y – Y coordinate in pixels
```

```cpp
void println(const char[])
Description:
    Print a one line including "/n"
Parameters:
    const char *

```

### MPU Sensors: <code>Adafruit_MPU6050.h</code>, <code>Adafruit_Sensor.h</code>, <code>Wire.h</code>

Below is a struct (like a menu of sensor values) that Adafruit library gives to us.
We can select any sensor values we want.

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

```cpp
bool Adafruit_MPU6050::begin(
    uint8_t     i2c_address = MPU6050_I2CADDR_DEFAULT,
    TwoWire * 	wire = &Wire,
    int32_t 	sensor_id = 0 
)
Description:
    Sets up the hardware and initializes I2C.
Parameters
    i2c_address:    The I2C address to be used.
    wire:   	    The Wire object to be used for I2C connections.
    sensor_id	    The user-defined ID to differentiate different sensors
Returns
    True if initialization was successful, otherwise false.
```

```cpp
void Adafruit_MPU6050::setAccelerometerRange	(
    mpu6050_accel_range_t 	new_range	
)
Description:
    Sets the accelerometer measurement range.
Parameters
    new_range: The new range to set. Must be a mpu6050_accel_range_t
```

```cpp

void Adafruit_MPU6050::setGyroRange	(	
    mpu6050_gyro_range_t new_range	
)	
Description:
    Sets the polarity of the INT pin when active.
Parameters
    active_low:	If true the pin will be low when an interrupt is active If false the pin will be high when an interrupt is active
```
```cpp
void Adafruit_MPU6050::setFilterBandwidth	(	
    mpu6050_bandwidth_t bandwidth	
)	
Description:
    Sets the bandwidth of the Digital Low-Pass Filter.
Parameters
    bandwidth:	the new mpu6050_bandwidth_t bandwidth
```

```cpp
bool Adafruit_MPU6050::getEvent	(
    sensors_event_t * 	accel,
    sensors_event_t * 	gyro,
    sensors_event_t * 	temp 
)
Description:	
    Gets the most recent sensor event, Adafruit Unified Sensor format.
Parameters
    accel:	Pointer to an Adafruit Unified sensor_event_t object to be filled with acceleration event data.
    gyro:	Pointer to an Adafruit Unified sensor_event_t object to be filled with gyroscope event data.
    temp:	Pointer to an Adafruit Unified sensor_event_t object to be filled with temperature event data.
Returns
    True on successful read
```

### ESP32: <code>WiFi.h</code>, <code>WiFiUDP.h</code>
```cpp
bool WiFiAPClass::softAP(
    const char *ssid, 
    const char *passphrase = (const char *)__null,
    int channel = 1,
    int ssid_hidden = 0,
    int max_connection = 4, 
    bool ftm_responder = false
)
Description:
    Set up an access point
Parameters:
    ssid:               Pointer to the SSID (max 63 char).
    passphrase:         (for WPA2 min 8 char, for open use NULL)
    channel:            WiFi channel number, 1 - 13.
    ssid_hidden:        Network cloaking (0 = broadcast SSID, 1 = hide SSID)
    max_connectionMax: simultaneous connected clients, 1 - 4.
```
```cpp
uint8_t WiFiUDP::begin(
    <error-type> a, uint16_t p
)
Description:
    Initializes the WiFi UDP library and network settings. Starts WiFiUDP socket, listening at local port PORT
Parameters:
    port: the local port to listen on (int)
Return:
    1: if successful 0: if there are no sockets available to use
```

```cpp
bool WiFiUDP::begin(
    uint8_t i2c_addr = MPU6050_I2CADDR_DEFAULT,
    TwoWire *wire = &Wire,
    int32_t sensorID = 0
)
Description:
    It starts processing the next available incoming packet, checks for the presence of a UDP packet, and reports the size. parsePacket() must be called before reading the buffer with UDP.read().
Parameters:
    None
Return 
    the size of the packet in bytes 0: if no packets are available
```

```cpp
int WiFiUDP::read(
    char* buffer, 
    size_t len
)
Descriptions:
    Reads UDP data from the specified buffer. If no arguments are given, it will return the next character in the buffer.
    This function can only be successfully called after WiFiUDP.parsePacket().
Parameters:
    buffer: buffer to hold incoming packets (char*)
    len: maximum size of the buffer (int)
Return:
    b: the characters in the buffer (char) size: the size of the buffer -1: if no buffer is available
```

```cpp
IPAddress WiFiUDP::remoteIP()
Description:
    Gets the IP address of the remote connection.
    This function must be called after WiFiUDP.parsePacket().
Parameters:
    None
Return:
   4 bytes : the IP address of the host who sent the current incoming packet 
```

```cpp
uint16_t WiFiUDP::remotePort()
Description:
    Gets the port of the remote UDP connection.
    This function must be called after UDP.parsePacket().
Parameters:
    None
Return:
    The port of the host who sent the current incoming packet
```

```cpp
int WiFiUDP::beginPacket(IPAddress ip, uint16_t port)
Description:
    Starts a connection to write UDP data to the remote connection
Parameters:
    hostName: the address of the remote host. It accepts a character string or an IPAddress
    hostIp: the IP address of the remote connection (4 bytes)
    port: the port of the remote connection (int)
Return:
    1: if successful 0: if there was a problem with the supplied IP address or port
```

```cpp
size_t WiFiUDP::write(const uint8_t *buffer, size_t size)
Description:
    Writes UDP data to the remote connection. Must be wrapped between beginPacket() and endPacket(). beginPacket() initializes the packet of data, it is not sent until endPacket() is called.
Parameters:
    byte: the outgoing byte buffer: the outgoing message size: the size of the buffer
Return:
    single byte into the packet bytes size from buffer into the packet
```

```cpp
int WiFiUDP::endPacket()
Description:
    Called after writing UDP data to the remote connection. It finishes off the packet and send it.
Parameters:
    None
Return:
    1: if the packet was sent successfully 0: if there was an error
```