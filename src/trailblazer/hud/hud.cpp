#include <trailblazer/hud/hud.hpp>


namespace trailblazer::hud
{

/////////////////////////////////////////////////////////////////////////////////////////
// BallDrawer_c implementation

void HUD_c::draw()
{
    Pipeline.run();
}

void HUD_c::sendMessage(msg_t m)
{
    if (isMessageType<msgRedrawTrigger>(m))
    {
        draw();
    }
    else if (isMessageType<msgBallPositionAndDistance>(m))
    {
        
    }
}

HUD_c::HUD_c(messaging::PostOffice_c* po) :
    MessageRecipient_i(po),
    Pipeline("./assets/fonts/font")
{   
    // Manage subscriptions
    PO->subscribeRecipient<msgRedrawTrigger>(this);
    PO->subscribeRecipient<msgBallPositionAndDistance>(this);
}

} // namespace trailblazer::ball
