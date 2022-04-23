#pragma once

#include "Containers/DynamicArray.h"

#include <functional>

class Graph
{
public:
    using Vertex = uint32_t;
    using Weight = uint32_t;
    using VertexPredicate = std::function<void(Vertex)>;

    static constexpr Weight INFINITY = UINT32_MAX;
    static constexpr Vertex MAX_SIZE = UINT32_MAX;

    Graph() = default;
    Graph(const Graph&) = default;
    Graph(Graph&&) = default;
    Graph& operator=(const Graph&) = default;
    Graph& operator=(Graph&&) = default;
    virtual ~Graph() = default;

    virtual Vertex AddVertex() = 0;
    virtual bool RemoveVertex(Vertex vertex) = 0;

    [[nodiscard]] virtual uint32_t GetOrder() const = 0;
    [[nodiscard]] virtual uint64_t GetSize() const = 0;

    [[nodiscard]] virtual bool DoesExist(Vertex vertex) const = 0;

    [[nodiscard]] virtual std::optional<DynamicArray<Vertex>> GetNeighboursOf(Vertex vertex) const = 0;
    [[nodiscard]] virtual DynamicArray<Vertex> GetVertices() const = 0;

    virtual bool ForEachNeighbourOf(Vertex vertex, VertexPredicate predicate) const = 0;
    virtual void ForEachVertex(VertexPredicate predicate) const = 0;
};