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

enum class msgBallEvent
{
    ROLLING,
    JUMPING,
    FALLING,
    FALLING_OFF
};

enum class msgKeyEvent
{
    NONE,
    LEFT,
    RIGHT,
    JUMP
};

struct msgActualTileType
{
    map::TileType_e Type;
};

struct msgBallPositionAndSpeed
{
    double Speed;
    glkit::functors::point3d_t Position;
};

struct msgBallPosition
{
    glkit::functors::point3d_t Position;
};

struct msgRedrawTrigger
{
};



} // namespace trailblazer::messaging