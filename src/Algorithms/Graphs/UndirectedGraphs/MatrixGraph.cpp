#include "MatrixGraph.h"

Graph::Vertex MatrixGraph::AddVertex()
{
    if (GetOrder() == MAX_SIZE)
    {
        throw std::runtime_error("Max number of vertices has been reached!");
    }

    Vertex newVertex = GetOrder() - 1;

    graph.PushBack(DynamicArray<Weight>(GetSize(), Graph::INFINITY_WEIGHT));

    return newVertex;
}

bool MatrixGraph::AddEdge(const EdgeData& edge)
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

    if (edge.weight == 0)
    {
        return false;
    }

    for (Vertex i = 0; i < GetOrder(); i++)
    {
        if (i == edge.vertices.first || i == edge.vertices.second)
        {
            graph[i].PushBack(edge.weight);
        }
        else
        {
            graph[i].PushBack(INFINITY_WEIGHT);
        }
    }

    size++;

    return true;
}

bool MatrixGraph::RemoveEdge(Edge edge)
{
    if (!DoesExist(edge.first) || !DoesExist(edge.second))
    {
        return false;
    }

    size_t edgeToRemove = 0;
    for (; edgeToRemove < GetSize(); edgeToRemove++)
    {
        if (graph[edge.first][edgeToRemove] == graph[edge.second][edgeToRemove] &&
            graph[edge.first][edgeToRemove] != INFINITY_WEIGHT)
        {
            break;
        }
    }

    if (edgeToRemove == GetSize())
    {
        return false;
    }

    for (Vertex i = 0; i < GetOrder(); i++)
    {
        graph[i].RemoveAt(edgeToRemove);
    }

    size--;

    return true;
}

std::optional<Graph::Weight> MatrixGraph::GetWeight(Edge edge) const
{
    if (!DoesExist(edge.first) || !DoesExist(edge.second))
    {
        return {};
    }

    if (edge.first == edge.second)
    {
        return {};
    }

    for (size_t edgeNumber = 0; edgeNumber < GetSize(); edgeNumber++)
    {
        if (graph[edge.first][edgeNumber] == graph[edge.second][edgeNumber] &&
            graph[edge.first][edgeNumber] != INFINITY_WEIGHT)
        {
            return graph[edge.first][edgeNumber];
        }
    }

    return {};
}

bool MatrixGraph::SetWeight(Edge edge, Weight weight)
{
    if (!DoesExist(edge.first) || !DoesExist(edge.second))
    {
        return false;
    }

    if (edge.first == edge.second)
    {
        return false;
    }

    if (weight == 0)
    {
        return false;
    }

    for (size_t edgeNumber = 0; edgeNumber < GetSize(); edgeNumber++)
    {
        if (graph[edge.first][edgeNumber] == graph[edge.second][edgeNumber] &&
            graph[edge.first][edgeNumber] != INFINITY_WEIGHT)
        {
            graph[edge.first][edgeNumber] = weight;
            graph[edge.second][edgeNumber] = weight;
            return true;
        }
    }

    return false;
}

uint32_t MatrixGraph::GetOrder() const noexcept
{
    return static_cast<uint32_t>(graph.Size());
}

size_t MatrixGraph::GetSize() const noexcept
{
    return size;
}

