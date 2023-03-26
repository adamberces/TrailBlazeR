#pragma once

#include <unordered_map>
#include <glkit/functors/functor_types.hpp>


namespace trailblazer::map
{

/////////////////////////////////////////////////////////////////////////////////////////
/// Type definitions and constants for tiles.
/// Tiles are the building blocks of the game map.
/// Each tile has a color and may have a special function


/// Defining the types of tiles of the game:
/// special types includes tiles which speeds up
/// or slows down the ball. Also we need to define a
/// type which marks the end of a map and the "gap", which
/// stands for the absence of a tile where the ball can fall off

enum class TileType_e
{
    GAP,
    NORMAL,
    FINISH,
    SPEEDUP,
    SLOWDOWN,
};


/// Setting up a classic CGA color palette
/// for an oldschool look and feel

enum class Color_e
{
    NONE,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHT_GRAY,
    DARK_GRAY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_CYAN,
    LIGHT_RED,
    LIGHT_MAGENTA,
    LIGHT_YELLOW,
    WHITE,

    COLOR_COUNT
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"

static glkit::functors::rgb_t ColorCodes[] = 
{
    { 0.F, 0.F, 0.F },
    { 0.F, 0.F, 0.667F },
    { 0.F, 0.667F, 0.F },
    { 0.F, 0.667F, 0.667F },
    { 0.667F, 0.F, 0.F },
    { 0.667F, 0.F, 0.667F },
    { 0.667F, 0.333F, 0.F },
    { 0.667F, 0.667F, 0.667F },
    { 0.333F, 0.333F, 0.333F },
    { 0.333F, 0.333F, 1.F },
    { 0.333F, 1.F, 0.333F },
    { 0.333F, 1.F, 1.F },
    { 1.F, 0.333F, 0.333F },
    { 1.F, 0.333F, 1.F },
    { 1.F, 1.F, 0.333F },
    { 1.F, 1.F, 1.F }
};

#pragma GCC diagnostic pop

/// Mapping some of the colors to have a special function
/// A map file contains only color information and the type
/// is implied from it's color using this mapping.

static std::unordered_map<Color_e, TileType_e> SpecialRules =
{
    { Color_e::NONE, TileType_e::GAP },
    { Color_e::LIGHT_GREEN, TileType_e::SPEEDUP },
    { Color_e::LIGHT_RED, TileType_e::SLOWDOWN },
    { Color_e::DARK_GRAY, TileType_e::FINISH },
    { Color_e::WHITE, TileType_e::FINISH }
};


/// Pack type and color into a struct

struct Tile_s
{
    TileType_e Type;
    Color_e Color;
};

} /// trailblazer::map
