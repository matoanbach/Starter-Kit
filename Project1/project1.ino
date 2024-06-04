
// This function is called once when the program starts. It is used 
// to initialize settings or components that are used throughout the program
void setup() {
  // Initializes the serial communication between the Arduino and a computer 
  // or other serial devices at a baud rate of 115200 bits per second. The baud 
  // rate specifies how fast data is exchanged. This speed needs to match the 
  // configuration on the receiving end of the serial data, typically a serial monitor in the Arduino IDE.
  Serial.begin(115200);
}

// This function is where the main operations intended to run repeatedly are placed. 
// Unlike setup(), loop() runs indefinitely, repeating its contents until the device 
// is powered down or reset.
void loop() {
  // Sends the string "Hello world" to the serial monitor, followed by a new line. 
  // This means every three seconds, "Hello world" appears on a new line on your 
  // serial monitor. This is useful for verifying that the program is running as
  // expected and that the microcontroller is able to send data out.
  delay(3000);
  Serial.println("Hello world");
}
