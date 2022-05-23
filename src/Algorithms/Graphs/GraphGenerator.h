#pragma once

#include "Algorithms/Graphs/DirectedGraphs/DirectedGraph.h"
#include "Algorithms/Graphs/UndirectedGraphs/UndirectedGraph.h"

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
[[nodiscard]] constexpr bool ValidateGraphConfiguration(const GraphConfiguration& configuration);

template<typename T, DirectedGraph::isDirectedGraph<T> = true>
[[nodiscard]] constexpr float GetMinimalDensity(uint32_t order);

template<typename T, UndirectedGraph::isUndirectedGraph<T> = true>
[[nodiscard]] constexpr float GetMinimalDensity(uint32_t order);



template<typename T, Graph::isGraph<T>>
constexpr bool ValidateGraphConfiguration(const GraphConfiguration& configuration)
{
    if (configuration.density > 1 || configuration.density < GetMinimalDensity<T>(configuration.order))
    {
        return false;
    }
    if (configuration.order == Graph::MAX_SIZE)
    {
        return false;
    }
    if (configuration.minimalWeight == Graph::INFINITY_WEIGHT || configuration.maximumWeight == Graph::INFINITY_WEIGHT)
    {
        return false;
    }
    if (configuration.minimalWeight > configuration.maximumWeight)
    {
        return false;
    }
    return true;
}

template<typename T, DirectedGraph::isDirectedGraph<T>>
constexpr float GetMinimalDensity(uint32_t order)
{
    return 1.0f / static_cast<float>(order);
}

template<typename T, UndirectedGraph::isUndirectedGraph<T>>
constexpr float GetMinimalDensity(uint32_t order)
{
    return 2.0f / static_cast<float>(order);
}


}