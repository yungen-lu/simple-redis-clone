#ifndef SERVER_H
#define SERVER_H
#include <netinet/in.h>  // for sockaddr_in, in_addr
// #include "../keyValue/keyValue.h"
#include "../parseInput/parseInput.h"
#include "../sharedData/sharedData.h"
#define MAX_CON 2
#define BLOCK_SIZE 4096
#define HASH_TABLE_SIZE 4096
struct sockaddr_in *setServerOptions(sa_family_t ip, in_addr_t addr, unsigned int port);
int *startServer(struct sockaddr_in *options);
void listinLoop(int *server_fd, struct sockaddr_in *options);
#endif