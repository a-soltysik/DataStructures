#include <array>

namespace Settings
{
    constexpr int32_t MAX_VALUE = INT32_MAX;
    constexpr int32_t MIN_VALUE = INT32_MIN;

    constexpr uint32_t NUMBER_OF_TESTS = 500u;

    constexpr std::array<size_t, 7> ADD_TEST_SIZES    = { 1'000u, 2'500u, 5'000u, 7'500u, 10'000u, 20'000u, 50'000u };

    constexpr std::array<size_t, 6> REMOVE_TEST_SIZES = { 100'000u, 500'000u, 1'000'000u, 5'000'000u, 10'000'000, 50'000'000 };

    constexpr std::array<size_t, 6> ACCESS_TEST_SIZES = { 100'000u, 500'000u, 1'000'000u, 5'000'000u, 10'000'000, 50'000'000 };

    constexpr std::array<size_t, 6> FIND_TEST_SIZES   = { 100'000u, 500'000u, 1'000'000u, 5'000'000u, 10'000'000, 50'000'000 };
}