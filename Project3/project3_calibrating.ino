// Includes the library necessary for interfacing with the HX711 load cell amplifier.
#include "HX711.h"


// Define pins to connect the Arduino to the data output and the serial clock pins of the HX711 module.
const int LOADCELL_DOUT_PIN = 17;
const int LOADCELL_SCK_PIN = 16;

// Define a global instance of HX711
HX711 scale;

void setup() {
  // Start serial communication with the console at 115200 baud
  Serial.begin(115200);
  // Initialize the HX711 module with the specified pins.
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
}

void loop() {
  // The loop continuously checks if the HX711 is ready to communicate using 
  if (scale.is_ready()) {
    // Resets any previous scale calibration.
    scale.set_scale();    
    Serial.println("Tare... remove any weights from the scale.");
    delay(5000);
    // 
    scale.tare();
    Serial.println("Tare done...");
    Serial.print("Place a known weight on the scale...");
    delay(5000);
    // Take 10 readings to average out the noise and stores this value in reading.
    long reading = scale.get_units(10);
    Serial.print("Result: ");
    Serial.println(reading);
  } 
  else {
    Serial.println("HX711 not found.");
  }
  delay(1000);
}

//calibration factor will be the (reading)/(known weight)