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
const int BUF_LEN = 255;
bool is_running = true;
const int CLIENT_PORT = 4211;
struct sockaddr_in client;
struct sockaddr_in server;

int open_flags =  O_WRONLY | O_CREAT | O_TRUNC;
int file_perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
int file;

// void *recv_func(void *arg);
void *send_func(void *arg);
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
    int file = open("log.txt", open_flags, file_perms);
    if (file == -1)
    {
        cout << "Failed to open file" << endl;
        return -1;
    }

    int fd, ret, len;
    memset((char *)&client, 0, sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons(CLIENT_PORT);
    client.sin_addr.s_addr = htonl(INADDR_ANY);

    memset((char *)&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(4210);
    if ((ret = inet_pton(AF_INET, "192.168.4.1", &server.sin_addr)) == 0)
    {
        cout << "Error: " << strerror(errno) << endl;
        return -1;
    }

    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        cout << "Error: " << strerror(errno) << endl;
        return -1;
    }

    int flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0)
    {
        perror("fcntl(F_GETFL) failed");
        close(fd);
        return -1;
    }

    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0)
    {
        perror("fcntl(F_SETFL) failed");
        close(fd);
        return -1;
    }

    if ((ret = bind(fd, (struct sockaddr *)&client, sizeof(client))) < 0)
    {
        cout << "Error: " << strerror(errno) << endl;
        return -1;
    }

    if ((ret = connect(fd, (struct sockaddr *)&server, sizeof(server))) < 0)
    {
        cout << "Error: " << strerror(errno) << endl;
        return -1;
    }

    pthread_t send_tid;
    pthread_create(&send_tid, NULL, send_func, &fd);
    struct sockaddr_in recvaddr;
    socklen_t addrlen = sizeof(recvaddr);
    char buffer[BUF_LEN];
    while (is_running)
    {
        memset(&buffer, 0, sizeof(buffer));
        if ((len = recvfrom(fd, buffer, BUF_LEN, 0, (struct sockaddr *)&recvaddr, &addrlen)) > 0)
        {
            write(file, buffer, sizeof(buffer));
        }
    }
    pthread_join(send_tid, NULL);
    close(file);
    close(fd);
}

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
