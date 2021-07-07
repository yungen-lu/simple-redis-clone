#include "keyValue.h"

#include "sharedData.h"

void insertStringDataToTable(hashStruct *hashTable, const size_t hashTableSize, const sds key, const sds value) {
    hashStruct *table = findHashTable(hashTable, hashTableSize, key);
    if (table) {
        table->key = sdsdup(key);
        table->pointer = sdsdup(value);
        table->type = sdsString;
        table->exist = true;
    } else {
        // TODO
        exit(EXIT_FAILURE);
    }
}
bool deleteStringByKeyInTable(hashStruct *hashTable, const size_t hashTableSize, const sds key) {
    hashStruct *table = findHashTable(hashTable, hashTableSize, key);
    if (table) {
        sdsfree((sds)table->pointer);
        sdsfree(table->key);
        table->exist = false;
        table->type = null;
        return true;
    } else
        return false;
}
bool renameStringKeyInTable(hashStruct *hashTable, const size_t hashTableSize, const sds oldkey, const sds newkey) {
    hashStruct *table = findHashTable(hashTable, hashTableSize, oldkey);
    if (table) {
        sdsfree(table->key);
        table->type = null;
        table->exist = false;
        sds tmpString = (sds)table->pointer;
        hashStruct *newTable = findHashTable(hashTable, hashTableSize, newkey);
        newTable->exist = true;
        newTable->key = sdsdup(newkey);
        newTable->pointer = tmpString;
        return true;
    } else
        return false;
}