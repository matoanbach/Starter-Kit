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

# Instruction

<ul>
    <li>Step 1: Download and install PackageSender</li>
    <li>Step 2: Visit this repo and download project5_2.ino</li>
    <li>Step 2: In project5_2.ino, you can change the name and password of the access point. Afterward, upload the code into the ESP32. If you don’t have a battery for the ESP32, then you can use your computer as a power souce for the ESP32.</li>
    <li>Step 3: The IP address of the ESP32 should be there on the TFT screen, so note it down because this will be used as an address that your message will be sent to.</li>
    <li>Step 4: Open PackSender and connect your computer with the name of your access point or “ESP32-Access-point” as default.</li>
    <li>Step 5: In PackageSender, you need to write an integer value under ASCII section, you copy the address and the port displayed on TFT screen and then put them under address and port section. Because we set up the ESP32 to accept UDP packet, we should set it to UDP in PackageSender and then press send. To be more illustrative, an picture is provided below:</li>
<ul>

<img src="https://raw.githubusercontent.com/matoanbach/Starter-Kit/main/pics/p5_22.png" width="60%">

# What you should see

<img src="https://raw.githubusercontent.com/matoanbach/Starter-Kit/main/pics/p5_23.jpeg" width="60%">
