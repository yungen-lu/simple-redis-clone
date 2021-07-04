#include "data.h"
#include "server.h"
int main() {
    // struct sockaddr_in *options = setServerOptions(AF_INET, INADDR_ANY, 8080);
    // int *server_fd = startServer(options);
    // listinLoop(server_fd, options);
    size_t hashTableSize = 4096;
    hashStruct *table = createHashTable(hashTableSize);
    insertDataToTable(table, hashTableSize, sdsnew("test2"), sdsnew("lkjldasdj"));
    insertDataToTable(table, hashTableSize, sdsnew("test2"), sdsnew("asldjalskj"));
    insertDataToTable(table, hashTableSize, sdsnew("test3"), sdsnew("laskdlaqj"));
    insertDataToTable(table, hashTableSize, sdsnew("test4"), sdsnew("iiiiik"));
    printf("hello\n");
    printf("%s\n", findByKeyInTable(table, hashTableSize, sdsnew("test2")));
}