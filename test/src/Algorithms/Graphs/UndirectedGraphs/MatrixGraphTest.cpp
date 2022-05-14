#include <gtest/gtest.h>

#include "Algorithms/Graphs/UndirectedGraphs/MatrixGraph.h"

using Vertex   = MatrixGraph::Vertex;
using Edge     = MatrixGraph::Edge;
using EdgeData = MatrixGraph::EdgeData;
using Weight   = MatrixGraph::Weight;

using Edges    = DynamicArray<EdgeData>;
using Vertices = DynamicArray<Vertex>;

class MatrixGraphTest : public testing::Test
{
public:
    static bool CompareEdges(const Edges& edges1, const Edges& edges2)
    {
        auto size1 = edges1.Size();
        auto size2 = edges2.Size();

        if (size1 != size2)
        {
            return false;
        }

        size_t equalityCounter = 0;

        for (const auto& edge1 : edges1)
        {
            for (const auto& edge2 : edges2)
            {
                if (edge1 == edge2)
                {
                    equalityCounter++;
                }
            }
        }

        return equalityCounter == size1;
    }

    static bool CompareVertices(const Vertices& vertices1, const Vertices& vertices2)
    {
        auto size1 = vertices1.Size();
        auto size2 = vertices2.Size();

        if (size1 != size2)
        {
            return false;
        }

        size_t equalityCounter = 0;

        for (const auto& vertex1 : vertices1)
        {
            for (const auto& vertex2 : vertices2)
            {
                if (vertex1 == vertex2)
                {
                    equalityCounter++;
                }
            }
        }

        return equalityCounter == size1;
    }

protected:
    MatrixGraph graph;
};

TEST_F(MatrixGraphTest, AddVertexTest)
{
    graph.AddVertex();
    ASSERT_EQ(graph.GetOrder(), 1);

    graph.AddVertex();
    ASSERT_EQ(graph.GetOrder(), 2);

    graph.AddVertex();
    ASSERT_EQ(graph.GetOrder(), 3);

    graph.AddVertex();
    ASSERT_EQ(graph.GetOrder(), 4);

    graph.AddVertex();
    ASSERT_EQ(graph.GetOrder(), 5);

    Vertices expected = {0, 1, 2, 3, 4};
    Vertices real = graph.GetVertices();

    EXPECT_TRUE(CompareVertices(expected, real));
}

TEST_F(MatrixGraphTest, AddEdgeTest)
{
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();

    Vertices expected = {0, 1, 2, 3, 4};
    Vertices real = graph.GetVertices();

    ASSERT_TRUE(CompareVertices(expected, real));

    ASSERT_EQ(graph.GetEdges().Size(), 0);
    EXPECT_FALSE(graph.AddEdge({{0, 5}, 1}));


    graph.AddEdge({{0, 1}, 1});
    graph.AddEdge({{4, 0}, 2});
    graph.AddEdge({{3, 1}, 3});

    ASSERT_EQ(graph.GetSize(), 3);

    Edges expectedEdges = {EdgeData {Edge{0, 1}, Weight{1}},
                           EdgeData {Edge{0, 4}, Weight{2}},
                           EdgeData {Edge{3, 1}, Weight{3}}};

    auto realEdges = graph.GetEdges();
    EXPECT_TRUE(CompareEdges(expectedEdges, realEdges));
}

TEST_F(MatrixGraphTest, GetWeightTest)
{
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();

    Vertices expected = {0, 1, 2, 3, 4};
    Vertices real = graph.GetVertices();

    ASSERT_TRUE(CompareVertices(expected, real));

    graph.AddEdge({{0, 1}, 1});
    graph.AddEdge({{4, 0}, 2});
    graph.AddEdge({{3, 1}, 3});

    ASSERT_EQ(graph.GetSize(), 3);

    EXPECT_EQ(graph.GetWeight({1, 0}).value(), 1);
    EXPECT_EQ(graph.GetWeight({0, 1}).value(), 1);
    EXPECT_EQ(graph.GetWeight({4, 0}).value(), 2);
    EXPECT_EQ(graph.GetWeight({0, 4}).value(), 2);
    EXPECT_EQ(graph.GetWeight({3, 1}).value(), 3);
    EXPECT_EQ(graph.GetWeight({1, 3}).value(), 3);
    EXPECT_EQ(graph.GetWeight({0, 0}), std::nullopt);
}

TEST_F(MatrixGraphTest, SetWeightTest)
{
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();

    Vertices expected = {0, 1, 2, 3, 4};
    Vertices real = graph.GetVertices();

    ASSERT_TRUE(CompareVertices(expected, real));

    graph.AddEdge({{0, 1}, 1});
    graph.AddEdge({{4, 0}, 2});
    graph.AddEdge({{3, 1}, 3});

    ASSERT_EQ(graph.GetSize(), 3);

    EXPECT_TRUE(graph.SetWeight({0, 1}, 11));
    EXPECT_TRUE(graph.SetWeight({0, 1}, 12));
    EXPECT_EQ(graph.GetWeight({1, 0}).value(), 12);
    EXPECT_EQ(graph.GetWeight({0, 1}).value(), 12);

    EXPECT_TRUE(graph.SetWeight({0, 4}, 13));
    EXPECT_TRUE(graph.SetWeight({4, 0}, 14));
    EXPECT_EQ(graph.GetWeight({4, 0}).value(), 14);
    EXPECT_EQ(graph.GetWeight({0, 4}).value(), 14);

    EXPECT_TRUE(graph.SetWeight({3, 1}, 15));
    EXPECT_TRUE(graph.SetWeight({1, 3}, 16));
    EXPECT_EQ(graph.GetWeight({3, 1}).value(), 16);
    EXPECT_EQ(graph.GetWeight({1, 3}).value(), 16);

    EXPECT_FALSE(graph.SetWeight({0, 3}, 11));
}

TEST_F(MatrixGraphTest, DoesExistTest)
{
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();

    Vertices expected = {0, 1, 2, 3, 4};
    Vertices real = graph.GetVertices();

    ASSERT_TRUE(CompareVertices(expected, real));

    graph.AddEdge({{0, 1}, 1});
    graph.AddEdge({{4, 0}, 2});
    graph.AddEdge({{3, 1}, 3});

    ASSERT_EQ(graph.GetSize(), 3);

    EXPECT_TRUE(graph.DoesExist(0));
    EXPECT_TRUE(graph.DoesExist(1));
    EXPECT_TRUE(graph.DoesExist(2));
    EXPECT_TRUE(graph.DoesExist(3));
    EXPECT_TRUE(graph.DoesExist(4));
    EXPECT_FALSE(graph.DoesExist(5));

    EXPECT_TRUE(graph.DoesExist({0, 1}));
    EXPECT_TRUE(graph.DoesExist({1, 0}));
    EXPECT_TRUE(graph.DoesExist({4, 0}));
    EXPECT_TRUE(graph.DoesExist({0, 4}));
    EXPECT_TRUE(graph.DoesExist({1, 3}));
    EXPECT_TRUE(graph.DoesExist({3, 1}));
    EXPECT_FALSE(graph.DoesExist({1, 1}));
    EXPECT_FALSE(graph.DoesExist({5, 1}));
}