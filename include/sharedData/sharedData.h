#ifndef SHAREDATA_H
#define SHAREDATA_H
#include <../sds/sds.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../murmurhash/murmurhash.h"
#define SEED 65
enum types { null, sdsString, doublell };
typedef struct {
    sds key;
    void *pointer;
    enum types type;
    bool exist;
} hashStruct;
typedef struct {
    hashStruct *hashTable;
    size_t hashTableSize;
} InMemStructs;
hashStruct *createHashTable(size_t hashTableSize);
InMemStructs *createInMemStructs(const size_t hashTableSize);
void deleteHashTable(hashStruct *hashTable, const size_t hashTableSize);
#endif