#include "doublell.h"

#include <stdio.h>
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
static void insertDoubleLlRight(doubleLl **head, doubleLl **tail, sds value) {
    doubleLl *new = (doubleLl *)malloc(sizeof(doubleLl));
    new->tail = NULL;
    new->value = sdsdup(value);
    if (*head == NULL && *tail == NULL) {
        new->head = NULL;
        *head = new;
        *tail = new;
        return;
    }
    new->head = *tail;
    *tail = new;
}
static void insertDoubleLlLeft(doubleLl **head, doubleLl **tail, sds value) {
    doubleLl *new = (doubleLl *)malloc(sizeof(doubleLl));
    new->head = NULL;
    new->value = sdsdup(value);
    if (*head == NULL && *tail == NULL) {
        new->tail = NULL;
        *head = new;
        *tail = new;
        return;
    }
    new->tail = *head;
    *head = new;
}

static sds popDoubleLlLeft(doubleLl **oldHead) {
    if (*oldHead == NULL) {
        fprintf(stderr, "doubell is null");
        return NULL;
    }
    doubleLl *newHead = (*oldHead)->tail;
    sds returnValue = (*oldHead)->value;
    free(*oldHead);
    if (newHead) {
        newHead->head = NULL;
    }
    *oldHead = newHead;
    return returnValue;
}
static sds popDoubleLlRight(doubleLl **oldTail) {
    if (*oldTail == NULL) {
        fprintf(stderr, "doubell is null");
        return NULL;
    }
    doubleLl *newTail = (*oldTail)->head;
    sds returnValue = (*oldTail)->value;
    free(*oldTail);
    if (newTail) {
        newTail->tail = NULL;
    }
    *oldTail = newTail;
    return returnValue;
}

static sds popStruct(listStruct *list, enum leftright type) {
    if (list == NULL) {
        fprintf(stderr, "list is null");
        return NULL;
    }
    if (type == left) {
        return popDoubleLlLeft(&(list->head));
    } else {
        return popDoubleLlRight(&(list->tail));
    }
}
static listStruct *insertToListStruct(listStruct *list, sds value, enum leftright type) {
    if (list == NULL) {
        listStruct *new = (listStruct *)malloc(sizeof(listStruct));
        new->head = NULL;
        new->tail = NULL;
        new->len = 0;
        insertDoubleLlLeft(&(new->head), &(new->tail), value);
        return new;
    }
    if (type == left) {
        insertDoubleLlLeft(&(list->head), &(list->tail), value);
    } else {
        insertDoubleLlRight(&(list->head), &(list->tail), value);
    }
    list->len += 1;
    return list;
}
bool insertListToTable(hashStruct *hashTable, const size_t hashTableSize, const sds key, const sds value,
                       enum leftright type) {
    const size_t pos = getTablePos(hashTableSize, key);
    for (size_t i = 0; i < hashTableSize; i++) {
        const size_t tmp = pos + probeFunc(i);
        if (hashTable[tmp].exist == false || sdscmp(hashTable[tmp].key, key) == 0) {
            hashTable[tmp].key = sdsdup(key);
            hashTable[tmp].pointer = insertToListStruct((listStruct *)hashTable[tmp].pointer, value, type);
            hashTable[tmp].type = doublell;
            hashTable[tmp].exist = true;
            return true;
        }
    }
    // TODO
    // exit(EXIT_FAILURE);
    return false;
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
    if (table) {
        listStruct *tmp = (listStruct *)table->pointer;
        sdsfree(table->key);
        table->type = null;
        table->exist = false;
        hashStruct *newTable = findHashTable(hashTable, hashTableSize, newkey);
        newTable->exist = true;
        newTable->type = doublell;
        newTable->key = sdsdup(newkey);
        newTable->pointer = tmp;
        return true;

    } else
        return false;
}
sds popListByKeyInTable(hashStruct *hashTable, const size_t hashTableSize, const sds key, enum leftright type) {
    hashStruct *table = findHashTable(hashTable, hashTableSize, key);
    if (table) {
        return popStruct((listStruct *)table->pointer, type);
    } else
        // TODO
        fprintf(stderr, "error cant find table");
    return NULL;
}
