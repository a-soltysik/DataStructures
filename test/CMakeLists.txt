include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set (gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(DS_TEST_SRC_DIR ${DS_TEST_DIR}/src)
set(DS_TEST_MOCK_DIR ${DS_TEST_DIR}/mocks)

set(DS_TEST_SRC_LIST
    ${DS_SRC_DIR}/Utils/Utils.cpp

    ${DS_SRC_DIR}/Algorithms/Graphs/DirectedGraphs/DirectedGraph.cpp
    ${DS_SRC_DIR}/Algorithms/Graphs/DirectedGraphs/DirectedListGraph.cpp
    ${DS_SRC_DIR}/Algorithms/Graphs/DirectedGraphs/DirectedMatrixGraph.cpp
    ${DS_SRC_DIR}/Algorithms/Graphs/UndirectedGraphs/UndirectedGraph.cpp
    ${DS_SRC_DIR}/Algorithms/Graphs/UndirectedGraphs/ListGraph.cpp
    ${DS_SRC_DIR}/Algorithms/Graphs/UndirectedGraphs/MatrixGraph.cpp
    ${DS_SRC_DIR}/Algorithms/Graphs/DSU.cpp

    ${DS_SRC_DIR}/Algorithms/MST/Kruskal.cpp
    ${DS_SRC_DIR}/Algorithms/MST/Prim.cpp
    )

set(DS_TEST_SRC_LIST
    ${DS_TEST_SRC_LIST}
    ${DS_TEST_SRC_DIR}/main.cpp

    ${DS_TEST_SRC_DIR}/Utils/AlgorithmsTest.cpp

    ${DS_TEST_SRC_DIR}/Container/DynamicArrayTest.cpp
    ${DS_TEST_SRC_DIR}/Container/ListTest.cpp
    ${DS_TEST_SRC_DIR}/Container/RedBlackTreeTest.cpp
    ${DS_TEST_SRC_DIR}/Container/HeapTest.cpp
    ${DS_TEST_SRC_DIR}/Container/AvlTreeTest.cpp

    ${DS_TEST_SRC_DIR}/Algorithms/Graphs/DirectedGraphs/DirectedListGraphTest.cpp
    ${DS_TEST_SRC_DIR}/Algorithms/Graphs/DirectedGraphs/DirectedMatrixGraphTest.cpp
    ${DS_TEST_SRC_DIR}/Algorithms/Graphs/UndirectedGraphs/ListGraphTest.cpp
    ${DS_TEST_SRC_DIR}/Algorithms/Graphs/UndirectedGraphs/MatrixGraphTest.cpp

    ${DS_TEST_SRC_DIR}/Algorithms/MST/KruskalTest.cpp
    ${DS_TEST_SRC_DIR}/Algorithms/MST/PrimTest.cpp
    )

add_executable(${DS_TEST_TARGET} ${DS_TEST_SRC_LIST})

target_include_directories(${DS_TEST_TARGET} PRIVATE ${DS_TEST_DIR} ${DS_SRC_DIR} ${DS_TEST_MOCK_DIR})
target_link_directories(${DS_TEST_TARGET} PRIVATE ${DS_TEST_MOCK_DIR})
target_link_libraries(${DS_TEST_TARGET} PRIVATE gtest gtest_main gmock_main)


enable_testing()
add_test(NAME ${DS_TEST_TARGET} COMMAND ${DS_TEST_TARGET})