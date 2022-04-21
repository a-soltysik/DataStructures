#pragma once

#include <functional>
#include <cstdint>

class Graph
{
public:
    using Vertex = uint32_t;
    using Weight = uint32_t;
    using VertexPredicate = std::function<void(Vertex)>;

    static constexpr Weight INF = UINT32_MAX;
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

    [[nodiscard]] virtual bool doesExist(Vertex vertex) const = 0;

    virtual bool ForEachNeighbour(Vertex source, VertexPredicate predicate) const = 0;
    virtual void ForEachVertex(VertexPredicate predicate) const = 0;
};