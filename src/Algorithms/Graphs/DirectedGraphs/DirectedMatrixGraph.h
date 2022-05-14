#pragma once

#include "Algorithms/Graphs/DirectedGraphs/DirectedGraph.h"

class DirectedMatrixGraph : public DirectedGraph
{
public:
    using DirectedGraph::DirectedGraph;

    Vertex AddVertex() override;
    bool AddDirectedEdge(const DirectedEdgeData& edge) override;
    bool RemoveDirectedEdge(DirectedEdge DirectedEdge) override;

    [[nodiscard]] std::optional<Weight> GetWeight(DirectedEdge directedEdge) const override;
    bool SetWeight(DirectedEdge directedEdge, Weight weight) override;

    [[nodiscard]] uint32_t GetOrder() const noexcept override;
    [[nodiscard]] uint64_t GetSize() const noexcept override;
    [[nodiscard]] uint32_t GetNumberOfNeighboursOf(Vertex vertex) const override;
    [[nodiscard]] bool DoesExist(Vertex vertex) const override;
    [[nodiscard]] bool DoesExist(DirectedEdge directedEdge) const override;

    [[nodiscard]] std::optional<DynamicArray<Neighbour>> GetNeighboursOf(Vertex vertex) const override;
    [[nodiscard]] DynamicArray<Vertex> GetVertices() const override;
    [[nodiscard]] DynamicArray<DirectedEdgeData> GetDirectedEdges() const override;

    bool ForEachNeighbourOf(Vertex vertex, NeighbourPredicate predicate) const override;
    void ForEachVertex(VertexPredicate predicate) const override;
    void ForEachDirectedEdge(DirectedEdgePredicate predicate) const override;

private:
    DynamicArray<DynamicArray<Weight>> graph;
    uint64_t size = 0;
};