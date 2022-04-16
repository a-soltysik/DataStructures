#pragma once

#include <chrono>

namespace Utils
{
    class Timer
    {
    public:
        void Start() noexcept;
        void Stop() noexcept;

        [[nodiscard]] int64_t GetTimeInNanos() const;
        [[nodiscard]] int64_t GetTimeInMicros() const;
        [[nodiscard]] int64_t GetTimeInMillis() const;
        [[nodiscard]] int64_t GetTimeInSeconds() const;

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> start;
        std::chrono::time_point<std::chrono::high_resolution_clock> stop;
    };
}