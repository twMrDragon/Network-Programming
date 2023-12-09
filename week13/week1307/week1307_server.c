#include "unp.h" //week1307_server.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PORT 13
#define MESSAGE_LEN 256

void decryptByShift(char *data, int shiftN)
{
    char *p = data;
    while (*p != '\0')
    {
        if (*p >= 'A' && *p <= 'Z')
        {
            int temp = ((*p) - 'A' - shiftN) + 'A';
            if (temp < 'A')
                temp += 26;
            *p = temp;
        }
        else if (*p >= 'a' && *p <= 'z')
        {
            int temp = ((*p) - 'a' - shiftN) + 'a';
            if (temp < 'a')
                temp += 26;
            *p = temp;
        }
        p++;
    }
}

void decryptFile(const char *srcFilename, const char *desFilename, int shiftN)
{
    FILE *srcfFile = fopen(srcFilename, "r");
    FILE *desFile = fopen(desFilename, "w");
    char buffer[MESSAGE_LEN];
    if (srcfFile == NULL)
    {
        perror("Source file open fail");
        exit(EXIT_FAILURE);
    }
    if (desFile == NULL)
    {
        perror("Destination file open fail");
        exit(EXIT_FAILURE);
    }
    while (fgets(buffer, sizeof(buffer), srcfFile) != NULL)
    {
        decryptByShift(buffer, shiftN);
        fputs(buffer, desFile);
    }
    fclose(srcfFile);
    fclose(desFile);
}

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

void receiveFile(int new_socket, const char *filename)
{
    char buffer[MESSAGE_LEN];
    FILE *file = fopen(filename, "wb");

    if (file == NULL)
    {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    int bytesRead;
    while ((bytesRead = recv(new_socket, buffer, sizeof(buffer), 0)) > 0)
    {
        fwrite(buffer, 1, bytesRead, file);
    }

    fclose(file);
}

int main(int argc, char **argv)
{
    int new_socket = createServerWithTCP();
    receiveFile(new_socket, "temp.txt");
    decryptFile("temp.txt", "server.txt", 4);
    remove("temp.txt");
}
