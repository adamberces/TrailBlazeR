#include <trailblazer/game/gamecontrol.hpp>


namespace trailblazer
{

/////////////////////////////////////////////////////////////////////////////////////////
// Implementation for GameControl_c

static GameSceneChange_e mapState(msgGameState_e gameState)
{
    GameSceneChange_e sc = GameSceneChange_e::SCENE_NOCHANGE;;

    switch (gameState)
    {
    case msgGameState_e::TILE_SCREEN:
    case msgGameState_e::GAME_WON:
    case msgGameState_e::GAME_OVER:
        sc = GameSceneChange_e::TOGGLE_TITLE;
        break;
    case msgGameState_e::NORMAL_GAMEPLAY:
        sc = GameSceneChange_e::TOGGLE_GAMEPLAY;
        break;
    case msgGameState_e::BALL_LOST_WAIT:
    case msgGameState_e::BALL_LOST:
    case msgGameState_e::LEVEL_WON_WAIT:
    case msgGameState_e::LEVEL_WON:
        break;
    }

    return sc;
}

GameSceneChange_e GameControl_c::updateGameState()
{
    GameSceneChange_e sc = GameSceneChange_e::SCENE_NOCHANGE;
    statemachine::TransitionResult_e tr = StateMachine.performTransition();
   
    if (tr == statemachine::TransitionResult_e::TRANSITION_PERFORMED)
    {
        std::cout << "Game state changed: " <<
            std::to_string(static_cast<int>(StateMachine.state())) << std::endl;
        sc = mapState(StateMachine.state()); 
    }
        
    // Reset these states to their initial values after they were used once
    // for a state transition to prevent shifting to unwanted states
    LastBallState = msgBallStateChange_e::UNUSED;
    LastKeyEvent = msgKeyEvent_e::NONE;
    
    // Inform HUD about the actual number of lives
    PO->broadcastMessage<msgRemainingLives_s>({ Lives });

    return sc;
}

void GameControl_c::broadcastEvents(msgSoundEvent_e snd, msgHUDStatus_e hud)
{
    PO->broadcastMessage<msgSoundEvent_e>(snd);
    PO->broadcastMessage<msgHUDStatus_e>(hud);
}

void GameControl_c::setupStateTransitions()
{
    using statemachine::OnetimeActionTag;
    using statemachine::RepeatedActionTag;
    using statemachine::TransitionConditionTag;

    // Transition from the default state (title screen) to gameplay
    StateMachine.addTransition({ msgGameState_e::TILE_SCREEN,
                                 msgGameState_e::NORMAL_GAMEPLAY,
                                 statemachine::empty_repeated_action,
                                 [this](TransitionConditionTag) { return LastKeyEvent == msgKeyEvent_e::SPACE; },
                                 [this](OnetimeActionTag) { Lives = Constants_s::INITIAL_LIVES;
                                    broadcastEvents(msgSoundEvent_e::NONE, msgHUDStatus_e::NORMAL_GAMEPLAY); }
                               });


    // Handle events when the ball is lost
    // The outcome can be either the restart of the current level
    // in case the player has enough lives, or game over which
    // leads us back to the initial state (title screen)
    StateMachine.addTransition({ msgGameState_e::NORMAL_GAMEPLAY,
                                 msgGameState_e::BALL_LOST_WAIT,
                                 statemachine::empty_repeated_action,
                                 [this](TransitionConditionTag) { return LastBallState == msgBallStateChange_e::BALL_LOST; },
                                 [this](OnetimeActionTag) { Lives > 1 ?
                                    broadcastEvents(msgSoundEvent_e::BALL_LOST, msgHUDStatus_e::BALL_LOST) :
                                    broadcastEvents(msgSoundEvent_e::GAME_OVER, msgHUDStatus_e::GAME_OVER); }
                               });

    StateMachine.addTransition({ msgGameState_e::BALL_LOST_WAIT,
                                 msgGameState_e::BALL_LOST,
                                 [this](RepeatedActionTag) { WaitTimer += GameClock_c::TimePeriodSec; },
                                 [this](TransitionConditionTag) { return WaitTimer >= Constants_s::WAIT_TIME; },
                                 [this](OnetimeActionTag) { WaitTimer = 0; Lives--; }
                               });

    StateMachine.addTransition({ msgGameState_e::BALL_LOST,
                                 msgGameState_e::NORMAL_GAMEPLAY,
                                 statemachine::empty_repeated_action,
                                 [this](TransitionConditionTag) { return Lives > 0; },
                                 [this](OnetimeActionTag) { broadcastEvents(msgSoundEvent_e::NONE, msgHUDStatus_e::NORMAL_GAMEPLAY); }
                               });
    

    StateMachine.addTransition({ msgGameState_e::BALL_LOST,
                                 msgGameState_e::GAME_OVER,
                                 statemachine::empty_repeated_action,
                                 [this](TransitionConditionTag) { return Lives == 0; },
                                 [this](OnetimeActionTag) { MapIndex = 0; }
                               });

    StateMachine.addTransition({ msgGameState_e::GAME_OVER,
                                 msgGameState_e::TILE_SCREEN,
                                 statemachine::empty_repeated_action,
                                 statemachine::default_condition,
                                 [this](OnetimeActionTag) { broadcastEvents(msgSoundEvent_e::NONE, msgHUDStatus_e::TILE_SCREEN); }
                                });


    // Handle events when the level is won
    // The outcome can be either shifting to the next level
    // in case there are maps left, or game won which
    // leads us back to the initial state (title screen)
    StateMachine.addTransition({ msgGameState_e::NORMAL_GAMEPLAY,
                                 msgGameState_e::LEVEL_WON_WAIT,
                                 statemachine::empty_repeated_action,
                                 [this](TransitionConditionTag) { return LastBallState == msgBallStateChange_e::LEVEL_WON; },
                                 [this](OnetimeActionTag) { MapIndex + 1 < MapCount ?
                                    broadcastEvents(msgSoundEvent_e::LEVEL_WON, msgHUDStatus_e::LEVEL_WON) :
                                    broadcastEvents(msgSoundEvent_e::GAME_WON, msgHUDStatus_e::GAME_WON); }
                               });

    StateMachine.addTransition({ msgGameState_e::LEVEL_WON_WAIT,
                                 msgGameState_e::LEVEL_WON,
                                 [this](RepeatedActionTag) { WaitTimer += GameClock_c::TimePeriodSec; },
                                 [this](TransitionConditionTag) { return WaitTimer >= Constants_s::WAIT_TIME; },
                                 [this](OnetimeActionTag) { WaitTimer = 0; MapIndex++; }
                               });

    StateMachine.addTransition({ msgGameState_e::LEVEL_WON,
                                 msgGameState_e::NORMAL_GAMEPLAY,
                                 statemachine::empty_repeated_action,
                                 [this](TransitionConditionTag) { return MapIndex + 1 <= MapCount; },
                                 [this](OnetimeActionTag) { Lives += Constants_s::LEVEL_WON_BONUS;
                                    broadcastEvents(msgSoundEvent_e::NONE, msgHUDStatus_e::NORMAL_GAMEPLAY); }
                               });


    StateMachine.addTransition({ msgGameState_e::LEVEL_WON,
                                 msgGameState_e::GAME_WON,
                                 statemachine::empty_repeated_action,
                                 [this](TransitionConditionTag) { return MapIndex + 1 > MapCount; },
                                 [this](OnetimeActionTag) { MapIndex = 0; }
                                });

    StateMachine.addTransition({ msgGameState_e::GAME_WON,
                                 msgGameState_e::TILE_SCREEN,
                                 statemachine::empty_repeated_action,
                                 statemachine::default_condition,
                                 [this](OnetimeActionTag) { broadcastEvents(msgSoundEvent_e::NONE, msgHUDStatus_e::TILE_SCREEN); }
                               });
}

void GameControl_c::sendMessage(msg_t m)
{
    if (isMessageType<msgBallStateChange_e>(m))
    {
        // We only interested in this one when we in normal gameplay,
        // so we can avoid unneccesary state transition checks
        if (StateMachine.state() == msgGameState_e::NORMAL_GAMEPLAY)
        {
            LastBallState = msg_cast<msgBallStateChange_e>(m);
        }
        else
        {
            LastBallState = msgBallStateChange_e::UNUSED;
        }
    }
    else if (isMessageType<msgKeyEvent_e>(m))
    {
        LastKeyEvent = msg_cast<msgKeyEvent_e>(m);
    }
}

GameControl_c::GameControl_c(messaging::PostOffice_c* po,
                             std::size_t mapCount) :
    MessageRecipient_i(po),
    StateMachine(msgGameState_e::TILE_SCREEN),
    Lives(Constants_s::INITIAL_LIVES),
    MapIndex(0U),
    MapCount(mapCount),
    LastKeyEvent(msgKeyEvent_e::NONE),
    LastBallState(msgBallStateChange_e::UNUSED),
    WaitTimer(0.F)
{   
    setupStateTransitions();

    // Manage subscriptions
    PO->subscribeRecipient<msgBallStateChange_e>(this);
    PO->subscribeRecipient<msgKeyEvent_e>(this);
}

} // namespace trailblazer
