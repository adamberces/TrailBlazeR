#include <trailblazer/presentation/gamewindow.hpp>


namespace trailblazer::presentation
{

/////////////////////////////////////////////////////////////////////////////////////////
// GameWindow_c implementation

void GameWindow_c::handleKeypressEvents()
{
    msgKeyEvent_e e =  msgKeyEvent_e::NONE;

    if (isPressed(GLFW_KEY_A) ||
        isPressed(GLFW_KEY_LEFT))
    {
        e = msgKeyEvent_e::LEFT;
    }
    else if (isPressed(GLFW_KEY_D) ||
             isPressed(GLFW_KEY_RIGHT))
    {
        e = msgKeyEvent_e::RIGHT;
    }
    else if (isPressed(GLFW_KEY_SPACE) ||
             isPressed(GLFW_KEY_LEFT_CONTROL))
    {
        e = msgKeyEvent_e::SPACE;
    }

    PO->broadcastMessage<msgKeyEvent_e>(e);

    // Polling the number keys from 1 to 9 for an undocumented
    // feature ("cheat"), which allows the user to secretly select
    // the stage number from the title screen.
    for (int key = GLFW_KEY_1; key <= GLFW_KEY_9; key++)
    {
        if (isPressed(key))
        {
            PO->broadcastMessage<msgStageSelectionCheat_s>({ key - GLFW_KEY_0 });
        }
    }
}

GameWindow_c::GameWindow_c(messaging::PostOffice_c* po) :
    GLWindow_i(Constants_s::WINDOW_WIDTH,
        Constants_s::WINDOW_HEIGHT, "TrailBlazeR"),
    MessageRecipient_i(po)
{}

} // namespace trailblazer::presentation