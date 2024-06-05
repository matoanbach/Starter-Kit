# Challenge

In this project we will explore the real power of ESP32, which is networking. We will set up one way communication where a client sending message and then display the message received on the TFT screen.

# Hardware Assembly

<img src="https://raw.githubusercontent.com/matoanbach/Starter-Kit/main/pics/p2.png">

# Pin Connection

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

# Network Diagram

<img src="https://raw.githubusercontent.com/matoanbach/Starter-Kit/main/pics/p5_1.jpeg" width="60%">

# Pseudocode for the Client

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

# Pseudocode for ESP32

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

# What you should see

<img src="https://raw.githubusercontent.com/matoanbach/Starter-Kit/main/pics/p5_11.jpeg">
