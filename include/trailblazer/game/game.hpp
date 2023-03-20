#pragma once

#include <trailblazer/game/clock.hpp>
#include <trailblazer/game/gamecontrol.hpp>

#include <trailblazer/ball/ball.hpp>
#include <trailblazer/ball/ballcontrol.hpp>
#include <trailblazer/map/mapmanager.hpp>
#include <trailblazer/presentation/gamewindow.hpp>
#include <trailblazer/presentation/gamescene.hpp>

#include <messaging/postoffice.hpp>

namespace trailblazer
{

class Game_c
{   
    messaging::PostOffice_c PostOffice;
    presentation::GameWindow_c GameWindow;
    map::MapManager_c MapManager;
    GameControl_c GameControl;
    
public:
    void gameLoop()
    {   
        size_t mapCount = MapManager.mapFiles().size();
        size_t actualMap = 0;
        for (; actualMap < mapCount;)
        {
            // Set up a new ball and a scene from the ball and the actual map
            // for the new level's scene
            ball::Ball_c Ball(&PostOffice);
            ball::BallControl_c BallControl(&PostOffice);
            map::Map_c Map(&PostOffice, mapFileName);
            presentation::GameScene_c GameScene(&PostOffice);

            presentation::GameWindow_c::WindowState_e WindowState =
                presentation::GameWindow_c::WindowState_e::OK;
            
            GameState_e GameState = GameState_e::NORMAL;
            while (GameState ==  GameState_e::NORMAL)
            {   
                GameClock_c::get().tick();
                WindowState = GameWindow.updateWindow();
                GameState = GameControl.getGameState();
            }

            if (GameState == GameState_e::LEVEL_WON)
            {
                actualMap++;
            }
        }
    }

    Game_c() :
        PostOffice(),
        GameWindow(&PostOffice),
        MapManager("./assets/maps"),
        GameControl(&PostOffice)
    {
        
    }
};

} // namespace trailblazer