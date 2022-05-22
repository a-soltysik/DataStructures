#include "Algorithms/Graphs/DSU.h"

DSU::DSU(const DynamicArray<Graph::Vertex>& vertices)
{
    parents.Resize(vertices.Size());
    ranks.Resize(vertices.Size());
    for (const auto& vertex : vertices)
    {
        AddVertex(vertex);
    }
}

Graph::Vertex DSU::Find(Graph::Vertex vertex)
{
    if (parents.Size() <= vertex)
    {
        return vertex;
    }

    auto& parent = parents[vertex];
    if (parent == NO_PARENT)
    {
        return vertex;
    }

    return parent = Find(parent);
}

void DSU::Union(Graph::Vertex u, Graph::Vertex v)
{
    auto uRoot = Find(u);
    auto vRoot = Find(v);

    if (uRoot != vRoot)
    {
        auto& uRootRank = ranks[uRoot];
        auto& vRootRank = ranks[vRoot];

        if (uRootRank < vRootRank)
        {
            parents[uRoot] = vRoot;
            vRootRank += uRootRank;
        }
        else
        {
            parents[vRoot] = uRoot;
            uRootRank += vRootRank;
        }
    }
}

void DSU::AddVertex(Graph::Vertex vertex)
{
    parents[vertex] = NO_PARENT;
    ranks[vertex] = 1;
}
