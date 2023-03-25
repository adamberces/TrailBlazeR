#pragma once

#include <messaging/postoffice.hpp>
#include <messaging/recipient.hpp>
#include <trailblazer/game/messagetypes.hpp>


namespace trailblazer
{

/////////////////////////////////////////////////////////////////////////////////////////
// Represents the actual state of the game, which is returned to the
// main Game class by GameControl in every cycle, 

enum class GameState_e
{
    NORMAL,
    BALL_LOST,
    LEVEL_WON,
    GAME_OVER,
    GAME_WON
};

/////////////////////////////////////////////////////////////////////////////////////////
// Controls the main flow of a stage. Counts the remaining lives and
// maintains a timer to wait a few seconds when the ball is lost or it
// has reached the finish line before shifting/restarting the stage.
//
// Inherits from MessageRecipient_i:
// Provides the msgRemainingLives_s message for HUD
// Receives the msgGameStateChange_e message from Ball Control

class GameControl_c : public messaging::MessageRecipient_i
{   
    GameState_e GameState;

    static int Lives;

    // Counter to measure the the short time before switching
    // or restarting scene after the ball is lost or the level is won
    float WaitTimer;

public:
    GameState_e getGameState();

    void sendMessage(msg_t m) override;

    GameControl_c(messaging::PostOffice_c* po);
};

} // namespace trailblazer