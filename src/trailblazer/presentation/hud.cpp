#include <trailblazer/presentation/hud.hpp>


namespace trailblazer::presentation
{

/////////////////////////////////////////////////////////////////////////////////////////
// HUD_c implementation

void HUD_c::draw()
{
    Pipeline.run("TRAILBLAZER 2023 by Adam Berces", 10, 30, { 1, 1, 1 });

    std::string stats =
        "Stage '" + MapData.Metadata.MapTitle + "'        Lives " + std::to_string(Lives) +
        "        Progress " + std::to_string(MapData.Metadata.TileCount) + "/" + 
        std::to_string(MapData.CurrentTile) + " m";
    
    Pipeline.run(stats, 10, 750, MapData.Metadata.ColorTheme);
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
    else if (isMessageType<msgMapData_s>(m))
    {
        MapData = msg_cast<msgMapData_s>(m);
    }
}

HUD_c::HUD_c(messaging::PostOffice_c* po) :
    MessageRecipient_i(po),
    Pipeline("./assets/fonts/font")
{   
    // Manage subscriptions
    PO->subscribeRecipient<msgRedrawTrigger_s>(this);
    PO->subscribeRecipient<msgRemainingLives_s>(this);
    PO->subscribeRecipient<msgMapData_s>(this);
}

} // namespace trailblazer::presentation
