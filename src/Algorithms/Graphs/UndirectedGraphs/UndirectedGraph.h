#pragma once

#include "Algorithms/Graphs/Graph.h"

#include <optional>

class UndirectedGraph : public Graph
{
public:
    struct Edge
    {
        Vertex first;
        Vertex second;

        [[nodiscard]] bool operator==(Edge rhs) const noexcept;
        [[nodiscard]] bool operator!=(Edge rhs) const noexcept;
    };

    struct EdgeData
    {
        Edge vertices;
        Weight weight;

        [[nodiscard]] bool operator==(const EdgeData& rhs) const noexcept;
        [[nodiscard]] bool operator!=(const EdgeData& rhs) const noexcept;
    };

    using EdgePredicate = std::function<void(const EdgeData&)>;

    using Graph::Graph;

    virtual bool AddEdge(const EdgeData& edge) = 0;
    virtual bool RemoveEdge(Edge edge) = 0;

    [[nodiscard]] virtual std::optional<Weight> GetWeight(Edge edge) const = 0;
    virtual bool SetWeight(Edge edge, Weight weight) = 0;

    [[nodiscard]] virtual bool DoesExist(Edge edge) const = 0;
    [[nodiscard]] float GetDensity() const noexcept override;
    [[nodiscard]] virtual DynamicArray<EdgeData> GetEdges() const = 0;

    virtual void ForEachEdge(EdgePredicate predicate) const = 0;

protected:
    void Serialize(std::ostream& os) const override;
    void Deserialize(std::istream& is) override;
};