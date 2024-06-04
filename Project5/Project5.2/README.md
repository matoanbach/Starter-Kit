# Challenge

We have previously set up a server sending some messages to our Access Point set up on the ESP32. In this project, we will use a software, PackageSender, to send messages to our ESP32 to light up our LED corresponding to our message. However, you can reuse client.cpp in Project5.1 If you have any trouble downloading and installing PackageSender.

# Hardware Assembly

<img src="https://raw.githubusercontent.com/matoanbach/Starter-Kit/main/pics/p5_2.jpeg" width="100%">

| Color | To ESP Pin |
| :---: | :--------: |
|  RED  |    P22     |
|  GND  |    GND     |
| GREEN |    P21     |
| BLUE  |    P19     |

# Network Diagram
<img src="https://raw.githubusercontent.com/matoanbach/Starter-Kit/main/pics/p5_21.jpeg" width="60%">

# Pseudocode

```cpp
Declare necessary libraries and define pins

Initialize TFT display settings
Initialize WiFi as Access Point
Print IP Address and UDP port on TFT display
Set up UDP communication
Configure LED pins and perform initial LED blinking sequence

In the main loop:
  Check for incoming UDP packets
  If a packet is received:
    Read and display the packet content on the TFT display
    Convert the received string to an integer and set the LED color

Define setColor function:
  Calculate color intensities based on the input value
  Set the LED to the calculated color intensities
  Wait for 5 seconds before the next change
```
