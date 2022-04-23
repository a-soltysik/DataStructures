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

float UndirectedGraph::GetDensity() const noexcept
{
    const uint32_t order = GetOrder();
    const uint64_t size  = GetSize();
    return static_cast<float>(2 * size) / static_cast<float>((order * (order - 1)));
}
