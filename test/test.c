#include "parseInput.h"
#include "unity.h"
#include "unity_internals.h"
#define HASH_TABLE_SIZE 4096
void setUp(void) { createWarningBuffer(); }
void tearDown(void) { deleteWarningBuffer(); }
void test_CmdParse(void) {
    char *arrOfCmd[] = {"DEL",   "DUMP", "EXISTS", "RENAME", "SET",   "GET",
                        "LPUSH", "LPOP", "LINDEX", "LLEN",   "RPUSH", "RPOP"};
    char *arrOfWrongCmd[] = {"qwe", "asd", "EOIW", "askd", "WS", " ", "\n", "\t", "\n\t"};
    size_t sizeOfarrOfCmd = sizeof(arrOfCmd) / sizeof(arrOfCmd[0]);
    size_t sizeOfarrOfWrongCmd = sizeof(arrOfWrongCmd) / sizeof(arrOfWrongCmd[0]);
    // TEST_ASSERT_EQUAL_INT(DEL_CMD,getCommand("DEL"));
    for (size_t i = 0; i < sizeOfarrOfCmd; i++) {
        TEST_ASSERT_EQUAL_INT(DEL_CMD + i, getCommand(arrOfCmd[i]));
    }
    for (size_t i = 0; i < sizeOfarrOfWrongCmd; i++) {
        TEST_ASSERT_EQUAL_INT(CMD_NOT_FOUND, getCommand(arrOfWrongCmd[i]));
    }
}
void test_GetCmd(void) {
    InMemStructs *structs = createInMemStructs(HASH_TABLE_SIZE);
    char *arrOfCmd[] = {"SET key1 value1",   "SET key2 value2",   "SET key3 value3",   "LPUSH key4 value4",
                        "LPUSH key4 value5", "RPUSH key4 value6", "RPUSH key5 value7", "RPUSH key5 value8"};
    size_t sizeOfarrOfCmd = sizeof(arrOfCmd) / sizeof(arrOfCmd[0]);
    char *arrOfGetCmd[] = {"LPOP key5", "LPOP key5", "RPOP key4", "RPOP key4",
                           "RPOP key4", "GET key3",  "GET key2",  "GET key1"};
    char *arrOfAns[] = {"value7", "value8", "value6", "value4", "value5", "value3", "value2", "value1"};
    for (size_t i = 0; i < sizeOfarrOfCmd; i++) {
        parseInput(arrOfCmd[i], structs);
        TEST_ASSERT_EQUAL_STRING("",getWarningBuffer());
        parseInput(arrOfGetCmd[i], structs);
        TEST_ASSERT_EQUAL_STRING(arrOfAns[i], getWarningBuffer());
    }
}
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_CmdParse);
    RUN_TEST(test_GetCmd);
    return UNITY_END();
}