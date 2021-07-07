#ifndef PARSEINPUT_H
#define PARSEINPUT_H

#include "../sharedData/sharedData.h"
#define DEL_CMD 10
#define DUMP_CMD 11
#define EXISTS_CMD 12
#define RENAME_CMD 13
#define SET_CMD 14
#define GET_CMD 15
#define LPUSH_CMD 16
#define LPOP_CMD 17
#define LINDEX_CMD 18
#define LLEN_CMD 19
#define RPUSH_CMD 20
#define RPOP_CMD 21
#define LREM

#define TOTAL_CMD 12
#define CMD_NOT_FOUND -1
void parseInput(const char *string, InMemStructs *structs);
int getCommand(const char *string);

#endif