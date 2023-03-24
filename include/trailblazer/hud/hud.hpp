#pragma once

#include <trailblazer/game/constants.hpp>

#include <messaging/postoffice.hpp>
#include <messaging/recipient.hpp>
#include <trailblazer/game/messagetypes.hpp>

#include <trailblazer/pipelines/pipeline_text.hpp>


namespace trailblazer::hud
{

/////////////////////////////////////////////////////////////////////////////////////////
// Wraps a text pipeline to draw the Head Up Display
//
// Inherits from MessageRecipient_i:
// Receives the msgMapInfo_s message from Map
// Receives the msgRemainingLives_s message from Game Control

class HUD_c : public messaging::MessageRecipient_i
{
    trailblazer::pipelines::TextPipeline_c Pipeline;

public:
    void draw();
    void setup();

    void sendMessage(msg_t m) override;
    
    HUD_c(messaging::PostOffice_c* po);
};

} // namespace trailblazer::hud