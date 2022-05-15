#include "Algorithms/Graphs/DirectedGraphs/DirectedGraph.h"

float DirectedGraph::GetDensity() const noexcept
{
    const uint32_t order = GetOrder();
    const uint64_t size  = GetSize();
    return static_cast<float>(size) / static_cast<float>((order * (order - 1)));
}

bool DirectedGraph::DirectedEdgeData::operator==(const DirectedEdgeData& rhs) const noexcept
{
    return vertices == rhs.vertices && weight == rhs.weight;
}

bool DirectedGraph::DirectedEdgeData::operator!=(const DirectedGraph::DirectedEdgeData& rhs) const noexcept
{
    return !(*this == rhs);
}

std::ostream& operator<<(std::ostream& os, const DirectedGraph& graph)
{
    os << graph.GetSize() << " " << graph.GetOrder() << "\n";
    graph.ForEachDirectedEdge([&os](const DirectedGraph::DirectedEdgeData& edge) {
        os << edge.vertices.first << " " << edge.vertices.second << " " << edge.weight << "\n";
    });

    return os;
}

std::istream& operator>>(std::istream& is, DirectedGraph& graph)
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

        graph.AddDirectedEdge({{first, second}, weight});
    }

    return is;
}
