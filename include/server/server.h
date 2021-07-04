#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define MAX_CON 2
struct sockaddr_in *setServerOptions(sa_family_t ip, in_addr_t addr,
                                     unsigned int port);
int *startServer(struct sockaddr_in *options);
void listinLoop(int *server_fd, struct sockaddr_in *options);
