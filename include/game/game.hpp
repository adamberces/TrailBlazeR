#include <game/gfx/gamewindow.hpp>

namespace trailblazer
{

class Game
{
    gfx::GameWindow_c GameWindow;

public:
    void gameLoop()
    {
        gfx::GameWindow_c::WindowState_e WindowState =
            gfx::GameWindow_c::WindowState_e::OK;
        while (WindowState == gfx::GameWindow_c::WindowState_e::OK)
        {
            WindowState = GameWindow.updateWindow();
        }
    }

    Game() :
        GameWindow(640, 480, "Test")
    {}
};

} // namespace trailblazer