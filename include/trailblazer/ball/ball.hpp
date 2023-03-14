#pragma once

#include <messaging/postoffice.hpp>
#include <messaging/recipient.hpp>
#include <trailblazer/game/messagetypes.hpp>

#include <trailblazer/pipelines/pipeline_ball.hpp>


namespace trailblazer::ball
{

class Ball_c : public messaging::MessageRecipient_i
{
    float Diameter = 0.25F;
    trailblazer::pipelines::BallPipeline_c Pipeline;

public:
    void moveLeft()
    {
        Pipeline.ModelConfig.Position.X -= .05;
    }

    void moveRight()
    {
        Pipeline.ModelConfig.Position.X += .05;
    }

    void jump()
    {}


    void sendMessage(std::any m) override
    {
        if (isMessageType<msgKeyEvent>(m))
        {
            msgKeyEvent e = std::any_cast<msgKeyEvent>(m);

            switch(e)
            {
            case msgKeyEvent::JUMP:
                jump();
                break;
            case msgKeyEvent::LEFT:
                moveLeft();
                break;
            case msgKeyEvent::RIGHT:
                moveRight();
                break;
            case msgKeyEvent::NONE:
                break;
            }
        }
        else if (isMessageType<msgRedrawTrigger>(m))
        {
            draw();
        }
    }


    float diameter()
    {
        return Diameter;
    }

    glkit::functors::point3d_t getPosition()
    {
        return Pipeline.ModelConfig.Position;
    }

    void draw()
    {
        Pipeline.ModelConfig.Position.Y += .05;
        Pipeline.ModelConfig.Rotation.Angle -= 5;
        Pipeline.run();

        // Broadcast a message with the actual position of the ball
        PO->broadcastMessage<msgBallPosition>(
            { Pipeline.ModelConfig.Position }
        );
    }

    void setup()
    {
        Pipeline.setup();
        Pipeline.ModelConfig.Position.X = 2;
        Pipeline.ModelConfig.Position.Y = Diameter;
        Pipeline.ModelConfig.Position.Z = Diameter;
        Pipeline.ModelConfig.Scale.X = Diameter;
        Pipeline.ModelConfig.Scale.Y = Diameter;
        Pipeline.ModelConfig.Scale.Z = Diameter;
        Pipeline.ModelColorConfig.Color.R = 1.F;
        Pipeline.ModelColorConfig.Color.G = 0.F;
        Pipeline.ModelColorConfig.Color.B = 0.F;
    }

    Ball_c(messaging::PostOffice_c* po) :
        MessageRecipient_i(po),
        Pipeline()
    {   
        // Manage subscriptions
        PO->subscribeRecipient<msgKeyEvent>(this);
        PO->subscribeRecipient<msgRedrawTrigger>(this);

        setup();
    }

};

} // namespace trailblazer::ball