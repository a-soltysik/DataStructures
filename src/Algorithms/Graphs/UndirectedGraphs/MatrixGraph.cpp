#include "Algorithms/Graphs/UndirectedGraphs/MatrixGraph.h"

Graph::Vertex MatrixGraph::AddVertex()
{
    if (GetOrder() == MAX_SIZE)
    {
        throw std::runtime_error("Max number of vertices has been reached!");
    }

    for (auto& row : graph)
    {
        row.PushBack(Graph::INFINITY);
    }

    Vertex newVertex;

    if (GetOrder() == 1)
    {
        newVertex = 0;
    }
    else
    {
        newVertex = verticesMap.Max().first + 1;
    }

    graph.PushBack(DynamicArray<Weight>(GetOrder() + 1, Graph::INFINITY));
    verticesMap[newVertex] = GetOrder() - 1;

    return newVertex;
}

bool MatrixGraph::RemoveVertex(Vertex vertex)
{
    if (!DoesExist(vertex)) {
        return false;
    }

    for (auto& row : graph)
    {
        row.RemoveAt(verticesMap.at(vertex));
    }

    graph.RemoveAt(verticesMap.at(vertex));
    RestoreIndicesFrom(vertex);

    return true;
}

bool MatrixGraph::AddEdge(Edge edge, Weight weight)
{
    if (!DoesExist(edge.first) || !DoesExist(edge.second))
    {
        return false;
    }

    if (DoesExist(edge))
    {
        return false;
    }

    graph[verticesMap.at(edge.first)][verticesMap.at(edge.second)] = weight;
    graph[verticesMap.at(edge.second)][verticesMap.at(edge.first)] = weight;

    size++;

    return true;
}

bool MatrixGraph::RemoveEdge(Edge edge)
{
    if (!DoesExist(edge))
    {
        return false;
    }

    graph[verticesMap.at(edge.first)][verticesMap.at(edge.second)] = Graph::INFINITY;
    graph[verticesMap.at(edge.second)][verticesMap.at(edge.first)] = Graph::INFINITY;

    size--;

    return true;
}

std::optional<Graph::Weight> MatrixGraph::GetWeight(Edge edge) const
{
    if (!DoesExist(edge))
    {
        return {};
    }
    return graph[verticesMap.at(edge.first)][verticesMap.at(edge.second)];
}

bool MatrixGraph::SetWeight(Edge edge, Weight weight)
{
    if (!DoesExist(edge))
    {
        return false;
    }

    graph[verticesMap.at(edge.first)][verticesMap.at(edge.second)] = weight;
    graph[verticesMap.at(edge.second)][verticesMap.at(edge.first)] = weight;

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

bool MatrixGraph::DoesExist(Vertex vertex) const
{
    return verticesMap.Find(vertex) != verticesMap.end();
}

bool MatrixGraph::DoesExist(Edge edge) const
{
    if (!DoesExist(edge.first) || !DoesExist(edge.second))
    {
        return false;
    }
    return graph[verticesMap.at(edge.first)][verticesMap.at(edge.second)] != Graph::INFINITY;
}

std::optional<DynamicArray<Graph::Vertex>> MatrixGraph::GetNeighboursOf(Vertex vertex) const
{
    if (!DoesExist(vertex))
    {
        return {};
    }

    DynamicArray<Vertex> result;
    uint32_t sourceIndex = verticesMap.at(vertex);

    for (const auto& pair : verticesMap)
    {
        if (graph[sourceIndex][pair.second] != Graph::INFINITY)
        {
            result.PushBack(pair.first);
        }
    }

    return result;
}


DynamicArray<Graph::Vertex> MatrixGraph::GetVertices() const
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


DynamicArray<Utils::Pair<UndirectedGraph::Edge, Graph::Weight>> MatrixGraph::GetEdges() const
{
    DynamicArray<Utils::Pair<UndirectedGraph::Edge, Graph::Weight>> result;
    result.Resize(GetSize());

    uint64_t edgeCounter = 0;
    for (uint32_t i = 1; i < GetOrder(); i++)
    {
        for (uint32_t j = 0; j < i; j++)
        {
            if (graph[i][j] != Graph::INFINITY)
            {

                result[edgeCounter] = {{FindVertexByIndex(i).value(), FindVertexByIndex(j).value()}, graph[i][j]};
                edgeCounter++;
            }
        }
    }
    return result;
}


bool MatrixGraph::ForEachNeighbourOf(Vertex vertex, VertexPredicate predicate) const
{
    if (!DoesExist(vertex))
    {
        return false;
    }

    uint32_t sourceIndex = verticesMap.at(vertex);

    for (const auto& pair : verticesMap)
    {
        if (graph[sourceIndex][pair.second] != Graph::INFINITY)
        {
            predicate(pair.first);
        }
    }

    return true;
}

void MatrixGraph::ForEachVertex(VertexPredicate predicate) const
{
    for (const auto& pair : verticesMap)
    {
        predicate(pair.first);
    }
}

void MatrixGraph::ForEachEdge(EdgePredicate predicate) const
{
    for (uint32_t i = 1; i < GetOrder(); i++)
    {
        for (uint32_t j = 0; j < i; j++)
        {
            if (graph[i][j] != Graph::INFINITY)
            {
                predicate({FindVertexByIndex(i).value(), FindVertexByIndex(j).value()}, graph[i][j]);
            }
        }
    }
}

void MatrixGraph::RestoreIndicesFrom(Vertex from)
{
    bool start = false;

    for (auto& pair : verticesMap)
    {
        if (start)
        {
            pair.second--;
        }
        if (pair.first == from)
        {
            start = true;
        }
    }

    verticesMap.Remove(from);
}

std::optional<Graph::Vertex> MatrixGraph::FindVertexByIndex(uint32_t index) const
{
    for (const auto& pair : verticesMap)
    {
        if (pair.second == index)
        {
            return pair.first;
        }
    }
    return {};
}


