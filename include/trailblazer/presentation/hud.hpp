#pragma once

#include <trailblazer/game/gameconfig.hpp>

#include <messaging/postoffice.hpp>
#include <messaging/recipient.hpp>
#include <trailblazer/game/messagetypes.hpp>

#include <trailblazer/pipelines/pipeline_text.hpp>


namespace trailblazer::presentation
{

/////////////////////////////////////////////////////////////////////////////////////////
/// Wraps a text pipeline to draw the Head Up Display
//
/// Inherits from MessageRecipient_i:
/// Receives the msgMapData_s message from Map
/// Receives the msgGameState_e message from Game Control
/// Receives the msgRemainingLives_s message from Game Control
/// Receives the msgRedrawTrigger_s message from Game Scene

class HUD_c : public messaging::MessageRecipient_i
{
    trailblazer::pipelines::TextPipeline_c Pipeline;

    /// Lives info received from Game Control
    int Lives;

    /// Map data received from Map
    msgMapData_s MapData;

    /// Game state message received from Game Control
    /// to display special messages. Defined as static
    /// because a HUD object is recreated for every game 
    /// but this value shall be kept
    static msgHUDStatus_e HUDStatus;

    /// Generates the special messages which is displayed
    /// instead of the in-game stats on game state changes
    void handleGameState(std::string& stats);

public:
    void draw();
    void setup();

    void sendMessage(msg_t m) override;
    explicit HUD_c(messaging::PostOffice_c*);
};

} // namespace trailblazer::hudpresentation