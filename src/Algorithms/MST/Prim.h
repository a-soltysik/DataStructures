#pragma once

#include "Result.h"

namespace MST::Prim
{

[[nodiscard]] Result FindMstOf(const UndirectedGraph& graph);

}