// Include necessary headers for networking and system operations
#include <arpa/inet.h>
#include <iostream>
#include <net/if.h>
#include <netinet/in.h>
#include <signal.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

// Global variables and definitions
const int BUF_LEN = 255;        // Buffer length for data
char buffer[BUF_LEN];           // Buffer used for retrieving data

bool is_running = true;         // Control variable for the main thread and receiving thread
const int CLIENT_PORT = 4211;   // Port number for client
const int SERVER_PORT = 4210;   // Port number for server
char SERVER_ADDR[] = "192.168.4.1";
struct sockaddr_in client;      // Client address
struct sockaddr_in server;      // Server address (ESP32 address)

// Signal handler function to handle signal interrupting when users press control C (SIGINT) or control Z (SIGTSTP)
static void shutdownHandler(int sig)
{
    switch (sig)
    {
    case SIGINT:
        is_running = false;
        break;

    case SIGTSTP:
        is_running = false;
        break;

    default:
        break;
    }
}

int main(){
    // Initialize client details
    int fd, ret, len;
    memset((char*)&client, 0, sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons(CLIENT_PORT);
    client.sin_addr.s_addr = htonl(INADDR_ANY);

    // Initialize server details
    memset((char*)&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    if ((ret = inet_pton(AF_INET, SERVER_ADDR, &server.sin_addr)) == 0)
    {
        cout << "Error: " << strerror(errno) << endl;
        return -1;
    }

    // Create UDP socket
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        cout << "Error:  " << strerror(errno) << endl;
        return -1;
    }

    // Get socket flags
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0)
    {
        perror("fcntl(F_GETFL) failed");
        close(fd);
        return -1;
    }

    // Set socket to non-blocking mode
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0)
    {
        perror("fcntl(F_GETFL) failed");
        close(fd);
        return -1;
    }

    // Bind the client socket
    if ((ret = bind(fd, (struct sockaddr*)&client, sizeof(server))) < 0)
    {
        perror("fcntl(F_GETFL) failed");
        close(fd);
        return -1;
    }
    
    // Connect to the server
    if ((ret = connect(fd, (struct sockaddr*)&server, sizeof(server))) < 0)
    {
        cout << "Error: " << strerror(errno) << endl;
        close(fd);
        return -1;
    }

    // Initialize receive address
    struct sockaddr_in recvaddr;
    socklen_t addrlen = sizeof(recvaddr);
    char buffer[BUF_LEN];

    // Receive and print out data into the console
    while (is_running)
    {
        memset(&buffer, 0, sizeof(buffer));
        if ((len = recvfrom(fd, buffer ,BUF_LEN, 0, (struct sockaddr *)&recvaddr, &addrlen)) > 0)
        {
            cout << buffer << endl;
        }
        
    }
    // close socket and exit 
    close(fd);
    return EXIT_SUCCESS;
}