#pragma once


namespace glkit::functors
{

struct point3d_t
{
    float X = 0.F;
    float Y = 0.F;
    float Z = 0.F;
};

struct scale_t
{
    float X = 1.F;
    float Y = 1.F;
    float Z = 1.F;
};


struct rotation3d_t
{
    float X = 1.F;
    float Y = 0.F;
    float Z = 0.F;
    float Angle = 0.F;
};

struct rgb_t
{
    float R = 1.F;
    float G = 1.F;
    float B = 1.F;
};

} // glkit::functors