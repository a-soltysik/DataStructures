#pragma once

#include "Algorithms/MST/Result.h"

namespace MST::Kruskal
{

[[nodiscard]] Result FindMstOf(const UndirectedGraph& graph);

}