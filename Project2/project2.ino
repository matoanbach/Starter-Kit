#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>             // Arduino SPI library
#include "Print.h"

// Define TFT_CS, TFT_RST, and TFT_DC are pin numbers
// assigned to the chip select, reset, and data/command
// signals of the display.
#define TFT_CS 5
#define TFT_RST 27
#define TFT_DC 32

// This line initializes an instance of the Adafruit_ST7735 class, 
// configuring it with specific pins for control. It sets up the 
// necessary hardware interface pins.
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// This function initializes the display and displays the text "Hello World".
void setup()
{
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
  // Prints "Hello World" at the current cursor position.
  tft.println("Hello World");
  // Pauses the program for 5000 milliseconds (5 seconds), leaving the message on the screen.
  delay(5000);
}

void loop()
{
  // Nothing to do here
}
