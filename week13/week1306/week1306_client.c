#include "unp.h" //week1306_client.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
        recv(sockfd, recvline, sizeof(buffer), 0);
        printf("Server: %s", recvline);

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

    exit(0);
}
