#pragma once

#include <game/map/map.hpp>
#include <game/ball/ball.hpp>

namespace trailblazer::gfx
{

class Scene_c
{
    size_t ActualMap;
    std::vector<map::Map_c> Maps;
    ball::Ball_c Ball;

    void shiftMap()
    {
        ActualMap++;
        if (ActualMap >= Maps.size())
        {
            ActualMap = 0;
        }
    }

    void update()
    {
        Maps.at(ActualMap).draw();
        Ball.draw();
    }

    Scene_c()
    {
        Maps = { map::Map_c("./assets/maps/1.map") };
    }
};

} // namespace trailblazer::gfx