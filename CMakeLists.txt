cmake_minimum_required(VERSION 3.16)

project(DataStructures)

set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall -O2")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}" ${PROJECT_SOURCE_DIR}/CMake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY )

include_directories(${PROJECT_SOURCE_DIR}/src)

file(GLOB_RECURSE SRC_LIST
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        )

add_executable(DataStructures ${SRC_LIST})