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

template<typename T>
struct Size2D_t
{
    T Width;
    T Height;
};

using fSize2D_t = Size2D_t<float>;
using uSize2D_t = Size2D_t<unsigned int>;
