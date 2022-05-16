#pragma once

#include "Algorithms/Graphs/DirectedGraphs/DirectedGraph.h"
#include "Algorithms/Graphs/UndirectedGraphs/UndirectedGraph.h"
#include "Utils/Utils.h"

namespace Generator
{

template<typename T>
using isDirectedGraph = std::enable_if_t<Utils::DerivedFrom<T, DirectedGraph>::Value, bool>;

template<typename T>
using isUndirectedGraph = std::enable_if_t<Utils::DerivedFrom<T, UndirectedGraph>::Value, bool>;

template<typename T>
using isGraph = std::enable_if_t<Utils::DerivedFrom<T, DirectedGraph>::Value ||
                                 Utils::DerivedFrom<T, UndirectedGraph>::Value, bool>;

struct GraphConfiguration
{
    uint32_t order;
    float density;
    Graph::Weight minimalWeight;
    Graph::Weight maximumWeight;
};

template<typename T, isGraph<T> = true>
[[nodiscard]] std::optional<T> GenerateConnectedGraph(const GraphConfiguration& configuration);

template<typename T, isGraph<T> = true>
[[nodiscard]] bool validateGraphConfiguration(const GraphConfiguration& configuration);

}