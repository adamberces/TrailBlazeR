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
        else if (isMessageType<msgBallPositionAndDistance>(m))
        {
            msgBallPositionAndDistance p =
                std::any_cast<msgBallPositionAndDistance>(m);
            
            Pipeline.ModelConfig.Position = p.Position;

            // Calculate the angular rotation for 1 meters of distance
            // taken by the ball on the ground from the circumference
            // of a circle got from the diameter of the ball
            constexpr float DegreePerMeter = 360.F / (Constants_s::BALL_DIAMETER * 3.14159F);
            
            // Calculate the actual extent of rotation from the actual distance
            // taken by the ball since the last frame
            Pipeline.ModelConfig.Rotation.Angle -= p.Distance * DegreePerMeter;

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
        Pipeline.ModelConfig.Position.X = 2;
        Pipeline.ModelConfig.Position.Y = 0;
        Pipeline.ModelConfig.Position.Z = 0;
        Pipeline.ModelConfig.Scale.X = Constants_s::BALL_DIAMETER;
        Pipeline.ModelConfig.Scale.Y = Constants_s::BALL_DIAMETER;
        Pipeline.ModelConfig.Scale.Z = Constants_s::BALL_DIAMETER;
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
        PO->subscribeRecipient<msgBallPositionAndDistance>(this);
        setup();
    }

};

} // namespace trailblazer::ball