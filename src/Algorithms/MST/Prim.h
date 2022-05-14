#pragma once

#include "Algorithms/MST/Result.h"

namespace MST::Prim
{

[[nodiscard]] Result FindMstOf(const UndirectedGraph& graph);

}