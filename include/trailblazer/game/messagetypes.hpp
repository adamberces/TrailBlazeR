#pragma once

#include <glkit/functors/functor_types.hpp>
#include <trailblazer/map/tile.hpp>

#include <trailblazer/game/clock.hpp>
#include <trailblazer/game/constants.hpp>

namespace trailblazer
{

enum class msgGameStateChange
{
    BALL_LOST,
    LEVEL_WON
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

struct msgBallPositionAndDistance
{
    float Distance;
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