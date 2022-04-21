#pragma once

#include "Algorithm/Graphs/DirectedGraphs/DirectedGraph.h"
#include "Containers/List.h"

class DirectedListGraph : public DirectedGraph
{
public:
    struct Neighbour
    {
        Vertex vertex;
        Weight weight;
    };

    Vertex AddVertex() override;
    bool RemoveVertex(Vertex vertex) override;

    bool AddDirectedEdge(DirectedEdge edge, Weight weight) override;
    bool RemoveDirectedEdge(DirectedEdge edge) override;

    [[nodiscard]] std::optional<Weight> GetWeight(DirectedEdge edge) const override;
    bool SetWeight(DirectedEdge edge, Weight weight) override;

    [[nodiscard]] uint32_t GetOrder() const override;
    [[nodiscard]] uint64_t GetSize() const override;

    bool ForEachNeighbour(Vertex source, VertexPredicate predicate) override;
    bool ForEachVertex(VertexPredicate predicate) override;
    bool ForEachDirectedEdge(DirectedEdgePredicate predicate) override;

    [[nodiscard]] bool doesExist(Vertex vertex) const;

private:
    [[nodiscard]] const Neighbour* GetNeighbourOfFirst(DirectedEdge edge) const;
    [[nodiscard]] Neighbour* GetNeighbourOfFirst(DirectedEdge edge);
    [[nodiscard]] bool FindDirectedEdge(DirectedEdge edge) const;

    List<List<Neighbour>> graph;
    uint64_t size = 0;
};