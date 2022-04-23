#pragma once

#include "Algorithms/Graphs/UndirectedGraphs/UndirectedGraph.h"
#include "Containers/List.h"
#include "Containers/Map.h"

class ListGraph : public UndirectedGraph
{
public:
    using UndirectedGraph::UndirectedGraph;

    Vertex AddVertex() override;
    bool RemoveVertex(Vertex vertex) override;

    bool AddEdge(const EdgeData& edge) override;
    bool RemoveEdge(Edge edge) override;

    [[nodiscard]] std::optional<Weight> GetWeight(Edge edge) const override;
    bool SetWeight(Edge edge, Weight weight) override;

    [[nodiscard]] uint32_t GetOrder() const noexcept override;
    [[nodiscard]] uint64_t GetSize() const noexcept override;
    [[nodiscard]] bool DoesExist(Vertex vertex) const override;
    [[nodiscard]] bool DoesExist(Edge edge) const override;

    [[nodiscard]] std::optional<DynamicArray<Neighbour>> GetNeighboursOf(Vertex vertex) const override;
    [[nodiscard]] DynamicArray<Vertex> GetVertices() const override;
    [[nodiscard]] DynamicArray<EdgeData> GetEdges() const override;

    bool ForEachNeighbourOf(Vertex vertex, NeighbourPredicate predicate) const override;
    void ForEachVertex(VertexPredicate predicate) const override;
    void ForEachEdge(EdgePredicate predicate) const override;

private:

    [[nodiscard]] const Neighbour* GetNeighbourOfFirst(Edge edge) const;
    [[nodiscard]] Neighbour* GetNeighbourOfFirst(Edge edge);

    List<List<Neighbour>> graph;
    Map<Vertex, List<List<Neighbour>>::Iterator> verticesMap;
    uint64_t size = 0;
};