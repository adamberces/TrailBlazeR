#pragma once

#include <string>

#include <glkit/functors/functor_types.hpp>
#include <trailblazer/map/tile.hpp>
#include <trailblazer/map/mapfile.hpp>

#include <trailblazer/game/gameclock.hpp>
#include <trailblazer/game/gameconfig.hpp>


namespace trailblazer
{

enum class msgKeyEvent_e
{
    NONE,
    LEFT,
    RIGHT,
    SPACE
};

enum class msgBallStateChange_e
{
    UNUSED,
    BALL_LOST,
    LEVEL_WON
};

enum class msgGameState_e
{
    TILE_SCREEN,
    NORMAL_GAMEPLAY,

    BALL_LOST,
    BALL_LOST_WAIT,
    GAME_OVER,

    LEVEL_WON,
    LEVEL_WON_WAIT,
    GAME_WON,
};

enum class msgHUDStatus_e
{
    TILE_SCREEN,
    NORMAL_GAMEPLAY,
    
    BALL_LOST,
    GAME_OVER,

    LEVEL_WON,
    GAME_WON,
};


enum class msgSoundEvent_e
{
    NONE,
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

struct msgStageSelectionCheat_s
{
    int MapIndex;
};

} // namespace trailblazer::messaging