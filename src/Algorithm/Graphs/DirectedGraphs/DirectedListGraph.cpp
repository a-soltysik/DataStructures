#include "Algorithm/Graphs/DirectedGraphs/DirectedListGraph.h"

#include "Containers/UnorderedSet.h"

Graph::Vertex DirectedListGraph::AddVertex()
{
    if (GetOrder() == MAX_SIZE)
    {
        throw std::runtime_error("Max number of vertices has been reached!");
    }

    graph.PushBack(List<Neighbour>());

    return GetOrder() - 1;
}

bool DirectedListGraph::RemoveVertex(Vertex vertex)
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

bool DirectedListGraph::AddDirectedEdge(DirectedEdge edge, Weight weight)
{
    if (!FindDirectedEdge(edge))
    {
        return false;
    }

    graph[edge.first].PushBack({edge.second, weight});

    size++;
    return true;
}

bool DirectedListGraph::RemoveDirectedEdge(DirectedEdge edge)
{
    if (!doesExist(edge.first) || !doesExist(edge.second))
    {
        return false;
    }

    auto& edges = graph[edge.first];
    bool found = false;

    for (auto it = edges.begin(); it != edges.end(); it++)
    {
        if (it->vertex == edge.second)
        {
            edges.RemoveAt(it);
            size--;
            found = true;
            break;
        }
    }
    return found;
}

std::optional<Graph::Weight> DirectedListGraph::GetWeight(DirectedEdge edge) const
{
    const auto* neighbour = GetNeighbourOfFirst(edge);

    if (neighbour != nullptr)
    {
        return neighbour->weight;
    }

    return {};
}

bool DirectedListGraph::SetWeight(DirectedEdge edge, Weight weight)
{
    auto* neighbour = GetNeighbourOfFirst(edge);

    if (neighbour == nullptr)
    {
        return false;
    }

    neighbour->weight = weight;

    return true;
}

uint32_t DirectedListGraph::GetOrder() const
{
    return static_cast<uint32_t>(graph.Size());
}

uint64_t DirectedListGraph::GetSize() const
{
    return size;
}

bool DirectedListGraph::ForEachNeighbour(Vertex source, VertexPredicate predicate)
{
    if (!doesExist(source))
    {
        return false;
    }

    auto& neighbours = graph[source];

    for (auto& neighbour : neighbours)
    {
        predicate(neighbour.vertex);
    }

    return true;
}

bool DirectedListGraph::ForEachVertex(Graph::VertexPredicate predicate)
{
    for (Vertex vertex = 0; vertex < GetOrder(); vertex++)
    {
        predicate(vertex);
    }

    return true;
}

bool DirectedListGraph::ForEachDirectedEdge(DirectedEdgePredicate predicate)
{
    Vertex vertexCounter = 0;
    for (auto& vertex : graph)
    {
        for (auto& neighbour : vertex)
        {
            predicate({vertexCounter, neighbour.vertex}, neighbour.weight);
        }
        vertexCounter++;
    }
    return true;
}

bool DirectedListGraph::doesExist(Graph::Vertex vertex) const
{
    return vertex < GetOrder();
}

bool DirectedListGraph::FindDirectedEdge(DirectedEdge edge) const
{
    return GetNeighbourOfFirst(edge) != nullptr;
}

DirectedListGraph::Neighbour* DirectedListGraph::GetNeighbourOfFirst(DirectedEdge edge)
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

const DirectedListGraph::Neighbour* DirectedListGraph::GetNeighbourOfFirst(DirectedEdge edge) const
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


