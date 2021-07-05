#include "data.h"

#include "sds.h"

hashStruct *createHashTable(const size_t hashTableSize) {
    hashStruct *new = (hashStruct *)malloc(sizeof(hashStruct) * hashTableSize);
    for (size_t i = 0; i < hashTableSize; i++) {
        new->exist = false;
    }
    return new;
}
void deleteHashTable(hashStruct *hashTable, const size_t hashTableSize) {
    for (size_t i = 0; i < hashTableSize; i++) {
        if (hashTable[i].exist == true) {
            sdsfree(hashTable[i].key);
            sdsfree(hashTable[i].value);
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
static const int probeFunc(const int i) { return i * i * (i % 2) * -1; }
static size_t getTablePos(const size_t hashTableSize, const sds string) {
    return murmurhash(string, (uint32_t)sdslen(string), SEED) % hashTableSize;
}
void insertDataToTable(hashStruct *hashTable, const size_t hashTableSize, const sds key, const sds value) {
    const size_t pos = getTablePos(hashTableSize, key);
    for (size_t i = 0; i < hashTableSize; i++) {
        const size_t tmp = pos + probeFunc(i);
        if ((hashTable[tmp].exist == false || sdscmp(hashTable[tmp].key, key) == 0)) {
            hashTable[tmp].key = sdsdup(key);
            hashTable[tmp].value = sdsdup(value);
            hashTable[tmp].exist = true;
            return;
        }
    }
    // TODO
    perror("can't find position in table");
    exit(EXIT_FAILURE);
}
sds findByKeyInTable(hashStruct *hashTable, const size_t hashTableSize, const sds key) {
    const size_t pos = getTablePos(hashTableSize, key);
    for (size_t i = 0; i < hashTableSize; i++) {
        const size_t tmp = (pos + probeFunc(i)) % hashTableSize;
        if (hashTable[tmp].exist == true && (sdscmp(hashTable[tmp].key, key) == 0)) {
            return hashTable[tmp].value;
        }
    }
    perror("not find");
    return NULL;
}
bool deleteByKeyInTable(hashStruct *hashTable, const size_t hashTableSize, const sds key) {
    const size_t pos = getTablePos(hashTableSize, key);
    for (size_t i = 0; i < hashTableSize; i++) {
        const size_t tmp = pos + probeFunc(i);
        if (hashTable[tmp].exist == true && (sdscmp(hashTable[tmp].key, key) == 0)) {
            sdsfree(hashTable[tmp].value);
            sdsfree(hashTable[tmp].key);
            hashTable[tmp].exist = false;
            return true;
        }
    }
    return false;
}