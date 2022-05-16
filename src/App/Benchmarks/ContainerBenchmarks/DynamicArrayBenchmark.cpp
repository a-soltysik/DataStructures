#include "App/Benchmarks/ContainerBenchmarks/DynamicArrayBenchmark.h"
#include "Containers/DynamicArray.h"
#include "Utils/Utils.h"
#include "Utils/Timer.h"
#include "App/Settings.h"

#include <vector>
#include <algorithm>

namespace DynamicArrayBenchmark
{
    struct TestCaseResult
    {
        int64_t dynamicArrayTime;
        int64_t stdVectorTime;
    };

    void FillArray(DynamicArray<ContainerSettings::DataType>& array, size_t size);
    void FillVector(std::vector<ContainerSettings::DataType>& vector, size_t size);

    std::string PushBack();
    TestCaseResult PushBackCase(size_t size);
    int64_t PushBackDynamicArrayTest(size_t size);
    int64_t PushBackVectorTest(size_t size);

    std::string PushFront();
    TestCaseResult PushFrontCase(size_t size);
    int64_t PushFrontDynamicArrayTest(size_t size);
    int64_t PushFrontVectorTest(size_t size);

    std::string Insert();
    TestCaseResult InsertCase(size_t size);
    int64_t InsertDynamicArrayTest(size_t size);
    int64_t InsertVectorTest(size_t size);

    std::string RemoveBack();
    TestCaseResult RemoveBackCase(size_t size);
    int64_t RemoveBackDynamicArrayTest(size_t size);
    int64_t RemoveBackVectorTest(size_t size);

    std::string RemoveFront();
    TestCaseResult RemoveFrontCase(size_t size);
    int64_t RemoveFrontDynamicArrayTest(size_t size);
    int64_t RemoveFrontVectorTest(size_t size);

    std::string RemoveAt();
    TestCaseResult RemoveAtCase(size_t size);
    int64_t RemoveAtDynamicArrayTest(size_t size);
    int64_t RemoveAtVectorTest(size_t size);

    TestCaseResult AccessCase(size_t size);
    int64_t AccessDynamicArrayTest(size_t size);
    int64_t AccessVectorTest(size_t size);

    TestCaseResult FindCase(size_t size);
    int64_t FindDynamicArrayTest(size_t size);
    int64_t FindVectorTest(size_t size);


    void FillArray(DynamicArray<ContainerSettings::DataType>& array, size_t size)
    {
        array.Resize(size);
        for (size_t i = 0u; i < size; i++)
        {
            array[i] = Utils::GetRandomNumber<ContainerSettings::DataType>(ContainerSettings::MIN_VALUE, ContainerSettings::MAX_VALUE);
        }
    }

    void FillVector(std::vector<ContainerSettings::DataType>& vector, size_t size)
    {
        vector.resize(size);
        for (size_t i = 0u; i < size; i++)
        {
            vector[i] = Utils::GetRandomNumber<ContainerSettings::DataType>(ContainerSettings::MIN_VALUE, ContainerSettings::MAX_VALUE);
        }
    }

