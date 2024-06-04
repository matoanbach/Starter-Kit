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

// Define pin numbers for RGB LEDs
const int RED_PIN = 22;
const int GREEN_PIN = 21;
const int BLUE_PIN = 19;

// Network credentials for ESP32 Access Point
const char *ssid = "ESP32-Access-Point";
const char *password = "123456789";

// Instance of the WiFiUDP class for handling UDP communications.
WiFiUDP udp;
// UDP port number on which the ESP32 listens.
unsigned int localUdpPort = 4210;       
// Buffer to store incoming UDP packets.
char incomingPacket[255];               

// Variables for LED color control
int colour = 0;
int redIntensity = 0;
int greenIntensity = 0;
int blueIntensity = 0;

// Forward declaration of setColor function
void setColor(int colour);

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


  // Configures the ESP32 as a WiFi access point with the given SSID and password.
  WiFi.softAP(ssid, password);
  // Begins listening for UDP packets on the specified port.
  udp.begin(localUdpPort);
  // Displays the IP address and port number on the TFT.
  tft.println("IP Address: ");
  tft.println(WiFi.softAPIP());
  tft.println("PORT: ");
  tft.println(localUdpPort);

  // Configure RGB LED pins as outputs
  pinMode(RED_PIN, OUTPUT);    // RED
  pinMode(GREEN_PIN, OUTPUT);  // GREEN 
  pinMode(BLUE_PIN, OUTPUT);   // BLUE

  // Blink RED and GREEN LEDs alternately ten times
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
  // Continuously checks for incoming UDP packets.
  int packetSize = udp.parsePacket();
  if (packetSize) {
    // Reads the packet into the buffer and null-terminates it to form a valid string.
    int len = udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = 0;  // Null-terminate the string
    }
    // Displays the received message on the TFT screen.
    tft.fillScreen(ST7735_BLACK);
    tft.println(incomingPacket);
    // Set the color based on the received message
    setColor(atoi(incomingPacket));
  }
}

// Function to set the RGB LED color based on an input value
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

  // Apply the calculated intensities to the LEDs
  analogWrite(RED_PIN, redIntensity);
  analogWrite(BLUE_PIN, blueIntensity);
  analogWrite(GREEN_PIN, greenIntensity);
  delay(5000);
}
