#include "Benchmark/List/Benchmark.h"
#include "Container/List/List.h"

#include "Benchmark/DynamicArray/Benchmark.h"
#include "Container/DynamicArray/DynamicArray.h"

#include <iostream>

int main()
{
    std::cout << ListBenchmark::RunBenchamark() << std::endl;
    std::cout << DynamicArrayBenchmark::RunBenchamark() << std::endl;

    return 0;
}