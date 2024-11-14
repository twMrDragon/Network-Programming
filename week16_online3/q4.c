#include "unp.h" //week1308_server.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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
    serverAddress.sin_port = htons(atoi(argv[1]));

    // Binding the socket to localhost:13
    if (bind(server_fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)))
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // send file name
    char filename[256];
    printf("Filename want send to client: ");
    scanf("%s", filename);

    // reveive client signal
    int signal;
    recvfrom(server_fd, &signal, sizeof(signal), 0, (struct sockaddr *)&clientAddress, &clientAddressLen);

    // send file
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
    sendto(server_fd, &fileLength, sizeof(fileLength), 0, (struct sockaddr *)&clientAddress, sizeof(clientAddress));

    // send file data n time
    for (int i = 0; i < numTransmissions; i++)
    {
        char buffer[MESSAGE_LEN];
        memset(buffer, 0, MESSAGE_LEN);

        // read data from file
        int bytesRead = fread(buffer, 1, MESSAGE_LEN - 1, file);

        // send data
        sendto(server_fd, buffer, bytesRead, 0, (struct sockaddr *)&clientAddress, sizeof(clientAddress));

        // wait a time
        usleep(10000);
    }

    printf("File send success\n");

    // // receive data
    // long fileLength;
    // recvfrom(server_fd, &fileLength, sizeof(fileLength), 0, (struct sockaddr *)&clientAddress, &clientAddressLen);

    // FILE *file = fopen("receive_file", "wb");
    // if (file == NULL)
    // {
    //     perror("Creat file failed");
    //     exit(EXIT_FAILURE);
    // }

    // for (int i = 0; i < fileLength / (MESSAGE_LEN - 1) + 1; i++)
    // {
    //     char buffer[MESSAGE_LEN];
    //     memset(buffer, 0, MESSAGE_LEN);
    //     int bytesRead = recvfrom(server_fd, buffer, MESSAGE_LEN - 1, 0, (struct sockaddr *)&clientAddress, &clientAddressLen);
    //     fwrite(buffer, 1, bytesRead, file);
    // }
    // printf("File recevice success\n");

    fclose(file);
    close(server_fd);
    exit(EXIT_FAILURE);
}

#include "unp.h" //week1308_client.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MESSAGE_LEN 256

int main(int argc, char **argv)
{
    if (argc != 3)
        err_quit("usage: a.out <IPaddress> <Port>");

    int clientSocket = 0;
    struct sockaddr_in serverAddress;

    // Creating socket file descriptor
    if ((clientSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(atoi(argv[2]));

    // Convert IPv4 address from argv
    if (inet_pton(AF_INET, argv[1], &serverAddress.sin_addr) <= 0)
        err_quit("inet_pton error for %s", argv[1]);

    // tell server want to receive file
    int signal = 1;
    sendto(clientSocket, &signal, sizeof(signal), 0, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

    // receive data
    long fileLength;
    recvfrom(clientSocket, &fileLength, sizeof(fileLength), 0, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

    FILE *file = fopen("receive_file.png", "wb");
    if (file == NULL)
    {
        perror("Creat file failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < fileLength / (MESSAGE_LEN - 1) + 1; i++)
    {
        char buffer[MESSAGE_LEN];
        memset(buffer, 0, MESSAGE_LEN);
        int bytesRead = recvfrom(clientSocket, buffer, MESSAGE_LEN - 1, 0, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
        fwrite(buffer, 1, bytesRead, file);
    }
    printf("File recevice success\n");

    // close file and socket
    fclose(file);
    close(clientSocket);

    return 0;
}