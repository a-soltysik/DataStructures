#include "Algorithms/Graphs/DirectedGraphs/DirectedMatrixGraph.h"

Graph::Vertex DirectedMatrixGraph::AddVertex()
{
    if (GetOrder() == MAX_SIZE)
    {
        throw std::runtime_error("Max number of vertices has been reached!");
    }

    for (auto& row : graph)
    {
        row.PushBack(Graph::INFINITY);
    }

    Vertex newVertex;

    if (GetOrder() == 1)
    {
        newVertex = 0;
    }
    else
    {
        newVertex = verticesMap.Max().first + 1;
    }

    graph.PushBack(DynamicArray<Weight>(GetOrder() + 1, Graph::INFINITY));
    verticesMap[newVertex] = GetOrder() - 1;

    return newVertex;
}

bool DirectedMatrixGraph::RemoveVertex(Vertex vertex)
{
    if (!DoesExist(vertex)) {
        return false;
    }

    for (auto& row : graph)
    {
        row.RemoveAt(verticesMap.at(vertex));
    }

    graph.RemoveAt(verticesMap.at(vertex));
    RestoreIndicesFrom(vertex);

    return true;
}

bool DirectedMatrixGraph::AddDirectedEdge(const DirectedEdgeData& edge)
{
    if (!DoesExist(edge.vertices.first) || !DoesExist(edge.vertices.second))
    {
        return false;
    }

    if (DoesExist(edge.vertices))
    {
        return false;
    }

    graph[verticesMap.at(edge.vertices.first)][verticesMap.at(edge.vertices.second)] = edge.weight;

    size++;

    return true;
}

bool DirectedMatrixGraph::RemoveDirectedEdge(DirectedEdge directedEdge)
{
    if (!DoesExist(directedEdge))
    {
        return false;
    }

    graph[verticesMap.at(directedEdge.first)][verticesMap.at(directedEdge.second)] = Graph::INFINITY;

    size--;

    return true;
}

std::optional<Graph::Weight> DirectedMatrixGraph::GetWeight(DirectedEdge directedEdge) const
{
    if (!DoesExist(directedEdge))
    {
        return {};
    }
    return graph[verticesMap.at(directedEdge.first)][verticesMap.at(directedEdge.second)];
}

bool DirectedMatrixGraph::SetWeight(DirectedEdge directedEdge, Weight weight)
{
    if (!DoesExist(directedEdge))
    {
        return false;
    }

    graph[verticesMap.at(directedEdge.first)][verticesMap.at(directedEdge.second)] = weight;

    return true;
}

uint32_t DirectedMatrixGraph::GetOrder() const noexcept
{
    return static_cast<uint32_t>(graph.Size());
}

uint64_t DirectedMatrixGraph::GetSize() const noexcept
{
    return size;
}

bool DirectedMatrixGraph::DoesExist(Vertex vertex) const
{
    return verticesMap.Find(vertex) != verticesMap.end();
}

bool DirectedMatrixGraph::DoesExist(DirectedEdge directedEdge) const
{
    if (!DoesExist(directedEdge.first) || !DoesExist(directedEdge.second))
    {
        return false;
    }
    return graph[verticesMap.at(directedEdge.first)][verticesMap.at(directedEdge.second)] != Graph::INFINITY;
}

std::optional<DynamicArray<Graph::Neighbour>> DirectedMatrixGraph::GetNeighboursOf(Vertex vertex) const
{
    if (!DoesExist(vertex))
    {
        return {};
    }

    DynamicArray<Neighbour> result;
    uint32_t sourceIndex = verticesMap.at(vertex);

    for (const auto& pair : verticesMap)
    {
        if (graph[sourceIndex][pair.second] != Graph::INFINITY)
        {
            result.PushBack({pair.first, graph[sourceIndex][pair.second]});
        }
    }

    return result;
}


DynamicArray<Graph::Vertex> DirectedMatrixGraph::GetVertices() const
{
    DynamicArray<Vertex> result;
    result.Resize(verticesMap.Size());

    size_t i = 0;
    for (const auto& pair : verticesMap)
    {
        result[i] = pair.first;
        i++;
    }

    return result;
}


DynamicArray<DirectedGraph::DirectedEdgeData> DirectedMatrixGraph::GetDirectedEdges() const
{
    DynamicArray<DirectedEdgeData> result;
    result.Resize(GetSize());

    uint64_t DirectedEdgeCounter = 0;
    for (const auto& pair1 : verticesMap)
    {
        for (const auto& pair2 : verticesMap)
        {
            if (graph[pair1.second][pair2.second] != Graph::INFINITY)
            {
                result[DirectedEdgeCounter] = {{pair1.first, pair2.first}, graph[pair1.second][pair2.second]};
                DirectedEdgeCounter++;
            }
        }
    }

    return result;
}


bool DirectedMatrixGraph::ForEachNeighbourOf(Vertex vertex, NeighbourPredicate predicate) const
{
    if (!DoesExist(vertex))
    {
        return false;
    }

    uint32_t sourceIndex = verticesMap.at(vertex);

    for (const auto& pair : verticesMap)
    {
        if (graph[sourceIndex][pair.second] != Graph::INFINITY)
        {
            predicate({pair.first, graph[sourceIndex][pair.second]});
        }
    }

    return true;
}

void DirectedMatrixGraph::ForEachVertex(VertexPredicate predicate) const
{
    for (const auto& pair : verticesMap)
    {
        predicate(pair.first);
    }
}

void DirectedMatrixGraph::ForEachDirectedEdge(DirectedEdgePredicate predicate) const
{
    for (const auto& pair1 : verticesMap)
    {
        for (const auto& pair2 : verticesMap)
        {
            if (graph[pair1.second][pair2.second] != Graph::INFINITY)
            {
                predicate({{pair1.first, pair2.first}, graph[pair1.second][pair2.second]});
            }
        }
    }
}

void DirectedMatrixGraph::RestoreIndicesFrom(Vertex from)
{
    bool start = false;

    for (auto& pair : verticesMap)
    {
        if (start)
        {
            pair.second--;
        }
        if (pair.first == from)
        {
            start = true;
        }
    }

    verticesMap.Remove(from);
}