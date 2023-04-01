#include <trailblazer/presentation/hud.hpp>


namespace trailblazer::presentation
{

/////////////////////////////////////////////////////////////////////////////////////////
// Definition for the static member HUDStatus
msgHUDStatus_e HUD_c::HUDStatus = msgHUDStatus_e::TILE_SCREEN;


/////////////////////////////////////////////////////////////////////////////////////////
// HUD_c implementation

void HUD_c::handleGameState(std::string& stats)
{
    switch (HUDStatus)
    {
    case msgHUDStatus_e::TILE_SCREEN:
        stats = "Press SPACE to start!";
        break;
    case msgHUDStatus_e::BALL_LOST:
        stats = "Ball lost";
        break;
    case msgHUDStatus_e::LEVEL_WON:
        stats = "Stage cleared!";
        break;
    case msgHUDStatus_e::GAME_OVER:
        stats = "Game over!";
        break;
    case msgHUDStatus_e::GAME_WON:
        stats = "Congratulations! You won the game!";
        break;
    default:
        break;
    }
}

void HUD_c::draw()
{
    // Print game title on the bottom of the screen
    if (HUDStatus != msgHUDStatus_e::TILE_SCREEN)
    {
        Pipeline.run("TRAILBLAZER 2023 by Adam Berces", 10, 30, { 1, 1, 1 });
    }

    std::string message;

    if (HUDStatus == msgHUDStatus_e::NORMAL_GAMEPLAY)
    {
        // Prepare in-game stats
        message =
            "Stage '" + MapData.Metadata.MapTitle + "'        Lives " + std::to_string(Lives) +
            "        Progress " + std::to_string(MapData.Metadata.TileCount) + "/" +
            std::to_string(MapData.CurrentTile) + " m";
    }
    else
    {
        // Display special message
        handleGameState(message);

    }
   
    // Print stats/special message on the top of the screen
    Pipeline.run(message, 10, 750, MapData.Metadata.ColorTheme);
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
    else if (isMessageType<msgHUDStatus_e>(m))
    {
        HUDStatus = msg_cast<msgHUDStatus_e>(m);
    }
}

HUD_c::HUD_c(messaging::PostOffice_c* po) :
    MessageRecipient_i(po),
    Pipeline("./assets/fonts/font")
{   
    // Manage subscriptions
    PO->subscribeRecipient<msgRedrawTrigger_s>(this);
    PO->subscribeRecipient<msgHUDStatus_e>(this);
    PO->subscribeRecipient<msgRemainingLives_s>(this);
    PO->subscribeRecipient<msgMapData_s>(this);
}

} // namespace trailblazer::presentation
