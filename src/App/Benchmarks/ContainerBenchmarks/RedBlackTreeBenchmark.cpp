#include "RedBlackTreeBenchmark.h"
#include "Containers/RedBlackTree.h"
#include "Utils/Timer.h"
#include "App/Settings.h"

#include <map>

namespace RedBlackTreeBenchmark
{
    struct TestCaseResult
    {
        int64_t treeTime;
        int64_t mapTime;
    };

    void FillRedBlackTree(RedBlackTree<ContainerSettings::DataType>& tree, size_t size);
    void FillMap(std::map<ContainerSettings::DataType, bool>& map, size_t size);

    std::string Insert();
    TestCaseResult InsertCase(size_t size);
    int64_t InsertRedBlackTreeTest(size_t size);
    int64_t InsertMapTest(size_t size);


    std::string Remove();
    TestCaseResult RemoveCase(size_t size);
    int64_t RemoveRedBlackTreeTest(size_t size);
    int64_t RemoveMapTest(size_t size);

    TestCaseResult FindCase(size_t size);
    int64_t FindRedBlackTreeTest(size_t size);
    int64_t FindMapTest(size_t size);

    void FillRedBlackTree(RedBlackTree<ContainerSettings::DataType>& tree, size_t size)
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
        return "All benchmarks for RedBlackTree:\n" + AddElements() + RemoveElements() + FindElements();
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
                          ": RedBlackTree: " + Utils::Parser::NumberToString(treeTime) + "ns" +
                          "; std::map: " + Utils::Parser::NumberToString(mapTime) + "ns\n");
        }
        return result;
    }

    TestCaseResult InsertCase(size_t size)
    {
        auto treeTime = InsertRedBlackTreeTest(size);
        auto mapTime = InsertMapTest(size);

        return TestCaseResult {treeTime, mapTime};
    }

    int64_t InsertRedBlackTreeTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            RedBlackTree<ContainerSettings::DataType> testedRedBlackTree;
            FillRedBlackTree(testedRedBlackTree, size);

            Utils::Timer timer;
            timer.Start();

            testedRedBlackTree.Insert(Utils::GetRandomNumber<ContainerSettings::DataType>(ContainerSettings::MIN_VALUE, ContainerSettings::MAX_VALUE));

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
                          ": RedBlackTree: " + Utils::Parser::NumberToString(treeTime) + "ns" +
                          "; std::map: " + Utils::Parser::NumberToString(mapTime) + "ns\n");
        }
        return result;
    }

    TestCaseResult RemoveCase(size_t size)
    {
        auto treeTime = RemoveRedBlackTreeTest(size);
        auto mapTime = RemoveMapTest(size);

        return TestCaseResult {treeTime, mapTime};
    }

    int64_t RemoveRedBlackTreeTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            RedBlackTree<ContainerSettings::DataType> testedRedBlackTree;
            FillRedBlackTree(testedRedBlackTree, size);
            auto min = *testedRedBlackTree.cbegin();

            Utils::Timer timer;
            timer.Start();

            testedRedBlackTree.Remove(min);

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
                          ": RedBlackTree: " + Utils::Parser::NumberToString(treeTime) + "ns" +
                          "; std::map: " + Utils::Parser::NumberToString(mapTime) + "ns\n");
        }
        return result;
    }

    TestCaseResult FindCase(size_t size)
    {
        auto treeTime = FindRedBlackTreeTest(size);
        auto mapTime = FindMapTest(size);

        return TestCaseResult {treeTime, mapTime};
    }

    int64_t FindRedBlackTreeTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            RedBlackTree<ContainerSettings::DataType> testedRedBlackTree;
            FillRedBlackTree(testedRedBlackTree, size);

            Utils::Timer timer;
            timer.Start();

            [[maybe_unused]] volatile auto tmp = testedRedBlackTree.Find(
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