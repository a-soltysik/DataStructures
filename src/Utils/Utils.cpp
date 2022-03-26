#include "Utils.h"

#include <random>

namespace Utils
{
    std::random_device device;
    std::mt19937 rng(device());

    void SetUtf8()
    {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif
    }

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