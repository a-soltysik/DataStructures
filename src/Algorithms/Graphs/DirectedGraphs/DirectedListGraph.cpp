#include "DirectedListGraph.h"

DirectedListGraph& DirectedListGraph::operator=(const DirectedGraph& rhs)
{
    Clear();
    for (uint32_t i = 0; i < rhs.GetOrder(); i++)
    {
        AddVertex();
    }

    rhs.ForEachDirectedEdge([this](const DirectedEdgeData& edge) {
        AddDirectedEdge(edge);
    });
    return *this;
}

DirectedListGraph& DirectedListGraph::operator=(DirectedGraph&& rhs)
{
    Clear();
    for (uint32_t i = 0; i < rhs.GetOrder(); i++)
    {
        AddVertex();
    }

    rhs.ForEachDirectedEdge([this](const DirectedEdgeData& edge) {
        AddDirectedEdge(edge);
    });
    return *this;
}

Graph::Vertex DirectedListGraph::AddVertex()
{
    if (GetOrder() == MAX_SIZE)
    {
        throw std::runtime_error("Max number of vertices has been reached!");
    }

    graph.PushBack(List<Neighbour>());

    Vertex newVertex = GetOrder() - 1;

    return newVertex;
}

void DirectedListGraph::Clear()
{
    graph.Clear();
    size = 0;
}

bool DirectedListGraph::AddDirectedEdge(const DirectedEdgeData& edge)
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

    size++;
    return true;
}

bool DirectedListGraph::RemoveDirectedEdge(DirectedEdge directedEdge)
{
    if (!DoesExist(directedEdge.first) || !DoesExist(directedEdge.second))
    {
        return false;
    }

    auto& edges = graph[directedEdge.first];
    bool found = false;

    for (auto it = edges.begin(); it != edges.end(); it++)
    {
        if (it->vertex == directedEdge.second)
        {
            edges.RemoveAt(it);
            size--;
            found = true;
            break;
        }
    }

    return found;
}

std::optional<Graph::Weight> DirectedListGraph::GetWeight(DirectedEdge directedEdge) const
{
    const auto* neighbour = GetNeighbourOfFirst(directedEdge);

    if (neighbour != nullptr)
    {
        return neighbour->weight;
    }

    return {};
}

bool DirectedListGraph::SetWeight(DirectedEdge directedEdge, Weight weight)
{
    auto* neighbour = GetNeighbourOfFirst({directedEdge.first, directedEdge.second});

    if (neighbour == nullptr)
    {
        return false;
    }

    neighbour->weight = weight;

    return true;
}

uint32_t DirectedListGraph::GetOrder() const noexcept
{
    return static_cast<uint32_t>(graph.Size());
}

size_t DirectedListGraph::GetSize() const noexcept
{
    return size;
}

uint32_t DirectedListGraph::GetNumberOfNeighboursOf(Graph::Vertex vertex) const
{
    if (!DoesExist(vertex))
    {
        return 0;
    }

    return static_cast<uint32_t>(graph[vertex].Size());
}

bool DirectedListGraph::DoesExist(Vertex vertex) const
{
    return vertex < GetOrder();
}

bool DirectedListGraph::DoesExist(DirectedEdge directedEdge) const
{
    return  GetNeighbourOfFirst(directedEdge) != nullptr;
}

std::optional<DynamicArray<Graph::Neighbour>> DirectedListGraph::GetNeighboursOf(Vertex vertex) const
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

DynamicArray<Graph::Vertex> DirectedListGraph::GetVertices() const
{
    DynamicArray<Vertex> result(GetOrder());

    for (Vertex i = 0; i < GetOrder(); i++)
    {
        result[i] = i;
    }

    return result;
}

DynamicArray<DirectedGraph::DirectedEdgeData> DirectedListGraph::GetDirectedEdges() const
{
    DynamicArray<DirectedEdgeData> result(GetSize());

    uint32_t i = 0;
    size_t edgeCounter = 0;
    for (const auto& neighbours : graph)
    {
        for (const auto& neighbour : neighbours)
        {
            result[edgeCounter++] = {{i, neighbour.vertex}, neighbour.weight};
        }
        i++;
    }

    return result;
}

bool DirectedListGraph::ForEachNeighbourOf(Vertex vertex, NeighbourPredicate predicate) const
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

void DirectedListGraph::ForEachVertex(VertexPredicate predicate) const
{
    for (Vertex i = 0; i < GetOrder(); i++)
    {
        predicate(i);
    }
}

void DirectedListGraph::ForEachDirectedEdge(DirectedEdgePredicate predicate) const
{
    uint32_t i = 0;
    for (const auto& neighbours : graph)
    {
        for (const auto& neighbour : neighbours)
        {
            DirectedEdge edge = {i, neighbour.vertex};
            predicate({edge, neighbour.weight});
        }
        i++;
    }
}

DirectedListGraph::Neighbour* DirectedListGraph::GetNeighbourOfFirst(DirectedEdge directedEdge)
{
    if (!DoesExist(directedEdge.first) || !DoesExist(directedEdge.second))
    {
        return nullptr;
    }

    auto& neighbours = graph[directedEdge.first];

    for (auto& neighbour : neighbours)
    {
        if (neighbour.vertex == directedEdge.second)
        {
            return &neighbour;
        }
    }

    return nullptr;
}

const DirectedListGraph::Neighbour* DirectedListGraph::GetNeighbourOfFirst(DirectedEdge DirectedEdge) const
{
    if (!DoesExist(DirectedEdge.first) || !DoesExist(DirectedEdge.second))
    {
        return nullptr;
    }

    const auto& neighbours = graph[DirectedEdge.first];

    for (const auto& neighbour : neighbours)
    {
        if (neighbour.vertex == DirectedEdge.second)
        {
            return &neighbour;
        }
    }

    return nullptr;
}

std::string DirectedListGraph::ToString() const
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