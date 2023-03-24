#pragma once

#include <string>

#include <glkit/functors/functor_types.hpp>
#include <trailblazer/map/tile.hpp>
#include <trailblazer/map/mapfile.hpp>

#include <trailblazer/game/clock.hpp>
#include <trailblazer/game/constants.hpp>

namespace trailblazer
{

enum class msgGameStateChange_e
{
    BALL_LOST,
    LEVEL_WON
};

enum class msgKeyEvent_e
{
    NONE,
    LEFT,
    RIGHT,
    JUMP
};

enum class msgSoundEvent_e
{
    JUMP,
    BOUNCE,
    LOST,
    GAME_OVER,
    GAME_WON
};

struct msgActualTileType_s
{
    map::TileType_e Type;
};

struct msgBallPosition_s
{
    glkit::functors::point3d_t Position;
};

struct msgBallPositionAndDistance_s : msgBallPosition_s
{
    float Distance;
};

struct msgMapInfo_s
{
    map::MapMetadata_s MapInfo;
};

struct msgRemainingLives_s
{
    int RemainingLives;
};

struct msgRedrawTrigger_s
{
};

} // namespace trailblazer::messaging