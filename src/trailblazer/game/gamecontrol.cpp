#include <trailblazer/game/gamecontrol.hpp>


namespace trailblazer
{

/////////////////////////////////////////////////////////////////////////////////////////
// Definition for the static class member Lives
int GameControl_c::Lives = Constants_s::INITIAL_LIVES;
std::size_t GameControl_c::MapIndex = 0U;

/////////////////////////////////////////////////////////////////////////////////////////
// Implementation for GameControl_c

static GameSceneChange_e mapState(msgGameState_e gameState)
{
    GameSceneChange_e sc;

    switch (gameState)
    {
    case msgGameState_e::TILE_SCREEN:
    case msgGameState_e::GAME_WON:
    case msgGameState_e::GAME_OVER:
        sc = GameSceneChange_e::TOGGLE_TITLE;
        break;
    case msgGameState_e::TILE_SCREEN_EXIT:
    case msgGameState_e::BALL_LOST:
    case msgGameState_e::LEVEL_WON:
        sc = GameSceneChange_e::TOGGLE_GAMEPLAY;
        break;
    case msgGameState_e::NORMAL_GAMEPLAY:
    case msgGameState_e::BALL_LOST_WAIT:
    case msgGameState_e::LEVEL_WON_WAIT:
        sc = GameSceneChange_e::SCENE_NOCHANGE;
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
        sc = mapState(StateMachine.state()); 
    }
    
    // Transfer the number of lives to the HUD component
    PO->broadcastMessage<msgRemainingLives_s>({ Lives });
    PO->broadcastMessage<msgGameState_e>(StateMachine.state());

    return sc;
}

void GameControl_c::playSound(msgSoundEvent_e e)
{
    PO->broadcastMessage<msgSoundEvent_e>(e);
}

void GameControl_c::setupStateTransitions()
{
    using statemachine::OnetimeActionTag;
    using statemachine::RepeatedActionTag;
    using statemachine::TransitionConditionTag;

    // Transition from the default state (title screen) to gameplay
    StateMachine.addTransition({ msgGameState_e::TILE_SCREEN,
                                 msgGameState_e::TILE_SCREEN_EXIT,
                                 statemachine::empty_repeated_action,
                                 [this](TransitionConditionTag) { return LastKeyEvent == msgKeyEvent_e::SPACE; },
                                 [this](OnetimeActionTag) { MapIndex = 0; Lives = Constants_s::INITIAL_LIVES; }
                               });

    StateMachine.addTransition({ msgGameState_e::TILE_SCREEN_EXIT,
                                 msgGameState_e::NORMAL_GAMEPLAY,
                                 statemachine::empty_repeated_action,
                                 statemachine::default_condition,
                                 statemachine::empty_onetime_action,
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
                                                            playSound(msgSoundEvent_e::BALL_LOST) :
                                                            playSound(msgSoundEvent_e::GAME_OVER); }
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
                                 statemachine::empty_onetime_action
                               });
    

    StateMachine.addTransition({ msgGameState_e::BALL_LOST,
                                 msgGameState_e::GAME_OVER,
                                 statemachine::empty_repeated_action,
                                 [this](TransitionConditionTag) { return Lives == 0; },
                                 statemachine::empty_onetime_action
                               });

    StateMachine.addTransition({ msgGameState_e::GAME_OVER,
                                 msgGameState_e::TILE_SCREEN,
                                 statemachine::empty_repeated_action,
                                 statemachine::default_condition,
                                 statemachine::empty_onetime_action
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
                                            playSound(msgSoundEvent_e::LEVEL_WON) :
                                            playSound(msgSoundEvent_e::GAME_WON); }
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
                                 [this](TransitionConditionTag) { return MapIndex + 1 < MapCount; },
                                 [this](OnetimeActionTag) { Lives += Constants_s::LEVEL_WON_BONUS; }
                               });


    StateMachine.addTransition({ msgGameState_e::LEVEL_WON,
                                 msgGameState_e::GAME_WON,
                                 statemachine::empty_repeated_action,
                                 [this](TransitionConditionTag) { return MapIndex + 1 == MapCount; },
                                 statemachine::empty_onetime_action
                               });

    StateMachine.addTransition({ msgGameState_e::GAME_WON,
                                 msgGameState_e::TILE_SCREEN,
                                 statemachine::empty_repeated_action,
                                 statemachine::default_condition,
                                 statemachine::empty_onetime_action
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
                             GameSceneChange_e initialState,
                             std::size_t mapCount) :
    MessageRecipient_i(po),
    StateMachine(initialState == GameSceneChange_e::TOGGLE_TITLE ? 
                 msgGameState_e::TILE_SCREEN : msgGameState_e::NORMAL_GAMEPLAY),
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
