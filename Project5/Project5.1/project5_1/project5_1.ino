#include <cstring>
#include <WiFi.h>
#include <WiFiUDP.h>

#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7735.h>  // Hardware-specific library for ST7735
#include <SPI.h>              // Arduino SPI library

#define TFT_CS 5
#define TFT_RST 27
#define TFT_DC 32

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

const char *ssid = "ESP32-Access-Point";
const char *password = "123456789";

WiFiUDP udp;
unsigned int localUdpPort = 4210;                      // Local port to listen on
char incomingPacket[255];                              // Buffer for incoming packets
char replyPacket[] = "Hi there! Got the message :-)";  // A reply string to send back

void setup() {
  tft.initR(INITR_BLACKTAB);       // Initialize screen type
  tft.fillScreen(ST7735_BLACK);    // Fill background
  tft.setTextColor(ST7735_WHITE);  // Set text color
  tft.setTextSize(1);              // Set text size
  tft.setCursor(0, 0);             // Set cursor position
  delay(5000);

  Serial.begin(115200);

  // Set up the ESP32 as an Access Point
  WiFi.softAP(ssid, password);
  tft.println("IP Address: ");
  tft.println(WiFi.softAPIP());

  // Start UDP
  udp.begin(localUdpPort);
  tft.println("PORT: ");
  tft.println(localUdpPort);
}

void loop() {
  int packetSize = udp.parsePacket();
  if (packetSize) {
    int len = udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = 0;  // Null-terminate the string
    }
    tft.println(incomingPacket);
  }
}
