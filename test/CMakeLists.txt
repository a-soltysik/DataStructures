include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set (gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(CONTAINER_DIR ${SRC_DIR}/Container)

set(FILES_TO_TEST
    ${CONTAINER_DIR}/DynamicArray/DynamicArray.cpp
    ${CONTAINER_DIR}/List/List.cpp
    ${CONTAINER_DIR}/RedBlackTree/RedBlackTree.cpp
    ${CONTAINER_DIR}/Heap/Heap.cpp
)

set(TEST_SRC
    ${TEST_DIR}/main.cpp
    ${TEST_DIR}/Container/DynamicArrayTest.cpp
    ${TEST_DIR}/Container/ListTest.cpp
    ${TEST_DIR}/Container/RedBlackTreeTest.cpp
    ${TEST_DIR}/Container/HeapTest.cpp
)

add_executable("Test" "${SRC_INCLUDES}" "${FILES_TO_TEST}" "${TEST_SRC}")
target_link_libraries("Test" gtest gtest_main)
target_include_directories("Test" PRIVATE ${TEST_DIR} ${SRC_DIR})
target_compile_definitions("Test" PRIVATE TEST)

enable_testing()
add_test("Test" "Test")