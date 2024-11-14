#include "unp.h" //daytimetcpsrv.c
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int createServerWithTCP(const char *port)
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
    serverAddress.sin_port = htons(atoi(port));

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

    printf("Server listening on port %s...\n", port);

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
    int new_socket = createServerWithTCP(argv[1]);

    // 回傳時間
    time_t ticks;
    char buffer[MAXLINE]; // 訊息緩衝區長度
    ticks = time(NULL);
    struct tm *current_time = localtime(&ticks);
    snprintf(buffer, sizeof(buffer), "%04d/%02d/%02d\r\n",
             current_time->tm_year + 1900, current_time->tm_mon + 1, current_time->tm_mday);
    printf("Send To Client:%s", buffer);
    // snprintf(buffer, sizeof(bufer), "=@>%.24s\r\n", ctime(&ticks));
    write(new_socket, buffer, strlen(buffer));
    close(new_socket);
}

#include "unp.h" //daytimetcpcli.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int connectToServerTCP(const char *ip, const char *port)
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
    serverAddress.sin_port = htons(atoi(port));

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
    if (argc != 3)
        err_quit("usage: a.out <IPaddress> <Port>");

    int sockfd = connectToServerTCP(argv[1], argv[2]);
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