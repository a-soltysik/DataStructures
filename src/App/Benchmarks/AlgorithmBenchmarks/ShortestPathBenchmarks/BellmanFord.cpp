#include "App/Benchmarks/AlgorithmBenchmarks/ShortestPathBenchmarks/DijkstraBenchmark.h"
#include "Algorithms/Graphs/DirectedGraphs/DirectedListGraph.h"
#include "Algorithms/Graphs/DirectedGraphs/DirectedMatrixGraph.h"
#include "Algorithms/Graphs/GraphGenerator.h"
#include "Algorithms/ShortestPath/BellmanFord.h"
#include "App/Settings.h"
#include "Utils/Timer.h"

namespace BellmanFordBenchmark
{

struct TestCaseResult
{
    int64_t directedListGraphTime;
    int64_t directedMatrixGraphTime;
};

template<typename T>
T GenerateGraph(uint32_t order, float density);

TestCaseResult TestCase(uint32_t order, float density);

template<typename T>
int64_t ConcreteGraphTest(uint32_t order, float density);

Utils::Pair<Graph::Vertex, Graph::Vertex> DrawEdge(const DynamicArray<Graph::Vertex>& vertices);

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
    std::string result = "Benchmark for BellmanFord's algorithm:\n";

    for (const auto& order: AlgorithmSettings::GRAPH_ORDERS)
    {
        for (const auto& density : AlgorithmSettings::GraphDensities)
        {
            auto[directedListGraphTime, directedMatrixGraphTime] = TestCase(order, density);
            result.append("Order: " + Utils::Parser::NumberToString(order) +
                          " Density: " + Utils::Parser::NumberToString(density, 2) +
                          ": DirectedListGraph: " + Utils::Parser::NumberToString(directedListGraphTime) + "ns" +
                          "; DirectedMatrixGraph: " + Utils::Parser::NumberToString(directedMatrixGraphTime) + "ns\n");
        }
        result += "\n";
    }
    return result;
}

TestCaseResult TestCase(uint32_t order, float density)
{
    auto directedListGraphTime = ConcreteGraphTest<DirectedListGraph>(order, density);
    auto directedMatrixGraphTime = ConcreteGraphTest<DirectedMatrixGraph>(order, density);

    return {directedListGraphTime, directedMatrixGraphTime};
}

template<typename T>
int64_t ConcreteGraphTest(uint32_t order, float density)
{
    int64_t averageTime = 0u;
    auto graph = GenerateGraph<T>(order, density);
    for (uint32_t i = 0u; i < AlgorithmSettings::NUMBER_OF_TESTS; i++)
    {
        auto[first, second] = DrawEdge(graph.GetVertices());
        Utils::Timer timer;
        timer.Start();

        [[maybe_unused]] volatile auto result = ShortestPath::BellmanFord::FindShortestPath(graph, first, second);

        timer.Stop();
        averageTime += timer.GetTimeInNanos();
    }
    return averageTime / ContainerSettings::NUMBER_OF_TESTS;
}

Utils::Pair<Graph::Vertex, Graph::Vertex> DrawEdge(const DynamicArray<Graph::Vertex>& vertices)
{
    Graph::Vertex first = vertices[static_cast<size_t>(Utils::GetRandomNumber<size_t>(0, vertices.Size() - 1))];

    Graph::Vertex second;

    do
    {
        second = vertices[static_cast<size_t>(Utils::GetRandomNumber<size_t>(0, vertices.Size() - 1))];
    } while (first == second);

    return {first, second};
}

}