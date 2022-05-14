#include "Algorithms/Graphs/DirectedGraphs/DirectedListGraph.h"

Graph::Vertex DirectedListGraph::AddVertex()
{
    if (GetOrder() == MAX_SIZE)
    {
        throw std::runtime_error("Max number of vertices has been reached!");
    }

    graph.PushBack(List<Neighbour>());

    Vertex newVertex = GetOrder() - 1;

    verticesMap.PushBack(--graph.end());

    return newVertex;
}

bool DirectedListGraph::AddDirectedEdge(const DirectedEdgeData& edge)
{
    if (!DoesExist(edge.vertices.first) || !DoesExist(edge.vertices.second))
    {
        return false;
    }

    if (DoesExist(edge.vertices))
    {
        return false;
    }

    verticesMap[edge.vertices.first]->PushBack({edge.vertices.second, edge.weight});

    size++;
    return true;
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

uint64_t DirectedListGraph::GetSize() const noexcept
{
    return size;
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

    const auto& neighbours = *verticesMap[vertex];

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

DynamicArray<Graph::Vertex> DirectedListGraph::GetVertices() const
{
    DynamicArray<Vertex> result;
    result.Resize(GetOrder());

    for (Vertex i = 0; i < GetOrder(); i++)
    {
        result[i] = i;
    }

    return result;
}

DynamicArray<DirectedGraph::DirectedEdgeData> DirectedListGraph::GetDirectedEdges() const
{
    DynamicArray<DirectedEdgeData> result;
    result.Resize(GetSize());

    uint64_t edgeCounter = 0;
    for (Vertex i = 0; i < GetOrder(); i++)
    {
        for (const auto& neighbour : *verticesMap[i])
        {
            result[edgeCounter] = {{i, neighbour.vertex}, neighbour.weight};
            edgeCounter++;
        }
    }

    return result;
}

bool DirectedListGraph::ForEachNeighbourOf(Vertex vertex, NeighbourPredicate predicate) const
{
    if (!DoesExist(vertex))
    {
        return false;
    }

    const auto& neighbours = *verticesMap[vertex];

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
    for (Vertex i = 0; i < GetOrder(); i++)
    {
        for (const auto& neighbour : *verticesMap[i])
        {
            predicate({{i, neighbour.vertex}, neighbour.weight});
        }
    }
}

DirectedListGraph::Neighbour* DirectedListGraph::GetNeighbourOfFirst(DirectedEdge directedEdge)
{
    if (!DoesExist(directedEdge.first) || !DoesExist(directedEdge.second))
    {
        return nullptr;
    }

    auto& neighbours = *verticesMap[directedEdge.first];

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

    const auto& neighbours = *verticesMap[DirectedEdge.first];

    for (const auto& neighbour : neighbours)
    {
        if (neighbour.vertex == DirectedEdge.second)
        {
            return &neighbour;
        }
    }

    return nullptr;
}