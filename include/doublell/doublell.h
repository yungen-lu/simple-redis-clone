#ifndef DOUBLELL_H
#define DOUBLELL_H
#include <stddef.h>

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
enum leftright { left, right };
bool insertListToTable(hashStruct *hashTable, const size_t hashTableSize, const sds key, const sds value,
                       enum leftright type);
bool deleteListByKeyInTable(hashStruct *hashTable, const size_t hashTableSize, const sds key);
bool renameListKeyInTable(hashStruct *hashTable, const size_t hashTableSize, const sds oldkey, const sds newkey);
sds popListByKeyInTable(hashStruct *hashTable, const size_t hashTableSize, const sds key, enum leftright type);
#endif