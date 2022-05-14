#pragma once

#include "Algorithms/Graphs/Graph.h"
#include "Utils/Pair.h"

#include <optional>

class DirectedGraph : public Graph
{
public:

    struct DirectedEdgeData;
    using DirectedEdge = Utils::Pair<Vertex, Vertex>;
    using DirectedEdgePredicate = std::function<void(const DirectedEdgeData&)>;

    struct DirectedEdgeData
    {
        DirectedEdge vertices;
        Weight weight;

        [[nodiscard]] bool operator==(const DirectedEdgeData& rhs) const noexcept;
        [[nodiscard]] bool operator!=(const DirectedEdgeData& rhs) const noexcept;
    };

    using Graph::Graph;

    virtual bool AddDirectedEdge(const DirectedEdgeData& edge) = 0;

    [[nodiscard]] virtual std::optional<Weight> GetWeight(DirectedEdge edge) const = 0;
    virtual bool SetWeight(DirectedEdge edge, Weight weight) = 0;

    [[nodiscard]] virtual bool DoesExist(DirectedEdge edge) const = 0;
    [[nodiscard]] float GetDensity() const noexcept override;
    [[nodiscard]] virtual DynamicArray<DirectedEdgeData> GetDirectedEdges() const = 0;

    virtual void ForEachDirectedEdge(DirectedEdgePredicate predicate) const = 0;
};