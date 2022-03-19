#include "Utils.h"

#include <random>

namespace Utils
{
    std::random_device device;
    std::mt19937 rng(device());

    int32_t GetRandomInt(int32_t from, int32_t to)
    {
        std::uniform_int_distribution<int32_t> distribution(from, to);
        return distribution(rng);
    }

    std::filesystem::path GetPathFromResources(const std::filesystem::path& path)
    {
        return std::filesystem::path("Resources") / path;
    }
}