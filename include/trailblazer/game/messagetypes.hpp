#pragma once

#include <string>

#include <glkit/functors/functor_types.hpp>
#include <trailblazer/map/tile.hpp>
#include <trailblazer/map/mapfile.hpp>

#include <trailblazer/game/clock.hpp>
#include <trailblazer/game/constants.hpp>

namespace trailblazer
{

enum class msgBallStateChange_e
{
    UNUSED,
    BALL_LOST,
    LEVEL_WON
};

enum class msgGameState_e
{
    TILE_SCREEN,
    TILE_SCREEN_EXIT,

    NORMAL_GAMEPLAY,

    BALL_LOST,
    BALL_LOST_WAIT,
    GAME_OVER,

    LEVEL_WON,
    LEVEL_WON_WAIT,
    GAME_WON,
};

enum class msgKeyEvent_e
{
    NONE,
    LEFT,
    RIGHT,
    SPACE
};

enum class msgSoundEvent_e
{
    JUMP,
    BOUNCE,
    SPEEDUP,
    BALL_LOST,
    LEVEL_WON,
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

struct msgMapData_s
{
    map::MapMetadata_s Metadata;
    int CurrentTile;
};

struct msgRemainingLives_s
{
    int RemainingLives;
};

struct msgRedrawTrigger_s
{
};

} // namespace trailblazer::messaging