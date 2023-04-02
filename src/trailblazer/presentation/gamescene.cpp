#include <trailblazer/presentation/gamescene.hpp>


namespace trailblazer::presentation
{

/////////////////////////////////////////////////////////////////////////////////////////
// GameScene_c implementation
//
// Note: there are some "magic" literals which are hardcoded instead of coming from the
// constants struct, as they are fine tuned and not meant to be changed for eg. debug reasons

// Updates the scene's globals (camera and lightning uniforms)
// to follow the movement of the ball
void GameScene_c::updateGlobals(glkit::functors::point3d_t ballPos)
{
    // Update lightning position
    RenderPipeline_i::LightningPositionConfig.Position.X =
        ballPos.X;
    RenderPipeline_i::LightningPositionConfig.Position.Y =
        ballPos.Y - Constants_s::BALL_DIAMETER;
    RenderPipeline_i::LightningPositionConfig.Position.Z = ballPos.Z + 0.5F;

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

void GameScene_c::sendMessage(msg_t m)
{
    if (isMessageType<msgBallPosition_s>(m))
    {
        msgBallPosition_s p =
            msg_cast<msgBallPosition_s>(m);
        updateGlobals(p.Position);

        PO->broadcastMessage<msgRedrawTrigger_s>({});
    }
}

void GameScene_c::setup(glkit::functors::rgb_t lightColor)
{
    // Setup projection matrix
    RenderPipeline_i::ProjectionConfig.FOV = 45.F;
    RenderPipeline_i::ProjectionConfig.ScreenWidth = Constants_s::WINDOW_WIDTH;
    RenderPipeline_i::ProjectionConfig.ScreenHeight = Constants_s::WINDOW_HEIGHT;
    RenderPipeline_i::ProjectionConfig.NearPlane = 0.1F;
    RenderPipeline_i::ProjectionConfig.FarPlane = 100.F;

    // Setup lightning color
    RenderPipeline_i::LightningColorConfig.Color = lightColor;
}

GameScene_c::GameScene_c(messaging::PostOffice_c* po, glkit::functors::rgb_t lightColor) :
    MessageRecipient_i(po)
{
    setup(lightColor);

    PO->subscribeRecipient<msgBallPosition_s>(this);
}


} // namespace trailblazer::presentation