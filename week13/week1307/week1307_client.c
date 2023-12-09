#include "unp.h" //week1307_client.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 13
#define MESSAGE_LEN 256

void encryptByShift(char *data, int shiftN)
{
    char *p = data;
    while (*p != '\0')
    {
        if (*p >= 'A' && *p <= 'Z')
        {
            (*p) = ((*p) - 'A' + shiftN) % 26 + 'A';
        }
        else if (*p >= 'a' && *p <= 'z')
        {
            (*p) = ((*p) - 'a' + shiftN) % 26 + 'a';
        }
        p++;
    }
}

void encryptInputAndWriteToFile(const char *filename)
{
    FILE *fp;
    char buffer[MESSAGE_LEN];

    printf("Input a sentence: ");
    scanf("%[^\n]s", buffer);
    encryptByShift(buffer, 4);

    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error opening file");
        exit(EXIT_FAILURE);
    }
    fwrite(buffer, sizeof(char), strlen(buffer), fp);
    fclose(fp);
}

void sendFile(int sockfd, const char *filename)
{
    char buffer[MESSAGE_LEN];
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }
    int byteRead;
    while ((byteRead = fread(buffer, 1, MESSAGE_LEN, file)) > 0)
    {
        send(sockfd, buffer, byteRead, 0);
    }
    fclose(file);
}

int connectToServerTCP(const char *ip)
{
    int sockfd = 0;
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
    encryptInputAndWriteToFile("client.txt");
    sendFile(sockfd, "client.txt");
}
