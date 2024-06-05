# Project 5.1: Real-time Data Communication and Display

## Overview

Project 5.1 focuses on establishing an one-way real-time communication system between a computer client application and an ESP32 server using UDP (User Datagram Protocol). This project aims to demonstrate the integration of network communication and data display on an Adafruit ST7735 TFT display

## Material

1. ESP32
2. TFT Screen

## Objectives

1. Implement a UDP client: Create a client application on a computer that can send data to an ESP32 server over a network.
2. Implement a ESP32 server: Configure the ESP32 to act as a server that receives data sent from the client.
3. Visual Feedback: Use a TFT display connected to the ESP32 to visually represent the data received from the computer

## Hardware Assembly

<img src="https://raw.githubusercontent.com/matoanbach/Starter-Kit/main/pics/p2.png">

| LCD Pin | Description | To ESP Pin |
| :-----: | :---------: | :--------: |
| 1 – RST |    Reset    |    P27     |
| 2 – CS  | Chip Select |     P5     |
| 3 – D/C |  Data/Cmd   |    P32     |
| 4 – DIN | MOSI Slave  |    P23     |
| 5 – CLK |    Clock    |    P18     |
| 6 – VCC |    Power    |     5V     |
| 7 – BL  |  Backlight  |     5V     |
| 8 – GND | Ground (0V) |    GND     |

## Network Diagram

<img src="https://raw.githubusercontent.com/matoanbach/Starter-Kit/main/pics/p5_1.jpeg" width="60%">

## Pseudocode for ESP32

```cpp
Include necessary libraries

Define pin connections for the TFT display
Create a TFT display object

Define WiFi credentials
Define UDP port and packet buffer

Function setup:
    Initialize the TFT display with specific settings
    Start serial communication for debugging
    Set up the ESP32 as a WiFi access point with the specified credentials
    Display the IP address and port on the TFT
    Start the UDP service on the specified port

Function loop:
    Check if a UDP packet is available
    If a packet is available:
        Read the packet into the buffer
        Ensure the packet is a properly terminated string
        Display the packet on the TFT display
```

## Pseudocode for the Client

```cpp
Set BUF_LEN to 255
Declare is_running as boolean
Set PORT to 4210
Set IP_ADDRESS to "192.168.4.1"

Start
    Declare variables for socket, server address, and buffer

    Create UDP socket
    If socket creation fails Then Print an error message

    Configure server address with AF_INET, PORT, and IP address
    If conversion of IP address fails Then Print an error message

    Connect socket to server address
    If connection fails Then Print an error message

    Set is_running to true
    While is_running
        Read input from standard input into buffer
        If length of input > 0 Then
            Send buffer content to the server via socket
            If send fails Then
                Print an error message
            Else
                Print "message sent: " + buffer content
            EndIf

            If buffer starts with "quit" Then
                Set is_running to false
            EndIf

            Clear buffer
        EndIf
    EndWhile

    Close socket
    Exit with code 0
End
```

## Instruction

1. Visit this repo and download two files for this project (client file, project5_1.ino).
2. In project5_1.ino, you can change the name and password of the access point. Afterward, upload the code into the ESP32. If you don’t have a battery for the ESP32, then you can use your computer as a power source for the ESP32.
3. The IP address of the ESP32 should be there on the TFT screen, so note it down because this will be used as an address of your message you want to send
4. In server.cpp, change IP_ADDRESS and PORT corresponding to the values displayed on the TFT screen. These are IP address and port number of our ESP32.
5. Create a new terminal and go to the client file and run: 
```console
make clean all
```

## What you should see

<img src="https://raw.githubusercontent.com/matoanbach/Starter-Kit/main/pics/p5_11.jpeg">
