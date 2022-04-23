#include "Algorithms/Graphs/DirectedGraphs/DirectedListGraph.h"

Graph::Vertex DirectedListGraph::AddVertex()
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

bool DirectedListGraph::RemoveVertex(Vertex vertex)
{
    if (!DoesExist(vertex)) {
        return false;
    }

    auto iteratorToRemove = verticesMap[vertex];
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

bool DirectedListGraph::AddDirectedEdge(DirectedEdge directedEdge, Weight weight)
{
    if (!DoesExist(directedEdge.first) || !DoesExist(directedEdge.second))
    {
        return false;
    }

    if (DoesExist(directedEdge))
    {
        return false;
    }

    verticesMap[directedEdge.first]->PushBack({directedEdge.second, weight});

    size++;
    return true;
}

bool DirectedListGraph::RemoveDirectedEdge(DirectedEdge directedEdge)
{
    if (!DoesExist(directedEdge.first) || !DoesExist(directedEdge.second))
    {
        return false;
    }

    auto& DirectedEdges1 = *verticesMap[directedEdge.first];
    bool found = false;

    for (auto it = DirectedEdges1.begin(); it != DirectedEdges1.end(); it++)
    {
        if (it->vertex == directedEdge.second)
        {
            DirectedEdges1.RemoveAt(it);
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

uint64_t DirectedListGraph::GetSize() const noexcept
{
    return size;
}

bool DirectedListGraph::DoesExist(Vertex vertex) const
{
    return verticesMap.Find(vertex) != verticesMap.end();
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

DynamicArray<Graph::Vertex> DirectedListGraph::GetVertices() const
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

DynamicArray<Utils::Pair<DirectedGraph::DirectedEdge, Graph::Weight>> DirectedListGraph::GetDirectedEdges() const
{
    DynamicArray<Utils::Pair<DirectedEdge, Weight>> result;
    result.Resize(GetSize());

    uint64_t edgeCounter = 0;
    for (const auto& pair : verticesMap)
    {
        for (const auto& neighbour : *pair.second)
        {
            result[edgeCounter] = {{pair.first, neighbour.vertex}, neighbour.weight};
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

    const auto& neighbours = *verticesMap.at(vertex);

    for (const auto& neighbour : neighbours)
    {
        predicate(neighbour);
    }

    return true;
}

void DirectedListGraph::ForEachVertex(VertexPredicate predicate) const
{
    for (const auto& pair : verticesMap)
    {
        predicate(pair.first);
    }
}

void DirectedListGraph::ForEachDirectedEdge(DirectedEdgePredicate predicate) const
{
    for (const auto& pair : verticesMap)
    {
        for (const auto& neighbour : *pair.second)
        {
            predicate({pair.first, neighbour.vertex}, neighbour.weight);
        }
    }
}

DirectedListGraph::Neighbour* DirectedListGraph::GetNeighbourOfFirst(DirectedEdge DirectedEdge)
{
    if (!DoesExist(DirectedEdge.first) || !DoesExist(DirectedEdge.second))
    {
        return nullptr;
    }

    auto& neighbours = *verticesMap.at(DirectedEdge.first);

    for (auto& neighbour : neighbours)
    {
        if (neighbour.vertex == DirectedEdge.second)
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

    const auto& neighbours = *verticesMap.at(DirectedEdge.first);

    for (const auto& neighbour : neighbours)
    {
        if (neighbour.vertex == DirectedEdge.second)
        {
            return &neighbour;
        }
    }

    return nullptr;
}