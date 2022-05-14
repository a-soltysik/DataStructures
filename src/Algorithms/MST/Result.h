#pragma once

#include "Algorithms/Graphs/UndirectedGraphs/UndirectedGraph.h"

#include <ostream>

namespace MST
{

struct Result
{
    DynamicArray<UndirectedGraph::EdgeData> edges;
    uint64_t weight;
};

}

std::ostream& operator<<(std::ostream& os, const MST::Result& result);