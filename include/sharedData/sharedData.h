#ifndef SHAREDATA_H
#define SHAREDATA_H

#include <stdbool.h>
#include <stdlib.h>

#include "../sds/sds.h"

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
void createWarningBuffer();
void pushMessageToWarningBuffer(sds message);
sds getWarningBuffer();
void deleteWarningBuffer();
hashStruct *createHashTable(size_t hashTableSize);
InMemStructs *createInMemStructs(const size_t hashTableSize);
void deleteHashTable(hashStruct *hashTable, const size_t hashTableSize);
bool checkExsistsByKeyInTable(hashStruct *hashTable, const size_t hashTableSize, const sds key);

void *findByKeyInTable(hashStruct *hashTable, const size_t hashTableSize, const sds key);
const long probeFunc(const long i);
size_t getTablePos(const size_t hashTableSize, const sds string);
hashStruct *findHashTable(hashStruct *hashTable, const size_t hashTableSize, const sds key);
#endif