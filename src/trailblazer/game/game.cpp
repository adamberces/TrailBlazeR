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
    msgGameState_e GameState = msgGameState_e::TILE_SCREEN;
    std::size_t mapCount = MapManager.mapFiles().size();

    while (true)
    {
        // GameControl handles the main state machine of the game
        GameControl_c GameControl(&PostOffice, GameState, mapCount);

        // Set up new controller classes for each stage
        ball::BallControl_c BallControl(&PostOffice);
        audio::SoundControl_c SoundControl(&PostOffice);

        // Set up new drawables for each stage
        // The order is important here, as msgRedrawTrigger calls
        // the draw functions in the order of their subscription 
        // to that message, which happens in the constructor
        presentation::BackgroundDrawer_c Background(&PostOffice);
        ball::BallDrawer_c Ball(&PostOffice);
        std::string mapFileName = MapManager.mapFiles().at(GameControl.mapIndex());
        map::Map_c Map(&PostOffice, mapFileName);
        
        // Setup game scene from the color theme metadata acquired from the
        // current mapfile and also load the background image
        auto mapData = Map.mapMetaData();
        presentation::GameScene_c GameScene(&PostOffice, mapData.ColorTheme);
        Background.setup("./assets/backgrounds/" + mapData.BackgroundFileName);

        // Setup a background object for the title screen
        // to be rendered in front of the original background
        std::unique_ptr<presentation::BackgroundDrawer_c> TitleScreen;
        if (GameState == msgGameState_e::TILE_SCREEN)
        {
            TitleScreen = std::make_unique<presentation::BackgroundDrawer_c>(&PostOffice);
            TitleScreen->setup("./assets/backgrounds/intro.png");
        }

        // Setup HUD as the topmost drawable component
        presentation::HUD_c HUD(&PostOffice);

        // This inner loop handles the main update-redraw cycle
        // of a scene (either the title screen or a stage)
        while (GameState == msgGameState_e::NORMAL_GAMEPLAY ||
               GameState == msgGameState_e::TILE_SCREEN)
        {   
            GameClock_c::get().tick();

            // Shift the fade in animation for the title screen,
            // if we have it anyways...
            if (TitleScreen)
            {
                TitleScreen->FadeIn(10);
            }
 
            // This one invokes keyboard polling from the game window,
            // which starts the casade of messages and events supervised
            // by PostOffice, which ultimately ends up in the redraw of drawables
            auto WindowState = GameWindow.updateWindow();

            // Updates the game's main state machine and returns the actual state
            GameState = GameControl.updateGameState();

            // Handle the keypress of ESC
            if (WindowState ==
                presentation::GameWindow_c::WindowState_e::CLOSING)
            {
                exit(0);
            }
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
}

} // namespace trailblazer