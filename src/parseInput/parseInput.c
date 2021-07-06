#include "parseInput.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void showCmdNotFoundError(char *string) {
    fprintf(stderr, "CMD \"%s\" is not valid\n", string);
    // TODO
    // PRINT USAGE
}
static int getCommand(char *string) {
    // char *arrOfCmd[] = {sdsnew("DEL"), sdsnew("DUMP"), sdsnew("EXIST"), sdsnew("RENAME"), sdsnew("SET"),
    // sdsnew("GET")}; sds ptr = string;
    char *arrOfCmd[] = {"DEL", "DUMP", "EXISTS", "RENAME", "SET", "GET"};
    char *ptr = string;
    char buffer[128];
    sscanf(ptr, "%127s", buffer);
    // sds tmp = sdsnew(buffer);
    for (size_t i = 0; i < TOTAL_CMD; i++) {
        if (strncmp(buffer, arrOfCmd[i], 127) == 0) {
            return i + 10;
        }
    }
    // sdsfree(tmp);
    // sdsfreesplitres(arrOfCmd, TOTAL_CMD);
    showCmdNotFoundError(buffer);
    return CMD_NOT_FOUND;
}
static sds *tokenizeString(char *string, int *count) {
    sds *tokens;
    const char *del = " \n\t";
    sds tmp = sdsnew(string);
    tokens = sdssplitlen(tmp, sdslen(tmp), del, 1, count);
    sdsfree(tmp);
    return tokens;
}
static int setCmd(char *string, InMemStructs *structs) {
    int count;
    sds *tokens = tokenizeString(string, &count);
    if (count != 3) {
        fprintf(stderr, "count error:%d\n", count);
        sdsfreesplitres(tokens, count);
        return -1;
    }
    insertDataToTable(structs->hashTable, structs->hashTableSize, tokens[1], tokens[2]);
    sdsfreesplitres(tokens, count);
    return 0;
}
static int getCmd(char *string, InMemStructs *structs) {
    int count;
    sds *tokens = tokenizeString(string, &count);
    if (count != 2) {
        fprintf(stderr, "count error:%d\n", count);
        sdsfreesplitres(tokens, count);
        return -1;
    }
    sds value = findByKeyInTable(structs->hashTable, structs->hashTableSize, tokens[1]);
    if (value) printf("value is :%s\n", value);
    return 0;
}
static int delCmd(char *string, InMemStructs *structs) {
    int count;
    sds *tokens = tokenizeString(string, &count);
    if (count != 2) {
        fprintf(stderr, "count error:%d\n", count);
        sdsfreesplitres(tokens, count);
        return -1;
    }
    if (deleteByKeyInTable(structs->hashTable, structs->hashTableSize, tokens[1])) {
        printf("delete \"%s\" success\n", tokens[1]);
    } else {
        printf("key not found\n");
    }
    return 0;
}
static int existsCmd(char *string, InMemStructs *structs) {
    int count;
    sds *tokens = tokenizeString(string, &count);
    if (count != 2) {
        fprintf(stderr, "count error:%d\n", count);
        sdsfreesplitres(tokens, count);
        return -1;
    }
    if (checkExsistsByKeyInTable(structs->hashTable, structs->hashTableSize, tokens[1])) {
        printf("true\n");
    } else
        printf("false\n");
    return 0;
}
static int renameCmd(char *string, InMemStructs *structs) {
    int count;
    sds *tokens = tokenizeString(string, &count);
    if (count != 3) {
        fprintf(stderr, "count error:%d\n", count);
        sdsfreesplitres(tokens, count);
        return -1;
    }
    if (renameKeyInTable(structs->hashTable, structs->hashTableSize, tokens[1], tokens[2])) {
        printf("key: \"%s\" renamed\n", tokens[1]);
    } else
        fprintf(stderr, "can't rename key");
    return 0;
}
void parseInput(char *string, InMemStructs *structs) {
    // sds sdsString = sdsnew(string);
    switch (getCommand(string)) {
        case DEL_CMD:
            delCmd(string, structs);
            break;
        case DUMP_CMD:
            // DO
            break;
        case EXISTS_CMD:
            existsCmd(string, structs);
            break;
        case RENAME_CMD:
            renameCmd(string, structs);
            break;
        case SET_CMD:
            setCmd(string, structs);
            break;
        case GET_CMD:
            getCmd(string, structs);
            break;
        case CMD_NOT_FOUND:
            // DO
            break;
    }
}
