// Import libraries for MPU sensors
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// Import libraries for TFT screen
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>             // Arduino SPI library

// Pins for the TFT display (CS, RST, DC) are defined for communication setup.
#define TFT_CS 5
#define TFT_RST 27
#define TFT_DC 32

Adafruit_MPU6050 mpu;
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup(void)
{
  // Initializes the TFT display with specific configurations like rotation, color, and text size.
  tft.initR(INITR_BLACKTAB);      
  tft.fillScreen(ST7735_BLACK);   
  tft.setTextColor(ST7735_WHITE); 
  tft.setTextSize(1);             
  tft.setCursor(0, 0);            
  Serial.begin(115200);

  // Initializes serial communication for debugging and starts communication with the MPU6050 sensor.
  mpu.begin();

  //Configures the MPU6050 settings such as accelerometer range, gyro range, and filter bandwidth
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  delay(100);
}

void loop()
{
  // Clears the TFT display 
  tft.fillScreen(ST7735_BLACK);

  // resets the cursor position.
  tft.setCursor(0, 0);

  // Retrieves sensor data for acceleration, gyroscope, and temperature from the MPU6050.
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Displays this data formatted on the TFT screen. Each sensor reading is labeled
  // and displayed with its respective units (meters per second squared for acceleration, 
  // radians per second for gyro, and degrees Celsius for temperature).
  tft.println("Accelaration: ");
  tft.print("X: ");
  tft.println(a.acceleration.x);
  tft.print("Y: ");
  tft.println(a.acceleration.y);
  tft.print("Z: ");
  tft.print(a.acceleration.z);
  tft.println(" m/s^2");
  tft.println("---------------------");

  tft.println("Rotation");
  tft.print("X: ");
  tft.println(g.gyro.x);
  tft.print("Y: ");
  tft.println(g.gyro.y);
  tft.print("Z: ");
  tft.print(g.gyro.z);
  tft.println(" rad/s");
  tft.println("---------------------");

  tft.println("Temperature: ");
  tft.print(temp.temperature);
  tft.println(" degC");
  tft.println("---------------------");
  delay(100);
}