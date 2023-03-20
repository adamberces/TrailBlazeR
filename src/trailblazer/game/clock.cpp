#include <trailblazer/game/clock.hpp>

std::chrono::time_point<std::chrono::steady_clock> trailblazer::GameClock_c::LastTimePoint =
    time_point<std::chrono::steady_clock> {};

float trailblazer::GameClock_c::ElapsedTime = 0.F;
