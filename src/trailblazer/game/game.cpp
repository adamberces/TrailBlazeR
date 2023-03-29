#include <trailblazer/game/game.hpp>

#include <trailblazer/ball/balldrawer.hpp>
#include <trailblazer/ball/ballcontrol.hpp>
#include <trailblazer/game/gamecontrol.hpp>
#include <trailblazer/audio/soundcontrol.hpp>
#include <trailblazer/presentation/gamescene.hpp>
#include <trailblazer/presentation/backgrounddrawer.hpp>
#include <trailblazer/presentation/hud.hpp>


namespace trailblazer
{

/////////////////////////////////////////////////////////////////////////////////////////
// Implementation for Game_c

void Game_c::gameLoop()
{   
    msgGameStateChange_e GameState = msgGameStateChange_e::TILE_SCREEN;

    std::size_t mapIndex = 0;
    std::size_t mapCount = MapManager.mapFiles().size();

    for (; mapIndex < mapCount;)
    {
        bool isLastMap = (mapIndex + 1 == mapCount);
        std::string mapFileName = MapManager.mapFiles().at(mapIndex);

        // Set up a new ball and a scene from the ball and the actual map
        // for the new level's scene
        ball::BallControl_c BallControl(&PostOffice);
        GameControl_c GameControl(&PostOffice, GameState);
        audio::SoundControl_c SoundControl(&PostOffice);

        // First instantiate the drawables.
        // The order is important here, as msgRedrawTrigger calls
        // the draw functions in the order of their subscription 
        // to that message, which happens in the constructor
        presentation::BackgroundDrawer_c Background(&PostOffice);
        ball::BallDrawer_c Ball(&PostOffice);
        map::Map_c Map(&PostOffice, mapFileName);
        
        // Setup game scene from the metadata acquired from the current map
        auto mapData = Map.mapMetaData();
        presentation::GameScene_c GameScene(&PostOffice, mapData.ColorTheme);
        Background.setup("./assets/backgrounds/" + mapData.BackgroundFileName);

        // Setup a background object for the title screen
        // to be rendered in front of the original background
        std::unique_ptr<presentation::BackgroundDrawer_c> TitleScreen;
        if (GameState == msgGameStateChange_e::TILE_SCREEN)
        {
            TitleScreen = std::make_unique<presentation::BackgroundDrawer_c>(&PostOffice);
            TitleScreen->setup("./assets/backgrounds/intro.png");
        }

        // Setup HUD as the topmost drawable component
        presentation::HUD_c HUD(&PostOffice);

        presentation::GameWindow_c::WindowState_e WindowState =
            presentation::GameWindow_c::WindowState_e::OK;

        while (GameState == msgGameStateChange_e::NORMAL ||
               GameState == msgGameStateChange_e::TILE_SCREEN)
        {   
            GameClock_c::get().tick();

            if (TitleScreen)
            {
                TitleScreen->FadeIn(10);
            }
 
            WindowState = GameWindow.updateWindow();
            GameState = GameControl.getGameState(isLastMap);

            if (WindowState ==
                presentation::GameWindow_c::WindowState_e::CLOSING)
            {
                exit(0);
            }
        }

        if (GameState == msgGameStateChange_e::GAME_START)
        {
            GameState = msgGameStateChange_e::NORMAL;
        }
        else if (GameState == msgGameStateChange_e::LEVEL_WON)
        {
            mapIndex++;
        }
        else if (GameState == msgGameStateChange_e::BALL_LOST)
        {
            GameState = msgGameStateChange_e::NORMAL;
        }
        else if (GameState == msgGameStateChange_e::GAME_OVER)
        {
            mapIndex = 0;
            GameState = msgGameStateChange_e::TILE_SCREEN;
        }

        PostOffice.unsubscribeAll();
    }
}

Game_c::Game_c() :
    PostOffice(),
    GameWindow(&PostOffice),
    BackgroundMusic("./assets/audio/music.ogg"),
    MapManager("./assets/maps")
{ 
    //titleScreen();
}

} // namespace trailblazer