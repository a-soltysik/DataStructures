#include "Algorithms/Graphs/DSU.h"

DSU::DSU(const DynamicArray<Graph::Vertex>& vertices)
{
    for (const auto& vertex : vertices)
    {
        AddVertex(vertex);
    }
}

Graph::Vertex DSU::Find(Graph::Vertex vertex)
{
    if (parentsMap.Find(vertex) == parentsMap.end())
    {
        AddVertex(vertex);
        return vertex;
    }

    auto& parent = parentsMap[vertex];
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
        auto& uRootRank = ranksMap[uRoot];
        auto& vRootRank = ranksMap[vRoot];

        if (uRootRank < vRootRank)
        {
            parentsMap[uRoot] = vRoot;
            vRootRank += uRootRank;
        }
        else
        {
            parentsMap[vRoot] = uRoot;
            uRootRank += vRootRank;
        }
    }
}

void DSU::AddVertex(Graph::Vertex vertex)
{
    parentsMap[vertex] = NO_PARENT;
    ranksMap[vertex] = 1;
}
