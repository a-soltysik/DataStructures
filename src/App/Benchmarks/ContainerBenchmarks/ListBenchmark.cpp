#include "ListBenchmark.h"
#include "Containers/List.h"
#include "Utils/Timer.h"
#include "App/Settings.h"

#include <list>
#include <algorithm>

namespace ListBenchmark
{
    struct TestCaseResult
    {
        int64_t listTime;
        int64_t stdListTime;
    };

    void FillList(List<ContainerSettings::DataType>& list, size_t size);
    void FillStdList(std::list<ContainerSettings::DataType>& list, size_t size);

    std::string PushBack();
    TestCaseResult PushBackCase(size_t size);
    int64_t PushBackListTest(size_t size);
    int64_t PushBackStdListTest(size_t size);

    std::string PushFront();
    TestCaseResult PushFrontCase(size_t size);
    int64_t PushFrontListTest(size_t size);
    int64_t PushFrontStdListTest(size_t size);

    std::string Insert();
    TestCaseResult InsertCase(size_t size);
    int64_t InsertListTest(size_t size);
    int64_t InsertStdListTest(size_t size);

    std::string RemoveBack();
    TestCaseResult RemoveBackCase(size_t size);
    int64_t RemoveBackListTest(size_t size);
    int64_t RemoveBackStdListTest(size_t size);

    std::string RemoveFront();
    TestCaseResult RemoveFrontCase(size_t size);
    int64_t RemoveFrontListTest(size_t size);
    int64_t RemoveFrontStdListTest(size_t size);

    std::string RemoveAt();
    TestCaseResult RemoveAtCase(size_t size);
    int64_t RemoveAtListTest(size_t size);
    int64_t RemoveAtStdListTest(size_t size);

    TestCaseResult AccessCase(size_t size);
    int64_t AccessListTest(size_t size);
    int64_t AccessStdListTest(size_t size);

    TestCaseResult FindCase(size_t size);
    int64_t FindListTest(size_t size);
    int64_t FindStdListTest(size_t size);

    void FillList(List<ContainerSettings::DataType>& list, size_t size)
    {
        for (size_t i = 0u; i < size; i++)
        {
            list.PushBack(Utils::GetRandomNumber<ContainerSettings::DataType>(ContainerSettings::MIN_VALUE, ContainerSettings::MAX_VALUE));
        }
    }

    void FillStdList(std::list<ContainerSettings::DataType>& list, size_t size)
    {
        for (size_t i = 0u; i < size; i++)
        {
            list.push_back(Utils::GetRandomNumber<ContainerSettings::DataType>(ContainerSettings::MIN_VALUE, ContainerSettings::MAX_VALUE));
        }
    }

