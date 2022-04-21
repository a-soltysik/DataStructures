#pragma once

#include "Algorithm/Graphs/UndirectedGraphs/UndirectedGraph.h"
#include "Containers/List.h"

class ListGraph : public UndirectedGraph
{
public:
    using UndirectedGraph::UndirectedGraph;

    struct Neighbour
    {
        Graph::Vertex vertex;
        Weight weight;
    };

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
    [[nodiscard]] const Neighbour* GetNeighbourOfFirst(Edge edge) const;
    [[nodiscard]] Neighbour* GetNeighbourOfFirst(Edge edge);

    List<List<Neighbour>> graph;
    uint64_t size = 0;
};