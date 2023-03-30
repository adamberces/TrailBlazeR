#pragma once

#include <messaging/postoffice.hpp>
#include <messaging/recipient.hpp>
#include <trailblazer/game/messagetypes.hpp>

#include <statemachine/statemachine.hpp>


namespace trailblazer
{

/////////////////////////////////////////////////////////////////////////////////////////
/// Controls the main flow of a stage. Counts the remaining lives and
/// maintains a timer to wait a few seconds when the ball is lost or it
/// has reached the finish line before shifting/restarting the stage.
//
/// Inherits from MessageRecipient_i:
/// Provides the msgRemainingLives_s message for HUD
/// Provides the msgSoundEvent_e message for Sound Control
/// Receives the msgBallStateChange_e message from Ball Control

class GameControl_c : public messaging::MessageRecipient_i
{   
    statemachine::StateMachine_i<msgGameState_e> StateMachine;

    /// The responsibility of the class is to maintain the value of 
    /// Lives and the actual map's index. Some state transitions are
    /// also depending the value of these variables
    static int Lives;
    static std::size_t MapIndex;
    std::size_t MapCount;

    /// Received messages
    msgKeyEvent_e LastKeyEvent;
    msgBallStateChange_e LastBallState;

    /// Counter to measure the the short time before switching
    /// or restarting scene after the ball is lost or the level is won
    float WaitTimer;

    /// Notifies Sound Control to play one of the "spoken word" sound
    /// effects either for ball lost, level won, game over or game won
    void triggerSound();

    void setupStateTransitions();

public:
    std::size_t mapIndex() const
    {
        return MapIndex;
    }

    /// Provides the current game state (returns NORMAL even when the 
    /// ball is lost or the level is won, but we are still under WaitTimer)
    /// An argument shall be provided from the main Game class to indicate
    /// if the current scene contains the last available map or not, 
    /// to make distinction between LEVEL_WON and GAME_WON
    /// (BALL_LOST and GAME_OVER can de distinguished using Lives).
    msgGameState_e updateGameState();

    void sendMessage(msg_t) override;
    explicit GameControl_c(messaging::PostOffice_c*,
        msgGameState_e initialState,
        std::size_t mapCount);
};

} // namespace trailblazer