#pragma once

#include "Algorithms/ShortestPath/Result.h"
#include "Algorithms/Graphs/DirectedGraphs/DirectedGraph.h"

namespace ShortestPath::BellmanFord
{

Result FindShortestPath(const DirectedGraph& graph, Graph::Vertex from, Graph::Vertex to);

}