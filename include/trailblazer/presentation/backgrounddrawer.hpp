#pragma once

#include <memory>
#include <trailblazer/game/constants.hpp>

#include <messaging/postoffice.hpp>
#include <messaging/recipient.hpp>
#include <trailblazer/game/messagetypes.hpp>

#include <trailblazer/pipelines/pipeline_bkg.hpp>


namespace trailblazer::presentation
{

/////////////////////////////////////////////////////////////////////////////////////////
/// Wraps a text pipeline to draw the Head Up Display
//
/// Inherits from MessageRecipient_i:
/// Receives the msgMapData_s message from Map
/// Receives the msgRemainingLives_s message from Game Control
/// Receives the msgRedrawTrigger_s message from Game Scene

class BackgroundDrawer_c : public messaging::MessageRecipient_i
{
    std::unique_ptr<trailblazer::pipelines::BackgroundPipeline_c> PipelinePtr;

public:
    /// We have to call a setup explicitly, where we need to specify the image
    /// because the order of subscriptions matters in Game_c. If we create and subscribe
    /// Background after we know the file name from the Map object, the background will
    /// be drawed over the map which will ultimately hide it.
    void setup(std::string fileName);

    void sendMessage(msg_t m) override;
    
    explicit BackgroundDrawer_c(messaging::PostOffice_c* po);
};

} // namespace trailblazer::presentation