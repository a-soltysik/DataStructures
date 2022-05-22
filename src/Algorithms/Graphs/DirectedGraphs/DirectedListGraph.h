#pragma once

#include "Algorithms/Graphs/DirectedGraphs/DirectedGraph.h"
#include "Containers/List.h"

class DirectedListGraph : public DirectedGraph
{
public:
    Vertex AddVertex() override;
    bool AddDirectedEdge(const DirectedEdgeData& edge) override;
    bool RemoveDirectedEdge(DirectedEdge DirectedEdge) override;

    [[nodiscard]] std::optional<Weight> GetWeight(DirectedEdge DirectedEdge) const override;
    bool SetWeight(DirectedEdge DirectedEdge, Weight weight) override;

    [[nodiscard]] uint32_t GetOrder() const noexcept override;
    [[nodiscard]] uint64_t GetSize() const noexcept override;
    [[nodiscard]] uint32_t GetNumberOfNeighboursOf(Vertex vertex) const override;
    [[nodiscard]] bool DoesExist(Vertex vertex) const override;
    [[nodiscard]] bool DoesExist(DirectedEdge DirectedEdge) const override;

    [[nodiscard]] std::optional<DynamicArray<Neighbour>> GetNeighboursOf(Vertex vertex) const override;
    [[nodiscard]] DynamicArray<Vertex> GetVertices() const override;
    [[nodiscard]] DynamicArray<DirectedEdgeData> GetDirectedEdges() const override;

    bool ForEachNeighbourOf(Vertex vertex, NeighbourPredicate predicate) const override;
    void ForEachVertex(VertexPredicate predicate) const override;
    void ForEachDirectedEdge(DirectedEdgePredicate predicate) const override;

    [[nodiscard]] std::string ToString() const override;

private:
    [[nodiscard]] const Neighbour* GetNeighbourOfFirst(DirectedEdge DirectedEdge) const;
    [[nodiscard]] Neighbour* GetNeighbourOfFirst(DirectedEdge DirectedEdge);

    List<List<Neighbour>> graph;
    uint64_t size = 0;
};