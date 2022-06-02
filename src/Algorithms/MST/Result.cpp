#include "Result.h"

std::ostream& operator<<(std::ostream& os, const MST::Result& result)
{
    os << "Waga drzewa: " << result.weight << "\n";
    os << "Krawędzie:\n";

    for (const auto& edge : result.edges)
    {
        os << "Krawędź { " << edge.vertices.first << ", " << edge.vertices.second << "}, Waga: " << edge.weight << "\n";
    }

    return os;
}