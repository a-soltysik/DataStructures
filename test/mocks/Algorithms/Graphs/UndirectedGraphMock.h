#pragma once

#include <gmock/gmock.h>

#include "Algorithms/Graphs/UndirectedGraphs/UndirectedGraph.h"

class UndirectedGraphMock : public UndirectedGraph
{
public:
    MOCK_METHOD(Vertex, AddVertex, (), (override));
    MOCK_METHOD(bool, AddEdge, (const EdgeData&), (override));
    MOCK_METHOD(std::optional<Weight>, GetWeight, (Edge), (const, override));
    MOCK_METHOD(bool, SetWeight, (Edge, Weight), (override));
    MOCK_METHOD(uint32_t, GetOrder, (), (const, override));
    MOCK_METHOD(uint64_t, GetSize, (), (const, override));
    MOCK_METHOD(bool, DoesExist, (Vertex), (const, override));
    MOCK_METHOD(bool, DoesExist, (Edge), (const, override));
    MOCK_METHOD(std::optional<DynamicArray<Neighbour>>, GetNeighboursOf, (Vertex), (const, override));
    MOCK_METHOD(DynamicArray<Vertex>, GetVertices, (), (const, override));
    MOCK_METHOD(DynamicArray<EdgeData>, GetEdges, (), (const, override));
    MOCK_METHOD(bool, ForEachNeighbourOf, (Vertex, NeighbourPredicate), (const, override));
    MOCK_METHOD(void, ForEachVertex, (VertexPredicate), (const, override));
    MOCK_METHOD(void, ForEachEdge, (EdgePredicate), (const, override));
};

inline std::ostream& operator<<(std::ostream& os, const UndirectedGraph::EdgeData& edge)
{
    os << "v: " << edge.vertices.first << ", u: " << edge.vertices.second << ", weight: " << edge.weight;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Graph::Neighbour& neighbour)
{
    os << "v: " << neighbour.vertex << ", weight: " << neighbour.weight;
    return os;
}