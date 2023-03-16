#include <trailblazer/game/clock.hpp>

trailblazer::time_point<trailblazer::steady_clock> trailblazer::GameClock_c::LastTimePoint =
    time_point<trailblazer::steady_clock> {};
