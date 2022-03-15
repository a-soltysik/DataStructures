cmake_minimum_required(VERSION 3.16)

project(DataStructures)

set (CMAKE_CXX_STANDARD 17)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Wall /W3 /sdl /MP /permissive- /Zc:preprocessor /Zc:rvalueCast")
    set(COMPILER_REL_CXX_FLAGS "/O2 /Ot")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpessimizing-move -Wredundant-move -pedantic -Wconversion")
    set(COMPILER_REL_CXX_FLAGS "-O2")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE " ${CMAKE_CXX_FLAGS_RELEASE} ${COMPILER_REL_CXX_FLAGS}")

set (TEST "test")
set (SOURCE "DataStructures")

set (TEST_DIR "${PROJECT_SOURCE_DIR}/test")
set (SRC_DIR  "${PROJECT_SOURCE_DIR}/src")

add_subdirectory(src)
add_subdirectory(test)