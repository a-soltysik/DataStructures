#include "Algorithms/ShortestPath/Result.h"

std::ostream& operator<<(std::ostream& os, const ShortestPath::Result& result)
{
    os << "Waga ścieżki: " << result.weight << "\n";
    os << "Droga: [";

    for (size_t i = 0; i < result.path.Size(); i++)
    {
        os << result.path[i];
        if (i != result.path.Size() - 1)
        {
            os << ", ";
        }
    }
    return os << "]";
}