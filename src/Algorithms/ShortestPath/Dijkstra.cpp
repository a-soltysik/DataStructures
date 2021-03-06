#include "Dijkstra.h"

namespace ShortestPath::Dijkstra
{

constexpr uint64_t INFINITY_DISTANCE = UINT64_MAX;
constexpr Graph::Vertex NO_VERTEX = UINT32_MAX;

Graph::Vertex GetMinimalVertex(const DynamicArray<uint64_t>& distances, const DynamicArray<bool>& usedFlags)
{
    Graph::Vertex minimalVertex = NO_VERTEX;
    uint64_t minimalDistance = INFINITY_DISTANCE;
    for (Graph::Vertex i = 0; i < distances.Size(); i++)
    {
        if (usedFlags[i] == false && distances[i] <= minimalDistance)
        {
            minimalDistance = distances[i];
            minimalVertex = i;
        }
    }

    return minimalVertex;
}

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
    DynamicArray<bool> usedFlags(graph.GetOrder(), false);

    graph.ForEachVertex([&distances, &parents](Graph::Vertex vertex){
        distances[vertex] = INFINITY_DISTANCE;
        parents[vertex] = NO_VERTEX;
    });

    distances[from] = 0;

    for (uint32_t i = 0; i < graph.GetOrder(); i++)
    {
        auto vertex = GetMinimalVertex(distances, usedFlags);
        if (distances[vertex] == INFINITY_DISTANCE)
        {
            break;
        }
        usedFlags[vertex] = true;

        graph.ForEachNeighbourOf(vertex, [&distances, &parents, vertex](Graph::Neighbour neighbour) {
            if (distances[neighbour.vertex] > Utils::SaturatingAdd<uint64_t>(distances[vertex], neighbour.weight))
            {
                distances[neighbour.vertex] = Utils::SaturatingAdd<uint64_t>(distances[vertex], neighbour.weight);
                parents[neighbour.vertex] = vertex;
            }
        });
    }

    if (distances[to] == INFINITY_DISTANCE)
    {
        return {{}, 0};
    }

    return {GetShortestPath(parents, from, to), distances[to]};
}

}
