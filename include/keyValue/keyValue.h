#ifndef DATA_H
#define DATA_H
#include "../sharedData/sharedData.h"

void insertStringDataToTable(hashStruct *hashTable, const size_t hashTableSize, const sds key, const sds value);
bool deleteStringByKeyInTable(hashStruct *hashTable, const size_t hashTableSize, const sds key);
bool renameStringKeyInTable(hashStruct *hashTable, const size_t hashTableSize, const sds oldkey, const sds newkey);

#endif