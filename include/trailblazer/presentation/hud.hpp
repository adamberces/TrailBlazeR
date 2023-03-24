#pragma once

#include <trailblazer/game/constants.hpp>

#include <messaging/postoffice.hpp>
#include <messaging/recipient.hpp>
#include <trailblazer/game/messagetypes.hpp>

#include <trailblazer/pipelines/pipeline_text.hpp>


namespace trailblazer::presentation
{

/////////////////////////////////////////////////////////////////////////////////////////
// Wraps a text pipeline to draw the Head Up Display
//
// Inherits from MessageRecipient_i:
// Receives the msgMapInfo_s message from Map
// Receives the msgRemainingLives_s message from Game Control
// Receives the msgRedrawTrigger_s message from Game Scene

class HUD_c : public messaging::MessageRecipient_i
{
    trailblazer::pipelines::TextPipeline_c Pipeline;

    // Lives info received from Game Control
    int Lives;

    // Map info received from Map
    map::MapMetadata_s MapInfo;

public:
    void draw();
    void setup();

    void sendMessage(msg_t m) override;
    
    HUD_c(messaging::PostOffice_c* po);
};

} // namespace trailblazer::hudpresentation