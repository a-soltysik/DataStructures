#pragma once

#include "Result.h"
#include "Algorithms/Graphs/DirectedGraphs/DirectedGraph.h"

namespace ShortestPath::Dijkstra
{

Result FindShortestPath(const DirectedGraph& graph, Graph::Vertex from, Graph::Vertex to);

}