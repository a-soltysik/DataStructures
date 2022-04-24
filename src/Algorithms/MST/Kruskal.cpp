#include "Algorithms/MST/Kruskal.h"
#include "Utils/Algorithms.h"
#include "Algorithms/Graphs/DSU.h"

namespace MST::Kruskal
{

void SortEdgesByWeight(DynamicArray<UndirectedGraph::EdgeData>& edges);
[[nodiscard]] uint64_t CalculateOverallWeight(const Result& result);

Result FindMstOf(const UndirectedGraph& graph)
{
    auto vertices = graph.GetVertices();
    auto edges = graph.GetEdges();

    DSU forest(vertices);
    Result result;

    SortEdgesByWeight(edges);

    for (const auto& edge : edges)
    {
        if (forest.Find(edge.vertices.first) != forest.Find(edge.vertices.second))
        {
            forest.Union(edge.vertices.first, edge.vertices.second);
            result.edges.PushBack(edge);
        }
    }

    result.weight = CalculateOverallWeight(result);
    return result;
}

void SortEdgesByWeight(DynamicArray<UndirectedGraph::EdgeData>& edges)
{
    Utils::QuickSort(edges.begin(),
                     edges.end(),
                     [](const auto& edge1, const auto& edge2)
                     {
                         return edge1.weight < edge2.weight;
                     });
}

uint64_t CalculateOverallWeight(const Result& result)
{
    uint64_t weight = 0;
    for (const auto& edge : result.edges)
    {
        weight += edge.weight;
    }
    return weight;
}

}
