#pragma once

#include <chrono>
#include <stdio.h>


namespace trailblazer
{

/////////////////////////////////////////////////////////////////////////////////////////
/// Provides a singleton class for a global game clock.
/// tick() shall be called in each cycle which updates TimePeriod,
/// which is the delta time elapsed after the last call

/// Import these for more convenient usage
using std::chrono::steady_clock;
using std::chrono::duration;
using std::chrono::time_point;

class GameClock_c
{
    static time_point<steady_clock> LastTimePoint;

    GameClock_c();

public:
    static constexpr float FPS = 30.F;
    static constexpr float TimePeriodSec = 1.F / FPS;
    static constexpr unsigned int TimePerioduSec =
            static_cast<unsigned int>(TimePeriodSec * 1E6);

    static GameClock_c& get();
    static float elapsedTime();
    static void tick();
};

} // namespace trailblazer
