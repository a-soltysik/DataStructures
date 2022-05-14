#include "Algorithms/Graphs/DirectedGraphs/DirectedMatrixGraph.h"

Graph::Vertex DirectedMatrixGraph::AddVertex()
{
    if (GetOrder() == MAX_SIZE)
    {
        throw std::runtime_error("Max number of vertices has been reached!");
    }

    for (auto& row : graph)
    {
        row.PushBack(Graph::INFINITY_WEIGHT);
    }

    Vertex newVertex = GetOrder() - 1;

    graph.PushBack(DynamicArray<Weight>(GetOrder() + 1, Graph::INFINITY_WEIGHT));

    return newVertex;
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

    graph[edge.vertices.first][edge.vertices.second] = edge.weight;

    size++;

    return true;
}

std::optional<Graph::Weight> DirectedMatrixGraph::GetWeight(DirectedEdge directedEdge) const
{
    if (!DoesExist(directedEdge))
    {
        return {};
    }
    return graph[directedEdge.first][directedEdge.second];
}

bool DirectedMatrixGraph::SetWeight(DirectedEdge directedEdge, Weight weight)
{
    if (!DoesExist(directedEdge))
    {
        return false;
    }

    graph[directedEdge.first][directedEdge.second] = weight;

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
    return vertex < GetOrder();
}

bool DirectedMatrixGraph::DoesExist(DirectedEdge directedEdge) const
{
    if (!DoesExist(directedEdge.first) || !DoesExist(directedEdge.second))
    {
        return false;
    }
    return graph[directedEdge.first][directedEdge.second] != Graph::INFINITY_WEIGHT;
}

std::optional<DynamicArray<Graph::Neighbour>> DirectedMatrixGraph::GetNeighboursOf(Vertex vertex) const
{
    if (!DoesExist(vertex))
    {
        return {};
    }

    uint32_t numberOfNeighbours = 0;

    for (Vertex i = 0; i < GetOrder(); i++)
    {
        if (graph[vertex][i] != Graph::INFINITY_WEIGHT)
        {
            numberOfNeighbours++;
        }
    }

    DynamicArray<Neighbour> result;
    result.Resize(numberOfNeighbours);

    for (Vertex i = 0; i < GetOrder(); i++)
    {
        if (graph[vertex][i] != Graph::INFINITY_WEIGHT)
        {
            result[numberOfNeighbours--] = {i, graph[vertex][i]};
        }
    }

    return result;
}


DynamicArray<Graph::Vertex> DirectedMatrixGraph::GetVertices() const
{
    DynamicArray<Vertex> result;
    result.Resize(GetOrder());

    for (Vertex i = 0; i < GetOrder(); i++)
    {
        result[i] = i;
    }

    return result;
}


DynamicArray<DirectedGraph::DirectedEdgeData> DirectedMatrixGraph::GetDirectedEdges() const
{
    DynamicArray<DirectedEdgeData> result;
    result.Resize(GetSize());

    uint64_t DirectedEdgeCounter = 0;
    for (Vertex i = 0; i < GetOrder(); i++)
    {
        for (Vertex j = 0; j < GetOrder(); j++)
        {
            if (graph[i][j] != Graph::INFINITY_WEIGHT)
            {
                result[DirectedEdgeCounter] = {{i, j}, graph[i][j]};
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

    for (Vertex i = 0; i < GetOrder(); i++)
    {
        if (graph[vertex][i] != Graph::INFINITY_WEIGHT)
        {
            predicate({i, graph[vertex][i]});
        }
    }

    return true;
}

void DirectedMatrixGraph::ForEachVertex(VertexPredicate predicate) const
{
    for (Vertex i = 0; i < GetOrder(); i++)
    {
        predicate(i);
    }
}

void DirectedMatrixGraph::ForEachDirectedEdge(DirectedEdgePredicate predicate) const
{
    for (Vertex i = 0; i < GetOrder(); i++)
    {
        for (Vertex j = 0; j < GetOrder(); j++)
        {
            if (graph[i][j] != Graph::INFINITY_WEIGHT)
            {
                predicate({{i, j}, graph[i][j]});
            }
        }
    }
}