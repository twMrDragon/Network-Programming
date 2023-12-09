#include "unp.h" //week1308_server.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PORT 13
#define MESSAGE_LEN 256

int main(int argc, char **argv)
{
    int server_fd, new_socket;
    struct sockaddr_in serverAddress, clientAddress;
    int clientAddressLen = sizeof(clientAddress);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) == 0)
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

    // receive data
    long fileLength;
    recvfrom(server_fd, &fileLength, sizeof(fileLength), 0, (struct sockaddr *)&clientAddress, &clientAddressLen);

    FILE *file = fopen("receive_file", "wb");
    if (file == NULL)
    {
        perror("Creat file failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < fileLength / (MESSAGE_LEN - 1) + 1; i++)
    {
        char buffer[MESSAGE_LEN];
        memset(buffer, 0, MESSAGE_LEN);
        int bytesRead = recvfrom(server_fd, buffer, MESSAGE_LEN - 1, 0, (struct sockaddr *)&clientAddress, &clientAddressLen);
        fwrite(buffer, 1, bytesRead, file);
    }
    printf("File recevice success\n");

    fclose(file);
    close(server_fd);
    exit(EXIT_FAILURE);
}
