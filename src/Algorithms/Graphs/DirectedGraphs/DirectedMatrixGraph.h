#pragma once

#include "Algorithms/Graphs/DirectedGraphs/DirectedGraph.h"
#include "Containers/Map.h"

class DirectedMatrixGraph : public DirectedGraph
{
public:
    using DirectedGraph::DirectedGraph;

    Vertex AddVertex() override;
    bool RemoveVertex(Vertex vertex) override;

    bool AddDirectedEdge(const DirectedEdgeData& edge) override;
    bool RemoveDirectedEdge(DirectedEdge directedEdge) override;

    [[nodiscard]] std::optional<Weight> GetWeight(DirectedEdge directedEdge) const override;
    bool SetWeight(DirectedEdge directedEdge, Weight weight) override;

    [[nodiscard]] uint32_t GetOrder() const noexcept override;
    [[nodiscard]] uint64_t GetSize() const noexcept override;
    [[nodiscard]] bool DoesExist(Vertex vertex) const override;
    [[nodiscard]] bool DoesExist(DirectedEdge directedEdge) const override;

    [[nodiscard]] std::optional<DynamicArray<Neighbour>> GetNeighboursOf(Vertex vertex) const override;
    [[nodiscard]] DynamicArray<Vertex> GetVertices() const override;
    [[nodiscard]] DynamicArray<DirectedEdgeData> GetDirectedEdges() const override;

    bool ForEachNeighbourOf(Vertex vertex, NeighbourPredicate predicate) const override;
    void ForEachVertex(VertexPredicate predicate) const override;
    void ForEachDirectedEdge(DirectedEdgePredicate predicate) const override;

private:
    void RestoreIndicesFrom(Vertex from);

    DynamicArray<DynamicArray<Weight>> graph;
    Map<Vertex, uint32_t> verticesMap;
    uint64_t size = 0;
};