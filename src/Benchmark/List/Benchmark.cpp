#include "Benchmark/List/Benchmark.h"
#include "Container/List/List.h"
#include "Utils/Utils.h"
#include "Utils/Timer.h"
#include "Settings.h"

#include <list>
#include <algorithm>

namespace ListBenchmark
{
    struct TestCaseResult
    {
        uint64_t listTime;
        uint64_t stdListTime;
    };

    List MakeList(size_t size);
    std::list<List::DataType> MakeStdList(size_t size);

    std::string PushBack();
    TestCaseResult PushBackCase(size_t size);
    uint64_t PushBackListTest(size_t size);
    uint64_t PushBackStdListTest(size_t size);

    std::string PushFront();
    TestCaseResult PushFrontCase(size_t size);
    uint64_t PushFrontListTest(size_t size);
    uint64_t PushFrontStdListTest(size_t size);

    std::string Insert();
    TestCaseResult InsertCase(size_t size);
    uint64_t InsertListTest(size_t size);
    uint64_t InsertStdListTest(size_t size);

    std::string RemoveBack();
    TestCaseResult RemoveBackCase(size_t size);
    uint64_t RemoveBackListTest(size_t size);
    uint64_t RemoveBackStdListTest(size_t size);

    std::string RemoveFront();
    TestCaseResult RemoveFrontCase(size_t size);
    uint64_t RemoveFrontListTest(size_t size);
    uint64_t RemoveFrontStdListTest(size_t size);

    std::string RemoveAt();
    TestCaseResult RemoveAtCase(size_t size);
    uint64_t RemoveAtListTest(size_t size);
    uint64_t RemoveAtStdListTest(size_t size);

    TestCaseResult AccessCase(size_t size);
    uint64_t AccessListTest(size_t size);
    uint64_t AccessStdListTest(size_t size);

    TestCaseResult FindCase(size_t size);
    uint64_t FindListTest(size_t size);
    uint64_t FindStdListTest(size_t size);

    List MakeList(size_t size)
    {
        List result;
        for (size_t i = 0u; i < size; i++)
        {
            result.PushBack(Utils::GetRandomInt(Settings::MIN_VALUE, Settings::MAX_VALUE));
        }
        return result;
    }

    std::list<List::DataType> MakeStdList(size_t size)
    {
        std::list<List::DataType> result;
        for (size_t i = 0u; i < size; i++)
        {
            result.push_back(Utils::GetRandomInt(Settings::MIN_VALUE, Settings::MAX_VALUE));
        }
        return result;
    }

    std::string RunBenchamark()
    {
        return "All benchmarks for List:\n" + AddElements() + RemoveElements() + AccessElements() + FindElements();
    }

    std::string AddElements()
    {
        return "Add elements tests: \n" + PushFront() + Insert() + PushBack();
    }

    std::string PushBack()
    {
        std::string result = "Push back test: \n";
        for (const auto& size : Settings::TEST_SIZES)
        {
            auto [listTime, stdListTime] = PushBackCase(size);
            result.append("Size: " + std::to_string(size) +
                ": List: " + std::to_string(listTime) +
                "ns; std::list: " + std::to_string(stdListTime) + "ns\n");
        }
        return result;
    }

    TestCaseResult PushBackCase(size_t size)
    {
        auto listTime = PushBackListTest(size);
        auto stdListTime = PushBackStdListTest(size);

        return TestCaseResult{ listTime, stdListTime };
    }

