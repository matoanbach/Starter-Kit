# Project 6.2: Real-Time IMU Data Logging to computer

## Overview

In Project 6.2, we build up from previous projects by implementing a system that supports bidirectional communication between a computer and an ESP32. This program not only allows the computer to receive data but also to send specific commands to request different types of data. By utilizing UDP protocol for network communication, this project involves the ESP32 sending sensor data based on requests and the computer dynamically displaying and logging this data to a separate file. 

## Material

1. IMU Sensor
2. ESP32
3. TFT Screen

## Objectives:

### Computer

1. UDP protocol: Integrate the computer with UDP protocol as a client that is capable of sending and receiving packages.
2. Command Handling: Implement a loop to continuously listen for user commands via the console and send those commands to the ESP32 to request specific type of data (e.g., accelerometer, gyroscope, temperature sensor).
3. Data Retrieval and Logging: Log the received sensor data into a file for storing and display it in real-time on a console

### ESP32

1. UDP protocol: Integrate the ESP32 with UDP protocol as a server that is capable of sending and receiving packages.
2. Command Handling: Implement a loop to continuously listen for computer commands via UDP network, then process those commands and send back the data that the computer wants.
3. Data Display and Sending: Process sensor data to display it on the screen and send it the computer continuously.

## Hardware Assembly

<img src="https://raw.githubusercontent.com/matoanbach/Starter-Kit/main/pics/p4.png" width="100%">

## Network Diagram

<img src="https://raw.githubusercontent.com/matoanbach/Starter-Kit/main/pics/p6_24.jpeg" width="100%">

## Pseudocode for ESP32

```cpp
Include necessary libraries for networking, graphics, and sensors

Define constants and settings for WiFi, UDP, and sensor components

Setup function:
  Initialize serial and display settings
  Configure WiFi as an access point and display IP details
  Begin listening for UDP packets on a specified port
  Initialize and configure the MPU6050 sensor
  Create tasks for sending data, receiving data, and displaying data

Receive Task:
  Continuously check for and read incoming UDP packets
  Parse received data to determine response type

Send Task:
  Continuously check response type and send appropriate sensor data via UDP
  Handle different types of data requests (acceleration, rotation, temperature)

Display Task:
  Continuously update and display sensor data on the TFT screen
  Display system and network status

Main Loop:
  Perform no operations, as all functionality is handled within tasks
```

## Pseudocode for Client

```cpp
Include necessary libraries

Define constants and global variables

Define signal handling function to stop the program on SIGINT or SIGTSTP

Define main function:
    Open log file for writing
    If file opening fails, terminate the program

    Configure client socket address structure
    Configure server socket address structure
    Convert and set server IP address

    Create UDP socket
    Set socket to non-blocking mode

    Bind the socket to the client's address
    Connect the socket to the server's address

    Create a thread for sending data

    Enter a loop that runs until the program is signaled to stop:
        Wait for incoming data on the socket
        If data is received, write it to the file

    On loop exit, join the send thread and close the file and socket

Define send function for the thread:
    Continuously read commands from the user
    Send these commands to the server
    If the user enters "0", stop the loop and exit the thread
```

## Instruction

1. Download project6_2.ino
2. Change your ESP32 name and password for the access point if you want
3. Verify and upload the instruction into the ESP32
4. Connect your computer to the ESP32 access point
5. Download client file
6. On your terminal, go to the client file and run:

```console
make clean all
```

7. Create a new terminal, go to the client file and run:

```console
tail -f log.txt
```

## What you should see

<img src="https://raw.githubusercontent.com/matoanbach/Starter-Kit/main/pics/p6_23.png" width="70%">
<img src="https://raw.githubusercontent.com/matoanbach/Starter-Kit/main/pics/p6_22.png" width="100%">
