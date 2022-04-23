#pragma once

#include "Algorithms/Graphs/DirectedGraphs/DirectedGraph.h"
#include "Containers/List.h"
#include "Containers/Map.h"

class DirectedListGraph : public DirectedGraph
{
public:
    using DirectedGraph::DirectedGraph;

    Vertex AddVertex() override;
    bool RemoveVertex(Vertex vertex) override;

    bool AddDirectedEdge(DirectedEdge DirectedEdge, Weight weight) override;
    bool RemoveDirectedEdge(DirectedEdge DirectedEdge) override;

    [[nodiscard]] std::optional<Weight> GetWeight(DirectedEdge DirectedEdge) const override;
    bool SetWeight(DirectedEdge DirectedEdge, Weight weight) override;

    [[nodiscard]] uint32_t GetOrder() const noexcept override;
    [[nodiscard]] uint64_t GetSize() const noexcept override;
    [[nodiscard]] bool DoesExist(Vertex vertex) const override;
    [[nodiscard]] bool DoesExist(DirectedEdge DirectedEdge) const override;

    [[nodiscard]] std::optional<DynamicArray<Neighbour>> GetNeighboursOf(Vertex vertex) const override;
    [[nodiscard]] DynamicArray<Vertex> GetVertices() const override;
    [[nodiscard]] DynamicArray<Utils::Pair<DirectedEdge, Weight>> GetDirectedEdges() const override;

    bool ForEachNeighbourOf(Vertex vertex, NeighbourPredicate predicate) const override;
    void ForEachVertex(VertexPredicate predicate) const override;
    void ForEachDirectedEdge(DirectedEdgePredicate predicate) const override;

private:
    [[nodiscard]] const Neighbour* GetNeighbourOfFirst(DirectedEdge DirectedEdge) const;
    [[nodiscard]] Neighbour* GetNeighbourOfFirst(DirectedEdge DirectedEdge);

    List<List<Neighbour>> graph;
    Map<Vertex, List<List<Neighbour>>::Iterator> verticesMap;
    uint64_t size = 0;
};