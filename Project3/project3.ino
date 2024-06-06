// Include libraries for the HX711 load cell amplifier and the Adafruit ST7735 Display
#include <Arduino.h>
#include "HX711.h"

// Include libraries for handling graphics on an Adafruit ST7735 TFT display.
#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7735.h>  // Hardware-specific library for ST7735
#include <SPI.h>              // Arduino SPI library

// Pins for the TFT display (CS, RST, DC) are defined for communication setup.
#define TFT_CS 5
#define TFT_RST 27
#define TFT_DC 32

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 17;
const int LOADCELL_SCK_PIN = 16;

HX711 scale;
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);
  // Initializes the display with specific settings.
  tft.initR(INITR_BLACKTAB);
  // Clears the display by filling it with black.
  tft.fillScreen(ST7735_BLACK);
  // Sets the text color to white.
  tft.setTextColor(ST7735_WHITE);
  // Sets the text size.
  tft.setTextSize(1);
  // Positions the cursor at the top-left corner of the display.
  tft.setCursor(0, 0);
  // Sets up the serial communication

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(1174.468);  // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0
}

void loop() {
  // Clears the TFT display
  tft.fillScreen(ST7735_BLACK);
  // resets the cursor position.
  tft.setCursor(0, 0);

  tft.print("Weight: ");
  // Read the current weight from the HX711 scale
  tft.print(scale.get_units(10), 5);
  tft.println(" gram");

  delay(1000);
}