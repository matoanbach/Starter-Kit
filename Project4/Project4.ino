// Import libraries for MPU sensors
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// Import libraries for TFT screen
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>             // Arduino SPI library

// Pin definitions for TFT screen
#define TFT_CS 5
#define TFT_RST 27
#define TFT_DC 32

// Initialize global variable for mpu sensors
Adafruit_MPU6050 mpu;
// Initialize global variable for TFT screen
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup(void)
{
  // Set up the screen
  tft.initR(INITR_BLACKTAB);      // Initialize screen type
  tft.fillScreen(ST7735_BLACK);   // Fill background
  tft.setTextColor(ST7735_WHITE); // Set text color
  tft.setTextSize(1);             // Set text size
  tft.setCursor(0, 0);            // Set cursor position
  Serial.begin(115200);

  // Set up mpu sensors
  mpu.begin();
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.println("");
  delay(100);
}

void loop()
{
  /*
  clear screen after a period of time
  and the reset the position to display outputs 
  */
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 0);

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values for acceleration */
  tft.println("Accelaration: ");
  tft.print("X: ");
  tft.println(a.acceleration.x);
  tft.print("Y: ");
  tft.println(a.acceleration.y);
  tft.print("Z: ");
  tft.print(a.acceleration.z);
  tft.println(" m/s^2");
  tft.println("---------------------");

  /* Print out the values for rotation */
  tft.println("Rotation");
  tft.print("X: ");
  tft.println(g.gyro.x);
  tft.print("Y: ");
  tft.println(g.gyro.y);
  tft.print("Z: ");
  tft.print(g.gyro.z);
  tft.println(" rad/s");
  tft.println("---------------------");

  /* Print out the values for temperature */
  tft.println("Temperature: ");
  tft.print(temp.temperature);
  tft.println(" degC");
  tft.println("---------------------");
  delay(100);
}