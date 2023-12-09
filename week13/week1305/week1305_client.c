#include "unp.h" //daytimetcpcli.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 13

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

int main(int argc, char **argv)
{
    if (argc != 2)
        err_quit("usage: a.out <IPaddress>");

    int sockfd = connectToServerTCP(argv[1]);
    int n;
    char recvline[MAXLINE];

    // Read time from server
    while ((n = read(sockfd, recvline, MAXLINE)) > 0)
    {
        recvline[n] = 0; /* null terminate */
        if (fputs(recvline, stdout) == EOF)
            err_sys("fputs error");
    }
    if (n < 0)
        err_sys("read error");
    exit(0);
}