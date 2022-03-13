#pragma once

#include <chrono>

namespace Utils
{
    class Timer
    {
    public:
        void Start() noexcept;
        void Stop() noexcept;

        [[nodiscard]] uint64_t GetTimeInNanos() const;
        [[nodiscard]] uint64_t GetTimeInMicros() const;
        [[nodiscard]] uint64_t GetTimeInMillis() const;
        [[nodiscard]] uint64_t GetTimeInSeconds() const;

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> start;
        std::chrono::time_point<std::chrono::high_resolution_clock> stop;
    };
}