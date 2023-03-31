#pragma once

#include <messaging/postoffice.hpp>
#include <messaging/recipient.hpp>
#include <trailblazer/game/messagetypes.hpp>

#include <statemachine/statemachine.hpp>


namespace trailblazer
{

/////////////////////////////////////////////////////////////////////////////////////////
/// This is the return type of updateGameState, which informs the main Game class
/// if the currently displayed scene shall change (either a title screen or an actual map),
/// by basically mapping the state of the Game state machine to these states,
/// so the Game class can decide if the current scene can be kept alive or a new one is needed

enum class GameSceneChange_e
{
    TOGGLE_TITLE,
    TOGGLE_GAMEPLAY,
    SCENE_NOCHANGE
};

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
    statemachine::StateMachine_c<msgGameState_e> StateMachine;

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

    void setupStateTransitions();

    void playSound(msgSoundEvent_e);

public:
    std::size_t mapIndex() const
    {
        return MapIndex;
    }

    /// Runs a state transition process on the underlying StateMachine
    /// and returns a GameSceneChange enum for the main Game class,
    /// which controls the game scenery accordingly
    GameSceneChange_e updateGameState();

    void sendMessage(msg_t) override;
    explicit GameControl_c(messaging::PostOffice_c*,
                           GameSceneChange_e,
                           std::size_t mapCount);
};

} // namespace trailblazer