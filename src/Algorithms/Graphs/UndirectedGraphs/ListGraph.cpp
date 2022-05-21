#include "Algorithms/Graphs/UndirectedGraphs/ListGraph.h"

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

bool ListGraph::RemoveEdge(UndirectedGraph::Edge edge)
{
    if (!DoesExist(edge.first) || !DoesExist(edge.second))
    {
        return false;
    }

    auto& DirectedEdges1 = graph[edge.first];
    bool found = false;

    for (auto it = DirectedEdges1.begin(); it != DirectedEdges1.end(); it++)
    {
        if (it->vertex == edge.second)
        {
            DirectedEdges1.RemoveAt(it);
            size--;
            found = true;
            break;
        }
    }

    auto& DirectedEdges2 = graph[edge.second];

    for (auto it = DirectedEdges1.begin(); it != DirectedEdges1.end(); it++)
    {
        if (it->vertex == edge.first)
        {
            DirectedEdges2.RemoveAt(it);
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

uint64_t ListGraph::GetSize() const noexcept
{
    return size;
}

uint32_t ListGraph::GetNumberOfNeighboursOf(Graph::Vertex vertex) const
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

    const auto& neighbours = graph[vertex];

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
    result.Resize(graph.Size());

    for (Vertex i = 0; i < GetOrder(); i++)
    {
        result[i] = i;
    }

    return result;
}

DynamicArray<UndirectedGraph::EdgeData> ListGraph::GetEdges() const
{
    DynamicArray<EdgeData> result;

    for (Vertex i = 0; i < GetOrder(); i++)
    {
        for (const auto& neighbour : graph[i])
        {
            Edge edge{i, neighbour.vertex};
            if (i > neighbour.vertex)
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

    for (Vertex i = 0; i < GetOrder(); i++)
    {
        for (const auto& neighbour : graph[i])
        {
            Edge edge{i, neighbour.vertex};
            if (i > neighbour.vertex)
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