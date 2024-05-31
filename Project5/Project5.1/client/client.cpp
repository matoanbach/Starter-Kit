#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
using namespace std;

const int BUF_LEN = 255;
bool is_running;
int PORT = 4210;
char IP_ADDRESS[] = "192.168.4.1";

int main()
{
    int len;
    int sock = 0;
    struct sockaddr_in serv_addr;
    const char *message = "Hello, server";
    char buffer[BUF_LEN] = {0};

    cout << "client: socket()" << endl;
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        std::cerr << "Socket creation error" << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT); 
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
    while (is_running && (len = read(STDIN_FILENO, buffer, BUF_LEN)) > 0)
    {

        if (write(sock, buffer, sizeof(buffer)) < len)
        {
            cout << "Error: send message failed." << endl;
        }
        else
        {
            cout << "message sent: " << buffer << endl;
        }
        if (strncmp("quit", buffer, 4) == 0)
        {
            is_running = false;
        }
        memset(&buffer, 0, sizeof(buffer));
    }

    // Close the socket
    close(sock);

    return 0;
}
