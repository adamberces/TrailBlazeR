#pragma once

#include <chrono>

#include <stdio.h>

namespace trailblazer
{

using std::chrono::steady_clock;
using std::chrono::duration;
using std::chrono::time_point;

class GameClock_c
{

    static time_point<steady_clock> LastTimePoint;
    static float ElapsedTime;

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
        printf("t %f\n", ElapsedTime);
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

}