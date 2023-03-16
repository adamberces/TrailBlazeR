#pragma once

#include <messaging/postoffice.hpp>
#include <messaging/recipient.hpp>
#include <trailblazer/game/messagetypes.hpp>

#include <trailblazer/pipelines/renderpipeline.hpp>
#include <trailblazer/pipelines/pipeline_bkg.hpp>


namespace trailblazer::presentation
{

using pipelines::RenderPipeline_i;

class GameScene_c : public messaging::MessageRecipient_i
{
    std::unique_ptr<pipelines::BackgroundPipeline_c> Background;

    // Updates the scene's globals (camera and lightning uniforms)
    // to follow the movement of the ball
    void updateGlobals(glkit::functors::point3d_t ballPos)
    {
        // Update lightning position

        RenderPipeline_i::LightningPositionConfig.Position.X =
            ballPos.X;
        RenderPipeline_i::LightningPositionConfig.Position.Y =
            ballPos.Y - .25; /*Ball.diameter()*/;
        RenderPipeline_i::LightningPositionConfig.Position.Z = 0.5F;

        // Update camera positions

        RenderPipeline_i::CameraConfig.Position.X = 2;
        RenderPipeline_i::CameraConfig.Position.Y = ballPos.Y - 5;
        RenderPipeline_i::CameraConfig.Position.Z = 1.5;

        RenderPipeline_i::CameraConfig.Direction.X = 2;
        RenderPipeline_i::CameraConfig.Direction.Y = ballPos.Y + 5;
        RenderPipeline_i::CameraConfig.Direction.Z = .5;

        RenderPipeline_i::CameraPositionConfig.Position =
            RenderPipeline_i::CameraConfig.Position;
    }

    void sendMessage(std::any m) override
    {
        if (isMessageType<msgBallPosition>(m))
        {
            msgBallPosition p =
                std::any_cast<msgBallPosition>(m);
            updateGlobals(p.Position);
            drawScene();
        }
    }


public:
    // Redraw the scene

    void drawScene()
    {
        printf("cam %f %f %f\n", RenderPipeline_i::LightningPositionConfig.Position.X,
            RenderPipeline_i::LightningPositionConfig.Position.Y,
            RenderPipeline_i::LightningPositionConfig.Position.Z); 

        // Redraw scene
        Background->run();
        PO->broadcastMessage<msgRedrawTrigger>({});
    }

    // Setup the uniforms of the render pipeline, which won't change
    // during the lifetime of the scene: projection matrix, lighning color
    void setup()
    {
        // Setup projection matrix
        RenderPipeline_i::ProjectionConfig.FOV = 45.F;
        RenderPipeline_i::ProjectionConfig.ScreenWidth = 640;
        RenderPipeline_i::ProjectionConfig.ScreenHeight = 480;
        RenderPipeline_i::ProjectionConfig.NearPlane = 0.1F;
        RenderPipeline_i::ProjectionConfig.FarPlane = 100.F;

        // Setup lightning color
        RenderPipeline_i::LightningColorConfig.Color.R = 0.51F;
        RenderPipeline_i::LightningColorConfig.Color.G = 0.45F;
        RenderPipeline_i::LightningColorConfig.Color.B = 0.57F;

        Background = std::make_unique<pipelines::BackgroundPipeline_c>("./assets/bkg.jpg");
        Background->setup();
    }

    GameScene_c(messaging::PostOffice_c* po) :
        MessageRecipient_i(po)
    {
        setup();

        PO->subscribeRecipient<msgBallPosition>(this);
    }

};

} // namespace trailblazer::presentation