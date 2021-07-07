#include "keyValue.h"

void insertStringDataToTable(hashStruct *hashTable, const size_t hashTableSize, const sds key, const sds value) {
    const size_t pos = getTablePos(hashTableSize, key);
    for (size_t i = 0; i < hashTableSize; i++) {
        const size_t tmp = pos + probeFunc(i);
        if (hashTable[tmp].exist == false || sdscmp(hashTable[tmp].key, key) == 0) {
            hashTable[tmp].key = sdsdup(key);
            hashTable[tmp].pointer = sdsdup(value);
            hashTable[tmp].type = sdsString;
            hashTable[tmp].exist = true;
            return;
        }
    }
    // TODO
    exit(EXIT_FAILURE);
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
        sds tmpValue = (sds)table->pointer;
        sdsfree(table->key);
        table->exist = false;
        insertStringDataToTable(hashTable, hashTableSize, newkey, tmpValue);
        sdsfree(tmpValue);
        return true;

    } else
        return false;
}