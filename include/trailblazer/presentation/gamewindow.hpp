#pragma once

#include <memory>

#include <glkit/window/glwindow.hpp>

#include <messaging/postoffice.hpp>
#include <messaging/recipient.hpp>
#include <trailblazer/game/messagetypes.hpp>

namespace trailblazer::presentation
{

class GameWindow_c :
    public glkit::window::GLWindow_i,
    public messaging::MessageRecipient_i

{
public:
    void handleKeypressEvents() override
    {
        msgKeyEvent e =
           msgKeyEvent::NONE;

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

    void sendMessage(std::any message) override
    {}

    GameWindow_c(messaging::PostOffice_c* po) :
        GLWindow_i(1024, 768, "TrailBlazeR"),
        MessageRecipient_i(po)
    {}
};

} // namespace trailblazer::presentation