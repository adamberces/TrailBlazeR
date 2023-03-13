#pragma once

#include <memory>

#include <glkit/window/glwindow.hpp>

#include <game/messaging/postoffice.hpp>
#include <game/messaging/recipient.hpp>
#include <game/messaging/messagetypes.hpp>

namespace trailblazer::presentation
{

class GameWindow_c :
    public glkit::window::GLWindow_i,
    public messaging::MessageRecipient_i

{
public:
    void handleKeypressEvents() override
    {
        messaging::KeyEvent_e e =
           messaging::KeyEvent_e::NONE;

        if (isPressed(GLFW_KEY_A))
        {
            e = messaging::KeyEvent_e::LEFT;
        }
        else if (isPressed(GLFW_KEY_D))
        {
            e = messaging::KeyEvent_e::RIGHT;
        }
        else if (isPressed(GLFW_KEY_SPACE))
        {
            e = messaging::KeyEvent_e::JUMP;
        }

        PO->broadcastMessage<messaging::KeyEvent_e>(e);
    }

    void sendMessage(std::any message) override
    {}

    GameWindow_c(messaging::PostOffice_c* po) :
        GLWindow_i(1024, 768, "TrailBlazeR"),
        MessageRecipient_i(po)
        {}
};

} // namespace trailblazer::presentation