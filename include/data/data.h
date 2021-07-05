#ifndef DATA_H
#define DATA_H
#include <../sds/sds.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../murmurhash/murmurhash.h"
#define SEED 65
typedef struct {
    sds key;
    sds value;
    bool exist;
} hashStruct;
typedef struct {
    hashStruct *hashTable;
    size_t hashTableSize;
} InMemStructs;

hashStruct *createHashTable(size_t hashTableSize);
InMemStructs *createInMemStructs(const size_t hashTableSize);
void insertDataToTable(hashStruct *hashTable, const size_t hashTableSize, const sds key, const sds value);
sds findByKeyInTable(hashStruct *hashTable, const size_t hashTableSize, const sds key);
bool deleteByKeyInTable(hashStruct *hashTable, const size_t hashTableSize, const sds key);
void deleteHashTable(hashStruct *hashTable, const size_t hashTableSize);
#endif