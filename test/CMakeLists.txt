LIST(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules")
include(code-coverage)

add_library(unity-lib STATIC ${PROJECT_SOURCE_DIR}/test/src/unity.c)
# add_library(parseInput-lib STATIC ${PROJECT_SOURCE_DIR}/src/parseInput/parseInput.c)

target_include_directories(unity-lib PUBLIC ${PROJECT_SOURCE_DIR}/test/src)
# target_include_directories(parseInput-lib PUBLIC ${PROJECT_SOURCE_DIR}/include/parseInput)

add_executable(simple-key-value-database-test test.c)
target_link_libraries(simple-key-value-database-test unity-lib parseInput-lib)
# target_link_libraries(parseInput-lib PRIVATE keyValue-lib PRIVATE doublell-lib)
# add_code_coverage(parseInput-lib doublell-lib keyValue-lib  sharedData-lib)
target_code_coverage(parseInput-lib)
target_code_coverage(doublell-lib)
target_code_coverage(keyValue-lib)
target_code_coverage(sharedData-lib)
target_code_coverage(simple-key-value-database-test)
# include(CodeCoverage)
# APPEND_COVERAGE_COMPILER_FLAGS()
# set(COVERAGE_LCOV_EXCLUDES 'src/sds/*' 'src/murmurhash/*' 'include/sds/*' 'include/murmurhash/*' 'test/*' 'test/src/*')
# set(GCOVR_ADDITIONAL_ARGS "--gcov-executable=llvm-cov gcov")
# set(GCOVR_PATH "/Users/yungen/.pyenv/shims/gcovr")
# set(GENHTML_EXTRA_ARGS "")
# SETUP_TARGET_FOR_COVERAGE_GCOVR_HTML(NAME code_coverage
#                                EXECUTABLE simple-key-value-database-test
#                                DEPENDENCIES simple-key-value-database-test)
# SETUP_TARGET_FOR_COVERAGE_LCOV(NAME code_coverage
#                                EXECUTABLE simple-key-value-database-test
#                                DEPENDENCIES simple-key-value-database-test)

