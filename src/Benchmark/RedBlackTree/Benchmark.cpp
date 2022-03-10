#include "Benchmark/RedBlackTree/Benchmark.h"
#include "Container/RedBlackTree/RedBlackTree.h"
#include "Utils/Utils.h"
#include "Utils/Timer.h"
#include "Settings.h"

#include <map>
#include <algorithm>

namespace RedBlackTreeBenchmark
{
    struct TestCaseResult
    {
        uint64_t treeTime;
        uint64_t mapTime;
    };

    RedBlackTree MakeRedBlackTree(size_t size);
    std::map<RedBlackTree::DataType, bool> MakeMap(size_t size);

    std::string Insert();
    TestCaseResult InsertCase(size_t size);
    uint64_t InsertRedBlackTreeTest(size_t size);
    uint64_t InsertMapTest(size_t size);


    std::string Remove();
    TestCaseResult RemoveCase(size_t size);
    uint64_t RemoveRedBlackTreeTest(size_t size);
    uint64_t RemoveMapTest(size_t size);

    TestCaseResult FindCase(size_t size);
    uint64_t FindRedBlackTreeTest(size_t size);
    uint64_t FindMapTest(size_t size);

    RedBlackTree MakeRedBlackTree(size_t size)
    {
        RedBlackTree result;
        for (size_t i = 0u; i < size; i++)
        {
            result.Insert(Utils::GetRandomInt(Settings::MIN_VALUE, Settings::MAX_VALUE));
        }
        return result;
    }

    std::map<RedBlackTree::DataType, bool> MakeMap(size_t size)
    {
        std::map<RedBlackTree::DataType, bool> result;
        for (size_t i = 0u; i < size; i++)
        {
            result.insert({ Utils::GetRandomInt(Settings::MIN_VALUE, Settings::MAX_VALUE), true });
        }
        return result;
    }

    std::string RunBenchamark()
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
        for (const auto& size : Settings::TEST_SIZES)
        {
            auto [treeTime, mapTime] = InsertCase(size);
            result.append("Size: " + std::to_string(size) +
                ": RedBlackTree: " + std::to_string(treeTime) +
                "; std::map: " + std::to_string(mapTime) + "\n");
        }
        return result;
    }

    TestCaseResult InsertCase(size_t size)
    {
        auto treeTime = InsertRedBlackTreeTest(size);
        auto mapTime = InsertMapTest(size);

        return TestCaseResult{ treeTime, mapTime };
    }

    uint64_t InsertRedBlackTreeTest(size_t size)
    {
        auto modelRedBlackTree = MakeRedBlackTree(size);
        uint64_t averageTime = 0u;
        for (uint32_t i = 0u; i < Settings::NUMBER_OF_TESTS; i++) {
            RedBlackTree testedRedBlackTree(modelRedBlackTree);
            size_t middle = testedRedBlackTree.Size() / 2;
            Utils::Timer timer;
            timer.Start();
            testedRedBlackTree.Insert(Utils::GetRandomInt(Settings::MIN_VALUE, Settings::MAX_VALUE));
            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / Settings::NUMBER_OF_TESTS;
    }

    uint64_t InsertMapTest(size_t size)
    {
        auto modelMap = MakeMap(size);
        uint64_t averageTime = 0u;
        for (uint32_t i = 0u; i < Settings::NUMBER_OF_TESTS; i++) {
            std::map<RedBlackTree::DataType, bool> testedMap(modelMap);
            Utils::Timer timer;
            timer.Start();
            testedMap.insert({ Utils::GetRandomInt(Settings::MIN_VALUE, Settings::MAX_VALUE), true });
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
        for (const auto& size : Settings::TEST_SIZES)
        {
            auto [treeTime, mapTime] = RemoveCase(size);
            result.append("Size: " + std::to_string(size) +
                ": RedBlackTree: " + std::to_string(treeTime) +
                "; std::map: " + std::to_string(mapTime) + "\n");
        }
        return result;
    }

    TestCaseResult RemoveCase(size_t size)
    {
        auto treeTime = RemoveRedBlackTreeTest(size);
        auto mapTime = RemoveMapTest(size);

        return TestCaseResult{ treeTime, mapTime };
    }

    uint64_t RemoveRedBlackTreeTest(size_t size)
    {
        auto modelRedBlackTree = MakeRedBlackTree(size);
        uint64_t averageTime = 0u;
        for (uint32_t i = 0u; i < Settings::NUMBER_OF_TESTS; i++) {
            RedBlackTree testedRedBlackTree(modelRedBlackTree);
            //std::cout << std::equal(modelRedBlackTree.begin(), modelRedBlackTree.end(), testedRedBlackTree.begin());
            auto min = *testedRedBlackTree.cbegin();

            Utils::Timer timer;
            timer.Start();
            testedRedBlackTree.Remove(min);
            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / Settings::NUMBER_OF_TESTS;
    }

    uint64_t RemoveMapTest(size_t size)
    {
        auto modelMap = MakeMap(size);
        uint64_t averageTime = 0u;
        for (uint32_t i = 0u; i < Settings::NUMBER_OF_TESTS; i++) {
            std::map<RedBlackTree::DataType, bool> testedMap(modelMap);
            Utils::Timer timer;
            timer.Start();
            auto min = (* testedMap.cbegin()).first;
            testedMap.erase(min);
            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / Settings::NUMBER_OF_TESTS;
    }



    std::string FindElements()
    {
        std::string result = "Find test: \n";
        for (const auto& size : Settings::TEST_SIZES)
        {
            auto [treeTime, mapTime] = FindCase(size);
            result.append("Size: " + std::to_string(size) +
                ": RedBlackTree: " + std::to_string(treeTime) +
                "; std::map: " + std::to_string(mapTime) + "\n");
        }
        return result;
    }

    TestCaseResult FindCase(size_t size)
    {
        auto treeTime = FindRedBlackTreeTest(size);
        auto mapTime = FindMapTest(size);

        return TestCaseResult{ treeTime, mapTime };
    }

    uint64_t FindRedBlackTreeTest(size_t size)
    {
        auto modelRedBlackTree = MakeRedBlackTree(size);
        uint64_t averageTime = 0u;
        for (uint32_t i = 0u; i < Settings::NUMBER_OF_TESTS; i++) {
            RedBlackTree testedRedBlackTree(modelRedBlackTree);
            Utils::Timer timer;
            timer.Start();
            auto tmp = testedRedBlackTree.Find(Utils::GetRandomInt(Settings::MIN_VALUE, Settings::MAX_VALUE));
            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / Settings::NUMBER_OF_TESTS;
    }

    uint64_t FindMapTest(size_t size)
    {
        auto modelMap = MakeMap(size);
        uint64_t averageTime = 0u;
        for (uint32_t i = 0u; i < Settings::NUMBER_OF_TESTS; i++) {
            std::map<RedBlackTree::DataType, bool> testedMap(modelMap);
            Utils::Timer timer;
            timer.Start();
            auto tmp = testedMap.find(Utils::GetRandomInt(Settings::MIN_VALUE, Settings::MAX_VALUE));
            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / Settings::NUMBER_OF_TESTS;
    }
}
