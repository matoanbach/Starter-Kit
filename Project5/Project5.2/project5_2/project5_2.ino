// Import libararies
#include <cstring>
#include <WiFi.h>
#include <WiFiUDP.h>

#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7735.h>  // Hardware-specific library for ST7735
#include <SPI.h>              // Arduino SPI library

// Define pins for TFT screen
#define TFT_CS 5
#define TFT_RST 27
#define TFT_DC 32

// Define pins for LED
const int RED_PIN = 22;
const int GREEN_PIN = 21;
const int BLUE_PIN = 19;

// Access point name and password
const char *ssid = "ESP32-Access-Point";
const char *password = "123456789";

// Set up udp variables for UDP communication
WiFiUDP udp;
unsigned int localUdpPort = 4210;                      // Local port to listen on
char incomingPacket[255];                              // Buffer for incoming packets

// Set up variables for TFT screen
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// Set up variables for toggling a colour
int colour = 0;
int redIntensity = 0;
int greenIntensity = 0;
int blueIntensity = 0;

void setColor(int colour);

void setup() {
  tft.initR(INITR_BLACKTAB);       // Initialize screen type
  tft.fillScreen(ST7735_BLACK);    // Fill background
  tft.setTextColor(ST7735_WHITE);  // Set text color
  tft.setTextSize(1);              // Set text size
  tft.setCursor(0, 0);             // Set cursor position


  // Set up the ESP32 as an Access Point
  WiFi.softAP(ssid, password);
  tft.println("IP Address: ");
  tft.println(WiFi.softAPIP());

  // Start UDP
  udp.begin(localUdpPort);
  tft.println("PORT: ");
  tft.println(localUdpPort);

  // Assign pins to LED
  pinMode(RED_PIN, OUTPUT);    // RED
  pinMode(GREEN_PIN, OUTPUT);  // GREEN
  pinMode(BLUE_PIN, OUTPUT);   // BLUE

  for (int i = 0; i < 10; i++) {
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, HIGH);
    delay(1000);
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    delay(1000);
  }

}

void loop() {
  int packetSize = udp.parsePacket();
  if (packetSize) {
    int len = udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = 0;  // Null-terminate the string
    }
    tft.fillScreen(ST7735_BLACK);
    tft.println(incomingPacket);
    setColor(atoi(incomingPacket));
  }
}

void setColor(int colour) {
  colour = colour % 767;

  if (colour <= 255)  // zone 1
  {
    redIntensity = 255 - colour;  // red goes from on to off
    greenIntensity = colour;      // green goes from off to on
    blueIntensity = 0;            // blue is always off
  } else if (colour <= 511)       // zone 2
  {
    redIntensity = 0;                       // red is always off
    greenIntensity = 255 - (colour - 256);  // green on to off
    blueIntensity = (colour - 256);         // blue off to on
  } else                                    // colour >= 512       // zone 3
  {
    redIntensity = (colour - 512);         // red off to on
    greenIntensity = 0;                    // green is always off
    blueIntensity = 255 - (colour - 512);  // blue on to off
  }

  // Now that the brightness values have been set, command the LED
  // to those values

  analogWrite(RED_PIN, redIntensity);
  analogWrite(BLUE_PIN, blueIntensity);
  analogWrite(GREEN_PIN, greenIntensity);
  delay(5000);
}
