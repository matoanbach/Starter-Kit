// #include "HX711.h"
// HX711 scale;

// void setup() {
//   Serial.begin(57600);
//   scale.begin(23, 21);  //  DO,CK


//   /*
//     // uncomment if you want to calibrate the bowl
//     scale. set_scale();
//     scale.tare();
//     Serial.println("Put known weight on ");
//     delay(2500);
//     Serial.print(scale.get_units(10));
//     Serial.print(" Divide this value to the weight and insert it in the scale.set_scale() statement");
//     while(1==1);
//   */
//   scale.set_scale(233.82);    // this value is obtained by calibrating the scale with known weights; see the README for details
//   scale.tare();				        // reset the scale to 0

//   Serial.println("After setting up the scale:");

//   Serial.print("read: \t\t");
//   Serial.println(scale.read());                 // print a raw reading from the ADC

//   Serial.print("read average: \t\t");
//   Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC

//   Serial.print("get value: \t\t");
//   Serial.println(scale.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight, set with tare()

//   Serial.print("get units: \t\t");
//   Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
//   // by the SCALE parameter set with set_scale

//   Serial.println("Readings:");
// }

// void loop() {

//   float averageWeight = (char)scale.get_units(10);
//   Serial.print("one reading:\t");
//   Serial.print(scale.get_units(), 1);
//   Serial.print("\t| average:\t");
//   Serial.println(averageWeight);

//   char buf[20];

//   scale.power_down();			        // put the ADC in sleep mode
//   delay(1000);
//   scale.power_up();
// }

#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 17;
const int LOADCELL_SCK_PIN = 16;

HX711 scale;

void setup() {
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
}

void loop() {

  if (scale.is_ready()) {
    long reading = scale.read();
    Serial.print("HX711 reading: ");
    Serial.println(reading);
  } else {
    Serial.println("HX711 not found.");
  }
  delay(1000);
}
