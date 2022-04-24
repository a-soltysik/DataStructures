#include <gtest/gtest.h>

#include "Algorithms/MST/Kruskal.h"
#include "mocks/Algorithms/Graphs/UndirectedGraphMock.h"

using ::testing::Return;

TEST(KruskalTest, CheckMST)
{
    UndirectedGraphMock graph;

    DynamicArray<Graph::Vertex> vertices = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    DynamicArray<UndirectedGraph::EdgeData> edges = {
        {{0, 1}, 3},
        {{0, 3}, 6},
        {{0, 4}, 9},
        {{1, 3}, 4},
        {{1, 4}, 9},
        {{1, 2}, 2},
        {{1, 5}, 9},
        {{2, 3}, 2},
        {{2, 5}, 8},
        {{2, 6}, 9},
        {{3, 6}, 9},
        {{4, 5}, 8},
        {{4, 9}, 18},
        {{5, 6}, 7},
        {{5, 8}, 9},
        {{6, 7}, 4},
        {{6, 8}, 5},
        {{7, 8}, 1},
        {{7, 9}, 4},
        {{8, 9}, 3}
    };

    EXPECT_CALL(graph, GetVertices).WillOnce(Return(vertices));
    EXPECT_CALL(graph, GetEdges).WillOnce(Return(edges));

    EXPECT_EQ(MST::Kruskal::FindMstOf(graph).weight, 38);
}

