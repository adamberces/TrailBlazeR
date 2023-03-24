#include <trailblazer/presentation/hud.hpp>


namespace trailblazer::presentation
{

/////////////////////////////////////////////////////////////////////////////////////////
// HUD_c implementation

void HUD_c::draw()
{
    Pipeline.run("teszt", 10, 10, {1, 1, 1});
}

void HUD_c::sendMessage(msg_t m)
{
    if (isMessageType<msgRedrawTrigger_s>(m))
    {
        draw();
    }
    else if (isMessageType<msgRemainingLives_s>(m))
    {
        
    }
    else if (isMessageType<msgMapInfo_s>(m))
    {
        
    }
}

HUD_c::HUD_c(messaging::PostOffice_c* po) :
    MessageRecipient_i(po),
    Pipeline("./assets/fonts/font")
{   
    // Manage subscriptions
    PO->subscribeRecipient<msgRedrawTrigger_s>(this);
    PO->subscribeRecipient<msgRemainingLives_s>(this);
    PO->subscribeRecipient<msgMapInfo_s>(this);
}

} // namespace trailblazer::presentation