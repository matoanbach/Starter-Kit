## Challenge:

This project is meant for environment set up. You will need to download and install Arduino IDE first. After that, you run a test to print "Hello World" to the console.

## How to install library for ESP32 board

Go to <code>tools</code> > <code>Board</code> > <code>Board Managers</code> and then find and install<code>esp32 by espressif Systems</code>. After installing, again, go to <code>tools</code> > <code>Board</code> > <code>es32</code> > <code>ES32 Dev Module</code>


## Pseudocode:

```cpp
Function setup:
    Initialize serial communication with baud rate of 115200

Function loop:
    Repeat indefinitely:
        Wait for 3000 milliseconds
        Print "Hello world" to the serial output
```

## Code explained:

```cpp
void setup()
    This function is called once when the program starts. It is used to initialize settings or components that are used throughout the program.
```

```cpp
Serial.begin(115200);
    Initializes the serial communication between the Arduino and a computer or other serial devices at a baud rate of 115200 bits per second. The baud rate specifies how fast data is exchanged. This speed needs to match the configuration on the receiving end of the serial data, typically a serial monitor in the Arduino IDE.
```

```cpp
void loop()
    This function is where the main operations intended to run repeatedly are placed. Unlike setup(), loop() runs indefinitely, repeating its contents until the device is powered down or reset.
```

```cpp
Serial.println("Hello world");
  Sends the string "Hello world" to the serial monitor, followed by a new line. This means every three seconds, "Hello world" appears on a new line on your serial monitor. This is useful for verifying that the program is running as expected and that the microcontroller is able to send data out.
```
