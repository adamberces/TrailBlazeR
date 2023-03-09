#pragma once

#include <game/ball/ball.hpp>
#include <game/map/mapmanager.hpp>
#include <game/presentation/gamewindow.hpp>
#include <game/presentation/gamescene.hpp>
#include <game/messaging/postoffice.hpp>


namespace trailblazer
{

class Game
{   
    messaging::PostOffice_c PostOffice;
    presentation::GameWindow_c GameWindow;

    ball::Ball_c Ball;
    map::MapManager_c MapManager;
    presentation::GameScene_c GameScene;

public:
    void gameLoop()
    {   
        
        while (!(MapManager.isLastMap()))
        {
            GameScene.setMap(MapManager.getNextMap());

            presentation::GameWindow_c::WindowState_e WindowState =
                presentation::GameWindow_c::WindowState_e::OK;
            
            while (WindowState == presentation::GameWindow_c::WindowState_e::OK)
            {   
                WindowState = GameWindow.updateWindow(&GameScene);
                
            }
        }
    }

    Game() :
        PostOffice(),
        GameWindow(&PostOffice),
        Ball(&PostOffice),
        MapManager("./assets/maps"),
        GameScene(&Ball)
    {
        
    }
};

} // namespace trailblazer