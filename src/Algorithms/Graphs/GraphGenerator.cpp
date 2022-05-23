#include "Algorithms/Graphs/GraphGenerator.h"
#include "Algorithms/Graphs/DirectedGraphs/DirectedListGraph.h"
#include "Algorithms/Graphs/DirectedGraphs/DirectedMatrixGraph.h"
#include "Algorithms/Graphs/UndirectedGraphs/ListGraph.h"
#include "Algorithms/Graphs/UndirectedGraphs/MatrixGraph.h"

#include <cmath>

namespace Generator
{

[[nodiscard]] Utils::Pair<Graph::Vertex, Graph::Vertex> DrawEdge(const DynamicArray<Graph::Vertex>& vertices);

template<typename T, Graph::isGraph<T> = true>
[[nodiscard]] T GenerateGraph(uint32_t order);

/**
 * DirectedGraph templates
 */

template<typename T, DirectedGraph::isDirectedGraph<T> = true>
[[nodiscard]] T GenerateSparseGraph(const GraphConfiguration& configuration, size_t size);

template<typename T, DirectedGraph::isDirectedGraph<T> = true>
[[nodiscard]] T GenerateDenseGraph(const GraphConfiguration& configuration, size_t size);

template<typename T, DirectedGraph::isDirectedGraph<T> = true>
[[nodiscard]] T GenerateSpanningTree(const GraphConfiguration& configuration);

template<typename T, DirectedGraph::isDirectedGraph<T> = true>
[[nodiscard]] uint64_t GetSize(const GraphConfiguration& configuration);

/**
 * UndirectedGraph templates
 */

template<typename T, UndirectedGraph::isUndirectedGraph<T> = true>
[[nodiscard]] T GenerateSparseGraph(const GraphConfiguration& configuration, size_t size);

template<typename T, UndirectedGraph::isUndirectedGraph<T> = true>
[[nodiscard]] T GenerateDenseGraph(const GraphConfiguration& configuration, size_t size);

template<typename T, UndirectedGraph::isUndirectedGraph<T> = true>
[[nodiscard]] T GenerateSpanningTree(const GraphConfiguration& configuration);

template<typename T, UndirectedGraph::isUndirectedGraph<T> = true>
[[nodiscard]] uint64_t GetSize(const GraphConfiguration& configuration);

/**
 * Definitions
 */



template<typename T, Graph::isGraph<T>>
std::optional<T> GenerateConnectedGraph(const GraphConfiguration& configuration)
{
    if (!ValidateGraphConfiguration<T>(configuration))
    {
        return {};
    }

    if (configuration.density < 0.5)
    {
        return GenerateSparseGraph<T>(configuration, GetSize<T>(configuration));
    }

    return GenerateDenseGraph<T>(configuration, GetSize<T>(configuration));
}

template<typename T, Graph::isGraph<T>>
T GenerateGraph(uint32_t order)
{
    T graph;
    for (uint32_t i = 0; i < order; i++)
    {
        graph.AddVertex();
    }

    return graph;
}

Utils::Pair<Graph::Vertex, Graph::Vertex> DrawEdge(const DynamicArray<Graph::Vertex>& vertices)
{
    Graph::Vertex first = vertices[static_cast<size_t>(Utils::GetRandomNumber<size_t>(0, vertices.Size() - 1))];

    Graph::Vertex second;

    do
    {
        second = vertices[static_cast<size_t>(Utils::GetRandomNumber<size_t>(0, vertices.Size() - 1))];
    } while (first == second);

    return {first, second};
}

template<typename T, DirectedGraph::isDirectedGraph<T>>
T GenerateSparseGraph(const GraphConfiguration& configuration, size_t size)
{
    T graph = GenerateSpanningTree<T>(configuration);

    auto vertices = graph.GetVertices();

    while (graph.GetSize() < size)
    {
        auto pair = DrawEdge(vertices);
        auto weight = Utils::GetRandomNumber<Graph::Weight>(configuration.minimalWeight, configuration.maximumWeight);

        graph.AddDirectedEdge({{pair.first, pair.second}, weight});
    }

    return graph;
}

template<typename T, DirectedGraph::isDirectedGraph<T>>
T GenerateDenseGraph(const GraphConfiguration& configuration, size_t size)
{
    T graph = GenerateGraph<T>(configuration.order);

    auto vertices = graph.GetVertices();

    for (uint32_t i = 0; i < vertices.Size(); i++)
    {
        for (uint32_t j = 0; j < vertices.Size(); j++)
        {
            if (i != j)
            {
                auto weight = Utils::GetRandomNumber<Graph::Weight>(configuration.minimalWeight, configuration.maximumWeight);

                graph.AddDirectedEdge({{i, j}, weight});
            }
        }
    }

    while (graph.GetSize() > size)
    {
        auto pair = DrawEdge(vertices);

        graph.RemoveDirectedEdge({pair.first, pair.second});

        if (graph.GetNumberOfNeighboursOf(pair.first) == 0)
        {
            auto weight = Utils::GetRandomNumber<Graph::Weight>(0, 100);
            graph.AddDirectedEdge({{pair.first, pair.second}, weight});
        }
    }

    return graph;
}

template<typename T, DirectedGraph::isDirectedGraph<T>>
T GenerateSpanningTree(const GraphConfiguration& configuration)
{
    T graph = GenerateGraph<T>(configuration.order);

    auto vertices = graph.GetVertices();

    for (uint32_t i = 0; i < graph.GetOrder() - 1; i++)
    {
        auto weight = Utils::GetRandomNumber<Graph::Weight>(configuration.minimalWeight, configuration.maximumWeight);
        graph.AddDirectedEdge({{vertices[i], vertices[i + 1]}, weight});
    }

    return graph;
}

template<typename T, DirectedGraph::isDirectedGraph<T>>
uint64_t GetSize(const GraphConfiguration& configuration)
{
    return std::llround(configuration.density * static_cast<float>(configuration.order) * static_cast<float>(configuration.order - 1));
}

template<typename T, UndirectedGraph::isUndirectedGraph<T>>
T GenerateSparseGraph(const GraphConfiguration& configuration, size_t size)
{
    T graph = GenerateSpanningTree<T>(configuration);

    auto vertices = graph.GetVertices();

    while (graph.GetSize() < size)
    {
        auto pair = DrawEdge(vertices);
        auto weight = Utils::GetRandomNumber<Graph::Weight>(configuration.minimalWeight, configuration.maximumWeight);

        graph.AddEdge({{pair.first, pair.second}, weight});
    }

    return graph;
}

template<typename T, UndirectedGraph::isUndirectedGraph<T>>
T GenerateDenseGraph(const GraphConfiguration& configuration, size_t size)
{
    T graph = GenerateGraph<T>(configuration.order);

    auto vertices = graph.GetVertices();

    for (uint32_t i = 0; i < vertices.Size(); i++)
    {
        for (uint32_t j = 0; j < vertices.Size(); j++)
        {
            if (i != j)
            {
                auto weight = Utils::GetRandomNumber<Graph::Weight>(configuration.minimalWeight, configuration.maximumWeight);

                graph.AddEdge({{i, j}, weight});
            }
        }
    }

    while (graph.GetSize() > size)
    {
        auto pair = DrawEdge(vertices);

        graph.RemoveEdge({pair.first, pair.second});

        if (graph.GetNumberOfNeighboursOf(pair.first) == 0)
        {
            auto weight = Utils::GetRandomNumber<Graph::Weight>(configuration.minimalWeight, configuration.maximumWeight);
            graph.AddEdge({{pair.first, pair.second}, weight});
        }
    }

    return graph;
}

template<typename T, UndirectedGraph::isUndirectedGraph<T>>
T GenerateSpanningTree(const GraphConfiguration& configuration)
{
    T graph = GenerateGraph<T>(configuration.order);

    auto vertices = graph.GetVertices();

    for (uint32_t i = 0; i < graph.GetOrder() - 1; i++)
    {
        auto weight = Utils::GetRandomNumber<Graph::Weight>(configuration.minimalWeight, configuration.maximumWeight);
        graph.AddEdge({{vertices[i], vertices[i + 1]}, weight});
    }

    return graph;
}

template<typename T, UndirectedGraph::isUndirectedGraph<T>>
uint64_t GetSize(const GraphConfiguration& configuration)
{
    return std::llround(configuration.density * static_cast<float>(configuration.order) * static_cast<float>(configuration.order - 1) / 2);
}

template
bool ValidateGraphConfiguration<DirectedListGraph>(const GraphConfiguration& configuration);

template
bool ValidateGraphConfiguration<DirectedMatrixGraph>(const GraphConfiguration& configuration);

template
bool ValidateGraphConfiguration<ListGraph>(const GraphConfiguration& configuration);

template
bool ValidateGraphConfiguration<MatrixGraph>(const GraphConfiguration& configuration);

template
std::optional<DirectedListGraph>GenerateConnectedGraph<DirectedListGraph, true>(const GraphConfiguration& configuration);

template
std::optional<DirectedMatrixGraph>GenerateConnectedGraph<DirectedMatrixGraph, true>(const GraphConfiguration& configuration);

template
std::optional<ListGraph>GenerateConnectedGraph<ListGraph, true>(const GraphConfiguration& configuration);

template
std::optional<MatrixGraph>GenerateConnectedGraph<MatrixGraph, true>(const GraphConfiguration& configuration);




}