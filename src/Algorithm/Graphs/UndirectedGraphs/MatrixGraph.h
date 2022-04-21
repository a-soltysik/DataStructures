#pragma once

#include "Algorithm/Graphs/UndirectedGraphs/UndirectedGraph.h"
#include "Containers/DynamicArray.h"

class MatrixGraph : public UndirectedGraph
{
    using UndirectedGraph::UndirectedGraph;

    Vertex AddVertex() override;
    bool RemoveVertex(Vertex vertex) override;

    bool AddEdge(Edge edge, Weight weight) override;
    bool RemoveEdge(Edge edge) override;

    [[nodiscard]] std::optional<Weight> GetWeight(Edge edge) const override;
    bool SetWeight(Edge edge, Weight weight) override;

    [[nodiscard]] uint32_t GetOrder() const override;
    [[nodiscard]] uint64_t GetSize() const override;

    bool ForEachNeighbour(Vertex source, VertexPredicate predicate) const override;
    void ForEachVertex(VertexPredicate predicate) const override;
    void ForEachEdge(EdgePredicate predicate) const override;

    [[nodiscard]] bool doesExist(Vertex vertex) const override;
    [[nodiscard]] bool doesExist(Edge edge) const override;

private:
    DynamicArray<DynamicArray<Weight>> graph;
    uint64_t size = 0;
};