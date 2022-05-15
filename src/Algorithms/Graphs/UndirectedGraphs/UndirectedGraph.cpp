#include "Algorithms/Graphs/UndirectedGraphs/UndirectedGraph.h"

bool UndirectedGraph::Edge::operator==(Edge rhs) const noexcept
{
    return (first == rhs.first && second == rhs.second) ||
           (first == rhs.second && second == rhs.first);
}

bool UndirectedGraph::Edge::operator!=(Edge rhs) const noexcept
{
    return !(*this == rhs);
}

bool UndirectedGraph::EdgeData::operator==(const EdgeData& rhs) const noexcept
{
    return vertices == rhs.vertices && weight == rhs.weight;
}

bool UndirectedGraph::EdgeData::operator!=(const UndirectedGraph::EdgeData& rhs) const noexcept
{
    return !(*this == rhs);
}

float UndirectedGraph::GetDensity() const noexcept
{
    const uint32_t order = GetOrder();
    const uint64_t size  = GetSize();
    return static_cast<float>(2 * size) / static_cast<float>((order * (order - 1)));
}

std::ostream& operator<<(std::ostream& os, const UndirectedGraph& graph)
{
    os << graph.GetSize() << " " << graph.GetOrder() << "\n";
    graph.ForEachEdge([&os](const UndirectedGraph::EdgeData& edge) {
        os << edge.vertices.first << " " << edge.vertices.second << " " << edge.weight << "\n";
    });

    return os;
}

std::istream& operator>>(std::istream& is, UndirectedGraph& graph)
{
    size_t size;
    uint32_t order;

    is >> size >> order;

    for (uint32_t i = 0; i < order; i++)
    {
        graph.AddVertex();
    }

    for (size_t i = 0; i < size; i++)
    {
        Graph::Vertex first;
        Graph::Vertex second;
        Graph::Weight weight;

        is >> first >> second >> weight;

        graph.AddEdge({{first, second}, weight});
    }

    return is;
}