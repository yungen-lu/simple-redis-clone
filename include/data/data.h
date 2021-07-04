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
hashStruct *createHashTable(size_t hashTableSize);
void insertDataToTable(hashStruct *hashTable, const size_t hashTableSize, const sds key, const sds value);
sds findByKeyInTable(hashStruct *hashTable, const size_t hashTableSize, const sds key);
bool deleteByKeyInTable(hashStruct *hashTable, const size_t hashTableSize, const sds key);
void deleteHashTable(hashStruct *hashTable, const size_t hashTableSize);
