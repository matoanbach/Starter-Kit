#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>             // Arduino SPI library
#include "Print.h"

#define TFT_CS     5
#define TFT_RST    27
#define TFT_DC     32

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  tft.initR(INITR_BLACKTAB);      // Initialize screen type
  tft.fillScreen(ST7735_BLACK);   // Fill background
  tft.setTextColor(ST7735_WHITE); // Set text color
  tft.setTextSize(1);             // Set text size
  tft.setCursor(0, 0);            // Set cursor position
  tft.println("Hello World");     // Print text
  delay(5000);
}

void loop() {
  // Nothing to do here
}

