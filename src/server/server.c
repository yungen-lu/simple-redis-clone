#include "server.h"
struct sockaddr_in *setServerOptions(sa_family_t ip, in_addr_t addr,
                                     unsigned int port) {
  struct sockaddr_in *address =
      (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
  address->sin_family = ip;
  address->sin_port = htons(port);
  address->sin_addr.s_addr = addr;
  return address;
}
int *startServer(struct sockaddr_in *options) {
  int *server_fd = (int *)malloc(sizeof(int));
  *server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (*server_fd == 0) {
    perror("socket init failed");
    exit(EXIT_FAILURE);
  }
  if (bind(*server_fd, (struct sockaddr *)&*options, sizeof(*options)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }
  if (listen(*server_fd, MAX_CON) < 0) {
    perror("listen failed");
    exit(EXIT_FAILURE);
  } else {
    printf("server is listening at PORT %d\n", ntohs((*options).sin_port));
    return server_fd;
  }
}
void listinLoop(int *server_fd, struct sockaddr_in *options) {
  int new_socket;
  int addrlen = sizeof(*options);
  int readSize;
  char buffer[1024] = {'\0'};
  while ((new_socket = accept(*server_fd, (struct sockaddr *)options,
                              (socklen_t *)&addrlen)) >= 0) {
    readSize = read(new_socket, buffer, 1024);
    printf("%s\n", buffer);
    send(new_socket, "hello", strlen("hello"), 0);
    shutdown(new_socket, SHUT_RDWR);
    close(new_socket);
  }
}
