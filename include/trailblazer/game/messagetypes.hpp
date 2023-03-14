#pragma once

#include <glkit/functors/functor_types.hpp>
#include <trailblazer/map/tile.hpp>

namespace trailblazer
{

enum class msgGameState
{
    MAIN_MENU,
    LEVEL_START,
    LEVEL_RUNNING,
    LEVEL_END,
    GAME_END,
    GAME_OVER
};

enum class msgKeyEvent
{
    NONE,
    LEFT,
    RIGHT,
    JUMP
};

enum class msgBallEvent
{
    ROLLING,
    JUMPING,
    FALLING,
    FALLING_OFF
};

struct msgActualTypeType
{
    map::TileType_e Type;
};

// Create a strong type for wrapping the Ball position
// so it will have an unique signature when dealing with 
// message types, if we may want to use another point3d_t
// in the future...

struct msgBallPosition
{
    glkit::functors::point3d_t Position;
};

struct msgRedrawTrigger
{
};



} // namespace trailblazer::messaging