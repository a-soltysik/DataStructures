#include "App/Benchmarks/ContainerBenchmarks/AvlTreeBenchmark.h"
#include "Containers/AvlTree.h"
#include "Utils/Utils.h"
#include "Utils/Timer.h"
#include "App/Settings.h"

#include <map>

namespace AvlTreeBenchmark
{
    struct TestCaseResult
    {
        int64_t treeTime;
        int64_t mapTime;
    };

    void FillAvlTree(AvlTree& tree, size_t size);
    void FillMap(std::map<AvlTree::DataType, bool>& map, size_t size);

    std::string Insert();
    TestCaseResult InsertCase(size_t size);
    int64_t InsertAvlTreeTest(size_t size);
    int64_t InsertMapTest(size_t size);


    std::string Remove();
    TestCaseResult RemoveCase(size_t size);
    int64_t RemoveAvlTreeTest(size_t size);
    int64_t RemoveMapTest(size_t size);

    TestCaseResult FindCase(size_t size);
    int64_t FindAvlTreeTest(size_t size);
    int64_t FindMapTest(size_t size);

    void FillAvlTree(AvlTree& tree, size_t size)
    {
        for (size_t i = 0u; i < size; i++)
        {
            tree.Insert(Utils::GetRandomInt(Settings::MIN_VALUE, Settings::MAX_VALUE));
        }
    }

    void FillMap(std::map<AvlTree::DataType, bool>& map, size_t size)
    {
        for (size_t i = 0u; i < size; i++)
        {
            map.insert({Utils::GetRandomInt(Settings::MIN_VALUE, Settings::MAX_VALUE), true});
        }
    }

    std::string RunBenchmark()
    {
        return "All benchmarks for AvlTree:\n" + AddElements() + RemoveElements() + FindElements();
    }

    std::string AddElements()
    {
        return "Add elements tests: \n" + Insert();
    }


    std::string Insert()
    {
        std::string result = "Insert test: \n";
        for (const auto& size: Settings::TEST_SIZES)
        {
            auto[treeTime, mapTime] = InsertCase(size);
            result.append("Size: " + std::to_string(size) +
                          ": AvlTree: " + std::to_string(treeTime) + "ns" +
                          "; std::map: " + std::to_string(mapTime) + "ns\n");
        }
        return result;
    }

    TestCaseResult InsertCase(size_t size)
    {
        auto treeTime = InsertAvlTreeTest(size);
        auto mapTime = InsertMapTest(size);

        return TestCaseResult {treeTime, mapTime};
    }

    int64_t InsertAvlTreeTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < Settings::NUMBER_OF_TESTS; i++)
        {
            AvlTree testedAvlTree;
            FillAvlTree(testedAvlTree, size);

            Utils::Timer timer;
            timer.Start();

            testedAvlTree.Insert(Utils::GetRandomInt(Settings::MIN_VALUE, Settings::MAX_VALUE));

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / Settings::NUMBER_OF_TESTS;
    }

    int64_t InsertMapTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < Settings::NUMBER_OF_TESTS; i++)
        {
            std::map<AvlTree::DataType, bool> testedMap;
            FillMap(testedMap, size);

            Utils::Timer timer;
            timer.Start();

            testedMap.insert({Utils::GetRandomInt(Settings::MIN_VALUE, Settings::MAX_VALUE), true});

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / Settings::NUMBER_OF_TESTS;
    }


    std::string RemoveElements()
    {
        return "Remove elements tests: \n" + Remove();
    }


    std::string Remove()
    {
        std::string result = "RemoveAt test: \n";
        for (const auto& size: Settings::TEST_SIZES)
        {
            auto[treeTime, mapTime] = RemoveCase(size);
            result.append("Size: " + std::to_string(size) +
                          ": AvlTree: " + std::to_string(treeTime) + "ns" +
                          "; std::map: " + std::to_string(mapTime) + "ns\n");
        }
        return result;
    }

    TestCaseResult RemoveCase(size_t size)
    {
        auto treeTime = RemoveAvlTreeTest(size);
        auto mapTime = RemoveMapTest(size);

        return TestCaseResult {treeTime, mapTime};
    }

    int64_t RemoveAvlTreeTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < Settings::NUMBER_OF_TESTS; i++)
        {
            AvlTree testedAvlTree;
            FillAvlTree(testedAvlTree, size);
            auto min = *testedAvlTree.cbegin();

            Utils::Timer timer;
            timer.Start();

            testedAvlTree.Remove(min);

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / Settings::NUMBER_OF_TESTS;
    }

    int64_t RemoveMapTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < Settings::NUMBER_OF_TESTS; i++)
        {
            std::map<AvlTree::DataType, bool> testedMap;
            FillMap(testedMap, size);
            auto min = (*testedMap.cbegin()).first;

            Utils::Timer timer;
            timer.Start();

            testedMap.erase(min);

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / Settings::NUMBER_OF_TESTS;
    }


    std::string FindElements()
    {
        std::string result = "Find test: \n";
        for (const auto& size: Settings::TEST_SIZES)
        {
            auto[treeTime, mapTime] = FindCase(size);
            result.append("Size: " + std::to_string(size) +
                          ": AvlTree: " + std::to_string(treeTime) + "ns" +
                          "; std::map: " + std::to_string(mapTime) + "ns\n");
        }
        return result;
    }

    TestCaseResult FindCase(size_t size)
    {
        auto treeTime = FindAvlTreeTest(size);
        auto mapTime = FindMapTest(size);

        return TestCaseResult {treeTime, mapTime};
    }

    int64_t FindAvlTreeTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < Settings::NUMBER_OF_TESTS; i++)
        {
            AvlTree testedAvlTree;
            FillAvlTree(testedAvlTree, size);

            Utils::Timer timer;
            timer.Start();

            [[maybe_unused]] volatile auto tmp = testedAvlTree.Find(
                Utils::GetRandomInt(Settings::MIN_VALUE, Settings::MAX_VALUE));

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / Settings::NUMBER_OF_TESTS;
    }

    int64_t FindMapTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < Settings::NUMBER_OF_TESTS; i++)
        {
            std::map<AvlTree::DataType, bool> testedMap;
            FillMap(testedMap, size);

            Utils::Timer timer;
            timer.Start();

            [[maybe_unused]] volatile auto tmp = testedMap.find(
                Utils::GetRandomInt(Settings::MIN_VALUE, Settings::MAX_VALUE));

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / Settings::NUMBER_OF_TESTS;
    }
}