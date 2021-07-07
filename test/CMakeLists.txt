add_library(unity-lib STATIC ${PROJECT_SOURCE_DIR}/test/src/unity.c)
target_include_directories(unity-lib PUBLIC ${PROJECT_SOURCE_DIR}/test/src)
add_executable(simple-key-value-database-test test.c)

target_link_libraries(simple-key-value-database-test PRIVATE unity-lib PRIVATE parseInput-lib PRIVATE sharedData-lib)