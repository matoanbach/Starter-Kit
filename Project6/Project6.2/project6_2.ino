// Include libraries for handling WiFi functions and UDP communications on the ESP32.
#include <cstring>
#include <WiFi.h>
#include <WiFiUDP.h>

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

const int BUF_LEN = 255;

// Network credentials for ESP32 Access Point
const char *ssid = "ESP32-Access-Point";
const char *password = "123456789";
// Client's address
const char *remoteIP = "192.168.4.2";
// Client's port
const int remotePort = 4211;

// Instance of the WiFiUDP class for handling UDP communications.
WiFiUDP udp;
// UDP port number on which the ESP32 listens.
unsigned int localUdpPort = 4210;  
// Buffer to for receive and send UDP packets.
char recv_package[BUF_LEN];        
char send_package[BUF_LEN];    
// Type of data that the computer wants   
int type_package = 1;

// set up sensor and tft screen
Adafruit_MPU6050 mpu;
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
sensors_event_t a, g, temp;


void setup(void) {
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

  // Try to initialize!
  mpu.begin();
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  delay(100);
  // start a new thread
  xTaskCreatePinnedToCore(sendTask, "sendTask", 4096, NULL, 2, NULL, 1);
  xTaskCreatePinnedToCore(recvTask, "recvTask", 4096, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(displayTask, "displayTask", 4096, NULL, 1, NULL, 0);
}

void recvTask(void *pvParameters) {
  // Continuously checks for incoming UDP packets.
  while (1) {
    int packageSize = udp.parsePacket();
    if (packageSize > 0) {
      // Reads the packet into the buffer and null-terminates it to form a valid string.
      udp.read(recv_package, BUF_LEN);
      type_package = atoi(recv_package);
    }
  }
}

void sendTask(void *pvParameters) {
  // Send data back to the remote client based on the received type
  while (1) {
    while (type_package != 0) {
      udp.beginPacket(remoteIP, remotePort);
      // Send different types of sensor data
      switch (type_package) {
        case 1:
          sprintf(send_package, "Acceleration: \nX: %f\nY: %f\nZ: %f\n", temp.acceleration.x, temp.acceleration.y, temp.acceleration.z);
          break;
        case 2:
          sprintf(send_package, "Rotation: \nX: %f\nY: %f\nZ: %f\n", temp.gyro.x, temp.gyro.y, temp.gyro.z);
          break;
        case 3:
          sprintf(send_package, "Temp: %f degC\n", temp.temperature);
          break;
      }
      udp.write((uint8_t *)send_package, strlen(send_package));
      udp.endPacket();
      delay(1000);
    }
  }
}

void displayTask(void *pvParameters) {
  // Continuously update and display sensor data on the TFT screen
  while (1) {
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(0, 0);
    mpu.getEvent(&a, &g, &temp);

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

    tft.println("IP: ");
    tft.println(WiFi.softAPIP());

    tft.println("PORT: ");
    tft.println(localUdpPort);
    tft.println("---------------------");
    delay(1000);
  }
}

void loop() {
  // do nothing
}