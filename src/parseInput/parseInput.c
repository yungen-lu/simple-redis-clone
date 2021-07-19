#include "parseInput.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "doublell.h"
#include "keyValue.h"
static void showCmdNotFoundError(char *string) {
    fprintf(stderr, "CMD \"%s\" is not valid\n", string);
    // TODO
    // PRINT USAGE
}
int getCommand(const char *string) {
    char *arrOfCmd[] = {"DEL",   "DUMP", "EXISTS", "RENAME", "SET",   "GET",
                        "LPUSH", "LPOP", "LINDEX", "LLEN",   "RPUSH", "RPOP"};
    char buffer[128];
    sscanf(string, "%127s", buffer);
    if (*buffer) {
        for (int i = 0; i < TOTAL_CMD; i++) {
            if (strncmp(buffer, arrOfCmd[i], 127) == 0) {
                return i + 10;
            }
        }
        showCmdNotFoundError(buffer);
    }
    sds tmp = sdsnew("command not found");
    pushMessageToWarningBuffer(tmp);
    sdsfree(tmp);
    return CMD_NOT_FOUND;
}
static int setCmd(const char *string, InMemStructs *structs) {
    int count;
    sds *tokens = sdssplitargs(string, &count);
    if (count != 3) {
        fprintf(stderr, "count error:%d\n", count);
        sdsfreesplitres(tokens, count);
        return -1;
    }
    insertStringDataToTable(structs->hashTable, structs->hashTableSize, tokens[1], tokens[2]);
    sdsfreesplitres(tokens, count);
    return 0;
}
static int getCmd(const char *string, InMemStructs *structs) {
    int count;
    sds *tokens = sdssplitargs(string, &count);
    if (count != 2) {
        fprintf(stderr, "count error:%d\n", count);
        sdsfreesplitres(tokens, count);
        return -1;
    }
    sds value = findByKeyInTable(structs->hashTable, structs->hashTableSize, tokens[1]);
    if (value) {
        pushMessageToWarningBuffer(value);
    }
    sdsfreesplitres(tokens, count);
    return 0;
}
static int delCmd(const char *string, InMemStructs *structs) {
    int count;
    sds *tokens = sdssplitargs(string, &count);
    if (count != 2) {
        fprintf(stderr, "count error:%d\n", count);
        sdsfreesplitres(tokens, count);
        return -1;
    }
    if (deleteStringByKeyInTable(structs->hashTable, structs->hashTableSize, tokens[1])) {
        printf("delete \"%s\" success\n", tokens[1]);
    } else {
        printf("key not found\n");
        sds tmp = sdsnew("key not found");
        pushMessageToWarningBuffer(tmp);
        sdsfree(tmp);
    }

    sdsfreesplitres(tokens, count);
    return 0;
}
static int existsCmd(const char *string, InMemStructs *structs) {
    int count;
    sds *tokens = sdssplitargs(string, &count);
    if (count != 2) {
        fprintf(stderr, "count error:%d\n", count);
        sdsfreesplitres(tokens, count);
        return -1;
    }
    if (checkExsistsByKeyInTable(structs->hashTable, structs->hashTableSize, tokens[1])) {
        printf("true\n");
        sds tmp = sdsnew("true");
        pushMessageToWarningBuffer(tmp);
        sdsfree(tmp);
    } else {
        printf("false\n");
        sds tmp = sdsnew("false");
        pushMessageToWarningBuffer(tmp);
        sdsfree(tmp);
    }

    sdsfreesplitres(tokens, count);
    return 0;
}
static int renameCmd(const char *string, InMemStructs *structs) {
    int count;
    sds *tokens = sdssplitargs(string, &count);
    if (count != 3) {
        fprintf(stderr, "count error:%d\n", count);
        sdsfreesplitres(tokens, count);
        return -1;
    }
    if (renameStringKeyInTable(structs->hashTable, structs->hashTableSize, tokens[1], tokens[2])) {
        printf("key: \"%s\" renamed\n", tokens[1]);
    } else {
        sds tmp = sdsnew("can't rename key");
        pushMessageToWarningBuffer(tmp);
        sdsfree(tmp);
    }

    sdsfreesplitres(tokens, count);
    return 0;
}
static int popListCmd(const char *string, InMemStructs *structs, enum leftright type) {
    int count;
    sds value;
    sds *tokens = sdssplitargs(string, &count);
    if (count != 2) {
        fprintf(stderr, "count error:%d\n", count);
        sdsfreesplitres(tokens, count);
        return -1;
    }
    if ((value = popListByKeyInTable(structs->hashTable, structs->hashTableSize, tokens[1], type))) {
        printf("%s\n", value);
        sds tmp = sdsnew(value);
        pushMessageToWarningBuffer(tmp);
        sdsfree(tmp);

    } else {
        sds tmp = sdsnew("pop failed");
        pushMessageToWarningBuffer(tmp);
        sdsfree(tmp);
        fprintf(stderr, "pop failed\n");
    }

    sdsfreesplitres(tokens, count);
    return 0;
}

static int pushListCmd(const char *string, InMemStructs *structs, enum leftright type) {
    int count;
    sds *tokens = sdssplitargs(string, &count);
    if (count != 3) {
        fprintf(stderr, "count error:%d\n", count);
        sdsfreesplitres(tokens, count);
        return -1;
    }
    if (insertListToTable(structs->hashTable, structs->hashTableSize, tokens[1], tokens[2], type)) {
    } else {
        sds tmp = sdsnew("can't push key");
        pushMessageToWarningBuffer(tmp);
        sdsfree(tmp);
        fprintf(stderr, "can't push key");
    }

    sdsfreesplitres(tokens, count);
    return 0;
}
void parseInput(const char *string, InMemStructs *structs) {
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
        case LPUSH_CMD:
            pushListCmd(string, structs, left);
            break;
        case LPOP_CMD:
            popListCmd(string, structs, left);
            break;
        case LINDEX_CMD:
            //
            break;
        case LLEN_CMD:
            //
            break;
        case RPUSH_CMD:
            pushListCmd(string, structs, right);
            break;
        case RPOP_CMD:
            popListCmd(string, structs, right);
            break;
        case CMD_NOT_FOUND:
            // DO
            break;
        default:
            fprintf(stderr, "switch case default");
    }
}
