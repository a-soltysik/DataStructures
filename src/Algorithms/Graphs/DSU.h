#pragma once

#include "Algorithms/Graphs/Graph.h"
#include "Containers/Map.h"

class DSU
{
public:
    DSU() = default;
    explicit DSU(const DynamicArray<Graph::Vertex>& vertices);

    [[nodiscard]] Graph::Vertex Find(Graph::Vertex vertex);

    void Union(Graph::Vertex u, Graph::Vertex v);

private:
    void AddVertex(Graph::Vertex vertex);

    static constexpr uint32_t NO_PARENT = UINT32_MAX;

    Map<Graph::Vertex, Graph::Vertex> parentsMap;
    Map<Graph::Vertex, uint32_t> ranksMap;
};