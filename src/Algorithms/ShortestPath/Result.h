#pragma once

#include "Algorithms/Graphs/DirectedGraphs/DirectedGraph.h"

#include <ostream>

namespace ShortestPath
{

struct Result
{
    DynamicArray<Graph::Vertex> path;
    uint64_t weight;
};

}

std::ostream& operator<<(std::ostream& os, const ShortestPath::Result& result);