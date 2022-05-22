#pragma once

#include "Algorithms/Graphs/DirectedGraphs/DirectedGraph.h"
#include "Algorithms/Graphs/UndirectedGraphs/UndirectedGraph.h"
#include "Utils/Utils.h"

namespace Generator
{

struct GraphConfiguration
{
    uint32_t order;
    float density;
    Graph::Weight minimalWeight;
    Graph::Weight maximumWeight;
};

template<typename T, Graph::isGraph<T> = true>
[[nodiscard]] std::optional<T> GenerateConnectedGraph(const GraphConfiguration& configuration);

template<typename T, Graph::isGraph<T> = true>
[[nodiscard]] bool validateGraphConfiguration(const GraphConfiguration& configuration);

}