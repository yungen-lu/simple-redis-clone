#include "server.h"
int main() {
    struct sockaddr_in *options = setServerOptions(AF_INET, INADDR_ANY, 8080);
    int *server_fd = startServer(options);
    listinLoop(server_fd, options);
}