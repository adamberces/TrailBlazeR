#pragma once

enum TileType_e
{
    NORMAL,
    FINISH,
    SPEEDUP,
    SPEEDDOWN,
};

enum Color_e
{
    BLACK,
    WHITE,
    RED,
    GREEN,
    BLUE,
};

struct Tile_t
{
    TileType_e Type;
    Color_e Color;
};
