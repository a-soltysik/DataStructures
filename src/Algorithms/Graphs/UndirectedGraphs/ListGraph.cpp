#include "Algorithms/Graphs/UndirectedGraphs/ListGraph.h"

#include "Containers/UnorderedSet.h"

Graph::Vertex ListGraph::AddVertex()
{
    if (GetOrder() == MAX_SIZE)
    {
        throw std::runtime_error("Max number of vertices has been reached!");
    }

    graph.PushBack(List<Neighbour>());

    Vertex newVertex;

    if (GetOrder() == 1)
    {
        newVertex = 0;
    }
    else
    {
        newVertex = verticesMap.Max().first + 1;
    }

    verticesMap[newVertex] = --graph.end();

    return newVertex;
}

bool ListGraph::RemoveVertex(Vertex vertex)
{
    if (!DoesExist(vertex)) {
        return false;
    }

    auto iteratorToRemove = verticesMap.at(vertex);
    auto graphIt = graph.begin();

    for (auto& neighbours : graph)
    {
        if (iteratorToRemove == graphIt)
        {
            continue;
        }

        for (auto it = neighbours.begin(); it != neighbours.end(); it++)
        {
            if (it->vertex == vertex)
            {
                neighbours.RemoveAt(it);
                break;
            }
        }
        graphIt++;
    }

    graph.RemoveAt(graphIt);
    verticesMap.Remove(vertex);

    return true;
}

bool ListGraph::AddEdge(const EdgeData& edge)
{
    if (!DoesExist(edge.vertices.first) || !DoesExist(edge.vertices.second))
    {
        return false;
    }

    if (DoesExist(edge.vertices))
    {
        return false;
    }

    verticesMap.at(edge.vertices.first)->PushBack({edge.vertices.second, edge.weight});
    verticesMap.at(edge.vertices.second)->PushBack({edge.vertices.first, edge.weight});

    size++;
    return true;
}

bool ListGraph::RemoveEdge(Edge edge)
{
    if (!DoesExist(edge.first) || !DoesExist(edge.second))
    {
        return false;
    }

    auto& edges1 = *verticesMap.at(edge.first);
    bool found = false;

    for (auto it = edges1.begin(); it != edges1.end(); it++)
    {
        if (it->vertex == edge.second)
        {
            edges1.RemoveAt(it);
            size--;
            found = true;
            break;
        }
    }

    if (!found)
    {
        return false;
    }

    auto& edges2 = *verticesMap.at(edge.second);

    for (auto it = edges2.begin(); it != edges2.end(); it++)
    {
        if (it->vertex == edge.first)
        {
            edges2.RemoveAt(it);
            break;
        }
    }

    return true;
}

std::optional<Graph::Weight> ListGraph::GetWeight(Edge edge) const
{
    const auto* neighbour = GetNeighbourOfFirst(edge);

    if (neighbour != nullptr)
    {
        return neighbour->weight;
    }

    return {};
}

bool ListGraph::SetWeight(Edge edge, Weight weight)
{
    auto* neighbour = GetNeighbourOfFirst({edge.first, edge.second});

    if (neighbour == nullptr)
    {
        return false;
    }

    neighbour->weight = weight;

    neighbour = GetNeighbourOfFirst({edge.second, edge.first});

    if (neighbour != nullptr)
    {
        neighbour->weight = weight;
    }

    return true;
}

uint32_t ListGraph::GetOrder() const noexcept
{
    return static_cast<uint32_t>(graph.Size());
}

uint64_t ListGraph::GetSize() const noexcept
{
    return size;
}

bool ListGraph::DoesExist(Vertex vertex) const
{
    return verticesMap.Find(vertex) != verticesMap.end();
}

bool ListGraph::DoesExist(UndirectedGraph::Edge edge) const
{
    bool foundFirst = (GetNeighbourOfFirst({edge.first, edge.second}) != nullptr);
    bool foundSecond = (GetNeighbourOfFirst({edge.second, edge.first}) != nullptr);

    return foundFirst && foundSecond;
}

std::optional<DynamicArray<Graph::Neighbour>> ListGraph::GetNeighboursOf(Vertex vertex) const
{
    if (!DoesExist(vertex))
    {
        return {};
    }

    const auto& neighbours = *verticesMap.at(vertex);

    DynamicArray<Neighbour> neighboursVertices;
    neighboursVertices.Resize(neighbours.Size());

    uint32_t i = 0;
    for (const auto& neighbour : neighbours)
    {
        neighboursVertices[i] = neighbour;
        i++;
    }

    return neighboursVertices;
}

DynamicArray<Graph::Vertex> ListGraph::GetVertices() const
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

DynamicArray<UndirectedGraph::EdgeData> ListGraph::GetEdges() const
{
    DynamicArray<EdgeData> result;
    UnorderedSet<Edge> edges;

    for (const auto& pair : verticesMap)
    {
        for (const auto& neighbour : *pair.second)
        {
            Edge edge{pair.first, neighbour.vertex};
            if (edges.Insert(edge) != edges.end())
            {
                result.PushBack({edge, neighbour.weight});
            }
        }
    }

    return result;
}

bool ListGraph::ForEachNeighbourOf(Vertex vertex, NeighbourPredicate predicate) const
{
    if (!DoesExist(vertex))
    {
        return false;
    }

    const auto& neighbours = *verticesMap.at(vertex);

    for (const auto& neighbour : neighbours)
    {
        predicate(neighbour);
    }

    return true;
}

void ListGraph::ForEachVertex(Graph::VertexPredicate predicate) const
{
    for (const auto& pair : verticesMap)
    {
        predicate(pair.first);
    }
}

void ListGraph::ForEachEdge(EdgePredicate predicate) const
{
    UnorderedSet<Edge> edges;

    for (const auto& pair : verticesMap)
    {
        for (const auto& neighbour : *pair.second)
        {
            Edge edge{pair.first, neighbour.vertex};
            if (edges.Insert(edge) != edges.end())
            {
                predicate({edge, neighbour.weight});
            }
        }
    }
}

ListGraph::Neighbour* ListGraph::GetNeighbourOfFirst(Edge edge)
{
    if (!DoesExist(edge.first) || !DoesExist(edge.second))
    {
        return nullptr;
    }

    auto& neighbours = *verticesMap.at(edge.first);

    for (auto& neighbour : neighbours)
    {
        if (neighbour.vertex == edge.second)
        {
            return &neighbour;
        }
    }

    return nullptr;
}

const ListGraph::Neighbour* ListGraph::GetNeighbourOfFirst(Edge edge) const
{
    if (!DoesExist(edge.first) || !DoesExist(edge.second))
    {
        return nullptr;
    }

    const auto& neighbours = *verticesMap.at(edge.first);

    for (const auto& neighbour : neighbours)
    {
        if (neighbour.vertex == edge.second)
        {
            return &neighbour;
        }
    }

    return nullptr;
}