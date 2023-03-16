#pragma once

#include <trailblazer/game/constants.hpp>

#include <messaging/postoffice.hpp>
#include <messaging/recipient.hpp>
#include <trailblazer/game/messagetypes.hpp>

#include <trailblazer/pipelines/pipeline_ball.hpp>


namespace trailblazer::ball
{

class Ball_c : public messaging::MessageRecipient_i
{
    trailblazer::pipelines::BallPipeline_c Pipeline;

public:

    void sendMessage(std::any m) override
    {
        if (isMessageType<msgRedrawTrigger>(m))
        {
            draw();
        }
        else if (isMessageType<msgBallPositionAndSpeed>(m))
        {
            msgBallPositionAndSpeed p =
                std::any_cast<msgBallPositionAndSpeed>(m);
            
            Pipeline.ModelConfig.Position = p.Position;
            Pipeline.ModelConfig.Rotation.Angle -= 5;

            PO->broadcastMessage<msgBallPosition>({p.Position});
          }
    }

    void draw()
    {
        Pipeline.run();
    }

    void setup()
    {
        Pipeline.setup();
        Pipeline.ModelConfig.Position.X = 2.5;
        Pipeline.ModelConfig.Position.Y = .375;
        Pipeline.ModelConfig.Position.Z = .375;
        Pipeline.ModelConfig.Scale.X = Constants_c::BALL_DIAMETER;
        Pipeline.ModelConfig.Scale.Y = Constants_c::BALL_DIAMETER;
        Pipeline.ModelConfig.Scale.Z = Constants_c::BALL_DIAMETER;
        Pipeline.ModelColorConfig.Color.R = 1.F;
        Pipeline.ModelColorConfig.Color.G = 0.F;
        Pipeline.ModelColorConfig.Color.B = 0.F;
    }

    Ball_c(messaging::PostOffice_c* po) :
        MessageRecipient_i(po),
        Pipeline()
    {   
        // Manage subscriptions
        PO->subscribeRecipient<msgRedrawTrigger>(this);
        PO->subscribeRecipient<msgBallPositionAndSpeed>(this);
        setup();
    }

};

} // namespace trailblazer::ball