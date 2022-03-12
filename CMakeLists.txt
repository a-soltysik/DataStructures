cmake_minimum_required(VERSION 3.16)

project(DataStructures)

set (CMAKE_CXX_STANDARD 17)

set (TEST "test")
set (SOURCE "DataStructures")

set (TEST_DIR "${PROJECT_SOURCE_DIR}/test")
set (SRC_DIR  "${PROJECT_SOURCE_DIR}/src")

add_subdirectory(src)
add_subdirectory(test)