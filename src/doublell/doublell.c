#include "doublell.h"

#include <stdlib.h>

#include "sharedData.h"
static void deleteDoubleLl(doubleLl *head) {
    if (head == NULL) return;
    doubleLl *ptr = head;
    doubleLl *last;

    do {
        sdsfree(ptr->value);
        last = ptr;
        ptr = ptr->tail;
        free(last);
    } while (ptr);
}
static void deleteListStruct(listStruct *list) {
    if (list == NULL) return;
    deleteDoubleLl(list->head);
    free(list);
}
static void insertDoubleLl(doubleLl **head, doubleLl **tail, sds value) {
    doubleLl *new = (doubleLl *)malloc(sizeof(doubleLl));
    new->tail = NULL;
    new->value = sdsdup(value);
    if (*head == NULL) {
        new->head = NULL;
        *head = new;
        *tail = new;
        return;
    }
    new->head = *tail;
    *tail = new;
}
static listStruct *insertToListStruct(listStruct *list, sds value) {
    if (list == NULL) {
        listStruct *new = (listStruct *)malloc(sizeof(listStruct));
        new->head = NULL;
        new->tail = NULL;
        new->len = 0;
        insertDoubleLl(&(new->head), &(new->tail), value);
        return new;
    }
    insertDoubleLl(&(list->head), &(list->tail), value);
    list->len += 1;
    return list;
}
void insertListToTable(hashStruct *hashTable, const size_t hashTableSize, const sds key, const sds value) {
    const size_t pos = getTablePos(hashTableSize, key);
    for (size_t i = 0; i < hashTableSize; i++) {
        const size_t tmp = pos + probeFunc(i);
        if (hashTable[tmp].exist == false || sdscmp(hashTable[tmp].key, key) == 0) {
            hashTable[tmp].key = sdsdup(key);
            insertToListStruct((listStruct *)hashTable[tmp].pointer, value);
            hashTable[tmp].type = doublell;
            hashTable[tmp].exist = true;
            return;
        }
    }
    // TODO
    exit(EXIT_FAILURE);
}
bool deleteListByKeyInTable(hashStruct *hashTable, const size_t hashTableSize, const sds key) {
    hashStruct *table = findHashTable(hashTable, hashTableSize, key);
    if (table) {
        deleteListStruct((listStruct *)table->pointer);
        sdsfree(table->key);
        table->exist = false;
        table->type = null;
        return true;
    } else
        return false;
}
bool renameListKeyInTable(hashStruct *hashTable, const size_t hashTableSize, const sds oldkey, const sds newkey) {
    hashStruct *table = findHashTable(hashTable, hashTableSize, oldkey);
    sds tmpValue;
    if (table) {
        tmpValue = sdsdup((sds)table->pointer);
        deleteListStruct((listStruct *)table->pointer);
        sdsfree(table->key);
        table->exist = false;
        insertListToTable(hashTable, hashTableSize, newkey, tmpValue);
        sdsfree(tmpValue);
        return true;

    } else
        return false;
}