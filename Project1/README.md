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
