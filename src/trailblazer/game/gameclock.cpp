#include <thread>
#include <trailblazer/game/gameclock.hpp>

namespace trailblazer
{

/////////////////////////////////////////////////////////////////////////////////////////
// Definition for the static class members of GameClock_c

std::chrono::time_point<std::chrono::steady_clock> trailblazer::GameClock_c::LastTimePoint =
    time_point<std::chrono::steady_clock> {};

/////////////////////////////////////////////////////////////////////////////////////////
// Implementation for GameClock_c

GameClock_c::GameClock_c()
{
    tick();
}

GameClock_c& GameClock_c::get()
{
    static GameClock_c gameClock;
    return gameClock;
}


void GameClock_c::tick()
{
    constexpr auto period = std::chrono::microseconds(TimePerioduSec);

    auto now = std::chrono::steady_clock::now();
    duration<float> delta =
        std::chrono::duration_cast<duration<float>>(now - LastTimePoint);
    LastTimePoint = now;

    if (delta < period)
    {
        auto wait = period - delta;
        std::this_thread::sleep_for(wait);
    }

}

} // namespace trailblazer

