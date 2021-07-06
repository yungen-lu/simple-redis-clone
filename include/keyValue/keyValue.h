#ifndef DATA_H
#define DATA_H
#include "../sharedData/sharedData.h"

void insertDataToTable(hashStruct *hashTable, const size_t hashTableSize, const sds key, const sds value);
sds findByKeyInTable(hashStruct *hashTable, const size_t hashTableSize, const sds key);
bool deleteByKeyInTable(hashStruct *hashTable, const size_t hashTableSize, const sds key);
bool checkExsistsByKeyInTable(hashStruct *hashTable, const size_t hashTableSize, const sds key);
bool renameKeyInTable(hashStruct *hashTable, const size_t hashTableSize, const sds oldkey, const sds newkey);

#endif