#pragma once

#include "DynamicArray/DynamicArray.h"

#include <string>

namespace DynamicArrayBenchmark
{
    std::string RunBenchamark();
    std::string AddElements();
    std::string RemoveElements();
    std::string AccessElements();
    std::string FindElements();
}