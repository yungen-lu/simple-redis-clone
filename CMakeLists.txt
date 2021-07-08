cmake_minimum_required(VERSION 3.0.0)
project(simple-key-value-database VERSION 0.1.0)

add_subdirectory(src)
add_subdirectory(test)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)