#include "sharedData.h"

#include <string.h>

#include "murmurhash.h"
#include "sds.h"

static sds WarningBuffer;
void createWarningBuffer() { WarningBuffer = sdsempty(); }
void pushMessageToWarningBuffer(sds message) { WarningBuffer = sdscatsds(WarningBuffer, message); }
sds getWarningBuffer() { return WarningBuffer; }
void resetWarningBuffer() {
    deleteWarningBuffer();
    createWarningBuffer();
}
void deleteWarningBuffer() { sdsfree(WarningBuffer); }

hashStruct *createHashTable(const size_t hashTableSize) {
    hashStruct *new = (hashStruct *)malloc(sizeof(hashStruct) * hashTableSize);
    for (size_t i = 0; i < hashTableSize; i++) {
        new->exist = false;
        new->pointer = NULL;
        new->type = null;
    }
    return new;
}
void deleteHashTable(hashStruct *hashTable, const size_t hashTableSize) {
    for (size_t i = 0; i < hashTableSize; i++) {
        if (hashTable[i].exist == true) {
            sdsfree(hashTable[i].key);
            if (hashTable[i].type == sdsString) {
                sdsfree((sds)hashTable[i].pointer);
            }
            if (hashTable[i].type == doublell) {
                // TODO
            }
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
const long probeFunc(const long i) { return i * i * (i % 2) * -1; }
size_t getTablePos(const size_t hashTableSize, const sds string) {
    return murmurhash(string, (uint32_t)sdslen(string), SEED) % hashTableSize;
}
hashStruct *findHashTable(hashStruct *hashTable, const size_t hashTableSize, const sds key) {
    const size_t pos = getTablePos(hashTableSize, key);
    for (size_t i = 0; i < hashTableSize; i++) {
        const size_t tmp = (pos + probeFunc(i)) % hashTableSize;
        if (hashTable[tmp].exist == false) {
            return &hashTable[tmp];
        } else if (sdscmp(hashTable[tmp].key, key) == 0) {
            return &hashTable[tmp];
        }
    }
    // TODO
    return NULL;
}
void *findByKeyInTable(hashStruct *hashTable, const size_t hashTableSize, const sds key) {
    hashStruct *table = findHashTable(hashTable, hashTableSize, key);
    if (table) {
        return table->pointer;
    } else {
        // TODO
        return NULL;
    }
}
bool checkExsistsByKeyInTable(hashStruct *hashTable, const size_t hashTableSize, const sds key) {
    const hashStruct *table = findHashTable(hashTable, hashTableSize, key);
    if (table) {
        return true;
    } else
        return false;
}
