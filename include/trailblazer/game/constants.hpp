#pragma once

namespace trailblazer
{

class Constants_c
{
public:
    static constexpr float BALL_DIAMETER = .25F;

    static constexpr int MAP_WIDTH = 5;
    static constexpr int MAX_DISPLAYED_TILES = 25;
/*
private:
    Constants_c() {}

public:
    static Constants_c& get()
    {
        static Constants_c& instance;
        return instance;
    }*/
};

} // namespace trailblazer