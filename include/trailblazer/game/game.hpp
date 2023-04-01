#pragma once

#include <messaging/postoffice.hpp>

#include <trailblazer/audio/music.hpp>
#include <trailblazer/map/mapmanager.hpp>
#include <trailblazer/presentation/gamewindow.hpp>


namespace trailblazer
{

/////////////////////////////////////////////////////////////////////////////////////////
/// The main class which instantiates all components' classes, controls the game scene
/// realizes the main game loop and the change between the title screen and normal gameplay

class Game_c
{   
    messaging::PostOffice_c PostOffice;
    presentation::GameWindow_c GameWindow;
    audio::Music_c BackgroundMusic;
    map::MapManager_c MapManager;
    
public:
    void gameLoop();

    Game_c();
};

} // namespace trailblazer