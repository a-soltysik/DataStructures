#include "Kruskal.h"
#include "DSU.h"
#include "Utils/Algorithms.h"

namespace MST::Kruskal
{

void SortEdgesByWeight(DynamicArray<UndirectedGraph::EdgeData>& edges);
[[nodiscard]] uint64_t CalculateOverallWeight(const Result& result);

Result FindMstOf(const UndirectedGraph& graph)
{
    auto vertices = graph.GetVertices();
    auto edges = graph.GetEdges();
    UndirectedGraph::Vertex numberOfEdges = 0;

    DSU forest(vertices);
    Result result;
    result.edges.Resize(graph.GetOrder() - 1);

    SortEdgesByWeight(edges);

    for (const auto& edge : edges)
    {
        if (forest.Find(edge.vertices.first) != forest.Find(edge.vertices.second))
        {
            forest.Union(edge.vertices.first, edge.vertices.second);
            result.edges[numberOfEdges++] = edge;
        }
        if (numberOfEdges >= graph.GetOrder() - 1)
        {
            result.weight = CalculateOverallWeight(result);
            return result;
        }
    }

    return {{}, 0};
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
