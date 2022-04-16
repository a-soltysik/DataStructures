file(GLOB_RECURSE DS_SRC_LIST
    "${DS_SRC_DIR}/*.h"
    "${DS_SRC_DIR}/*.cpp"
    )

add_executable(${DS_TARGET} ${DS_SRC_LIST})
target_include_directories(${DS_TARGET} PRIVATE ${DS_SRC_DIR})