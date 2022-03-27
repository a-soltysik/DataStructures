#pragma once

#include <array>

namespace Settings
{
    constexpr int32_t MAX_VALUE = INT32_MAX;
    constexpr int32_t MIN_VALUE = INT32_MIN;

    constexpr uint32_t NUMBER_OF_TESTS = 500u;

    constexpr std::array<size_t, 7> TEST_SIZES = {1'000u, 2'000u, 5'000u, 10'000u, 20'000u, 50'000u, 100'000u};
}