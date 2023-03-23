#pragma once

#include <chrono>

#include <stdio.h>

namespace trailblazer
{

/////////////////////////////////////////////////////////////////////////////////////////
// Provides a singleton class for a global game clock
// tick() shall be called in each cycle which updates ElapsedTime,
// which is the delta time elapsed after the last call

// Import these for more convenient usage
using std::chrono::steady_clock;
using std::chrono::duration;
using std::chrono::time_point;

class GameClock_c
{
    static float ElapsedTime;
    static time_point<steady_clock> LastTimePoint;

    GameClock_c()
    {
        tick();
    }

public:
    static GameClock_c& get() {
        static GameClock_c gameClock;
        return gameClock;
    }

    static inline float elapsedTime()
    {
        return ElapsedTime;
    }

    static inline void tick()
    {
        auto now = std::chrono::steady_clock::now();
        duration<float> delta =
            std::chrono::duration_cast<duration<float>>(now - LastTimePoint);
        LastTimePoint = now;

        ElapsedTime = delta.count();
    }
};

} // namespace trailblazer
