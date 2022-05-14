#include "Algorithms/Graphs/UndirectedGraphs/MatrixGraph.h"

Graph::Vertex MatrixGraph::AddVertex()
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

bool MatrixGraph::AddEdge(const EdgeData& edge)
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
    graph[edge.vertices.second][edge.vertices.first] = edge.weight;

    size++;

    return true;
}

bool MatrixGraph::RemoveEdge(UndirectedGraph::Edge edge)
{
    if (!DoesExist(edge))
    {
        return false;
    }

    graph[edge.first][edge.second] = INFINITY_WEIGHT;
    graph[edge.second][edge.first] = INFINITY_WEIGHT;

    size--;

    return true;
}


std::optional<Graph::Weight> MatrixGraph::GetWeight(Edge edge) const
{
    if (!DoesExist(edge))
    {
        return {};
    }
    return graph[edge.first][edge.second];
}

bool MatrixGraph::SetWeight(Edge edge, Weight weight)
{
    if (!DoesExist(edge))
    {
        return false;
    }

    graph[edge.first][edge.second] = weight;
    graph[edge.second][edge.first] = weight;

    return true;
}

uint32_t MatrixGraph::GetOrder() const noexcept
{
    return static_cast<uint32_t>(graph.Size());
}

uint64_t MatrixGraph::GetSize() const noexcept
{
    return size;
}

uint32_t MatrixGraph::GetNumberOfNeighboursOf(Graph::Vertex vertex) const
{
    if (!DoesExist(vertex))
    {
        return 0;
    }

    uint32_t number = 0;

    for (Vertex i = 0; i < GetOrder(); i++)
    {
        if (graph[vertex][i] != Graph::INFINITY_WEIGHT)
        {
            number++;
        }
    }

    return number;
}

bool MatrixGraph::DoesExist(Vertex vertex) const
{
    return vertex < GetOrder();
}

bool MatrixGraph::DoesExist(Edge edge) const
{
    if (!DoesExist(edge.first) || !DoesExist(edge.second))
    {
        return false;
    }
    return graph[edge.first][edge.second] != Graph::INFINITY_WEIGHT;
}

std::optional<DynamicArray<Graph::Neighbour>> MatrixGraph::GetNeighboursOf(Vertex vertex) const
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


DynamicArray<Graph::Vertex> MatrixGraph::GetVertices() const
{
    DynamicArray<Vertex> result;
    result.Resize(GetOrder());

    for (Vertex i = 0; i < GetOrder(); i++)
    {
        result[i] = i;
    }

    return result;
}


DynamicArray<UndirectedGraph::EdgeData> MatrixGraph::GetEdges() const
{
    DynamicArray<EdgeData> result;
    result.Resize(GetSize());

    uint64_t edgeCounter = 0;
    for (uint32_t i = 1; i < GetOrder(); i++)
    {
        for (uint32_t j = 0; j < i; j++)
        {
            if (graph[i][j] != Graph::INFINITY_WEIGHT)
            {

                result[edgeCounter] = {{i, j}, graph[i][j]};
                edgeCounter++;
            }
        }
    }
    return result;
}


bool MatrixGraph::ForEachNeighbourOf(Vertex vertex, NeighbourPredicate predicate) const
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

void MatrixGraph::ForEachVertex(VertexPredicate predicate) const
{
    for (Vertex i = 0; i < GetOrder(); i++)
    {
        predicate(i);
    }
}

void MatrixGraph::ForEachEdge(EdgePredicate predicate) const
{
    for (uint32_t i = 1; i < GetOrder(); i++)
    {
        for (uint32_t j = 0; j < i; j++)
        {
            if (graph[i][j] != Graph::INFINITY_WEIGHT)
            {
                predicate({{i, j}, graph[i][j]});
            }
        }
    }
}