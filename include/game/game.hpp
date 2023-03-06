#include <game/gfx/gamewindow.hpp>
#include <game/map/mapmanager.hpp>
#include <game/ball/ball.hpp>

namespace trailblazer
{

class Game
{
    gfx::GameWindow_c GameWindow;
    map::MapManager_c MapManager;
    std::shared_ptr<ball::Ball> Ball;

public:
    void gameLoop()
    {
        GameWindow.setMap(MapManager.getNextMap());
        GameWindow.setBall(Ball);

        gfx::GameWindow_c::WindowState_e WindowState =
            gfx::GameWindow_c::WindowState_e::OK;
        while (WindowState == gfx::GameWindow_c::WindowState_e::OK)
        {   
            WindowState = GameWindow.updateWindow();
        }
    }

    Game() :
        GameWindow(640, 480, "Test"),
        MapManager("./assets/maps"),
        Ball(std::make_shared<ball::Ball>())
    {}
};

} // namespace trailblazer