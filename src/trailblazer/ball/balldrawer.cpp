#include <trailblazer/ball/balldrawer.hpp>


namespace trailblazer::ball
{

/////////////////////////////////////////////////////////////////////////////////////////
// BallDrawer_c implementation

void BallDrawer_c::setup()
{
    Pipeline.setup();
    Pipeline.ModelConfig.Scale.X = Constants_s::BALL_DIAMETER;
    Pipeline.ModelConfig.Scale.Y = Constants_s::BALL_DIAMETER;
    Pipeline.ModelConfig.Scale.Z = Constants_s::BALL_DIAMETER;
    Pipeline.ModelColorConfig.Color.R = Constants_s::BALL_COLOR_R;
    Pipeline.ModelColorConfig.Color.G = Constants_s::BALL_COLOR_G;
    Pipeline.ModelColorConfig.Color.B = Constants_s::BALL_COLOR_B;
}

void BallDrawer_c::draw()
{
    Pipeline.run();
}

void BallDrawer_c::sendMessage(msg_t m)
{
    if (isMessageType<msgRedrawTrigger>(m))
    {
        draw();
    }
    else if (isMessageType<msgBallPositionAndDistance>(m))
    {
        msgBallPositionAndDistance p = msg_cast<msgBallPositionAndDistance>(m);
        
        Pipeline.ModelConfig.Position = p.Position;

        // Calculate the angular rotation for 1 meters of distance
        // taken by the ball on the ground from the circumference
        // of a circle got from the diameter of the ball
        constexpr float DegreePerMeter = 360.F / (Constants_s::BALL_DIAMETER * Constants_s::PI);
        
        // Calculate the actual extent of rotation from the actual distance
        // taken by the ball since the last frame
        Pipeline.ModelConfig.Rotation.Angle -= p.Distance * DegreePerMeter;

        PO->broadcastMessage<msgBallPosition>({p.Position});
    }
}

BallDrawer_c::BallDrawer_c(messaging::PostOffice_c* po) :
    MessageRecipient_i(po),
    Pipeline()
{   
    // Manage subscriptions
    PO->subscribeRecipient<msgRedrawTrigger>(this);
    PO->subscribeRecipient<msgBallPositionAndDistance>(this);
    setup();
}

} // namespace trailblazer::ball