    uint64_t PushBackListTest(size_t size)
    {
        auto modelList = MakeList(size);
        uint64_t averageTime = 0u;
        for (uint32_t i = 0u; i < Settings::NUMBER_OF_TESTS; i++) {
            List testedList(modelList);
            Utils::Timer timer;
            timer.Start();
            testedList.PushBack(Utils::GetRandomInt(Settings::MIN_VALUE, Settings::MAX_VALUE));
            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / Settings::NUMBER_OF_TESTS;
    }

    uint64_t PushBackStdListTest(size_t size)
    {
        auto modelStdList = MakeStdList(size);
        uint64_t averageTime = 0u;
        for (uint32_t i = 0u; i < Settings::NUMBER_OF_TESTS; i++) {
            std::list<List::DataType> testedStdList(modelStdList);
            Utils::Timer timer;
            timer.Start();
            testedStdList.push_back(Utils::GetRandomInt(Settings::MIN_VALUE, Settings::MAX_VALUE));
            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / Settings::NUMBER_OF_TESTS;
    }

    std::string PushFront()
    {
        std::string result = "Push front test: \n";
        for (const auto& size : Settings::TEST_SIZES)
        {
            auto [listTime, stdListTime] = PushFrontCase(size);
            result.append("Size: " + std::to_string(size) +
                ": List: " + std::to_string(listTime) +
                "; std::list: " + std::to_string(stdListTime) + "\n");
        }
        return result;
    }

    TestCaseResult PushFrontCase(size_t size)
    {
        auto listTime = PushFrontListTest(size);
        auto stdListTime = PushFrontStdListTest(size);

        return TestCaseResult{ listTime, stdListTime };
    }

    uint64_t PushFrontListTest(size_t size)
    {
        auto modelList = MakeList(size);
        uint64_t averageTime = 0u;
        for (uint32_t i = 0u; i < Settings::NUMBER_OF_TESTS; i++) {
            List testedList(modelList);
            Utils::Timer timer;
            timer.Start();
            testedList.PushFront(Utils::GetRandomInt(Settings::MIN_VALUE, Settings::MAX_VALUE));
            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / Settings::NUMBER_OF_TESTS;
    }

    uint64_t PushFrontStdListTest(size_t size)
    {
        auto modelStdList = MakeStdList(size);
        uint64_t averageTime = 0u;
        for (uint32_t i = 0u; i < Settings::NUMBER_OF_TESTS; i++) {
            std::list<List::DataType> testedStdList(modelStdList);
            Utils::Timer timer;
            timer.Start();
            testedStdList.push_front(Utils::GetRandomInt(Settings::MIN_VALUE, Settings::MAX_VALUE));
            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / Settings::NUMBER_OF_TESTS;
    }

    std::string Insert()
    {
        std::string result = "Insert test: \n";
        for (const auto& size : Settings::TEST_SIZES)
        {
            auto [listTime, stdListTime] = InsertCase(size);
            result.append("Size: " + std::to_string(size) +
                ": List: " + std::to_string(listTime) +
                "; std::list: " + std::to_string(stdListTime) + "\n");
        }
        return result;
    }

    TestCaseResult InsertCase(size_t size)
    {
        auto listTime = InsertListTest(size);
        auto stdListTime = InsertStdListTest(size);

        return TestCaseResult{ listTime, stdListTime };
    }

    uint64_t InsertListTest(size_t size)
    {
        auto modelList = MakeList(size);
        uint64_t averageTime = 0u;
        for (uint32_t i = 0u; i < Settings::NUMBER_OF_TESTS; i++) {
            List testedList(modelList);
            size_t middle = testedList.Size() / 2;
            Utils::Timer timer;
            timer.Start();
            testedList.Insert(middle, Utils::GetRandomInt(Settings::MIN_VALUE, Settings::MAX_VALUE));
            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / Settings::NUMBER_OF_TESTS;
    }

    uint64_t InsertStdListTest(size_t size)
    {
        auto modelStdList = MakeStdList(size);
        uint64_t averageTime = 0u;
        for (uint32_t i = 0u; i < Settings::NUMBER_OF_TESTS; i++) {
            std::list<List::DataType> testedStdList(modelStdList);
            Utils::Timer timer;
            timer.Start();
            auto middle = testedStdList.begin();
            std::advance(middle, testedStdList.size() / 2);
            testedStdList.insert(middle, Utils::GetRandomInt(Settings::MIN_VALUE, Settings::MAX_VALUE));
            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / Settings::NUMBER_OF_TESTS;
    }





    std::string RemoveElements()
    {
        return "Remove elements tests: \n" + RemoveFront() + RemoveAt() + RemoveBack();
    }

    std::string RemoveBack()
    {
        std::string result = "Remove back test: \n";
        for (const auto& size : Settings::TEST_SIZES)
        {
            auto [listTime, stdListTime] = RemoveBackCase(size);
            result.append("Size: " + std::to_string(size) +
                ": List: " + std::to_string(listTime) +
                "ns; std::list: " + std::to_string(stdListTime) + "ns\n");
        }
        return result;
    }

    TestCaseResult RemoveBackCase(size_t size)
    {
        auto listTime = RemoveBackListTest(size);
        auto stdListTime = RemoveBackStdListTest(size);

        return TestCaseResult{ listTime, stdListTime };
    }

    uint64_t RemoveBackListTest(size_t size)
    {
        auto modelList = MakeList(size);
        uint64_t averageTime = 0u;
        for (uint32_t i = 0u; i < Settings::NUMBER_OF_TESTS; i++) {
            List testedList(modelList);
            Utils::Timer timer;
            timer.Start();
            testedList.RemoveBack();
            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / Settings::NUMBER_OF_TESTS;
    }

    uint64_t RemoveBackStdListTest(size_t size)
    {
        auto modelStdList = MakeStdList(size);
        uint64_t averageTime = 0u;
        for (uint32_t i = 0u; i < Settings::NUMBER_OF_TESTS; i++) {
            std::list<List::DataType> testedStdList(modelStdList);
            Utils::Timer timer;
            timer.Start();
            testedStdList.pop_back();
            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / Settings::NUMBER_OF_TESTS;
    }

    std::string RemoveFront()
    {
        std::string result = "Remove front test: \n";
        for (const auto& size : Settings::TEST_SIZES)
        {
            auto [listTime, stdListTime] = RemoveFrontCase(size);
            result.append("Size: " + std::to_string(size) +
                ": List: " + std::to_string(listTime) +
                "; std::list: " + std::to_string(stdListTime) + "\n");
        }
        return result;
    }

    TestCaseResult RemoveFrontCase(size_t size)
    {
        auto listTime = RemoveFrontListTest(size);
        auto stdListTime = RemoveFrontStdListTest(size);

        return TestCaseResult{ listTime, stdListTime };
    }

    uint64_t RemoveFrontListTest(size_t size)
    {
        auto modelList = MakeList(size);
        uint64_t averageTime = 0u;
        for (uint32_t i = 0u; i < Settings::NUMBER_OF_TESTS; i++) {
            List testedList(modelList);
            Utils::Timer timer;
            timer.Start();
            testedList.RemoveFront();
            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / Settings::NUMBER_OF_TESTS;
    }

    uint64_t RemoveFrontStdListTest(size_t size)
    {
        auto modelStdList = MakeStdList(size);
        uint64_t averageTime = 0u;
        for (uint32_t i = 0u; i < Settings::NUMBER_OF_TESTS; i++) {
            std::list<List::DataType> testedStdList(modelStdList);
            Utils::Timer timer;
            timer.Start();
            testedStdList.pop_back();
            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / Settings::NUMBER_OF_TESTS;
    }

    std::string RemoveAt()
    {
        std::string result = "RemoveAt test: \n";
        for (const auto& size : Settings::TEST_SIZES)
        {
            auto [listTime, stdListTime] = RemoveAtCase(size);
            result.append("Size: " + std::to_string(size) +
                ": List: " + std::to_string(listTime) +
                "; std::list: " + std::to_string(stdListTime) + "\n");
        }
        return result;
    }

    TestCaseResult RemoveAtCase(size_t size)
    {
        auto listTime = RemoveAtListTest(size);
        auto stdListTime = RemoveAtStdListTest(size);

        return TestCaseResult{ listTime, stdListTime };
    }

    uint64_t RemoveAtListTest(size_t size)
    {
        auto modelList = MakeList(size);
        uint64_t averageTime = 0u;
        for (uint32_t i = 0u; i < Settings::NUMBER_OF_TESTS; i++) {
            List testedList(modelList);
            size_t middle = testedList.Size() / 2;
            Utils::Timer timer;
            timer.Start();
            testedList.RemoveAt(middle);
            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / Settings::NUMBER_OF_TESTS;
    }

    uint64_t RemoveAtStdListTest(size_t size)
    {
        auto modelStdList = MakeStdList(size);
        uint64_t averageTime = 0u;
        for (uint32_t i = 0u; i < Settings::NUMBER_OF_TESTS; i++) {
            std::list<List::DataType> testedStdList(modelStdList);
            Utils::Timer timer;
            timer.Start();
            auto middle = testedStdList.begin();
            std::advance(middle, testedStdList.size() / 2);
            testedStdList.erase(middle);
            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / Settings::NUMBER_OF_TESTS;
    }

    std::string AccessElements()
    {
        std::string result = "Access test: \n";
        for (const auto& size : Settings::TEST_SIZES)
        {
            auto [listTime, stdListTime] = AccessCase(size);
            result.append("Size: " + std::to_string(size) +
                ": List: " + std::to_string(listTime) +
                "; std::list: " + std::to_string(stdListTime) + "\n");
        }
        return result;
    }

    TestCaseResult AccessCase(size_t size)
    {
        auto listTime = AccessListTest(size);
        auto stdListTime = AccessStdListTest(size);

        return TestCaseResult{ listTime, stdListTime };
    }

    uint64_t AccessListTest(size_t size)
    {
        auto modelList = MakeList(size);
        uint64_t averageTime = 0u;
        for (uint32_t i = 0u; i < Settings::NUMBER_OF_TESTS; i++) {
            List testedList(modelList);
            size_t middle = testedList.Size() / 2;
            Utils::Timer timer;
            timer.Start();
            auto tmp = testedList[middle];
            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / Settings::NUMBER_OF_TESTS;
    }

    uint64_t AccessStdListTest(size_t size)
    {
        auto modelStdList = MakeStdList(size);
        uint64_t averageTime = 0u;
        for (uint32_t i = 0u; i < Settings::NUMBER_OF_TESTS; i++) {
            std::list<List::DataType> testedStdList(modelStdList);
            Utils::Timer timer;
            timer.Start();
            auto middle = testedStdList.begin();
            std::advance(middle, testedStdList.size() / 2);
            auto tmp = *middle;
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
            auto [listTime, stdListTime] = FindCase(size);
            result.append("Size: " + std::to_string(size) +
                ": List: " + std::to_string(listTime) +
                "; std::list: " + std::to_string(stdListTime) + "\n");
        }
        return result;
    }

    TestCaseResult FindCase(size_t size)
    {
        auto listTime = FindListTest(size);
        auto stdListTime = FindStdListTest(size);

        return TestCaseResult{ listTime, stdListTime };
    }

    uint64_t FindListTest(size_t size)
    {
        auto modelList = MakeList(size);
        uint64_t averageTime = 0u;
        for (uint32_t i = 0u; i < Settings::NUMBER_OF_TESTS; i++) {
            List testedList(modelList);
            Utils::Timer timer;
            timer.Start();
            auto tmp = testedList.Find(Utils::GetRandomInt(Settings::MIN_VALUE, Settings::MAX_VALUE));
            timer.Stop();
            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / Settings::NUMBER_OF_TESTS;
    }

    uint64_t FindStdListTest(size_t size)
    {
        auto modelStdList = MakeStdList(size);
        uint64_t averageTime = 0u;
        for (uint32_t i = 0u; i < Settings::NUMBER_OF_TESTS; i++) {
            std::list<List::DataType> testedStdList(modelStdList);
            Utils::Timer timer;
            timer.Start();
            auto tmp = std::find(testedStdList.cbegin(), testedStdList.cend(), Utils::GetRandomInt(Settings::MIN_VALUE, Settings::MAX_VALUE));
            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / Settings::NUMBER_OF_TESTS;
    }
}
