#include "Prim.h"

namespace MST::Prim
{

constexpr uint32_t INFINITY_PRIORITY = UINT32_MAX;
constexpr Graph::Vertex NO_VERTEX = UINT32_MAX;

Graph::Vertex GetMinimalVertex(const DynamicArray<uint32_t>& priorities, const DynamicArray<bool>& usedFlags)
{
    Graph::Vertex minimalVertex = NO_VERTEX;
    uint32_t minimalPriority = INFINITY_PRIORITY;
    for (Graph::Vertex i = 0; i < priorities.Size(); i++)
    {
        if (usedFlags[i] == false && priorities[i] <= minimalPriority)
        {
            minimalPriority = priorities[i];
            minimalVertex = i;
        }
    }

    return minimalVertex;
}

Result GetMst(const UndirectedGraph& graph, const DynamicArray<Graph::Vertex>& parents)
{
    Result result;
    result.weight = 0;
    result.edges.Resize(graph.GetOrder() - 1);
    for (Graph::Vertex i = 1; i < graph.GetOrder(); i++)
    {
        if (parents[i] == NO_VERTEX)
        {
            return {{}, 0};
        }
        UndirectedGraph::Edge edge = {parents[i], i};
        Graph::Weight weight = graph.GetWeight(edge).value();
        result.edges[i - 1] = {edge, weight};
        result.weight += weight;
    }
    return result;
}

Result FindMstOf(const UndirectedGraph& graph)
{
    if (graph.GetSize() < 1)
    {
        return {{}, 0};
    }

    DynamicArray<uint32_t> priorities(graph.GetOrder());
    DynamicArray<Graph::Vertex> parents(graph.GetOrder());
    DynamicArray<bool> usedFlags(graph.GetOrder(), false);

    graph.ForEachVertex([&priorities, &parents](Graph::Vertex vertex){
       priorities[vertex] = INFINITY_PRIORITY;
       parents[vertex] = NO_VERTEX;
    });

    priorities[0] = 0;

    for (uint32_t i = 0; i < graph.GetOrder() - 1; i++)
    {
        auto vertex = GetMinimalVertex(priorities, usedFlags);
        if (priorities[vertex] == INFINITY_PRIORITY)
        {
            return {{}, 0};
        }
        usedFlags[vertex] = true;

        graph.ForEachNeighbourOf(vertex, [&usedFlags, &priorities, &parents, vertex](Graph::Neighbour neighbour) {
            if (usedFlags[neighbour.vertex] == false && neighbour.weight < priorities[neighbour.vertex])
            {
                parents[neighbour.vertex] = vertex;
                priorities[neighbour.vertex] = neighbour.weight;
            }
        });
    }

    return GetMst(graph, parents);
}

}
