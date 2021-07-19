#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define PORT 8080

int main(int argc, char const *argv[]) {
    int sock;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {'\0'};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    char inputBuffer[4096];
    ssize_t valread;
    while (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) != -1) {
        while (fgets(inputBuffer, 4096, stdin) != NULL) {
            if (send(sock, inputBuffer, strlen(inputBuffer), 0) == -1) {
                fprintf(stderr, "send error\n");
            }
            valread = read(sock, buffer, 1024);
            if (valread < 0) {
                fprintf(stderr, "read error\n");
            }
            buffer[valread] = '\0';
            printf("%s\n", buffer);
        }
    }
    shutdown(sock, SHUT_RDWR);
    close(sock);
    return 0;
}