uint32_t MatrixGraph::GetNumberOfNeighboursOf(Vertex vertex) const
{
    if (!DoesExist(vertex))
    {
        return 0;
    }

    uint32_t number = 0;

    for (size_t edgeNumber = 0; edgeNumber < GetSize(); edgeNumber++)
    {
        if (graph[vertex][edgeNumber] != INFINITY_WEIGHT)
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
    if (edge.first == edge.second)
    {
        return false;
    }

    if (!DoesExist(edge.first) || !DoesExist(edge.second))
    {
        return false;
    }

    for (size_t edgeNumber = 0; edgeNumber < GetSize(); edgeNumber++)
    {
        if (graph[edge.first][edgeNumber] == graph[edge.second][edgeNumber] &&
            graph[edge.first][edgeNumber] != INFINITY_WEIGHT)
        {
            return true;
        }
    }
    return false;
}

std::optional<DynamicArray<Graph::Neighbour>> MatrixGraph::GetNeighboursOf(Vertex vertex) const
{
    if (!DoesExist(vertex))
    {
        return {};
    }

    DynamicArray<Neighbour> result(GetNumberOfNeighboursOf(vertex));

    uint32_t neighbour = 0;
    for (size_t edgeNumber = 0; edgeNumber < GetSize(); edgeNumber++)
    {
        if (graph[vertex][edgeNumber] != INFINITY_WEIGHT)
        {
            for (Vertex i = 0; i < GetOrder(); i++)
            {
                if (i == vertex)
                {
                    continue;
                }
                if (graph[i][edgeNumber] != INFINITY_WEIGHT)
                {
                    result[neighbour++] = {i, graph[i][edgeNumber]};
                }
            }
        }
    }

    return result;
}

DynamicArray<Graph::Vertex> MatrixGraph::GetVertices() const
{
    DynamicArray<Vertex> result(GetOrder());

    for (Vertex i = 0; i < GetOrder(); i++)
    {
        result[i] = i;
    }

    return result;
}

DynamicArray<UndirectedGraph::EdgeData> MatrixGraph::GetEdges() const
{
    DynamicArray<EdgeData> result(GetSize());

    size_t edgeCounter = 0;
    for (size_t edge = 0; edge < GetSize(); edge++)
    {
        Edge currentEdge = {MAX_SIZE, MAX_SIZE};
        for (Vertex i = 0; i < GetOrder(); i++)
        {
            if (graph[i][edge] != INFINITY_WEIGHT)
            {
                if (currentEdge.first == MAX_SIZE)
                {
                    currentEdge.first = i;
                }
                else
                {
                    currentEdge.second = i;
                }
            }
        }
        result[edgeCounter++] = {currentEdge, graph[currentEdge.first][edge]};
    }

    return result;
}


bool MatrixGraph::ForEachNeighbourOf(Vertex vertex, NeighbourPredicate predicate) const
{
    if (!DoesExist(vertex))
    {
        return false;
    }

    for (size_t edgeNumber = 0; edgeNumber < GetSize(); edgeNumber++)
    {
        if (graph[vertex][edgeNumber] != INFINITY_WEIGHT)
        {
            for (Vertex i = 0; i < GetOrder(); i++)
            {
                if (i == vertex)
                {
                    continue;
                }
                if (graph[i][edgeNumber] != INFINITY_WEIGHT)
                {
                    predicate({i, graph[i][edgeNumber]});
                }
            }
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
    for (size_t edge = 0; edge < GetSize(); edge++)
    {
        Edge currentEdge = {MAX_SIZE, MAX_SIZE};
        for (Vertex i = 0; i < GetOrder(); i++)
        {
            if (graph[i][edge] != INFINITY_WEIGHT)
            {
                if (currentEdge.first == MAX_SIZE)
                {
                    currentEdge.first = i;
                }
                else
                {
                    currentEdge.second = i;
                }
            }
        }
        predicate({currentEdge, graph[currentEdge.first][edge]});
    }
}

std::string MatrixGraph::ToString() const
{
    std::string result = "\n";
    auto columnWidth = CalculateColumnWidth();
    auto separator = RowSeparator(GetSize() + 1, columnWidth);

    for (uint32_t i = 0; i <= GetOrder(); i++)
    {
        for (uint32_t j = 0; j <= GetSize(); j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    result += std::string(columnWidth, ' ') + Utils::DOUBLE_VERTICAL_BAR;
                }
                else
                {
                    std::string number = Utils::Parser::NumberToString(j - 1);
                    result += Utils::PutInStringCenter(number, columnWidth) + Utils::VERTICAL_BAR;
                }
            }
            else
            {
                if (j == 0)
                {
                    std::string number = Utils::Parser::NumberToString(i - 1);
                    result += Utils::PutInStringCenter(number, columnWidth) + Utils::DOUBLE_VERTICAL_BAR;
                }
                else
                {
                    std::string number;
                    if (graph[i - 1][j - 1] == INFINITY_WEIGHT)
                    {
                        number = "inf";
                    }
                    else
                    {
                        number = Utils::Parser::NumberToString(graph[i - 1][j - 1]);
                    }
                    result += Utils::PutInStringCenter(number, columnWidth) + Utils::VERTICAL_BAR;
                }
            }
        }
        if (i == 0)
        {
            result += "\n" + OpeningSeparator(GetSize() + 1, columnWidth) + "\n";
        }
        else if (i != GetOrder())
        {
            result += "\n" + separator + "\n";
        }
        else
        {
            result += "\n" + ClosingSeparator(GetSize() + 1, columnWidth);
        }
    }
    return result;
}

size_t MatrixGraph::CalculateColumnWidth() const
{
    size_t columnWidth = 0;
    for (uint32_t i = 0; i <= GetSize(); i++)
    {
        if (i == 0)
        {
            auto length = Utils::Parser::NumberToString(GetOrder() - 1).length();
            if (length > columnWidth)
            {
                columnWidth = length;
            }
        }
        else
        {
            for (uint32_t j = 0; j <= GetOrder(); j++)
            {
                size_t weightLength;
                if (j == 0)
                {
                    weightLength = Utils::Parser::NumberToString(i - 1).length();
                }
                else if (graph[j - 1][i - 1] == INFINITY_WEIGHT)
                {
                    weightLength = 3;
                }
                else
                {
                    weightLength = Utils::Parser::NumberToString(graph[j - 1][i - 1]).length();
                }

                if (weightLength > columnWidth)
                {
                    columnWidth = weightLength;
                }
            }
        }
    }

    return columnWidth;
}

std::string MatrixGraph::RowSeparator(size_t columns, size_t columnWidth)
{
    std::string result;
    for (uint32_t i = 0; i < columns; i++)
    {
        for (uint32_t j = 0; j < columnWidth; j++)
        {
            result += Utils::HORIZONTAL_BAR;
        }
        if (i == 0)
        {
            result += Utils::DOUBLE_VERTICAL_BAR_HORIZONTAL_BAR;
        }
        else if (i != columns - 1)
        {
            result += Utils::CROSS;
        }
        else
        {
            result += Utils::VERTICAL_BAR_LEFT;
        }
    }
    return result;
}

std::string MatrixGraph::ClosingSeparator(size_t columns, size_t columnWidth)
{
    std::string result;
    for (uint32_t i = 0; i < columns; i++)
    {
        for (uint32_t j = 0; j < columnWidth; j++)
        {
            result += Utils::HORIZONTAL_BAR;
        }
        if (i == 0)
        {
            result += Utils::HORIZONTAL_BAR_DOUBLE_UP;
        }
        else if (i != columns - 1)
        {
            result += Utils::HORIZONTAL_BAR_UP;
        }
        else
        {
            result += Utils::UP_LEFT;
        }
    }
    return result;
}

std::string MatrixGraph::OpeningSeparator(size_t columns, size_t columnWidth)
{
    std::string result;
    for (uint32_t i = 0; i < columns; i++)
    {
        for (uint32_t j = 0; j < columnWidth; j++)
        {
            result += Utils::DOUBLE_HORIZONTAL_BAR;
        }
        if (i == 0)
        {
            result += Utils::DOUBLE_CROSS;
        }
        else if (i != columns - 1)
        {
            result += Utils::DOUBLE_HORIZONTAL_BAR_VERTICAL_BAR;
        }
        else
        {
            result += Utils::VERTICAL_BAR_DOUBLE_LEFT;
        }
    }
    return result;
}
