#pragma once

#include "Algorithms/Graphs/UndirectedGraphs/UndirectedGraph.h"
#include "Containers/Map.h"

class MatrixGraph : public UndirectedGraph
{
public:
    using UndirectedGraph::UndirectedGraph;

    Vertex AddVertex() override;
    bool RemoveVertex(Vertex vertex) override;

    bool AddEdge(Edge edge, Weight weight) override;
    bool RemoveEdge(Edge edge) override;

    [[nodiscard]] std::optional<Weight> GetWeight(Edge edge) const override;
    bool SetWeight(Edge edge, Weight weight) override;

    [[nodiscard]] uint32_t GetOrder() const noexcept override;
    [[nodiscard]] uint64_t GetSize() const noexcept override;
    [[nodiscard]] bool DoesExist(Vertex vertex) const override;
    [[nodiscard]] bool DoesExist(Edge edge) const override;

    [[nodiscard]] std::optional<DynamicArray<Vertex>> GetNeighboursOf(Vertex vertex) const override;
    [[nodiscard]] DynamicArray<Vertex> GetVertices() const override;
    [[nodiscard]] DynamicArray<Utils::Pair<Edge, Weight>> GetEdges() const override;

    bool ForEachNeighbourOf(Vertex vertex, VertexPredicate predicate) const override;
    void ForEachVertex(VertexPredicate predicate) const override;
    void ForEachEdge(EdgePredicate predicate) const override;

private:
    void RestoreIndicesFrom(Vertex from);
    std::optional<Vertex> FindVertexByIndex(uint32_t index) const;

    DynamicArray<DynamicArray<Weight>> graph;
    Map<Vertex, uint32_t> verticesMap;
    uint64_t size = 0;
};