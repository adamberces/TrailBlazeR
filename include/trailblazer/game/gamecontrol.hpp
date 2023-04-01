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
/// Controls the main flow of the game. Maintains a state machine and informs the main
/// game class if a new scene shall be set up and also counts the number of lives and
/// an index to the actual, which are also the main drivers of the actual game state
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
    int Lives;
    std::size_t MapIndex;
    std::size_t MapCount;

    /// Received messages kept as an innter state
    msgKeyEvent_e LastKeyEvent;
    msgBallStateChange_e LastBallState;

    /// Counter to measure the the short time before switching
    /// or restarting scene after the ball is lost or the level is won
    float WaitTimer;

    /// Sends message to the HUD and the sound control
    void broadcastEvents(msgSoundEvent_e, msgHUDStatus_e);

    /// This function is the main part of this class,
    /// contains the definition of state transitions
    void setupStateTransitions();

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
                           std::size_t mapCount);
};

} // namespace trailblazer