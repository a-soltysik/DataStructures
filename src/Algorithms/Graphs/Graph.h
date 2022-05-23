#pragma once

#include "Containers/DynamicArray.h"

class Graph
{
public:
    template<typename T>
    using isGraph = std::enable_if_t<Utils::DerivedFrom<T, Graph>::Value, bool>;

    struct Neighbour;
    using Vertex = uint32_t;
    using Weight = uint32_t;
    using VertexPredicate = std::function<void(Vertex)>;
    using NeighbourPredicate = std::function<void(Neighbour)>;

    struct Neighbour
    {
        Vertex vertex;
        Weight weight;
    };

    static constexpr Weight INFINITY_WEIGHT = UINT32_MAX;
    static constexpr Vertex MAX_SIZE = UINT32_MAX;

    Graph() = default;
    Graph(const Graph&) = default;
    Graph(Graph&&) = default;
    Graph& operator=(const Graph&) = default;
    Graph& operator=(Graph&&) = default;
    virtual ~Graph() = default;

    virtual Vertex AddVertex() = 0;

    [[nodiscard]] virtual uint32_t GetOrder() const = 0;
    [[nodiscard]] virtual size_t GetSize() const = 0;
    [[nodiscard]] virtual float GetDensity() const = 0;
    [[nodiscard]] virtual uint32_t GetNumberOfNeighboursOf(Vertex vertex) const = 0;

    [[nodiscard]] virtual bool DoesExist(Vertex vertex) const = 0;

    [[nodiscard]] virtual std::optional<DynamicArray<Neighbour>> GetNeighboursOf(Vertex vertex) const = 0;
    [[nodiscard]] virtual DynamicArray<Vertex> GetVertices() const = 0;

    virtual bool ForEachNeighbourOf(Vertex vertex, NeighbourPredicate predicate) const = 0;
    virtual void ForEachVertex(VertexPredicate predicate) const = 0;

    [[nodiscard]] virtual std::string ToString() const = 0;
    friend std::ostream& operator<<(std::ostream& os, const Graph& graph);
    friend std::istream& operator>>(std::istream& os, Graph& graph);

protected:
    virtual void Serialize(std::ostream& os) const = 0;
    virtual void Deserialize(std::istream& is) = 0;
};
