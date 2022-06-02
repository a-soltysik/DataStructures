#pragma once

#include "Result.h"

namespace MST::Kruskal
{

[[nodiscard]] Result FindMstOf(const UndirectedGraph& graph);

}