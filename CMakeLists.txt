cmake_minimum_required(VERSION 3.16)

project(DataStructures)

set(DS_TARGET "DataStructures")
set(DS_TEST_TARGET "DataStructuresTest")

set(DS_BIN_DIR ${CMAKE_BINARY_DIR})
set(DS_SRC_BIN_DIR ${CMAKE_BINARY_DIR}/src)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Wall /W2 /sdl /MP /permissive- /Zc:rvalueCast /volatile:iso")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /volatile:ms")
    set(COMPILER_REL_CXX_FLAGS "/O2 /MT")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpessimizing-move -Wredundant-move -pedantic -Wconversion")
    set(COMPILER_REL_CXX_FLAGS "-O3 -static")
endif ()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE " ${CMAKE_CXX_FLAGS_RELEASE} ${COMPILER_REL_CXX_FLAGS}")

set(RUNTIME_OUTPUT_DIRECTORY_DEBUG ${DS_BIN_DIR})
set(RUNTIME_OUTPUT_DIRECTORY_RELEASE ${DS_BIN_DIR})


set(DS_TEST_DIR ${PROJECT_SOURCE_DIR}/test)
set(DS_SRC_DIR ${PROJECT_SOURCE_DIR}/src)

set(DS_RES_DIR ${SRC_DIR}/Resources)
file(COPY ${RES_DIR} DESTINATION ${DS_SRC_BIN_DIR})

add_subdirectory(${DS_SRC_DIR})
add_subdirectory(${DS_TEST_DIR})