#include "HeapBenchmark.h"
#include "Containers/Heap.h"
#include "Utils/Timer.h"
#include "App/Settings.h"

#include <vector>
#include <algorithm>

namespace HeapBenchmark
{
    struct TestCaseResult
    {
        int64_t heapTime;
        int64_t vectorTime;
    };

    void FillHeap(Heap<ContainerSettings::DataType>& heap, size_t size);
    void FillVectorHeap(std::vector<ContainerSettings::DataType>& vector, size_t size);

    std::string Insert();
    TestCaseResult InsertCase(size_t size);
    int64_t InsertHeapTest(size_t size);
    int64_t InsertVectorHeapTest(size_t size);


    std::string Remove();
    TestCaseResult RemoveCase(size_t size);
    int64_t RemoveHeapTest(size_t size);
    int64_t RemoveVectorHeapTest(size_t size);

    TestCaseResult FindCase(size_t size);
    int64_t FindHeapTest(size_t size);
    int64_t FindVectorHeapTest(size_t size);

    void FillHeap(Heap<ContainerSettings::DataType>& heap, size_t size)
    {
        DynamicArray<ContainerSettings::DataType> array;
        array.Resize(size);
        for (size_t i = 0u; i < size; i++)
        {
            array[i] = Utils::GetRandomNumber<ContainerSettings::DataType>(ContainerSettings::MIN_VALUE, ContainerSettings::MAX_VALUE);
        }
        heap.Assign(array);
    }

    void FillVectorHeap(std::vector<ContainerSettings::DataType>& vector, size_t size)
    {
        vector.resize(size);
        for (size_t i = 0u; i < size; i++)
        {
            vector[i] = Utils::GetRandomNumber<ContainerSettings::DataType>(ContainerSettings::MIN_VALUE, ContainerSettings::MAX_VALUE);
        }
        std::make_heap(vector.begin(), vector.end());
    }

    std::string RunBenchmark()
    {
        return "All benchmarks for Heap:\n" + AddElements() + RemoveElements() + FindElements();
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
            auto[heapTime, vectorTime] = InsertCase(size);
            result.append("Size: " + Utils::Parser::NumberToString(size) +
                          ": Heap: " + Utils::Parser::NumberToString(heapTime) + "ns" +
                          "; std::vector: " + Utils::Parser::NumberToString(vectorTime) + "ns\n");
        }
        return result;
    }

    TestCaseResult InsertCase(size_t size)
    {
        auto heapTime = InsertHeapTest(size);
        auto vectorTime = InsertVectorHeapTest(size);

        return TestCaseResult {heapTime, vectorTime};
    }

    int64_t InsertHeapTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            Heap<ContainerSettings::DataType> testedHeap;
            FillHeap(testedHeap, size);

            Utils::Timer timer;
            timer.Start();

            testedHeap.Insert(Utils::GetRandomNumber<ContainerSettings::DataType>(ContainerSettings::MIN_VALUE, ContainerSettings::MAX_VALUE));

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }

    int64_t InsertVectorHeapTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            std::vector<ContainerSettings::DataType> testedVectorHeap;
            FillVectorHeap(testedVectorHeap, size);

            Utils::Timer timer;
            timer.Start();

            testedVectorHeap.push_back(Utils::GetRandomNumber<ContainerSettings::DataType>(ContainerSettings::MIN_VALUE, ContainerSettings::MAX_VALUE));
            std::push_heap(testedVectorHeap.begin(), testedVectorHeap.end());

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
            auto[heapTime, vectorTime] = RemoveCase(size);
            result.append("Size: " + Utils::Parser::NumberToString(size) +
                          ": Heap: " + Utils::Parser::NumberToString(heapTime) + "ns" +
                          "; std::vector: " + Utils::Parser::NumberToString(vectorTime) + "ns\n");
        }
        return result;
    }

    TestCaseResult RemoveCase(size_t size)
    {
        auto heapTime = RemoveHeapTest(size);
        auto vectorTime = RemoveVectorHeapTest(size);

        return TestCaseResult {heapTime, vectorTime};
    }

    int64_t RemoveHeapTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            Heap<ContainerSettings::DataType> testedHeap;
            FillHeap(testedHeap, size);

            Utils::Timer timer;
            timer.Start();

            testedHeap.Pop();

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }

    int64_t RemoveVectorHeapTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            std::vector<ContainerSettings::DataType> testedVectorHeap;
            FillVectorHeap(testedVectorHeap, size);

            Utils::Timer timer;
            timer.Start();

            testedVectorHeap.pop_back();
            std::pop_heap(testedVectorHeap.begin(), testedVectorHeap.end());

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
            auto[heapTime, vectorTime] = FindCase(size);
            result.append("Size: " + Utils::Parser::NumberToString(size) +
                          ": Heap: " + Utils::Parser::NumberToString(heapTime) + "ns" +
                          "; std::vector: " + Utils::Parser::NumberToString(vectorTime) + "ns\n");
        }
        return result;
    }

    TestCaseResult FindCase(size_t size)
    {
        auto heapTime = FindHeapTest(size);
        auto vectorTime = FindVectorHeapTest(size);

        return TestCaseResult {heapTime, vectorTime};
    }

    int64_t FindHeapTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            Heap<ContainerSettings::DataType> testedHeap;
            FillHeap(testedHeap, size);

            Utils::Timer timer;
            timer.Start();

            [[maybe_unused]] volatile auto tmp = testedHeap.Find(
                Utils::GetRandomNumber<ContainerSettings::DataType>(ContainerSettings::MIN_VALUE, ContainerSettings::MAX_VALUE));

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }

    int64_t FindVectorHeapTest(size_t size)
    {
        int64_t averageTime = 0u;
        for (uint32_t i = 0u; i < ContainerSettings::NUMBER_OF_TESTS; i++)
        {
            std::vector<ContainerSettings::DataType> testedVectorHeap;
            FillVectorHeap(testedVectorHeap, size);

            Utils::Timer timer;
            timer.Start();

            [[maybe_unused]] volatile auto tmp = std::find(testedVectorHeap.cbegin(), testedVectorHeap.cend(),
                                                           Utils::GetRandomNumber<ContainerSettings::DataType>(ContainerSettings::MIN_VALUE,
                                                                                                               ContainerSettings::MAX_VALUE));

            timer.Stop();
            averageTime += timer.GetTimeInNanos();
        }
        return averageTime / ContainerSettings::NUMBER_OF_TESTS;
    }
}