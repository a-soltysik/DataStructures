#include <gtest/gtest.h>

#include "Algorithms/Graphs/DirectedGraphs/DirectedListGraph.h"

using Vertex           = DirectedListGraph::Vertex;
using DirectedEdge     = DirectedListGraph::DirectedEdge;
using DirectedEdgeData = DirectedListGraph::DirectedEdgeData;
using Weight           = DirectedListGraph::Weight;

using DirectedEdges = DynamicArray<DirectedEdgeData>;
using Vertices      = DynamicArray<Vertex>;

class DirectedListGraphTest : public testing::Test
{
public:
    static bool CompareDirectedEdges(const DirectedEdges& DirectedEdges1, const DirectedEdges& DirectedEdges2)
    {
        auto size1 = DirectedEdges1.Size();
        auto size2 = DirectedEdges2.Size();

        if (size1 != size2)
        {
            return false;
        }

        size_t equalityCounter = 0;

        for (const auto& DirectedEdge1 : DirectedEdges1)
        {
            for (const auto& DirectedEdge2 : DirectedEdges2)
            {
                if (DirectedEdge1 == DirectedEdge2)
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
    DirectedListGraph graph;
};

TEST_F(DirectedListGraphTest, AddVertexTest)
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

TEST_F(DirectedListGraphTest, RemoveVertexTest)
{
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();

    Vertices expected = {0, 1, 2, 3, 4};
    Vertices real = graph.GetVertices();

    ASSERT_TRUE(CompareVertices(expected, real));

    EXPECT_FALSE(graph.RemoveVertex(5));
    EXPECT_EQ(graph.GetOrder(), 5);

    graph.RemoveVertex(3);
    EXPECT_EQ(graph.GetOrder(), 4);

    graph.RemoveVertex(2);
    EXPECT_EQ(graph.GetOrder(), 3);

    graph.AddVertex();
    ASSERT_EQ(graph.GetOrder(), 4);

    expected = {0, 1, 4, 5};
    real = graph.GetVertices();

    ASSERT_TRUE(CompareVertices(expected, real));
}

TEST_F(DirectedListGraphTest, AddDirectedEdgeTest)
{
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();
    graph.RemoveVertex(2);

    Vertices expected = {0, 1, 3, 4};
    Vertices real = graph.GetVertices();

    ASSERT_TRUE(CompareVertices(expected, real));

    ASSERT_EQ(graph.GetDirectedEdges().Size(), 0);
    EXPECT_FALSE(graph.AddDirectedEdge({{0, 2}, 1}));


    graph.AddDirectedEdge({{0, 1}, 1});
    graph.AddDirectedEdge({{4, 0}, 2});
    graph.AddDirectedEdge({{3, 1}, 3});
    graph.AddDirectedEdge({{1, 3}, 4});

    ASSERT_EQ(graph.GetSize(), 4);

    DirectedEdges expectedDirectedEdges = {DirectedEdgeData {DirectedEdge{0, 1}, Weight{1}},
                                           DirectedEdgeData {DirectedEdge{4, 0}, Weight{2}},
                                           DirectedEdgeData {DirectedEdge{3, 1}, Weight{3}},
                                           DirectedEdgeData {DirectedEdge{1, 3}, Weight{4}}};

    auto realDirectedEdges = graph.GetDirectedEdges();
    EXPECT_TRUE(CompareDirectedEdges(expectedDirectedEdges, realDirectedEdges));
}

TEST_F(DirectedListGraphTest, RemoveDirectedEdgeTest)
{
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();
    graph.RemoveVertex(2);

    Vertices expected = {0, 1, 3, 4};
    Vertices real = graph.GetVertices();

    ASSERT_TRUE(CompareVertices(expected, real));

    graph.AddDirectedEdge({{0, 1}, 1});
    graph.AddDirectedEdge({{4, 0}, 2});
    graph.AddDirectedEdge({{3, 1}, 3});

    ASSERT_EQ(graph.GetSize(), 3);

    EXPECT_FALSE(graph.RemoveDirectedEdge({1, 3}));
    graph.RemoveDirectedEdge({3, 1});

    ASSERT_EQ(graph.GetSize(), 2);

    DirectedEdges expectedDirectedEdges = {DirectedEdgeData {DirectedEdge{0, 1}, Weight{1}},
                                           DirectedEdgeData {DirectedEdge{4, 0}, Weight{2}}};

    auto realDirectedEdges = graph.GetDirectedEdges();
    EXPECT_TRUE(CompareDirectedEdges(expectedDirectedEdges, realDirectedEdges));
}

TEST_F(DirectedListGraphTest, GetWeightTest)
{
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();
    graph.RemoveVertex(2);

    Vertices expected = {0, 1, 3, 4};
    Vertices real = graph.GetVertices();

    ASSERT_TRUE(CompareVertices(expected, real));

    graph.AddDirectedEdge({{0, 1}, 1});
    graph.AddDirectedEdge({{4, 0}, 2});
    graph.AddDirectedEdge({{3, 1}, 3});

    ASSERT_EQ(graph.GetSize(), 3);

    EXPECT_EQ(graph.GetWeight({1, 0}), std::nullopt);
    EXPECT_EQ(graph.GetWeight({0, 1}).value(), 1);
    EXPECT_EQ(graph.GetWeight({4, 0}).value(), 2);
    EXPECT_EQ(graph.GetWeight({0, 4}), std::nullopt);
    EXPECT_EQ(graph.GetWeight({3, 1}).value(), 3);
    EXPECT_EQ(graph.GetWeight({1, 3}), std::nullopt);
    EXPECT_EQ(graph.GetWeight({0, 0}), std::nullopt);
}

TEST_F(DirectedListGraphTest, SetWeightTest)
{
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();
    graph.RemoveVertex(2);

    Vertices expected = {0, 1, 3, 4};
    Vertices real = graph.GetVertices();

    ASSERT_TRUE(CompareVertices(expected, real));

    graph.AddDirectedEdge({{0, 1}, 1});
    graph.AddDirectedEdge({{4, 0}, 2});
    graph.AddDirectedEdge({{3, 1}, 3});

    ASSERT_EQ(graph.GetSize(), 3);

    EXPECT_TRUE(graph.SetWeight({0, 1}, 11));
    EXPECT_FALSE(graph.SetWeight({1, 0}, 12));
    EXPECT_EQ(graph.GetWeight({1, 0}), std::nullopt);
    EXPECT_EQ(graph.GetWeight({0, 1}).value(), 11);

    EXPECT_TRUE(graph.SetWeight({4, 0}, 13));
    EXPECT_FALSE(graph.SetWeight({0, 4}, 14));
    EXPECT_EQ(graph.GetWeight({4, 0}).value(), 13);
    EXPECT_EQ(graph.GetWeight({0, 4}), std::nullopt);

    EXPECT_TRUE(graph.SetWeight({3, 1}, 15));
    EXPECT_FALSE(graph.SetWeight({1, 3}, 16));
    EXPECT_EQ(graph.GetWeight({3, 1}).value(), 15);
    EXPECT_EQ(graph.GetWeight({1, 3}), std::nullopt);

    EXPECT_FALSE(graph.SetWeight({0, 3}, 11));
}

TEST_F(DirectedListGraphTest, DoesExistTest)
{
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();
    graph.RemoveVertex(2);

    Vertices expected = {0, 1, 3, 4};
    Vertices real = graph.GetVertices();

    ASSERT_TRUE(CompareVertices(expected, real));

    graph.AddDirectedEdge({{0, 1}, 1});
    graph.AddDirectedEdge({{4, 0}, 2});
    graph.AddDirectedEdge({{3, 1}, 3});
    graph.RemoveDirectedEdge({1, 3});

    ASSERT_EQ(graph.GetSize(), 3);

    EXPECT_TRUE(graph.DoesExist(0));
    EXPECT_TRUE(graph.DoesExist(1));
    EXPECT_FALSE(graph.DoesExist(2));
    EXPECT_TRUE(graph.DoesExist(3));
    EXPECT_TRUE(graph.DoesExist(4));
    EXPECT_FALSE(graph.DoesExist(5));

    EXPECT_TRUE(graph.DoesExist({0, 1}));
    EXPECT_FALSE(graph.DoesExist({1, 0}));
    EXPECT_TRUE(graph.DoesExist({4, 0}));
    EXPECT_FALSE(graph.DoesExist({0, 4}));
    EXPECT_FALSE(graph.DoesExist({1, 3}));
    EXPECT_TRUE(graph.DoesExist({3, 1}));
    EXPECT_FALSE(graph.DoesExist({1, 1}));
    EXPECT_FALSE(graph.DoesExist({5, 1}));
}