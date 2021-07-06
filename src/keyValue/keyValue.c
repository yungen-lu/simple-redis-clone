#include "keyValue.h"

#include "murmurhash.h"

hashStruct *createHashTable(const size_t hashTableSize) {
    hashStruct *new = (hashStruct *)malloc(sizeof(hashStruct) * hashTableSize);
    for (size_t i = 0; i < hashTableSize; i++) {
        new->exist = false;
        new->type = null;
    }
    return new;
}
void deleteHashTable(hashStruct *hashTable, const size_t hashTableSize) {
    for (size_t i = 0; i < hashTableSize; i++) {
        if (hashTable[i].exist == true) {
            sdsfree(hashTable[i].key);
            sdsfree((sds)hashTable[i].pointer);
        }
    }
    free(hashTable);
}
InMemStructs *createInMemStructs(const size_t hashTableSize) {
    InMemStructs *new = (InMemStructs *)malloc(sizeof(InMemStructs));
    new->hashTable = createHashTable(hashTableSize);
    new->hashTableSize = hashTableSize;
    return new;
}
static const int probeFunc(const size_t i) { return i * i * (i % 2) * -1; }
static size_t getTablePos(const size_t hashTableSize, const sds string) {
    return murmurhash(string, (uint32_t)sdslen(string), SEED) % hashTableSize;
}
static hashStruct *findHashTable(hashStruct *hashTable, const size_t hashTableSize, const sds key) {
    const size_t pos = getTablePos(hashTableSize, key);
    for (size_t i = 0; i < hashTableSize; i++) {
        const size_t tmp = (pos + probeFunc(i)) % hashTableSize;
        if (hashTable[tmp].exist == true && (sdscmp(hashTable[tmp].key, key) == 0)) {
            return &hashTable[tmp];
        }
    }
    // TODO
    return NULL;
}
void insertDataToTable(hashStruct *hashTable, const size_t hashTableSize, const sds key, const sds value) {
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
sds findByKeyInTable(hashStruct *hashTable, const size_t hashTableSize, const sds key) {
    hashStruct *table = findHashTable(hashTable, hashTableSize, key);
    if (table) {
        return (sds)table->pointer;
    } else {
        // TODO
        return NULL;
    }
}
bool deleteByKeyInTable(hashStruct *hashTable, const size_t hashTableSize, const sds key) {
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
bool checkExsistsByKeyInTable(hashStruct *hashTable, const size_t hashTableSize, const sds key) {
    hashStruct *table = findHashTable(hashTable, hashTableSize, key);
    if (table) {
        return true;
    } else
        return false;
}
bool renameKeyInTable(hashStruct *hashTable, const size_t hashTableSize, const sds oldkey, const sds newkey) {
    hashStruct *table = findHashTable(hashTable, hashTableSize, oldkey);
    sds tmpValue;
    if (table) {
        tmpValue = sdsdup((sds)table->pointer);
        sdsfree((sds)table->pointer);
        sdsfree(table->key);
        table->exist = false;
        insertDataToTable(hashTable, hashTableSize, newkey, tmpValue);
        sdsfree(tmpValue);
        return true;

    } else
        return false;
}