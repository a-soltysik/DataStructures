cmake_minimum_required(VERSION 3.19)

project(DataStructures)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}" ${PROJECT_SOURCE_DIR}/CMake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY )

include_directories(${PROJECT_SOURCE_DIR}/src)

file(GLOB_RECURSE SRC_LIST
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        )

add_executable(DataStructures ${SRC_LIST})