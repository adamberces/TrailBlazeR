#include <game/gfx/gamewindow.hpp>

namespace trailblazer
{

class Game
{
    gfx::GameWindow_c GameWindow;
    gfx::Scene_c GameScene;

public:
    void gameLoop()
    {
        gfx::GameWindow_c::WindowState_e WindowState =
            gfx::GameWindow_c::WindowState_e::OK;
        while (WindowState == gfx::GameWindow_c::WindowState_e::OK)
        {   
            GameScene.update();
            WindowState = GameWindow.updateWindow();
        }
    }

    Game() :
        GameWindow(640, 480, "Test")
    {}
};

} // namespace trailblazer