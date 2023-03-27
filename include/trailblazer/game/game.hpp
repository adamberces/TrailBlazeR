#pragma once

#include <messaging/postoffice.hpp>

#include <trailblazer/map/mapmanager.hpp>
#include <trailblazer/audio/soundcontrol.hpp>
#include <trailblazer/presentation/gamewindow.hpp>


namespace trailblazer
{

/////////////////////////////////////////////////////////////////////////////////////////
/// The main class which instantiates all components and realizes the main game loop

class Game_c
{   
    messaging::PostOffice_c PostOffice;
    presentation::GameWindow_c GameWindow;
    audio::SoundControl_c SoundControl;
    map::MapManager_c MapManager;
    
public:
    void gameLoop();

    Game_c();
};

} // namespace trailblazer