#ifndef PARSEINPUT_H
#define PARSEINPUT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../data/data.h"
#include "../sds/sds.h"
#define DEL_CMD 10
#define DUMP_CMD 11
#define EXISTS_CMD 12
#define RENAME_CMD 13
#define SET_CMD 14
#define GET_CMD 15
#define TOTAL_CMD 6
#define CMD_NOT_FOUND -1
void parseInput(char *string, InMemStructs *structs);
#endif