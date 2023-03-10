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
    map::MapManager_c MapManager;
    
public:
    void gameLoop()
    {   
        
        while (!(MapManager.isLastMap()))
        {
            // Set up a new ball and a scene from the ball and the actual map
            // for the new level's scene
            ball::Ball_c Ball(PostOffice);
            presentation::GameScene_c GameScene(MapManager.getNextMap(), Ball);

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
        MapManager("./assets/maps"),
    {
        
    }
};

} // namespace trailblazer