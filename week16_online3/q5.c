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

void sendMessage(int sockfd)
{
    char buffer[MESSAGE_LEN];
    char recvline[MESSAGE_LEN];
    while (1)
    {
        recv(sockfd, recvline, sizeof(buffer), 0);
        printf("Client: %s\n", recvline);
        if (strcmp(recvline, "Bye") == 0)
            break;
        printf("Server: ");
        scanf("%[^\n]", buffer);
        // strcat(buffer, "\n");
        send(sockfd, buffer, sizeof(buffer), 0);
        if (strcmp(buffer, "Bye") == 0)
            break;
        // Clear the input buffer
        while (getchar() != '\n')
            ; // Flush the input buffer
    }
}

int main(int argc, char **argv)
{
    int new_socket = createServerWithTCP();
    sendMessage(new_socket);
    close(new_socket);
}

#include "unp.h" //week1306_client.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PORT 13
#define MESSAGE_LEN 256

int connectToServerTCP(const char *ip)
{
    int sockfd;
    struct sockaddr_in serverAddress;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);

    // Convert IPv4 address from argv
    if (inet_pton(AF_INET, ip, &serverAddress.sin_addr) <= 0)
        err_quit("inet_pton error for %s", ip);

    // Connecting to the server
    if (connect(sockfd, (SA *)&serverAddress, sizeof(serverAddress)) < 0)
        err_sys("connect error");
    return sockfd;
}

void sendMessage(int sockfd)
{
    char buffer[MESSAGE_LEN];
    char recvline[MESSAGE_LEN];
    while (1)
    {
        printf("Client: ");
        scanf("%[^\n]", buffer);
        // strcat(buffer, "\n");
        send(sockfd, buffer, sizeof(buffer), 0);
        if (strcmp(buffer, "Bye") == 0)
            break;
        recv(sockfd, recvline, sizeof(buffer), 0);
        printf("Server: %s\n", recvline);
        if (strcmp(recvline, "Bye") == 0)
            break;
        // Clear the input buffer
        while (getchar() != '\n')
            ; // Flush the input buffer
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
        err_quit("usage: a.out <IPaddress>");

    int sockfd = connectToServerTCP(argv[1]);
    sendMessage(sockfd);
    close(sockfd);
    exit(0);
}
