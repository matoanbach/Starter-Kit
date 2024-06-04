// Include libraries to handle WiFi functions and UDP communications on the ESP32.
#include <cstring>
#include <WiFi.h>
#include <WiFiUDP.h>

// Include libraries for handling graphics on an Adafruit ST7735 TFT display.
#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7735.h>  // Hardware-specific library for ST7735
#include <SPI.h>              // Arduino SPI library

// Pins for the TFT display (CS, RST, DC) are defined for communication setup.
#define TFT_CS 5
#define TFT_RST 27
#define TFT_DC 32

// This line initializes an instance of the Adafruit_ST7735 class, 
// configuring it with specific pins for control. It sets up the 
// necessary hardware interface pins.
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// Credentials for the WiFi access point.
const char *ssid = "ESP32-Access-Point";
const char *password = "123456789";

// Instance of the WiFiUDP class for handling UDP communications.
WiFiUDP udp;
// UDP port number on which the ESP32 listens.
unsigned int localUdpPort = 4210;
// Buffer to store incoming UDP packets.
char incomingPacket[255];

void setup() {
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

  delay(5000);
  // Sets up the serial communication
  Serial.begin(115200);

  // Configures the ESP32 as a WiFi access point with the given SSID and password.
  WiFi.softAP(ssid, password);
  // Begins listening for UDP packets on the specified port.
  udp.begin(localUdpPort);
  // Displays the IP address and port number on the TFT.
  tft.println("IP Address: ");
  tft.println(WiFi.softAPIP());
  tft.println("PORT: ");
  tft.println(localUdpPort);
}

void loop() {
  // Continuously checks for incoming UDP packets.
  int packetSize = udp.parsePacket();
  if (packetSize) {
    // Reads the packet into the buffer and null-terminates it to form a valid string.
    int len = udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = 0;  // Null-terminate the string
    }
    // Displays the received message on the TFT screen.
    tft.println(incomingPacket);
  }
}
