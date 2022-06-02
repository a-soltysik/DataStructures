#include "AvlTreeBenchmark.h"
#include "Containers/AvlTree.h"
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

    void FillAvlTree(AvlTree<ContainerSettings::DataType>& tree, size_t size);
    void FillMap(std::map<ContainerSettings::DataType, bool>& map, size_t size);

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

    void FillAvlTree(AvlTree<ContainerSettings::DataType>& tree, size_t size)
    {
        for (size_t i = 0u; i < size; i++)
        {
            tree.Insert(Utils::GetRandomNumber<ContainerSettings::DataType>(ContainerSettings::MIN_VALUE, ContainerSettings::MAX_VALUE));
        }
    }

    void FillMap(std::map<ContainerSettings::DataType, bool>& map, size_t size)
    {
        for (size_t i = 0u; i < size; i++)
        {
            map.insert({Utils::GetRandomNumber<ContainerSettings::DataType>(ContainerSettings::MIN_VALUE, ContainerSettings::MAX_VALUE), true});
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
        for (const auto& size: ContainerSettings::TEST_SIZES)
        {
            auto[treeTime, mapTime] = InsertCase(size);
            result.append("Size: " + Utils::Parser::NumberToString(size) +
                          ": AvlTree: " + Utils::Parser::NumberToString(treeTime) + "ns" +
                          "; std::map: " + Utils::Parser::NumberToString(mapTime) + "ns\n");
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
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            AvlTree<ContainerSettings::DataType> testedAvlTree;
            FillAvlTree(testedAvlTree, size);

            Utils::Timer timer;
            timer.Start();

            testedAvlTree.Insert(Utils::GetRandomNumber<ContainerSettings::DataType>(ContainerSettings::MIN_VALUE, ContainerSettings::MAX_VALUE));

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }

    int64_t InsertMapTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            std::map<ContainerSettings::DataType, bool> testedMap;
            FillMap(testedMap, size);

            Utils::Timer timer;
            timer.Start();

            testedMap.insert({Utils::GetRandomNumber<ContainerSettings::DataType>(ContainerSettings::MIN_VALUE, ContainerSettings::MAX_VALUE), true});

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }


    std::string RemoveElements()
    {
        return "Remove elements tests: \n" + Remove();
    }


    std::string Remove()
    {
        std::string result = "RemoveAt test: \n";
        for (const auto& size: ContainerSettings::TEST_SIZES)
        {
            auto[treeTime, mapTime] = RemoveCase(size);
            result.append("Size: " + Utils::Parser::NumberToString(size) +
                          ": AvlTree: " + Utils::Parser::NumberToString(treeTime) + "ns" +
                          "; std::map: " + Utils::Parser::NumberToString(mapTime) + "ns\n");
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
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            AvlTree<ContainerSettings::DataType> testedAvlTree;
            FillAvlTree(testedAvlTree, size);
            auto min = *testedAvlTree.cbegin();

            Utils::Timer timer;
            timer.Start();

            testedAvlTree.Remove(min);

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }

    int64_t RemoveMapTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            std::map<ContainerSettings::DataType, bool> testedMap;
            FillMap(testedMap, size);
            auto min = (*testedMap.cbegin()).first;

            Utils::Timer timer;
            timer.Start();

            testedMap.erase(min);

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }


    std::string FindElements()
    {
        std::string result = "Find test: \n";
        for (const auto& size: ContainerSettings::TEST_SIZES)
        {
            auto[treeTime, mapTime] = FindCase(size);
            result.append("Size: " + Utils::Parser::NumberToString(size) +
                          ": AvlTree: " + Utils::Parser::NumberToString(treeTime) + "ns" +
                          "; std::map: " + Utils::Parser::NumberToString(mapTime) + "ns\n");
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
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            AvlTree<ContainerSettings::DataType> testedAvlTree;
            FillAvlTree(testedAvlTree, size);

            Utils::Timer timer;
            timer.Start();

            [[maybe_unused]] volatile auto tmp = testedAvlTree.Find(
                Utils::GetRandomNumber<ContainerSettings::DataType>(ContainerSettings::MIN_VALUE, ContainerSettings::MAX_VALUE));

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }

    int64_t FindMapTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            std::map<ContainerSettings::DataType, bool> testedMap;
            FillMap(testedMap, size);

            Utils::Timer timer;
            timer.Start();

            [[maybe_unused]] volatile auto tmp = testedMap.find(
                Utils::GetRandomNumber<ContainerSettings::DataType>(ContainerSettings::MIN_VALUE, ContainerSettings::MAX_VALUE));

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }
}