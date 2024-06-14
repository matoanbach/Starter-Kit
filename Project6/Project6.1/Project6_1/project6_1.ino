// Include libraries for handling WiFi functions and UDP communications on the ESP32.
#include <cstring>
#include <WiFi.h>
#include <WiFiUDP.h>

// Include libraries for the HX711 load cell amplifier and the Adafruit ST7735 Display
#include <Arduino.h>
#include "HX711.h"

// Include libraries for handling graphics on an Adafruit ST7735 TFT display.
#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7735.h>  // Hardware-specific library for ST7735
#include <SPI.h>              // Arduino SPI library

// Include libraries for handling sensors.
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// Pins for the TFT display (CS, RST, DC) are defined for communication setup.
#define TFT_CS 5
#define TFT_RST 27
#define TFT_DC 32

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 17;
const int LOADCELL_SCK_PIN = 16;

// Network credentials for ESP32 Access Point
const char *ssid = "ESP32-Access-Point";
const char *password = "123456789";
// Client's address
const char *remoteIP = "192.168.4.2";
// Client's port
const int remotePort = 4211;

const int BUF_LEN = 255;
float weight;
// Instance of the WiFiUDP class for handling UDP communications.
WiFiUDP udp;
// UDP port number on which the ESP32 listens.
unsigned int localUdpPort = 4210;
// Buffer to for receive and send UDP packets.
char send_package[BUF_LEN];
// Type of data that the computer wants
int type_package = 1;

// set up sensor and tft screen
HX711 scale;
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);
  tft.initR(INITR_BLACKTAB);       // Initialize screen type
  tft.fillScreen(ST7735_BLACK);    // Fill background
  tft.setTextColor(ST7735_WHITE);  // Set text color
  tft.setTextSize(1);              // Set text size
  tft.setCursor(0, 0);             // Set cursor position

  // Set up the ESP32 as an Access Point
  WiFi.softAP(ssid, password);
  // Start UDP
  udp.begin(localUdpPort);
  // Displays the IP address and port number on the TFT for 5 seconds.
  tft.println("IP Address: ");
  tft.println(WiFi.softAPIP());

  tft.println("PORT: ");
  tft.println(localUdpPort);
  delay(5000);

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(1174.468);  // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0
  xTaskCreatePinnedToCore(sendTask, "sendTask", 4096, NULL, 2, NULL, 1);
}


void sendTask(void *pvParameters) {
  // Send data back to the remote client based on the received type
  while (1) {
    udp.beginPacket(remoteIP, remotePort);
    sprintf(send_package, "Weight: %f\n", weight);
    udp.write((uint8_t *)send_package, strlen(send_package));
    udp.endPacket();
    delay(1000);
  }
}

void loop() {
  // Clears the TFT display
  tft.fillScreen(ST7735_BLACK);
  // resets the cursor position.
  tft.setCursor(0, 0);

  tft.print("Weight: ");
  weight = scale.get_units(10);
  tft.print(weight, 5);
  tft.println(" gram");

  delay(1000);
}