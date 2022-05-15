#pragma once

#include "Algorithms/Graphs/UndirectedGraphs/UndirectedGraph.h"

class MatrixGraph : public UndirectedGraph
{
public:
    using UndirectedGraph::UndirectedGraph;

    Vertex AddVertex() override;

    bool AddEdge(const EdgeData& edge) override;
    bool RemoveEdge(Edge edge) override;

    [[nodiscard]] std::optional<Weight> GetWeight(Edge edge) const override;
    bool SetWeight(Edge edge, Weight weight) override;

    [[nodiscard]] uint32_t GetOrder() const noexcept override;
    [[nodiscard]] uint64_t GetSize() const noexcept override;
    [[nodiscard]] uint32_t GetNumberOfNeighboursOf(Vertex vertex) const override;
    [[nodiscard]] bool DoesExist(Vertex vertex) const override;
    [[nodiscard]] bool DoesExist(Edge edge) const override;

    [[nodiscard]] std::optional<DynamicArray<Neighbour>> GetNeighboursOf(Vertex vertex) const override;
    [[nodiscard]] DynamicArray<Vertex> GetVertices() const override;
    [[nodiscard]] DynamicArray<EdgeData> GetEdges() const override;

    bool ForEachNeighbourOf(Vertex vertex, NeighbourPredicate predicate) const override;
    void ForEachVertex(VertexPredicate predicate) const override;
    void ForEachEdge(EdgePredicate predicate) const override;

    [[nodiscard]] std::string ToString() const;

private:
    [[nodiscard]] size_t GetColumnWidth() const;
    [[nodiscard]] static std::string RowSeparator(size_t columns, size_t columnWidth) ;
    [[nodiscard]] static std::string RowEndSeparator(size_t columns, size_t columnWidth) ;
    [[nodiscard]] static std::string RowBeginSeparator(size_t columns, size_t columnWidth) ;

    DynamicArray<DynamicArray<Weight>> graph;
    uint64_t size = 0;
};