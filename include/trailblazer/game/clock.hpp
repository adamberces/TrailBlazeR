#pragma once

#include <chrono>
#include <stdio.h>


namespace trailblazer
{

/////////////////////////////////////////////////////////////////////////////////////////
/// Provides a singleton class for a global game clock.
/// tick() shall be called in each cycle which updates ElapsedTime,
/// which is the delta time elapsed after the last call

/// Import these for more convenient usage
using std::chrono::steady_clock;
using std::chrono::duration;
using std::chrono::time_point;

class GameClock_c
{
    static float ElapsedTime;
    static time_point<steady_clock> LastTimePoint;

    GameClock_c();

public:
    static GameClock_c& get();
    static float elapsedTime();
    static void tick();
};

} // namespace trailblazer
