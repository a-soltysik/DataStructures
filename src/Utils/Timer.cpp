#include "Timer.h"

namespace Utils
{
    void Timer::Start() noexcept
    {
        start = std::chrono::high_resolution_clock::now();
    }

    void Timer::Stop() noexcept
    {
        stop = std::chrono::high_resolution_clock::now();
    }

    int64_t Timer::GetTimeInNanos() const
    {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
    }

    int64_t Timer::GetTimeInMicros() const
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
    }

    int64_t Timer::GetTimeInMillis() const
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
    }

    int64_t Timer::GetTimeInSeconds() const
    {
        return std::chrono::duration_cast<std::chrono::seconds>(stop - start).count();
    }
}