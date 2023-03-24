#include <trailblazer/presentation/hud.hpp>


namespace trailblazer::presentation
{

/////////////////////////////////////////////////////////////////////////////////////////
// HUD_c implementation

void HUD_c::draw()
{
    Pipeline.run("TRAILBLAZER 2023 by Adam Berces", 10, 30, { 1, 1, 1 });

    std::string msg = "Lives " + std::to_string(Lives);
    Pipeline.run(msg, 10, 750, {0, 1, 1});
}

void HUD_c::sendMessage(msg_t m)
{
    if (isMessageType<msgRedrawTrigger_s>(m))
    {
        draw();
    }
    else if (isMessageType<msgRemainingLives_s>(m))
    {
        Lives = msg_cast<msgRemainingLives_s>(m).RemainingLives;
    }
    else if (isMessageType<msgMapInfo_s>(m))
    {
        MapInfo = msg_cast<msgMapInfo_s>(m).MapInfo;
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
