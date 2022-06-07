#include "BellmanFord.h"

namespace ShortestPath::BellmanFord
{

constexpr uint64_t INFINITY_DISTANCE = UINT64_MAX;
constexpr Graph::Vertex NO_VERTEX = UINT32_MAX;

DynamicArray<Graph::Vertex> GetShortestPath(const DynamicArray<Graph::Vertex>& parents,
                                            Graph::Vertex from,
                                            Graph::Vertex to)
{
    DynamicArray<Graph::Vertex> path;
    while (from != to)
    {
        path.PushFront(to);
        to = parents[to];
    }
    path.PushFront(to);
    return path;
}

Result FindShortestPath(const DirectedGraph& graph, Graph::Vertex from, Graph::Vertex to)
{
    if (!graph.DoesExist(from) || !graph.DoesExist(to))
    {
        return {{}, 0};
    }
    Result result;

    DynamicArray<uint64_t> distances(graph.GetOrder());
    DynamicArray<Graph::Vertex> parents(graph.GetOrder());

    graph.ForEachVertex([&distances, &parents](Graph::Vertex vertex){
        distances[vertex] = INFINITY_DISTANCE;
        parents[vertex] = NO_VERTEX;
    });

    distances[from] = 0;

    for (uint32_t i = 0; i < graph.GetOrder() - 1; i++)
    {
        graph.ForEachDirectedEdge([&distances, &parents](const DirectedGraph::DirectedEdgeData& edge) {
            if (distances[edge.vertices.second] > Utils::SaturatingAdd<uint64_t>(distances[edge.vertices.first], edge.weight))
            {
                distances[edge.vertices.second] = Utils::SaturatingAdd<uint64_t>(distances[edge.vertices.first], edge.weight);
                parents[edge.vertices.second] = edge.vertices.first;
            }
        });
    }

    bool fail = false;

    graph.ForEachDirectedEdge([&distances, &fail](const DirectedGraph::DirectedEdgeData& edge) {
        if (distances[edge.vertices.second] > Utils::SaturatingAdd<uint64_t>(distances[edge.vertices.first], edge.weight))
        {
            fail = true;
        }
    });

    if (fail || distances[to] == INFINITY_DISTANCE)
    {
        return {{}, 0};
    }

    return {GetShortestPath(parents, from, to), distances[to]};
}

}
