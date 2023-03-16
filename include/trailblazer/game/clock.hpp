#pragma once

#include <chrono>


namespace trailblazer
{

using std::chrono::steady_clock;
using std::chrono::duration;
using std::chrono::time_point;

class GameClock_c
{

    static time_point<steady_clock> LastTimePoint;

    GameClock_c()
    {
        elapsedTime();
    }

public:
    static GameClock_c& get() {
        static GameClock_c gameClock;
        return gameClock;
    }

    static double elapsedTime()
    {
        auto now = std::chrono::steady_clock::now();
        duration<double> delta =
            std::chrono::duration_cast<duration<double>>(now - LastTimePoint);
        LastTimePoint = now;

        return delta.count();
    }
};

}