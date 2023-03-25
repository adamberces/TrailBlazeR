#include <trailblazer/game/game.hpp>

#include <trailblazer/ball/balldrawer.hpp>
#include <trailblazer/ball/ballcontrol.hpp>
#include <trailblazer/game/gamecontrol.hpp>
#include <trailblazer/presentation/gamescene.hpp>
#include <trailblazer/presentation/backgrounddrawer.hpp>
#include <trailblazer/presentation/hud.hpp>


namespace trailblazer
{

/////////////////////////////////////////////////////////////////////////////////////////
// Implementation for Game_c

void Game_c::gameLoop()
{   
    size_t mapCount = MapManager.mapFiles().size();
    size_t actualMap = 0;
    for (; actualMap < mapCount;)
    {
        std::string mapFileName = MapManager.mapFiles().at(actualMap);

        // Set up a new ball and a scene from the ball and the actual map
        // for the new level's scene
        ball::BallControl_c BallControl(&PostOffice);
        GameControl_c GameControl(&PostOffice);

        // First instantiate the drawables.
        // The order is important here, as msgRedrawTrigger calls
        // the draw functions in the order of their subscription 
        // to that message, which happens in the constructor
        presentation::BackgroundDrawer_c Background(&PostOffice);
        ball::BallDrawer_c Ball(&PostOffice);
        map::Map_c Map(&PostOffice, mapFileName);
        presentation::HUD_c HUD(&PostOffice);

        // Setup game scene from the metadata acquired from the current map
        auto mapData = Map.mapMetaData();
        presentation::GameScene_c GameScene(&PostOffice, mapData.ColorTheme);
        Background.setup("./assets/backgrounds/" + mapData.BackgroundFileName);

        presentation::GameWindow_c::WindowState_e WindowState =
            presentation::GameWindow_c::WindowState_e::OK;
        
        GameState_e GameState = GameState_e::NORMAL;
        while (GameState ==  GameState_e::NORMAL)
        {   
            GameClock_c::get().tick();
            WindowState = GameWindow.updateWindow();
            GameState = GameControl.getGameState();

            if (WindowState ==
                presentation::GameWindow_c::WindowState_e::CLOSING)
            {
                exit(0);
            }
        }

        if (GameState == GameState_e::LEVEL_WON)
        {
            actualMap++;
        }

        PostOffice.unsubscribeAll();
    }
}

Game_c::Game_c() :
    PostOffice(),
    GameWindow(&PostOffice),
    MapManager("./assets/maps")
{ 
}

} // namespace trailblazer