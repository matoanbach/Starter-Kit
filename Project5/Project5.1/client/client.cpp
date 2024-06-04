// Include necessary libraries for MPU6050 and TFT display
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
using namespace std;

// Constant defining the maximum length of the buffer used for reading and sending
const int BUF_LEN = 255;
// Boolean variable to control the main loop of the client.
bool is_running;
// Port number on which the server is expected to listen
int PORT = 4210;
// The IP address of the server.
char IP_ADDRESS[] = "192.168.4.1";

int main()
{
    int len;
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUF_LEN] = {0};

    // creates a UDP socket. AF_INET specifies the IPv4 protocol, and SOCK_DGRAM specifies the datagram (UDP) socket type.
    cout << "client: socket()" << endl;
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        std::cerr << "Socket creation error" << std::endl;
        return -1;
    }

    // The family is set to AF_INET (IPv4)
    serv_addr.sin_family = AF_INET;

    // ensure it's in network byte order.
    serv_addr.sin_port = htons(PORT);

    // converts the IP address string IP_ADDRESS to a network address structure.
    if (inet_pton(AF_INET, IP_ADDRESS, &serv_addr.sin_addr) <= 0)
    {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return -1;
    }

    // Connect to the server
    cout << "server: connect()" << endl;
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "Connection Failed" << std::endl;
        return -1;
    }

    is_running = true;
    // Continues to read data from stdin using read().
    while (is_running && (len = read(STDIN_FILENO, buffer, BUF_LEN)) > 0)
    {
        // Sends the data to the server using write(). If the entire message is not sent, it reports an error.
        if (write(sock, buffer, sizeof(buffer)) < len)
        {
            cout << "Error: send message failed." << endl;
        }
        else
        {
            // Prints the sent message for confirmation.
            cout << "message sent: " << buffer << endl;
        }
        // Checks if the message is "quit" (to exit the loop and close the client).
        if (strncmp("quit", buffer, 4) == 0)
        {
            is_running = false;
        }
        memset(&buffer, 0, sizeof(buffer));
    }

    // Closes the socket with close(sock) to release resources
    close(sock);
    return 0;
}
