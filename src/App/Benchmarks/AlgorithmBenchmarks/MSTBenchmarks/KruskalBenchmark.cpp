#include "App/Benchmarks/AlgorithmBenchmarks/MSTBenchmarks/KruskalBenchmark.h"
#include "Algorithms/Graphs/UndirectedGraphs/ListGraph.h"
#include "Algorithms/Graphs/UndirectedGraphs/MatrixGraph.h"
#include "Algorithms/Graphs/GraphGenerator.h"
#include "Algorithms/MST/Kruskal.h"
#include "App/Settings.h"
#include "Utils/Timer.h"

namespace KruskalBenchmark
{

struct TestCaseResult
{
    int64_t listGraphTime;
    int64_t matrixGraphTime;
};

template<typename T>
T GenerateGraph(uint32_t order, float density);

TestCaseResult TestCase(uint32_t order, float density);

template<typename T>
int64_t ConcreteGraphTest(uint32_t order, float density);

template<typename T>
T GenerateGraph(uint32_t order, float density)
{
    return Generator::GenerateConnectedGraph<T>({order,
                                                 density,
                                                 AlgorithmSettings::MIN_WEIGHT,
                                                 AlgorithmSettings::MAX_WEIGHT}).value();
}

std::string RunBenchmark()
{
    std::string result = "Benchmark for Kruskal's algorithm:\n";

    for (const auto& order: AlgorithmSettings::GRAPH_ORDERS)
    {
        for (const auto& density : AlgorithmSettings::GraphDensities)
        {
            auto[listGraphTime, matrixGraphTime] = TestCase(order, density);
            result.append("Order: " + std::to_string(order) + " Density: " + std::to_string(density) +
                          ": ListGraph: " + std::to_string(listGraphTime) + "ns" +
                          "; MatrixGraph: " + std::to_string(matrixGraphTime) + "ns\n");
        }
    }
    return result;
}

TestCaseResult TestCase(uint32_t order, float density)
{
    auto listGraphTime = ConcreteGraphTest<ListGraph>(order, density);
    auto matrixGraphTime = ConcreteGraphTest<MatrixGraph>(order, density);

    return {listGraphTime, matrixGraphTime};
}

template<typename T>
int64_t ConcreteGraphTest(uint32_t order, float density)
{
    int64_t averageTime = 0u;
    auto graph = GenerateGraph<T>(order, density);
    for (uint32_t i = 0u; i < AlgorithmSettings::NUMBER_OF_TESTS; i++)
    {


        Utils::Timer timer;
        timer.Start();

        [[maybe_unused]] volatile auto result = MST::Kruskal::FindMstOf(graph);

        timer.Stop();
        averageTime += timer.GetTimeInNanos();
    }
    return averageTime / ContainerSettings::NUMBER_OF_TESTS;
}

}