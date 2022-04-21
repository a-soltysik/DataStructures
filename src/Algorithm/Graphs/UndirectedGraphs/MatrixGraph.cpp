#include "Algorithm/Graphs/UndirectedGraphs/MatrixGraph.h"

Graph::Vertex MatrixGraph::AddVertex()
{
    if (GetOrder() == MAX_SIZE)
    {
        throw std::runtime_error("Max number of vertices has been reached!");
    }

    for (auto& row : graph)
    {
        row.PushBack(Graph::INF);
    }
    graph.PushBack(DynamicArray<Weight>(GetOrder() + 1, Graph::INF));

    return GetOrder() - 1;
}

bool MatrixGraph::RemoveVertex(Vertex vertex)
{
    if (!doesExist(vertex)) {
        return false;
    }

    for (auto& row : graph)
    {
        row.RemoveAt(vertex);
    }

    graph.RemoveAt(vertex);
}

bool MatrixGraph::AddEdge(Edge edge, Weight weight)
{
    if (!doesExist(edge.first) || !doesExist(edge.second))
    {
        return false;
    }

    if (doesExist(edge))
    {
        return false;
    }

    graph[edge.first][edge.second] = weight;
    graph[edge.second][edge.first] = weight;

    size++;

    return true;
}

bool MatrixGraph::RemoveEdge(Edge edge)
{
    if (!doesExist(edge))
    {
        return false;
    }

    graph[edge.first][edge.second] = Graph::INF;
    graph[edge.second][edge.first] = Graph::INF;

    size--;

    return true;
}

std::optional<Graph::Weight> MatrixGraph::GetWeight(Edge edge) const
{
    if (!doesExist(edge))
    {
        return {};
    }
    return graph[edge.first][edge.second];
}

bool MatrixGraph::SetWeight(Edge edge, Weight weight)
{
    if (!doesExist(edge))
    {
        return false;
    }

    graph[edge.first][edge.second] = weight;
    graph[edge.second][edge.first] = weight;

    return true;
}

uint32_t MatrixGraph::GetOrder() const
{
    return static_cast<uint32_t>(graph.Size());
}

uint64_t MatrixGraph::GetSize() const
{
    return size;
}

bool MatrixGraph::ForEachNeighbour(Vertex source, VertexPredicate predicate) const
{
    if (!doesExist(source))
    {
        return false;
    }

    for (uint32_t i = 0; i < graph[source].Size(); i++)
    {
        if (graph[source][i] != Graph::INF)
        {
            predicate(i);
        }
    }
}

void MatrixGraph::ForEachVertex(VertexPredicate predicate) const
{
    for (Vertex vertex = 0; vertex < GetOrder(); vertex++)
    {
        predicate(vertex);
    }
}

void MatrixGraph::ForEachEdge(EdgePredicate predicate) const
{
    for (uint32_t i = 1; i < GetOrder(); i++)
    {
        for (uint32_t j = 0; j < i; j++)
        {
            if (graph[i][j] != Graph::INF)
            {
                predicate({i, j}, graph[i][j]);
            }
        }
    }
}

bool MatrixGraph::doesExist(Vertex vertex) const
{
    return vertex < GetOrder();
}

bool MatrixGraph::doesExist(Edge edge) const
{
    return graph[edge.first][edge.second] != Graph::INF;
}
