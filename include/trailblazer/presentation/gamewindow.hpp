#pragma once

#include <memory>

#include <glkit/window/glwindow.hpp>

#include <messaging/postoffice.hpp>
#include <messaging/recipient.hpp>
#include <trailblazer/game/messagetypes.hpp>

namespace trailblazer::presentation
{

/////////////////////////////////////////////////////////////////////////////////////////
// Represents the main game window.
//
// Inherits from MessageRecipient_i:
// Provides the msgKeyEvent_e message
// It is the initial provider of messages, does not subscribed to anything

class GameWindow_c :
    public glkit::window::GLWindow_i,
    public messaging::MessageRecipient_i
{
public:
    void handleKeypressEvents() override;
    void sendMessage(msg_t message) override {}
    
    GameWindow_c(messaging::PostOffice_c* po);
};

} // namespace trailblazer::presentation