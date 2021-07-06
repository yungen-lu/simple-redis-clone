#include "sharedData.h"
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
