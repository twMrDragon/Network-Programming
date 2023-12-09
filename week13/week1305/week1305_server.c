#include "unp.h" //daytimetcpsrv.c
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 13

int createServerWithTCP()
{
    int server_fd, new_socket;
    struct sockaddr_in serverAddress;
    int addrLen = sizeof(serverAddress);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    // Binding the socket to localhost:13
    if (bind(server_fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)))
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listening for incoming connections
    if (listen(server_fd, LISTENQ) < 0)
    {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    // Accepting incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&serverAddress, (socklen_t *)&addrLen)) < 0)
    {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }
    return new_socket;
}

int main(int argc, char **argv)
{
    int new_socket = createServerWithTCP();

    // 回傳時間
    time_t ticks;
    char buffer[MAXLINE]; // 訊息緩衝區長度
    ticks = time(NULL);
    snprintf(buffer, sizeof(buffer), "=@>%.24s\r\n", ctime(&ticks));
    write(new_socket, buffer, strlen(buffer));
    close(new_socket);
}