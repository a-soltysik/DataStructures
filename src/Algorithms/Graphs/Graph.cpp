#include "Graph.h"

std::ostream& operator<<(std::ostream& os, const Graph& graph)
{
    graph.Serialize(os);
    return os;
}

std::istream& operator>>(std::istream& is,Graph& graph)
{
    graph.Deserialize(is);
    return is;
}