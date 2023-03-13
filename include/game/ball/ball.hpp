#pragma once

#include <game/messaging/postoffice.hpp>
#include <game/messaging/recipient.hpp>
#include <game/messaging/messagetypes.hpp>

#include <game/presentation/ballpipeline.hpp>


namespace trailblazer::ball
{

class Ball_c : public messaging::MessageRecipient_i
{
    float Diameter = 0.25F;
    trailblazer::presentation::BallPipeline_c Pipeline;

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


    void sendMessage(std::any message) override
    {
        if (message.type() == typeid(messaging::KeyEvent_e))
        {
            messaging::KeyEvent_e e =
                std::any_cast<messaging::KeyEvent_e>(message);

            switch(e)
            {
            case messaging::KeyEvent_e::JUMP:
                jump();
                break;
            case messaging::KeyEvent_e::LEFT:
                moveLeft();
                break;
            case messaging::KeyEvent_e::RIGHT:
                moveRight();
                break;
            case messaging::KeyEvent_e::NONE:
                break;
            }
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
        PO->broadcastMessage<messaging::BallPosition_t>(
            { Pipeline.ModelConfig.Position }
        );
    }

    Ball_c(messaging::PostOffice_c* po) :
        MessageRecipient_i(po),
        Pipeline()
    {   
        PO->subscribeRecipient<messaging::KeyEvent_e>(this);

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

};

} // namespace trailblazer::ball