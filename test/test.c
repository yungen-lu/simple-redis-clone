#include "parseInput.h"
#include "unity.h"
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
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_CmdParse);
    return UNITY_END();
}