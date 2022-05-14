#include <gtest/gtest.h>

#include "Algorithms/MST/Prim.h"
#include "Algorithms/Graphs/UndirectedGraphs/ListGraph.h"

ListGraph GenerateListGraph()
{
    ListGraph graph;
    for (uint32_t i = 0; i < 10; i++)
    {
        graph.AddVertex();
    }

    graph.AddEdge({{0, 1}, 3});
    graph.AddEdge({{0, 3}, 6});
    graph.AddEdge({{0, 4}, 9});
    graph.AddEdge({{1, 3}, 4});
    graph.AddEdge({{1, 4}, 9});
    graph.AddEdge({{1, 2}, 2});
    graph.AddEdge({{1, 5}, 9});
    graph.AddEdge({{2, 3}, 2});
    graph.AddEdge({{2, 5}, 8});
    graph.AddEdge({{2, 6}, 9});
    graph.AddEdge({{3, 6}, 9});
    graph.AddEdge({{4, 5}, 8});
    graph.AddEdge({{4, 9}, 18});
    graph.AddEdge({{5, 6}, 7});
    graph.AddEdge({{5, 8}, 9});
    graph.AddEdge({{6, 7}, 4});
    graph.AddEdge({{6, 8}, 5});
    graph.AddEdge({{7, 8}, 1});
    graph.AddEdge({{7, 9}, 4});
    graph.AddEdge({{8, 9}, 3});

    return graph;
}

TEST(PrimTest, MstExists)
{
    auto graph = GenerateListGraph();

    auto result = MST::Prim::FindMstOf(graph);
    EXPECT_EQ(result.edges.Size(), 9);
    EXPECT_EQ(result.weight, 38);
}

TEST(PrimTest, MstDoesNotExists)
{
    auto graph = GenerateListGraph();
    graph.AddVertex();

    auto result = MST::Prim::FindMstOf(graph);
    EXPECT_EQ(result.edges.Size(), 0);
    EXPECT_EQ(result.weight, 0);
}
