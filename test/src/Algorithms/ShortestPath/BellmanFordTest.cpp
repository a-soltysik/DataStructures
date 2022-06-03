#include <gtest/gtest.h>

#include "Algorithms/ShortestPath/BellmanFord.h"
#include "Algorithms/Graphs/DirectedGraphs/DirectedMatrixGraph.h"

class BellmanFordTest : public testing::Test
{
protected:
    void GenerateListGraph()
    {
        graph.Clear();
        for (uint32_t i = 0; i < 7; i++)
        {
            graph.AddVertex();
        }

        graph.AddDirectedEdge({{0, 1}, 4});
        graph.AddDirectedEdge({{0, 3}, 8});
        graph.AddDirectedEdge({{1, 2}, 8});
        graph.AddDirectedEdge({{1, 3}, 11});
        graph.AddDirectedEdge({{2, 4}, 2});
        graph.AddDirectedEdge({{2, 5}, 4});
        graph.AddDirectedEdge({{3, 4}, 7});
        graph.AddDirectedEdge({{3, 6}, 1});
        graph.AddDirectedEdge({{4, 6}, 6});
        graph.AddDirectedEdge({{5, 6}, 2});
    }

    void ExpectStartingIn0()
    {
        auto result = ShortestPath::BellmanFord::FindShortestPath(graph, 0, 1);
        EXPECT_EQ(result.weight, 4);
        EXPECT_EQ(result.path.Size(), 2);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 0, 2);
        EXPECT_EQ(result.weight, 12);
        EXPECT_EQ(result.path.Size(), 3);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 0, 3);
        EXPECT_EQ(result.weight, 8);
        EXPECT_EQ(result.path.Size(), 2);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 0, 4);
        EXPECT_EQ(result.weight, 14);
        EXPECT_EQ(result.path.Size(), 4);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 0, 5);
        EXPECT_EQ(result.weight, 16);
        EXPECT_EQ(result.path.Size(), 4);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 0, 6);
        EXPECT_EQ(result.weight, 9);
        EXPECT_EQ(result.path.Size(), 3);
    }

    void ExpectStartingIn1()
    {
        auto result = ShortestPath::BellmanFord::FindShortestPath(graph, 1, 0);
        EXPECT_EQ(result.weight, 0);
        EXPECT_EQ(result.path.Size(), 0);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 1, 2);
        EXPECT_EQ(result.weight, 8);
        EXPECT_EQ(result.path.Size(), 2);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 1, 3);
        EXPECT_EQ(result.weight, 11);
        EXPECT_EQ(result.path.Size(), 2);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 1, 4);
        EXPECT_EQ(result.weight, 10);
        EXPECT_EQ(result.path.Size(), 3);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 1, 5);
        EXPECT_EQ(result.weight, 12);
        EXPECT_EQ(result.path.Size(), 3);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 1, 6);
        EXPECT_EQ(result.weight, 12);
        EXPECT_EQ(result.path.Size(), 3);
    }

    void ExpectStartingIn2()
    {
        auto result = ShortestPath::BellmanFord::FindShortestPath(graph, 2, 0);
        EXPECT_EQ(result.weight, 0);
        EXPECT_EQ(result.path.Size(), 0);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 2, 1);
        EXPECT_EQ(result.weight, 0);
        EXPECT_EQ(result.path.Size(), 0);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 2, 3);
        EXPECT_EQ(result.weight, 0);
        EXPECT_EQ(result.path.Size(), 0);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 2, 4);
        EXPECT_EQ(result.weight, 2);
        EXPECT_EQ(result.path.Size(), 2);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 2, 5);
        EXPECT_EQ(result.weight, 4);
        EXPECT_EQ(result.path.Size(), 2);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 2, 6);
        EXPECT_EQ(result.weight, 6);
        EXPECT_EQ(result.path.Size(), 3);
    }

    void ExpectStartingIn3()
    {
        auto result = ShortestPath::BellmanFord::FindShortestPath(graph, 3, 0);
        EXPECT_EQ(result.weight, 0);
        EXPECT_EQ(result.path.Size(), 0);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 3, 1);
        EXPECT_EQ(result.weight, 0);
        EXPECT_EQ(result.path.Size(), 0);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 3, 2);
        EXPECT_EQ(result.weight, 0);
        EXPECT_EQ(result.path.Size(), 0);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 3, 4);
        EXPECT_EQ(result.weight, 7);
        EXPECT_EQ(result.path.Size(), 2);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 3, 5);
        EXPECT_EQ(result.weight, 0);
        EXPECT_EQ(result.path.Size(), 0);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 3, 6);
        EXPECT_EQ(result.weight, 1);
        EXPECT_EQ(result.path.Size(), 2);
    }

    void ExpectStartingIn4()
    {
        auto result = ShortestPath::BellmanFord::FindShortestPath(graph, 4, 0);
        EXPECT_EQ(result.weight, 0);
        EXPECT_EQ(result.path.Size(), 0);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 4, 1);
        EXPECT_EQ(result.weight, 0);
        EXPECT_EQ(result.path.Size(), 0);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 4, 2);
        EXPECT_EQ(result.weight, 0);
        EXPECT_EQ(result.path.Size(), 0);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 4, 3);
        EXPECT_EQ(result.weight, 0);
        EXPECT_EQ(result.path.Size(), 0);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 4, 5);
        EXPECT_EQ(result.weight, 0);
        EXPECT_EQ(result.path.Size(), 0);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 4, 6);
        EXPECT_EQ(result.weight, 6);
        EXPECT_EQ(result.path.Size(), 2);
    }

    void ExpectStartingIn5()
    {
        auto result = ShortestPath::BellmanFord::FindShortestPath(graph, 5, 0);
        EXPECT_EQ(result.weight, 0);
        EXPECT_EQ(result.path.Size(), 0);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 5, 1);
        EXPECT_EQ(result.weight, 0);
        EXPECT_EQ(result.path.Size(), 0);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 5, 2);
        EXPECT_EQ(result.weight, 0);
        EXPECT_EQ(result.path.Size(), 0);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 5, 3);
        EXPECT_EQ(result.weight, 0);
        EXPECT_EQ(result.path.Size(), 0);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 5, 4);
        EXPECT_EQ(result.weight, 0);
        EXPECT_EQ(result.path.Size(), 0);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 5, 6);
        EXPECT_EQ(result.weight, 2);
        EXPECT_EQ(result.path.Size(), 2);
    }

    void ExpectStartingIn6()
    {
        auto result = ShortestPath::BellmanFord::FindShortestPath(graph, 6, 0);
        EXPECT_EQ(result.weight, 0);
        EXPECT_EQ(result.path.Size(), 0);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 6, 1);
        EXPECT_EQ(result.weight, 0);
        EXPECT_EQ(result.path.Size(), 0);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 6, 2);
        EXPECT_EQ(result.weight, 0);
        EXPECT_EQ(result.path.Size(), 0);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 6, 3);
        EXPECT_EQ(result.weight, 0);
        EXPECT_EQ(result.path.Size(), 0);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 6, 4);
        EXPECT_EQ(result.weight, 0);
        EXPECT_EQ(result.path.Size(), 0);

        result = ShortestPath::BellmanFord::FindShortestPath(graph, 6, 5);
        EXPECT_EQ(result.weight, 0);
        EXPECT_EQ(result.path.Size(), 0);
    }

    DirectedMatrixGraph graph;
};



TEST_F(BellmanFordTest, ShortestPathForAll)
{
    GenerateListGraph();
    ExpectStartingIn0();
    ExpectStartingIn1();
    ExpectStartingIn2();
    ExpectStartingIn3();
    ExpectStartingIn4();
    ExpectStartingIn5();
    ExpectStartingIn6();
}