#pragma once

#include "DirectedGraph.h"

namespace DirectedGraphConverter
{

template<typename T, DirectedGraph::isDirectedGraph<T> = true>
T convert(const DirectedGraph& graph)
{
    T newGraph;

    for (uint32_t i = 0; i < graph.GetOrder(); i++)
    {
        newGraph.AddVertex();
    }

    graph.ForEachDirectedEdge([&newGraph](const DirectedGraph::DirectedEdgeData& edge) {
        newGraph.AddDirectedEdge(edge);
    });

    return newGraph;
}

}