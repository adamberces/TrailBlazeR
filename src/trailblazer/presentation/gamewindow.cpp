#include <trailblazer/presentation/gamewindow.hpp>


namespace trailblazer::presentation
{

/////////////////////////////////////////////////////////////////////////////////////////
// GameWindow_c implementation

void GameWindow_c::handleKeypressEvents()
{
    msgKeyEvent e =  msgKeyEvent::NONE;

    if (isPressed(GLFW_KEY_A) ||
        isPressed(GLFW_KEY_LEFT))
    {
        e = msgKeyEvent::LEFT;
    }
    else if (isPressed(GLFW_KEY_D) ||
                isPressed(GLFW_KEY_RIGHT))
    {
        e = msgKeyEvent::RIGHT;
    }
    else if (isPressed(GLFW_KEY_SPACE))
    {
        e = msgKeyEvent::JUMP;
    }

    PO->broadcastMessage<msgKeyEvent>(e);
}

GameWindow_c::GameWindow_c(messaging::PostOffice_c* po) :
    GLWindow_i(1024, 768, "TrailBlazeR"),
    MessageRecipient_i(po)
{}

} // namespace trailblazer::presentation