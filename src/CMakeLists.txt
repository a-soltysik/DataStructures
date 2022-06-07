file(GLOB_RECURSE DS_SRC_LIST
    "${DS_SRC_DIR}/*.h"
    "${DS_SRC_DIR}/*.cpp"
    )

set(PCH_FILES
    ${DS_SRC_DIR}/Utils/Utils.h
    ${DS_SRC_DIR}/Utils/Parser.h
    <iostream>)

add_executable(${DS_TARGET} ${DS_SRC_LIST})
target_include_directories(${DS_TARGET} PRIVATE ${DS_SRC_DIR})