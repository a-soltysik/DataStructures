#pragma once

#include "Algorithms/Graphs/Graph.h"
#include "Utils/Pair.h"

class DirectedGraph : public Graph
{
public:
    template<typename T>
    using isDirectedGraph = std::enable_if_t<Utils::DerivedFrom<T, DirectedGraph>::Value, bool>;

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

    virtual bool AddDirectedEdge(const DirectedEdgeData& edge) = 0;
    virtual bool RemoveDirectedEdge(DirectedEdge edge) = 0;

    [[nodiscard]] virtual std::optional<Weight> GetWeight(DirectedEdge edge) const = 0;
    virtual bool SetWeight(DirectedEdge edge, Weight weight) = 0;

    [[nodiscard]] virtual bool DoesExist(DirectedEdge edge) const = 0;
    [[nodiscard]] float GetDensity() const noexcept override;
    [[nodiscard]] virtual DynamicArray<DirectedEdgeData> GetDirectedEdges() const = 0;

    virtual void ForEachDirectedEdge(DirectedEdgePredicate predicate) const = 0;

protected:
    void Serialize(std::ostream& os) const override;
    void Deserialize(std::istream& is) override;
};