#include <trailblazer/game/clock.hpp>

namespace trailblazer
{

/////////////////////////////////////////////////////////////////////////////////////////
// Definition for the static class members of GameClock_c

std::chrono::time_point<std::chrono::steady_clock> trailblazer::GameClock_c::LastTimePoint =
    time_point<std::chrono::steady_clock> {};

float trailblazer::GameClock_c::ElapsedTime = 0.F;


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

float GameClock_c::elapsedTime()
{
    return ElapsedTime;
}

void GameClock_c::tick()
{
    auto now = std::chrono::steady_clock::now();
    duration<float> delta =
        std::chrono::duration_cast<duration<float>>(now - LastTimePoint);
    LastTimePoint = now;

    ElapsedTime = delta.count();
}

} // namespace trailblazer

