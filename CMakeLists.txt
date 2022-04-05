cmake_minimum_required(VERSION 3.16)

project(DataStructures)

set(BIN_DIR ${CMAKE_BINARY_DIR})
set(SRC_BIN_DIR ${CMAKE_BINARY_DIR}/src)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Wall /W3 /sdl /MP /permissive- /Zc:rvalueCast /volatile:iso")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /volatile:ms")
    set(COMPILER_REL_CXX_FLAGS "/O2")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpessimizing-move -Wredundant-move -pedantic -Wconversion")
    set(COMPILER_REL_CXX_FLAGS "-O3")
endif ()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE " ${CMAKE_CXX_FLAGS_RELEASE} ${COMPILER_REL_CXX_FLAGS}")

set(RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BIN_DIR})
set(RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BIN_DIR})

set(TEST "test")
set(SOURCE "DataStructures")

set(TEST_DIR "${PROJECT_SOURCE_DIR}/test")
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")

set(RES_DIR ${SRC_DIR}/Resources)
file(COPY ${RES_DIR} DESTINATION ${SRC_BIN_DIR})

add_subdirectory(src)
add_subdirectory(test)