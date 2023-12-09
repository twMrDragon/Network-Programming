#include "unp.h" //week1308_client.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 13
#define MESSAGE_LEN 256

int main(int argc, char **argv)
{
    if (argc != 2)
        err_quit("usage: a.out <IPaddress>");

    int clientSocket = 0;
    struct sockaddr_in serverAddress;

    // Creating socket file descriptor
    if ((clientSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);

    // Convert IPv4 address from argv
    if (inet_pton(AF_INET, argv[1], &serverAddress.sin_addr) <= 0)
        err_quit("inet_pton error for %s", argv[1]);

    char filename[256];
    printf("Filename want to send to server: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        perror("Open file failed");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long fileLength = ftell(file);
    fseek(file, 0, SEEK_SET);

    int numTransmissions = (fileLength / (MESSAGE_LEN - 1)) + 1;

    // send file length;
    sendto(clientSocket, &fileLength, sizeof(fileLength), 0, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

    // send file data n time
    for (int i = 0; i < numTransmissions; i++)
    {
        char buffer[MESSAGE_LEN];
        memset(buffer, 0, MESSAGE_LEN);

        // read data from file
        int bytesRead = fread(buffer, 1, MESSAGE_LEN - 1, file);

        // send data
        sendto(clientSocket, buffer, bytesRead, 0, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

        // wait a time
        usleep(10000);
    }

    printf("File send success\n");

    // close file and socket
    fclose(file);
    close(clientSocket);

    return 0;
}