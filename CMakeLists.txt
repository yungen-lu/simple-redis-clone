cmake_minimum_required(VERSION 3.0.0)
project(simple-key-value-database VERSION 0.1.0)

# include(CTest)
# enable_testing()
# add_subdirectory(src)
# add_executable(simple-key-value-database src/main.c)
# target_link_libraries(simple-key-value-database PUBLIC src/server)

# target_include_directories(simple-key-value-database PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/src/server")
# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
# set(SOURCES
#     src/main.c
#     src/server/server.c
# )
# add_executable(simple-key-value-database ${SOURCES})
# target_include_directories(simple-key-value-database
#     PRIVATE
#         ${PROJECT_SOURCE_DIR}/include/server
# )
add_subdirectory(src)
add_subdirectory(test)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)