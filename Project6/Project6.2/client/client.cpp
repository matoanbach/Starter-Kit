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
const int BUF_LEN = 255;            // Buffer length for data
bool is_running = true;             // Control variable for the main thread and receiving thread
const int CLIENT_PORT = 4211;       // Port number for client
const int SERVER_PORT = 4210;       // Port number for server
char SERVER_ADDR[] = "192.168.4.1"; // Server address
struct sockaddr_in client;          // Client address
struct sockaddr_in server;          // Server address (ESP32 address)

// File handling variables
int open_flags = O_WRONLY | O_CREAT | O_TRUNC;                              // Flags for file opening (write-only, create if not exist, truncate when opening)
int file_perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; // File permissions
int file;                                                                   // File descriptor ID

void *send_func(void *arg);

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

int main()
{
    // Open a log file to write incoming data
    int file = open("log.txt", open_flags, file_perms);
    if (file == -1)
    {
        cout << "Failed to open file" << endl;
        return -1;
    }

    // Initialize client details
    int fd, ret, len;
    memset((char *)&client, 0, sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons(CLIENT_PORT);
    client.sin_addr.s_addr = htonl(INADDR_ANY);

    // Initialize server details
    memset((char *)&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(4210);
    if ((ret = inet_pton(AF_INET, "192.168.4.1", &server.sin_addr)) == 0)
    {
        cout << "Error: " << strerror(errno) << endl;
        close(file);
        return -1;
    }

    // Create UDP socket
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        cout << "Error: " << strerror(errno) << endl;
        close(file);
        return -1;
    }

    // Get socket flags
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0)
    {
        cout << "Error: " << strerror(errno) << endl;
        close(file);
        close(fd);
        return -1;
    }
    // Set socket to non-blocking mode
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0)
    {
        cout << "Error: " << strerror(errno) << endl;
        close(file);
        close(fd);
        return -1;
    }
    // Bind the client socket
    if ((ret = bind(fd, (struct sockaddr *)&client, sizeof(client))) < 0)
    {
        cout << "Error: " << strerror(errno) << endl;
        close(file);
        close(fd);
        return -1;
    }
    // Connect to the server
    if ((ret = connect(fd, (struct sockaddr *)&server, sizeof(server))) < 0)
    {
        cout << "Error: " << strerror(errno) << endl;
        close(file);
        close(fd);
        return -1;
    }
    // Start a new thread to handle sending data
    pthread_t send_tid;
    pthread_create(&send_tid, NULL, send_func, &fd);

    // Initialize receive address
    struct sockaddr_in recvaddr;
    socklen_t addrlen = sizeof(recvaddr);
    char buffer[BUF_LEN];

    // Receive and log data into a separate file
    while (is_running)
    {
        memset(&buffer, 0, sizeof(buffer));
        if ((len = recvfrom(fd, buffer, BUF_LEN, 0, (struct sockaddr *)&recvaddr, &addrlen)) > 0)
        {
            write(file, buffer, sizeof(buffer));
        }
    }
    // Client and exit
    pthread_join(send_tid, NULL);
    close(file);
    close(fd);
    return EXIT_SUCCESS
}

// Function to handle sending data based on user input
void *send_func(void *arg)
{
    int fd = *(int *)arg;
    char buf[BUF_LEN];
    int len;
    int ret;
    while (is_running)
    {
        cout << "1. Acceleration" << endl;
        cout << "2. Rotation" << endl;
        cout << "3. Temperature" << endl;
        cout << "0. Exit" << endl;
        len = read(STDIN_FILENO, buf, sizeof(buf));

        if (strncmp(buf, "0", 1) == 0)
            is_running = false;
        ret = sendto(fd, buf, sizeof(buf), 0, NULL, 0);
        system("clear");
    }
    pthread_exit(NULL);
}
