#include "Algorithm/Graphs/UndirectedGraphs/ListGraph.h"

#include "Containers/UnorderedSet.h"

Graph::Vertex ListGraph::AddVertex()
{
    if (GetOrder() == MAX_SIZE)
    {
        throw std::runtime_error("Max number of vertices has been reached!");
    }

    graph.PushBack(List<Neighbour>());

    return GetOrder() - 1;
}

bool ListGraph::RemoveVertex(Vertex vertex)
{
    if (!doesExist(vertex)) {
        return false;
    }

    Vertex vertexCounter = 0;
    for (auto& vertices : graph)
    {
        if (vertexCounter == vertex)
        {
            continue;
        }

        for (auto it = vertices.begin(); it != vertices.end(); it++)
        {
            if (it->vertex == vertex)
            {
                vertices.RemoveAt(it);
                break;
            }
        }
    }

    graph.RemoveAt(vertex);
    return true;
}

bool ListGraph::AddEdge(Edge edge, Weight weight)
{
    if (!doesExist(edge.first) || !doesExist(edge.second))
    {
        return false;
    }

    if (doesExist(edge))
    {
        return false;
    }

    graph[edge.first].PushBack({edge.second, weight});
    graph[edge.second].PushBack({edge.first, weight});

    size++;
    return true;
}

bool ListGraph::RemoveEdge(Edge edge)
{
    if (!doesExist(edge.first) || !doesExist(edge.second))
    {
        return false;
    }

    auto& edges1 = graph[edge.first];
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

    auto& edges2 = graph[edge.second];

    for (auto it = edges2.begin(); it != edges2.end(); it++)
    {
        if (it->vertex == edge.first)
        {
            edges2.RemoveAt(it);
            size--;
            found = true;
            break;
        }
    }

    return found;
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

uint32_t ListGraph::GetOrder() const
{
    return static_cast<uint32_t>(graph.Size());
}

uint64_t ListGraph::GetSize() const
{
    return size;
}

bool ListGraph::ForEachNeighbour(Vertex source, VertexPredicate predicate) const
{
    if (!doesExist(source))
    {
        return false;
    }

    const auto& neighbours = graph[source];

    for (const auto& neighbour : neighbours)
    {
        predicate(neighbour.vertex);
    }

    return true;
}

void ListGraph::ForEachVertex(Graph::VertexPredicate predicate) const
{
    for (Vertex vertex = 0; vertex < GetOrder(); vertex++)
    {
        predicate(vertex);
    }
}

void ListGraph::ForEachEdge(EdgePredicate predicate) const
{
    UnorderedSet<Edge> edges;
    Vertex vertexCounter = 0;
    for (const auto& vertex : graph)
    {
        for (const auto& neighbour : vertex)
        {
            Edge edge{vertexCounter, neighbour.vertex};
            if (edges.Insert(edge) != edges.end())
            {
                predicate(edge, neighbour.weight);
            }
        }
        vertexCounter++;
    }
}

bool ListGraph::doesExist(Graph::Vertex vertex) const
{
    return vertex < GetOrder();
}

bool ListGraph::doesExist(UndirectedGraph::Edge edge) const
{
    bool foundFirst = (GetNeighbourOfFirst({edge.first, edge.second}) != nullptr);
    bool foundSecond = (GetNeighbourOfFirst({edge.second, edge.first}) != nullptr);

    return foundFirst && foundSecond;
}

ListGraph::Neighbour* ListGraph::GetNeighbourOfFirst(Edge edge)
{
    if (!doesExist(edge.first) || !doesExist(edge.second))
    {
        return nullptr;
    }

    auto& neighbours = graph[edge.first];

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
    if (!doesExist(edge.first) || !doesExist(edge.second))
    {
        return nullptr;
    }

    const auto& neighbours = graph[edge.first];

    for (const auto& neighbour : neighbours)
    {
        if (neighbour.vertex == edge.second)
        {
            return &neighbour;
        }
    }

    return nullptr;
}
