file(GLOB_RECURSE PROJECT_SRC
        "${SRC_DIR}/*.h"
        "${SRC_DIR}/*.cpp"
        )

add_executable("DataStructures" ${PROJECT_SRC})
target_include_directories(${SOURCE} PRIVATE ${SRC_DIR})