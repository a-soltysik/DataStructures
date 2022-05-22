#pragma once

#include "Algorithms/Graphs/Graph.h"
#include "Containers/Map.h"

class DSU
{
public:
    explicit DSU(const DynamicArray<Graph::Vertex>& vertices);

    [[nodiscard]] Graph::Vertex Find(Graph::Vertex vertex);

    void Union(Graph::Vertex u, Graph::Vertex v);

private:
    void AddVertex(Graph::Vertex vertex);

    static constexpr uint32_t NO_PARENT = UINT32_MAX;

    DynamicArray<Graph::Vertex> parents;
    DynamicArray<uint32_t> ranks;
};