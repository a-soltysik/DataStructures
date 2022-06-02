#include "ListGraph.h"

ListGraph& ListGraph::operator=(const UndirectedGraph& rhs)
{
    Clear();
    for (uint32_t i = 0; i < rhs.GetOrder(); i++)
    {
        AddVertex();
    }

    rhs.ForEachEdge([this](const EdgeData& edge) {
        AddEdge(edge);
    });
    return *this;
}

ListGraph& ListGraph::operator=(UndirectedGraph&& rhs)
{
    Clear();
    for (uint32_t i = 0; i < rhs.GetOrder(); i++)
    {
        AddVertex();
    }

    rhs.ForEachEdge([this](const EdgeData& edge) {
        AddEdge(edge);
    });
    return *this;
}

Graph::Vertex ListGraph::AddVertex()
{
    if (GetOrder() == MAX_SIZE)
    {
        throw std::runtime_error("Max number of vertices has been reached!");
    }

    graph.PushBack(List<Neighbour>());

    Vertex newVertex = GetOrder() - 1;

    return newVertex;
}

void ListGraph::Clear()
{
    graph.Clear();
    size = 0;
}

bool ListGraph::AddEdge(const EdgeData& edge)
{
    if (edge.vertices.first == edge.vertices.second)
    {
        return false;
    }

    if (!DoesExist(edge.vertices.first) || !DoesExist(edge.vertices.second))
    {
        return false;
    }

    if (DoesExist(edge.vertices))
    {
        return false;
    }

    graph[edge.vertices.first].PushBack({edge.vertices.second, edge.weight});
    graph[edge.vertices.second].PushBack({edge.vertices.first, edge.weight});

    size++;
    return true;
}

bool ListGraph::RemoveEdge(Edge edge)
{
    if (!DoesExist(edge.first) || !DoesExist(edge.second))
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

uint32_t ListGraph::GetOrder() const noexcept
{
    return static_cast<uint32_t>(graph.Size());
}

size_t ListGraph::GetSize() const noexcept
{
    return size;
}

uint32_t ListGraph::GetNumberOfNeighboursOf(Vertex vertex) const
{
    if (!DoesExist(vertex))
    {
        return 0;
    }

    return static_cast<uint32_t>(graph[vertex].Size());
}

bool ListGraph::DoesExist(Vertex vertex) const
{
    return vertex < GetOrder();
}

bool ListGraph::DoesExist(Edge edge) const
{
    return GetNeighbourOfFirst({edge.first, edge.second}) != nullptr;
}

std::optional<DynamicArray<Graph::Neighbour>> ListGraph::GetNeighboursOf(Vertex vertex) const
{
    if (!DoesExist(vertex))
    {
        return {};
    }

    const auto& neighbours = graph[vertex];

    DynamicArray<Neighbour> neighboursVertices(neighbours.Size());

    uint32_t i = 0;
    for (const auto& neighbour : neighbours)
    {
        neighboursVertices[i++] = neighbour;
    }

    return neighboursVertices;
}

DynamicArray<Graph::Vertex> ListGraph::GetVertices() const
{
    DynamicArray<Vertex> result(GetOrder());

    for (Vertex i = 0; i < GetOrder(); i++)
    {
        result[i] = i;
    }

    return result;
}

DynamicArray<UndirectedGraph::EdgeData> ListGraph::GetEdges() const
{
    DynamicArray<EdgeData> result(GetSize());

    uint32_t i = 0;
    size_t edgeCounter = 0;
    for (const auto& neighbours : graph)
    {
        for (const auto& neighbour : neighbours)
        {
            Edge edge{i, neighbour.vertex};
            if (i > neighbour.vertex)
            {
                result[edgeCounter++] = {edge, neighbour.weight};
            }
        }
        i++;
    }

    return result;
}

bool ListGraph::ForEachNeighbourOf(Vertex vertex, NeighbourPredicate predicate) const
{
    if (!DoesExist(vertex))
    {
        return false;
    }

    const auto& neighbours = graph[vertex];

    for (const auto& neighbour : neighbours)
    {
        predicate(neighbour);
    }

    return true;
}

void ListGraph::ForEachVertex(Graph::VertexPredicate predicate) const
{
    for (Vertex i = 0; i < GetOrder(); i++)
    {
        predicate(i);
    }
}

void ListGraph::ForEachEdge(EdgePredicate predicate) const
{
    uint32_t i = 0;
    for (const auto& neighbours : graph)
    {
        for (const auto& neighbour : neighbours)
        {
            Edge edge{i, neighbour.vertex};
            if (i > neighbour.vertex)
            {
                predicate({edge, neighbour.weight});
            }
        }
        i++;
    }
}

ListGraph::Neighbour* ListGraph::GetNeighbourOfFirst(Edge edge)
{
    if (!DoesExist(edge.first) || !DoesExist(edge.second))
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
    if (!DoesExist(edge.first) || !DoesExist(edge.second))
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

std::string ListGraph::ToString() const
{
    std::string result = "\n";
    Graph::Vertex vertex = 0;
    for (const auto& list : graph)
    {
        result += "[" + Utils::Parser::NumberToString(vertex) + "] -> ";
        Graph::Vertex neighbourNumber = 0;
        for (const auto& neighbour : list)
        {
            result += "[" + Utils::Parser::NumberToString(neighbour.vertex) + ": " +
                      Utils::Parser::NumberToString(neighbour.weight) + "]";
            neighbourNumber++;
            if (neighbourNumber != list.Size())
            {
                result += "->";
            }
        }
        vertex++;
        if (vertex != GetOrder())
        {
            result += "\n";
        }
    }
    return result;
}