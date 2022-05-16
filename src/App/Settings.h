#pragma once

#include "Algorithms/Graphs/Graph.h"

#include <array>

struct ContainerSettings
{
    using DataType = int32_t;
    static constexpr int32_t MAX_VALUE = INT32_MAX;
    static constexpr int32_t MIN_VALUE = INT32_MIN;

    inline static uint32_t NUMBER_OF_TESTS = 500u;

    static constexpr std::array<size_t, 7> TEST_SIZES = {1'000u,
                                                         2'000u,
                                                         5'000u,
                                                         10'000u,
                                                         20'000u,
                                                         50'000u,
                                                         100'000u};
};

struct AlgorithmSettings
{
    static constexpr Graph::Weight MAX_WEIGHT = 0;
    static constexpr Graph::Weight MIN_WEIGHT = 0;

    inline static uint32_t NUMBER_OF_TESTS = 5u;

    static constexpr std::array<uint32_t, 4> GRAPH_ORDERS = {20,
                                                             50,
                                                             100,
                                                             200};

    static constexpr std::array<float, 4> GraphDensities = {0.25f,
                                                            0.50f,
                                                            0.75f,
                                                            0.99f};
};