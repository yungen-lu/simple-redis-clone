#ifndef SERVER_H
#define SERVER_H
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../data/data.h"
#include "../parseInput/parseInput.h"
#define MAX_CON 2
#define BLOCK_SIZE 4096
#define HASH_TABLE_SIZE 4096
struct sockaddr_in *setServerOptions(sa_family_t ip, in_addr_t addr, unsigned int port);
int *startServer(struct sockaddr_in *options);
void listinLoop(int *server_fd, struct sockaddr_in *options);
#endif