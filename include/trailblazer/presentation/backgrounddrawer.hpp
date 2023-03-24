#pragma once

#include <trailblazer/game/constants.hpp>

#include <messaging/postoffice.hpp>
#include <messaging/recipient.hpp>
#include <trailblazer/game/messagetypes.hpp>

#include <trailblazer/pipelines/pipeline_bkg.hpp>


namespace trailblazer::presentation
{

/////////////////////////////////////////////////////////////////////////////////////////
// Wraps a text pipeline to draw the Head Up Display
//
// Inherits from MessageRecipient_i:
// Receives the msgMapInfo_s message from Map
// Receives the msgRemainingLives_s message from Game Control
// Receives the msgRedrawTrigger_s message from Game Scene

class BackgroundDrawer_c : public messaging::MessageRecipient_i
{
    trailblazer::pipelines::BackgroundPipeline_c Pipeline;

public:
    void sendMessage(msg_t m) override;
    
    BackgroundDrawer_c(messaging::PostOffice_c* po, std::string fileName);
};

} // namespace trailblazer::presentation