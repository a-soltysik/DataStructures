#include "Algorithms/Graphs/DirectedGraphs/DirectedMatrixGraph.h"
#include "Utils/Utils.h"

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

    graph[edge.vertices.first][edge.vertices.second] = edge.weight;

    size++;

    return true;
}

bool DirectedMatrixGraph::RemoveDirectedEdge(DirectedEdge directedEdge)
{
    if (!DoesExist(directedEdge))
    {
        return false;
    }

    graph[directedEdge.first][directedEdge.second] = INFINITY_WEIGHT;

    size--;

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

uint32_t DirectedMatrixGraph::GetNumberOfNeighboursOf(Graph::Vertex vertex) const
{
    if (!DoesExist(vertex))
    {
        return 0;
    }

    uint32_t number = 0;

    for (Vertex i = 0; i < GetOrder(); i++)
    {
        if (graph[vertex][i] != INFINITY_WEIGHT)
        {
            number++;
        }
    }

    return number;
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
    return graph[directedEdge.first][directedEdge.second] != INFINITY_WEIGHT;
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
        if (graph[vertex][i] != INFINITY_WEIGHT)
        {
            numberOfNeighbours++;
        }
    }

    DynamicArray<Neighbour> result(numberOfNeighbours);

    for (Vertex i = 0; i < GetOrder(); i++)
    {
        if (graph[vertex][i] != INFINITY_WEIGHT)
        {
            result[numberOfNeighbours--] = {i, graph[vertex][i]};
        }
    }

    return result;
}

DynamicArray<Graph::Vertex> DirectedMatrixGraph::GetVertices() const
{
    DynamicArray<Vertex> result(GetOrder());

    for (Vertex i = 0; i < GetOrder(); i++)
    {
        result[i] = i;
    }

    return result;
}

DynamicArray<DirectedGraph::DirectedEdgeData> DirectedMatrixGraph::GetDirectedEdges() const
{
    DynamicArray<DirectedEdgeData> result(GetSize());

    uint64_t DirectedEdgeCounter = 0;
    for (Vertex i = 0; i < GetOrder(); i++)
    {
        for (Vertex j = 0; j < GetOrder(); j++)
        {
            if (graph[i][j] != INFINITY_WEIGHT)
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
        if (graph[vertex][i] != INFINITY_WEIGHT)
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

std::string DirectedMatrixGraph::ToString() const
{
    std::string result = "\n";
    auto columnWidth = GetColumnWidth();
    auto separator = RowSeparator(GetOrder() + 1, columnWidth);

    for (uint32_t i = 0; i <= GetOrder(); i++)
    {
        for (uint32_t j = 0; j <= GetOrder(); j++)
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
            result += "\n" + RowBeginSeparator(GetOrder() + 1, columnWidth) + "\n";
        }
        else if (i != GetOrder())
        {
            result += "\n" + separator + "\n";
        }
        else
        {
            result += "\n" + RowEndSeparator(GetOrder() + 1, columnWidth);
        }
    }
    return result;
}

size_t DirectedMatrixGraph::GetColumnWidth() const
{
    size_t columnWidth = 0;
    for (uint32_t i = 0; i <= GetOrder(); i++)
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

std::string DirectedMatrixGraph::RowSeparator(size_t columns, size_t columnWidth)
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

std::string DirectedMatrixGraph::RowEndSeparator(size_t columns, size_t columnWidth)
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

std::string DirectedMatrixGraph::RowBeginSeparator(size_t columns, size_t columnWidth)
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