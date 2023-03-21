#pragma once

#include <trailblazer/game/constants.hpp>

#include <messaging/postoffice.hpp>
#include <messaging/recipient.hpp>
#include <trailblazer/game/messagetypes.hpp>

#include <trailblazer/pipelines/pipeline_ball.hpp>


namespace trailblazer::ball
{

/////////////////////////////////////////////////////////////////////////////////////////
// Wraps a ball pipeline to draw the ball object
//
// Inherits from MessageRecipient_i:
// Provides the msgBallPosition message for Map and Game scene
// Receives the msgRedrawTrigger message from Game scene
// Receives the msgBallPositionAndDistance message from Ball Controller

class BallDrawer_c : public messaging::MessageRecipient_i
{
    trailblazer::pipelines::BallPipeline_c Pipeline;

public:
    void draw();
    void setup();

    void sendMessage(msg_t m) override;
    
    BallDrawer_c(messaging::PostOffice_c* po);
};

} // namespace trailblazer::ball