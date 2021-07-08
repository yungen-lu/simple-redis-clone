#include "server.h"

#include <netinet/in.h>  // for sockaddr_in, in_addr
#include <stdio.h>       // for printf, size_t
#include <stdlib.h>      // for exit, malloc, free, EXIT_FAILURE, realloc
#include <string.h>
#include <sys/socket.h>  // for accept, bind, listen, shutdown, socket, AF_...
#include <unistd.h>      // for close, read

#include "parseInput.h"  // for parseInput
#include "sharedData.h"  // for createInMemStructs, InMemStructs
struct sockaddr_in *setServerOptions(sa_family_t ip, in_addr_t addr, unsigned short port) {
    struct sockaddr_in *address = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
    address->sin_family = ip;
    address->sin_port = htons(port);
    address->sin_addr.s_addr = addr;
    return address;
}
int *startServer(struct sockaddr_in *options) {
    int *server_fd = (int *)malloc(sizeof(int));
    *server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (*server_fd == 0) {
        fprintf(stderr, "socket init failed");
        exit(EXIT_FAILURE);
    }
    if (bind(*server_fd, (struct sockaddr *)options, sizeof(*options)) < 0) {
        fprintf(stderr, "bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(*server_fd, MAX_CON) < 0) {
        fprintf(stderr, "listen failed");
        exit(EXIT_FAILURE);
    } else {
        printf("server is listening at PORT %d\n", ntohs((*options).sin_port));
        return server_fd;
    }
}
void closeServer(const int *server_fd, struct sockaddr_in *options) {
    close(*server_fd);
    free(options);
}
void listinLoop(const int *server_fd, struct sockaddr_in *options) {
    int new_socket;
    int addrlen = sizeof(*options);
    InMemStructs *structs = createInMemStructs(HASH_TABLE_SIZE);
    while ((new_socket = accept(*server_fd, (struct sockaddr *)options, (socklen_t *)&addrlen)) >= 0) {
        ssize_t readSize;
        size_t offset = 0;
        size_t bufferSize = 2 << 20;
        char *buffer = (char *)malloc(sizeof(char) * bufferSize);
        // SEND
        readSize = read(new_socket, buffer, BLOCK_SIZE);
        if (readSize > 0) {
            buffer[readSize] = '\0';
        }
        parseInput(buffer, structs);
        ssize_t sentBytes;
        char *globalWarningBuffer = getWarningBuffer();
        if (*globalWarningBuffer) {
            sentBytes = send(new_socket, globalWarningBuffer, strlen(globalWarningBuffer), 0);
        } else {
            sentBytes = send(new_socket, "OK", strlen("OK"), 0);
        }
        if (sentBytes == -1) {
            fprintf(stderr, "send error");
        }
        shutdown(new_socket, SHUT_RDWR);
        close(new_socket);
        free(buffer);
    }
}