    std::string RunBenchmark()
    {
        return "All benchmarks for DynamicArray:\n" +
               AddElements() +
               RemoveElements() +
               AccessElements() +
               FindElements();
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
            auto[dynamicArrayTime, stdVectorTime] = PushBackCase(size);
            result.append("Size: " + std::to_string(size) +
                          ": DynamicArray: " + std::to_string(dynamicArrayTime) + "ns"
                                                                                  "; std::vector: " +
                          std::to_string(stdVectorTime) + "ns\n");
        }
        return result;
    }

    TestCaseResult PushBackCase(size_t size)
    {
        auto dynamicArrayTime = PushBackDynamicArrayTest(size);
        auto stdVectorTime = PushBackVectorTest(size);

        return TestCaseResult {dynamicArrayTime, stdVectorTime};
    }

    int64_t PushBackDynamicArrayTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            DynamicArray<ContainerSettings::DataType> testedArray;
            FillArray(testedArray, size);

            Utils::Timer timer;
            timer.Start();

            testedArray.PushBack(Utils::GetRandomNumber<ContainerSettings::DataType>(ContainerSettings::MIN_VALUE, ContainerSettings::MAX_VALUE));

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }

    int64_t PushBackVectorTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            std::vector<ContainerSettings::DataType> testedVector;
            FillVector(testedVector, size);

            Utils::Timer timer;
            timer.Start();

            testedVector.push_back(Utils::GetRandomNumber<ContainerSettings::DataType>(ContainerSettings::MIN_VALUE, ContainerSettings::MAX_VALUE));

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
            auto[dynamicArrayTime, stdVectorTime] = PushFrontCase(size);
            result.append("Size: " + std::to_string(size) +
                          ": DynamicArray: " + std::to_string(dynamicArrayTime) + "ns" +
                          "; std::vector: " + std::to_string(stdVectorTime) + "ns\n");
        }
        return result;
    }

    TestCaseResult PushFrontCase(size_t size)
    {
        auto dynamicArrayTime = PushFrontDynamicArrayTest(size);
        auto stdVectorTime = PushFrontVectorTest(size);

        return TestCaseResult {dynamicArrayTime, stdVectorTime};
    }

    int64_t PushFrontDynamicArrayTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            DynamicArray<ContainerSettings::DataType> testedArray;
            FillArray(testedArray, size);

            Utils::Timer timer;
            timer.Start();

            testedArray.PushFront(Utils::GetRandomNumber<ContainerSettings::DataType>(ContainerSettings::MIN_VALUE, ContainerSettings::MAX_VALUE));

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }

    int64_t PushFrontVectorTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            std::vector<ContainerSettings::DataType> testedVector;
            FillVector(testedVector, size);

            Utils::Timer timer;
            timer.Start();

            testedVector.insert(testedVector.cbegin(), Utils::GetRandomNumber<ContainerSettings::DataType>(ContainerSettings::MIN_VALUE, ContainerSettings::MAX_VALUE));

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
            auto[dynamicArrayTime, stdVectorTime] = InsertCase(size);
            result.append("Size: " + std::to_string(size) +
                          ": DynamicArray: " + std::to_string(dynamicArrayTime) + "ns" +
                          "; std::vector: " + std::to_string(stdVectorTime) + "ns\n");
        }
        return result;
    }

    TestCaseResult InsertCase(size_t size)
    {
        auto dynamicArrayTime = InsertDynamicArrayTest(size);
        auto stdVectorTime = InsertVectorTest(size);

        return TestCaseResult {dynamicArrayTime, stdVectorTime};
    }

    int64_t InsertDynamicArrayTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            DynamicArray<ContainerSettings::DataType> testedArray;
            FillArray(testedArray, size);
            size_t middle = testedArray.Size() / 2;

            Utils::Timer timer;
            timer.Start();

            testedArray.Insert(middle, Utils::GetRandomNumber<ContainerSettings::DataType>(ContainerSettings::MIN_VALUE, ContainerSettings::MAX_VALUE));

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }

    int64_t InsertVectorTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            std::vector<ContainerSettings::DataType> testedVector;
            FillVector(testedVector, size);
            auto middle = testedVector.cbegin() + testedVector.size() / 2;

            Utils::Timer timer;
            timer.Start();

            testedVector.insert(middle, Utils::GetRandomNumber<ContainerSettings::DataType>(ContainerSettings::MIN_VALUE, ContainerSettings::MAX_VALUE));

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
            auto[dynamicArrayTime, stdVectorTime] = RemoveBackCase(size);
            result.append("Size: " + std::to_string(size) +
                          ": DynamicArray: " + std::to_string(dynamicArrayTime) + "ns" +
                          "; std::vector: " + std::to_string(stdVectorTime) + "ns\n");
        }
        return result;
    }

    TestCaseResult RemoveBackCase(size_t size)
    {
        auto dynamicArrayTime = RemoveBackDynamicArrayTest(size);
        auto stdVectorTime = RemoveBackVectorTest(size);

        return TestCaseResult {dynamicArrayTime, stdVectorTime};
    }

    int64_t RemoveBackDynamicArrayTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            DynamicArray<ContainerSettings::DataType> testedArray;
            FillArray(testedArray, size);

            Utils::Timer timer;
            timer.Start();

            testedArray.RemoveBack();

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }

    int64_t RemoveBackVectorTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            std::vector<ContainerSettings::DataType> testedVector;
            FillVector(testedVector, size);

            Utils::Timer timer;
            timer.Start();

            testedVector.pop_back();

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
            auto[dynamicArrayTime, stdVectorTime] = RemoveFrontCase(size);
            result.append("Size: " + std::to_string(size) +
                          ": DynamicArray: " + std::to_string(dynamicArrayTime) + "ns" +
                          "; std::vector: " + std::to_string(stdVectorTime) + "ns\n");
        }
        return result;
    }

    TestCaseResult RemoveFrontCase(size_t size)
    {
        auto dynamicArrayTime = RemoveFrontDynamicArrayTest(size);
        auto stdVectorTime = RemoveFrontVectorTest(size);

        return TestCaseResult {dynamicArrayTime, stdVectorTime};
    }

    int64_t RemoveFrontDynamicArrayTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            DynamicArray<ContainerSettings::DataType> testedArray;
            FillArray(testedArray, size);

            Utils::Timer timer;
            timer.Start();

            testedArray.RemoveFront();

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }

    int64_t RemoveFrontVectorTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            std::vector<ContainerSettings::DataType> testedVector;
            FillVector(testedVector, size);

            Utils::Timer timer;
            timer.Start();

            testedVector.erase(testedVector.cbegin());

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
            auto[dynamicArrayTime, stdVectorTime] = RemoveAtCase(size);
            result.append("Size: " + std::to_string(size) +
                          ": DynamicArray: " + std::to_string(dynamicArrayTime) + "ns" +
                          "; std::vector: " + std::to_string(stdVectorTime) + "ns\n");
        }
        return result;
    }

    TestCaseResult RemoveAtCase(size_t size)
    {
        auto dynamicArrayTime = RemoveAtDynamicArrayTest(size);
        auto stdVectorTime = RemoveAtVectorTest(size);

        return TestCaseResult {dynamicArrayTime, stdVectorTime};
    }

    int64_t RemoveAtDynamicArrayTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            DynamicArray<ContainerSettings::DataType> testedArray;
            FillArray(testedArray, size);
            size_t middle = testedArray.Size() / 2;

            Utils::Timer timer;
            timer.Start();

            testedArray.RemoveAt(middle);

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }

    int64_t RemoveAtVectorTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            std::vector<ContainerSettings::DataType> testedVector;
            FillVector(testedVector, size);
            auto middle = testedVector.cbegin() + testedVector.size() / 2;

            Utils::Timer timer;
            timer.Start();

            testedVector.erase(middle);

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
            auto[dynamicArrayTime, stdVectorTime] = AccessCase(size);
            result.append("Size: " + std::to_string(size) +
                          ": DynamicArray: " + std::to_string(dynamicArrayTime) + "ns" +
                          "; std::vector: " + std::to_string(stdVectorTime) + "ns\n");
        }
        return result;
    }

    TestCaseResult AccessCase(size_t size)
    {
        auto dynamicArrayTime = AccessDynamicArrayTest(size);
        auto stdVectorTime = AccessVectorTest(size);

        return TestCaseResult {dynamicArrayTime, stdVectorTime};
    }

    int64_t AccessDynamicArrayTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            DynamicArray<ContainerSettings::DataType> testedArray;
            FillArray(testedArray, size);
            size_t middle = testedArray.Size() / 2;

            Utils::Timer timer;
            timer.Start();

            [[maybe_unused]] volatile auto tmp = testedArray[middle];

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }

    int64_t AccessVectorTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            std::vector<ContainerSettings::DataType> testedVector;
            FillVector(testedVector, size);
            size_t middle = testedVector.size() / 2;

            Utils::Timer timer;
            timer.Start();

            [[maybe_unused]] volatile auto tmp = testedVector[middle];

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
            auto[dynamicArrayTime, stdVectorTime] = FindCase(size);
            result.append("Size: " + std::to_string(size) +
                          ": DynamicArray: " + std::to_string(dynamicArrayTime) + "ns" +
                          "; std::vector: " + std::to_string(stdVectorTime) + "ns\n");
        }
        return result;
    }

    TestCaseResult FindCase(size_t size)
    {
        auto dynamicArrayTime = FindDynamicArrayTest(size);
        auto stdVectorTime = FindVectorTest(size);

        return TestCaseResult {dynamicArrayTime, stdVectorTime};
    }

    int64_t FindDynamicArrayTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            DynamicArray<ContainerSettings::DataType> testedArray;
            FillArray(testedArray, size);

            Utils::Timer timer;
            timer.Start();

            [[maybe_unused]] volatile auto tmp = testedArray.Find(
                Utils::GetRandomNumber<ContainerSettings::DataType>(ContainerSettings::MIN_VALUE, ContainerSettings::MAX_VALUE));

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }

    int64_t FindVectorTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            std::vector<ContainerSettings::DataType> testedVector;
            FillVector(testedVector, size);

            Utils::Timer timer;
            timer.Start();

            [[maybe_unused]] volatile auto tmp = std::find(testedVector.cbegin(), testedVector.cend(),
                                                           Utils::GetRandomNumber<ContainerSettings::DataType>(ContainerSettings::MIN_VALUE,
                                                                                                               ContainerSettings::MAX_VALUE));

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }
}