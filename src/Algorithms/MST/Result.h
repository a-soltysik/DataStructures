#pragma once

#include "Algorithms/Graphs/UndirectedGraphs/UndirectedGraph.h"
#include "Containers/Set.h"

namespace MST
{

struct Result
{
    DynamicArray<UndirectedGraph::EdgeData> edges;
    uint64_t weight;
};

}