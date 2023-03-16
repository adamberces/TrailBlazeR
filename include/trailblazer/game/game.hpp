#pragma once

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
    
public:
    void gameLoop()
    {   
        
        for (const std::string& mapFileName : MapManager.mapFiles())
        {
            // Set up a new ball and a scene from the ball and the actual map
            // for the new level's scene
            ball::Ball_c Ball(&PostOffice);
            ball::BallControl_c BallControl(&PostOffice);
            map::Map_c Map(&PostOffice, mapFileName);
            presentation::GameScene_c GameScene(&PostOffice);

            presentation::GameWindow_c::WindowState_e WindowState =
                presentation::GameWindow_c::WindowState_e::OK;
            
            while (WindowState == presentation::GameWindow_c::WindowState_e::OK)
            {   
                WindowState = GameWindow.updateWindow();
            }
        }
    }

    Game_c() :
        PostOffice(),
        GameWindow(&PostOffice),
        MapManager("./assets/maps")
    {
        
    }
};

} // namespace trailblazer