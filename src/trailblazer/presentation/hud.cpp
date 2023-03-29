#include <trailblazer/presentation/hud.hpp>


namespace trailblazer::presentation
{

/////////////////////////////////////////////////////////////////////////////////////////
// HUD_c implementation

void HUD_c::handleGameState(std::string& stats)
{
    if (GameState != msgGameStateChange_e::NORMAL)
    {
        switch (GameState)
        {
        case msgGameStateChange_e::TILE_SCREEN:
            stats = "Press SPACE to start!";
            break;
        case msgGameStateChange_e::BALL_LOST:
            stats = "Ball lost";
            break;
        case msgGameStateChange_e::LEVEL_WON:
            stats = "Stage cleared!";
            break;
        case msgGameStateChange_e::GAME_OVER:
            stats = "Game over!";
            break;
        case msgGameStateChange_e::GAME_WON:
            stats = "Congratulations! You won the game!";
            break;
        default:
            break;
        }
    }
}

void HUD_c::draw()
{
    // Print game title on the bottom of the screen
    if  (GameState != msgGameStateChange_e::TILE_SCREEN)
    {
        Pipeline.run("TRAILBLAZER 2023 by Adam Berces", 10, 30, { 1, 1, 1 });
    }
    
    // Prepare in-game stats
    std::string stats =
        "Stage '" + MapData.Metadata.MapTitle + "'        Lives " + std::to_string(Lives) +
        "        Progress " + std::to_string(MapData.Metadata.TileCount) + "/" + 
        std::to_string(MapData.CurrentTile) + " m";

    // Overwrite the stats line if we are in a game state other than NORMAL
    handleGameState(stats);

    // Print stats/special message on the top of the screen
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
    else if (isMessageType<msgGameStateChange_e>(m))
    {
        GameState = msg_cast<msgGameStateChange_e>(m);
    }
}

HUD_c::HUD_c(messaging::PostOffice_c* po) :
    MessageRecipient_i(po),
    Pipeline("./assets/fonts/font")
{   
    // Manage subscriptions
    PO->subscribeRecipient<msgRedrawTrigger_s>(this);
    PO->subscribeRecipient<msgGameStateChange_e>(this);
    PO->subscribeRecipient<msgRemainingLives_s>(this);
    PO->subscribeRecipient<msgMapData_s>(this);
}

} // namespace trailblazer::presentation
