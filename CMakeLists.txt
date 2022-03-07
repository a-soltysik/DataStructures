cmake_minimum_required(VERSION 3.16)

project(DataStructures)

set (CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG           "${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE         "${CMAKE_CXX_FLAGS_RELEASE} -O2")

set (TEST "test")
set (SOURCE "DataStructures")

set (TEST_DIR "${PROJECT_SOURCE_DIR}/test")
set (SRC_DIR  "${PROJECT_SOURCE_DIR}/src")

add_subdirectory(src)
add_subdirectory(test)