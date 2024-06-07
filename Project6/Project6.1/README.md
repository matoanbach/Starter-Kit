# Project 6.1: From Strain gauge to Computer

## Overview

Project 6.1 involves creating a system where an ESP32 wirelessly transmits strain gauge sensor values to a computer. This project enhances the capabilities of an earlier setup (we can resuse project4.ino) by incorporating wireless data transmission, allowing remote monitoring of sensor data.

## Material

1. Strain Gauge
2. HX711 Amplifier
3. ESP32
4. TFT screen

## Objectives

### Computer

1. Socket Creation and Configuration: The program creates a UDP socket and configures it for non-blocking mode
2. Connection Setup: It sets up the address and port details for both the client and the server (ESP32), and binds the socket to the client's address.
3. Receiving Data: receive data continuously from the ESP32. The data received is displayed in the console. The program listens to signal interrupting to shut down.

### ESP32

1. Sensor and Display Initialization: Set up the HX711 load cell for weight measurement and initializes the TFT display.
2. Network Configuration: Configures the ESP32 to act as a WiFi access point and starts a UDP server to send data to the client defined by its IP and PORT.
3. Data Handling and Transmission: Measure the weight, displays it on the TFT, and sends this data to the client.

## Hardware Assembly

<img src="https://raw.githubusercontent.com/matoanbach/Starter-Kit/main/pics/p4.png">

## Network Diagram

<img src="https://raw.githubusercontent.com/matoanbach/Starter-Kit/main/pics/p6_11.jpeg">

## Pseudocode for Client

```cpp
Include necessary libraries

Define constants for buffer length, server and client ports, and server IP

Initialize signal handlers for clean shutdown

Main:
    Initialize socket and server/client structures
    Create and configure UDP socket
    Bind the socket to the client's address
    Connect the socket to the server's address
    Enter a loop:
        Receive data from the server
        Print received data to console
        Check for "quit" command to terminate loop
    Close the socket and terminate

```

## Pseudocode for ESP32

```cpp
Include necessary libraries for WiFi, HX711, and TFT display

Define constants for pin configurations and network settings

Setup:
    Initialize serial communication and TFT display
    Configure WiFi access point and display network details
    Initialize and configure HX711 load cell
    Start UDP server
    Begin task for sending data

Send Task:
    Loop continuously:
        Measure weight with HX711
        Format and send weight data via UDP to the client
        Delay briefly

Loop:
    Measure weight
    Display weight on TFT display
    Delay briefly to update display

```

## Instruction

1. Download project6_1.ino
2. Change your ESP32 name and password for the access point if you want
3. Verify and upload the instruction into the ESP32
4. Connect your computer to the ESP32 access point
5. Download client file
6. On your terminal, go to the client file and run:

```console
make clean all
```

```console
./client
```

## What you should see
To proceed to measure an object, we need to calibrate it first, so visit project 4 to see how we can calibrate. 

<img src="https://raw.githubusercontent.com/matoanbach/Starter-Kit/main/pics/p6_12.jpeg" width="50%">

<img src="https://raw.githubusercontent.com/matoanbach/Starter-Kit/main/pics/p6_13.jpeg" width="50%">
