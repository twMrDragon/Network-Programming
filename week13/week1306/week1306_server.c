#include "unp.h" //week1306_server.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PORT 13
#define MESSAGE_LEN 256

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

void replyMessage(int new_socket)
{
    char buffer[MESSAGE_LEN]; // 訊息緩衝區長度

    // Return message
    while (1)
    {
        recv(new_socket, buffer, sizeof(buffer), 0);
        if (strcmp(buffer, "Hello~") == 0)
        {
            snprintf(buffer, sizeof(buffer), "Hi~\n");
        }
        else if (strcmp(buffer, "Good!") == 0)
        {
            snprintf(buffer, sizeof(buffer), "Thanks!\n");
        }
        else if (strcmp(buffer, "How are you?") == 0)
        {
            snprintf(buffer, sizeof(buffer), "I am find. How are you.\n");
        }
        else if (strcmp(buffer, "How old are you?") == 0)
        {
            snprintf(buffer, sizeof(buffer), "I am twenty years old.\n");
        }
        else
        {
            snprintf(buffer, sizeof(buffer), "I don't know what you are talk about.\n");
        }
        send(new_socket, buffer, sizeof(buffer), 0);
    }
}

int main(int argc, char **argv)
{
    int new_socket = createServerWithTCP();
    replyMessage(new_socket);
}
