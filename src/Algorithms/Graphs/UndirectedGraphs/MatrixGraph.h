#pragma once

#include "UndirectedGraph.h"

class MatrixGraph : public UndirectedGraph
{
public:
    MatrixGraph& operator=(const UndirectedGraph& rhs);
    MatrixGraph& operator=(UndirectedGraph&& rhs);

    Vertex AddVertex() override;
    void Clear() override;

    bool AddEdge(const EdgeData& edge) override;
    bool RemoveEdge(Edge edge) override;

    [[nodiscard]] std::optional<Weight> GetWeight(Edge edge) const override;
    bool SetWeight(Edge edge, Weight weight) override;

    [[nodiscard]] uint32_t GetOrder() const noexcept override;
    [[nodiscard]] size_t GetSize() const noexcept override;
    [[nodiscard]] uint32_t GetNumberOfNeighboursOf(Vertex vertex) const override;
    [[nodiscard]] bool DoesExist(Vertex vertex) const override;
    [[nodiscard]] bool DoesExist(Edge edge) const override;

    [[nodiscard]] std::optional<DynamicArray<Neighbour>> GetNeighboursOf(Vertex vertex) const override;
    [[nodiscard]] DynamicArray<Vertex> GetVertices() const override;
    [[nodiscard]] DynamicArray<EdgeData> GetEdges() const override;

    bool ForEachNeighbourOf(Vertex vertex, NeighbourPredicate predicate) const override;
    void ForEachVertex(VertexPredicate predicate) const override;
    void ForEachEdge(EdgePredicate predicate) const override;

    [[nodiscard]] std::string ToString() const override;

private:
    [[nodiscard]] size_t CalculateColumnWidth() const;
    [[nodiscard]] static std::string RowSeparator(size_t columns, size_t columnWidth);
    [[nodiscard]] static std::string ClosingSeparator(size_t columns, size_t columnWidth);
    [[nodiscard]] static std::string OpeningSeparator(size_t columns, size_t columnWidth);

    DynamicArray<DynamicArray<Weight>> graph;
    uint64_t size = 0;
};