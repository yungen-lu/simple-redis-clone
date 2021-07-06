#ifndef DOUBLELL_H
#define DOUBLELL_H
#include "../sharedData/sharedData.h"
typedef struct doubleLl {
    sds value;
    struct doubleLl *head;
    struct doubleLl *tail;

} doubleLl;
typedef struct {
    doubleLl *head;
    doubleLl *tail;
    size_t len;
} listStruct;

void insertListToTable(hashStruct *hashTable, const size_t hashTableSize, const sds key, const sds value);
bool deleteListByKeyInTable(hashStruct *hashTable, const size_t hashTableSize, const sds key);
bool renameListKeyInTable(hashStruct *hashTable, const size_t hashTableSize, const sds oldkey, const sds newkey);
#endif