#pragma once

#include "Algorithm/Graphs/Graph.h"

#include <optional>

class UndirectedGraph : public Graph
{
public:
    struct Edge
    {
        Vertex first;
        Vertex second;

        bool operator==(Edge rhs) const noexcept
        {
            return (first == rhs.first && second == rhs.second) || (first == rhs.second && second == rhs.first);
        }

        bool operator!=(Edge rhs) const noexcept
        {
            return !(*this == rhs);
        }
    };

    using EdgePredicate = std::function<void(Edge, Weight)>;

    using Graph::Graph;

    virtual bool AddEdge(Edge edge, Weight weight) = 0;
    virtual bool RemoveEdge(Edge edge) = 0;

    [[nodiscard]] virtual std::optional<Weight> GetWeight(Edge edge) const = 0;
    virtual bool SetWeight(Edge edge, Weight weight) = 0;

    [[nodiscard]] virtual bool doesExist(Edge edge) const = 0;

    virtual void ForEachEdge(EdgePredicate predicate) const = 0;
};