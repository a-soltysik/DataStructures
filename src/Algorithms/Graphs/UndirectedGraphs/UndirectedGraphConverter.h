#pragma once

#include "UndirectedGraph.h"

namespace UndirectedGraphConverter
{

template<typename T, UndirectedGraph::isUndirectedGraph<T> = true>
T convert(const UndirectedGraph& graph)
{
    T newGraph;

    for (uint32_t i = 0; i < graph.GetOrder(); i++)
    {
        newGraph.AddVertex();
    }

    graph.ForEachEdge([&newGraph](const UndirectedGraph::EdgeData& edge) {
        newGraph.AddEdge(edge);
    });

    return newGraph;
}

}