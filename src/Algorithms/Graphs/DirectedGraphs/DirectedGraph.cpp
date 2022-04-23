#include "Algorithms/Graphs/DirectedGraphs/DirectedGraph.h"

float DirectedGraph::GetDensity() const noexcept
{
    const uint32_t order = GetOrder();
    const uint64_t size  = GetSize();
    return static_cast<float>(size) / static_cast<float>((order * (order - 1)));
}