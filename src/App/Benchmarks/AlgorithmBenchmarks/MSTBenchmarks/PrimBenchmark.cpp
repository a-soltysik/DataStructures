#include "PrimBenchmark.h"
#include "Algorithms/Graphs/UndirectedGraphs/ListGraph.h"
#include "Algorithms/Graphs/UndirectedGraphs/MatrixGraph.h"
#include "Algorithms/Graphs/GraphGenerator.h"
#include "Algorithms/MST/Prim.h"
#include "App/Settings.h"
#include "Utils/Timer.h"

namespace PrimBenchmark
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
    static_assert(AlgorithmSettings::Validate<ListGraph>());
    static_assert(AlgorithmSettings::Validate<MatrixGraph>());

    return Generator::GenerateConnectedGraph<T>({order,
                                                 density,
                                                 AlgorithmSettings::MIN_WEIGHT,
                                                 AlgorithmSettings::MAX_WEIGHT}).value();
}

std::string RunBenchmark()
{
    std::string result = "Benchmark for Prim's algorithm:\n";

    for (const auto& order: AlgorithmSettings::GRAPH_ORDERS)
    {
        for (const auto& density : AlgorithmSettings::GRAPH_DENSITIES)
        {
            auto[listGraphTime, matrixGraphTime] = TestCase(order, density);
            result.append("Order: " + Utils::Parser::NumberToString(order) +
                          " Density: " + Utils::Parser::NumberToString(density, 2) +
                          ": ListGraph: " + Utils::Parser::NumberToString(listGraphTime) + "ns" +
                          "; MatrixGraph: " + Utils::Parser::NumberToString(matrixGraphTime) + "ns\n");
        }
        result += "\n";
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

        [[maybe_unused]] volatile auto result = MST::Prim::FindMstOf(graph);

        timer.Stop();
        averageTime += timer.GetTimeInNanos();
    }
    return averageTime / ContainerSettings::NUMBER_OF_TESTS;
}

}