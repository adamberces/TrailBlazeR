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
    else if (isPressed(GLFW_KEY_SPACE))
    {
        e = msgKeyEvent_e::JUMP;
    }

    PO->broadcastMessage<msgKeyEvent_e>(e);
}

GameWindow_c::GameWindow_c(messaging::PostOffice_c* po) :
    GLWindow_i(1024, 768, "TrailBlazeR"),
    MessageRecipient_i(po)
{}

} // namespace trailblazer::presentation