    std::string RunBenchmark()
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
        for (const auto& size: ContainerSettings::TEST_SIZES)
        {
            auto[listTime, stdListTime] = PushBackCase(size);
            result.append("Size: " + Utils::Parser::NumberToString(size) +
                          ": List: " + Utils::Parser::NumberToString(listTime) + "ns" +
                          "; std::list: " + Utils::Parser::NumberToString(stdListTime) + "ns\n");
        }
        return result;
    }

    TestCaseResult PushBackCase(size_t size)
    {
        auto listTime = PushBackListTest(size);
        auto stdListTime = PushBackStdListTest(size);

        return TestCaseResult {listTime, stdListTime};
    }

    int64_t PushBackListTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            List<ContainerSettings::DataType> testedList;
            FillList(testedList, size);

            Utils::Timer timer;
            timer.Start();

            testedList.PushBack(Utils::GetRandomNumber<ContainerSettings::DataType>(ContainerSettings::MIN_VALUE, ContainerSettings::MAX_VALUE));

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }

    int64_t PushBackStdListTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            std::list<ContainerSettings::DataType> testedStdList;
            FillStdList(testedStdList, size);

            Utils::Timer timer;
            timer.Start();

            testedStdList.push_back(Utils::GetRandomNumber<ContainerSettings::DataType>(ContainerSettings::MIN_VALUE, ContainerSettings::MAX_VALUE));

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }

    std::string PushFront()
    {
        std::string result = "Push front test: \n";
        for (const auto& size: ContainerSettings::TEST_SIZES)
        {
            auto[listTime, stdListTime] = PushFrontCase(size);
            result.append("Size: " + Utils::Parser::NumberToString(size) +
                          ": List: " + Utils::Parser::NumberToString(listTime) + "ns" +
                          "; std::list: " + Utils::Parser::NumberToString(stdListTime) + "ns\n");
        }
        return result;
    }

    TestCaseResult PushFrontCase(size_t size)
    {
        auto listTime = PushFrontListTest(size);
        auto stdListTime = PushFrontStdListTest(size);

        return TestCaseResult {listTime, stdListTime};
    }

    int64_t PushFrontListTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            List<ContainerSettings::DataType> testedList;
            FillList(testedList, size);

            Utils::Timer timer;
            timer.Start();

            testedList.PushFront(Utils::GetRandomNumber<ContainerSettings::DataType>(ContainerSettings::MIN_VALUE, ContainerSettings::MAX_VALUE));

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }

    int64_t PushFrontStdListTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            std::list<ContainerSettings::DataType> testedStdList;
            FillStdList(testedStdList, size);

            Utils::Timer timer;
            timer.Start();

            testedStdList.push_front(Utils::GetRandomNumber<ContainerSettings::DataType>(ContainerSettings::MIN_VALUE, ContainerSettings::MAX_VALUE));

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }

    std::string Insert()
    {
        std::string result = "Insert test: \n";
        for (const auto& size: ContainerSettings::TEST_SIZES)
        {
            auto[listTime, stdListTime] = InsertCase(size);
            result.append("Size: " + Utils::Parser::NumberToString(size) +
                          ": List: " + Utils::Parser::NumberToString(listTime) + "ns" +
                          "; std::list: " + Utils::Parser::NumberToString(stdListTime) + "ns\n");
        }
        return result;
    }

    TestCaseResult InsertCase(size_t size)
    {
        auto listTime = InsertListTest(size);
        auto stdListTime = InsertStdListTest(size);

        return TestCaseResult {listTime, stdListTime};
    }

    int64_t InsertListTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            List<ContainerSettings::DataType> testedList;
            FillList(testedList, size);
            size_t middle = testedList.Size() / 2;

            Utils::Timer timer;
            timer.Start();

            testedList.Insert(middle, Utils::GetRandomNumber<ContainerSettings::DataType>(ContainerSettings::MIN_VALUE, ContainerSettings::MAX_VALUE));

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }

    int64_t InsertStdListTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            std::list<ContainerSettings::DataType> testedStdList;
            FillStdList(testedStdList, size);

            Utils::Timer timer;
            timer.Start();

            auto middle = testedStdList.begin();
            std::advance(middle, testedStdList.size() / 2);
            testedStdList.insert(middle, Utils::GetRandomNumber<ContainerSettings::DataType>(ContainerSettings::MIN_VALUE, ContainerSettings::MAX_VALUE));

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }


    std::string RemoveElements()
    {
        return "Remove elements tests: \n" + RemoveFront() + RemoveAt() + RemoveBack();
    }

    std::string RemoveBack()
    {
        std::string result = "Remove back test: \n";
        for (const auto& size: ContainerSettings::TEST_SIZES)
        {
            auto[listTime, stdListTime] = RemoveBackCase(size);
            result.append("Size: " + Utils::Parser::NumberToString(size) +
                          ": List: " + Utils::Parser::NumberToString(listTime) + "ns" +
                          "; std::list: " + Utils::Parser::NumberToString(stdListTime) + "ns\n");
        }
        return result;
    }

    TestCaseResult RemoveBackCase(size_t size)
    {
        auto listTime = RemoveBackListTest(size);
        auto stdListTime = RemoveBackStdListTest(size);

        return TestCaseResult {listTime, stdListTime};
    }

    int64_t RemoveBackListTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            List<ContainerSettings::DataType> testedList;
            FillList(testedList, size);

            Utils::Timer timer;
            timer.Start();

            testedList.RemoveBack();

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }

    int64_t RemoveBackStdListTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            std::list<ContainerSettings::DataType> testedStdList;
            FillStdList(testedStdList, size);

            Utils::Timer timer;
            timer.Start();

            testedStdList.pop_back();

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }

    std::string RemoveFront()
    {
        std::string result = "Remove front test: \n";
        for (const auto& size: ContainerSettings::TEST_SIZES)
        {
            auto[listTime, stdListTime] = RemoveFrontCase(size);
            result.append("Size: " + Utils::Parser::NumberToString(size) +
                          ": List: " + Utils::Parser::NumberToString(listTime) + "ns" +
                          "; std::list: " + Utils::Parser::NumberToString(stdListTime) + "ns\n");
        }
        return result;
    }

    TestCaseResult RemoveFrontCase(size_t size)
    {
        auto listTime = RemoveFrontListTest(size);
        auto stdListTime = RemoveFrontStdListTest(size);

        return TestCaseResult {listTime, stdListTime};
    }

    int64_t RemoveFrontListTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            List<ContainerSettings::DataType> testedList;
            FillList(testedList, size);

            Utils::Timer timer;
            timer.Start();

            testedList.RemoveFront();

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }

    int64_t RemoveFrontStdListTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            std::list<ContainerSettings::DataType> testedStdList;
            FillStdList(testedStdList, size);

            Utils::Timer timer;
            timer.Start();

            testedStdList.pop_back();

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }

    std::string RemoveAt()
    {
        std::string result = "RemoveAt test: \n";
        for (const auto& size: ContainerSettings::TEST_SIZES)
        {
            auto[listTime, stdListTime] = RemoveAtCase(size);
            result.append("Size: " + Utils::Parser::NumberToString(size) +
                          ": List: " + Utils::Parser::NumberToString(listTime) + "ns" +
                          "; std::list: " + Utils::Parser::NumberToString(stdListTime) + "ns\n");
        }
        return result;
    }

    TestCaseResult RemoveAtCase(size_t size)
    {
        auto listTime = RemoveAtListTest(size);
        auto stdListTime = RemoveAtStdListTest(size);

        return TestCaseResult {listTime, stdListTime};
    }

    int64_t RemoveAtListTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            List<ContainerSettings::DataType> testedList;
            FillList(testedList, size);
            size_t middle = testedList.Size() / 2;

            Utils::Timer timer;
            timer.Start();

            testedList.RemoveAt(middle);

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }

    int64_t RemoveAtStdListTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            std::list<ContainerSettings::DataType> testedStdList;
            FillStdList(testedStdList, size);

            Utils::Timer timer;
            timer.Start();

            auto middle = testedStdList.begin();
            std::advance(middle, testedStdList.size() / 2);
            testedStdList.erase(middle);

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }

    std::string AccessElements()
    {
        std::string result = "Access test: \n";
        for (const auto& size: ContainerSettings::TEST_SIZES)
        {
            auto[listTime, stdListTime] = AccessCase(size);
            result.append("Size: " + Utils::Parser::NumberToString(size) +
                          ": List: " + Utils::Parser::NumberToString(listTime) + "ns" +
                          "; std::list: " + Utils::Parser::NumberToString(stdListTime) + "ns\n");
        }
        return result;
    }

    TestCaseResult AccessCase(size_t size)
    {
        auto listTime = AccessListTest(size);
        auto stdListTime = AccessStdListTest(size);

        return TestCaseResult {listTime, stdListTime};
    }

    int64_t AccessListTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            List<ContainerSettings::DataType> testedList;
            FillList(testedList, size);
            size_t middle = testedList.Size() / 2;

            Utils::Timer timer;
            timer.Start();

            [[maybe_unused]] volatile auto tmp = testedList[middle];

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }

    int64_t AccessStdListTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            std::list<ContainerSettings::DataType> testedStdList;
            FillStdList(testedStdList, size);

            Utils::Timer timer;
            timer.Start();

            auto middle = testedStdList.begin();
            std::advance(middle, testedStdList.size() / 2);
            [[maybe_unused]] volatile auto tmp = *middle;

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
            auto[listTime, stdListTime] = FindCase(size);
            result.append("Size: " + Utils::Parser::NumberToString(size) +
                          ": List: " + Utils::Parser::NumberToString(listTime) + "ns" +
                          "; std::list: " + Utils::Parser::NumberToString(stdListTime) + "ns\n");
        }
        return result;
    }

    TestCaseResult FindCase(size_t size)
    {
        auto listTime = FindListTest(size);
        auto stdListTime = FindStdListTest(size);

        return TestCaseResult {listTime, stdListTime};
    }

    int64_t FindListTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            List<ContainerSettings::DataType> testedList;
            FillList(testedList, size);

            Utils::Timer timer;
            timer.Start();

            [[maybe_unused]] volatile auto tmp = testedList.Find(
                Utils::GetRandomNumber<ContainerSettings::DataType>(ContainerSettings::MIN_VALUE, ContainerSettings::MAX_VALUE));

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }

    int64_t FindStdListTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            std::list<ContainerSettings::DataType> testedStdList;
            FillStdList(testedStdList, size);

            Utils::Timer timer;
            timer.Start();

            [[maybe_unused]] volatile auto tmp = std::find(testedStdList.cbegin(), testedStdList.cend(),
                                                           Utils::GetRandomNumber<ContainerSettings::DataType>(ContainerSettings::MIN_VALUE,
                                                                                                               ContainerSettings::MAX_VALUE));

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }
}