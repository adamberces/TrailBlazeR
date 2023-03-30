#include <trailblazer/game/gamecontrol.hpp>


namespace trailblazer
{

/////////////////////////////////////////////////////////////////////////////////////////
// Definition for the static class member Lives
int GameControl_c::Lives = Constants_s::INITIAL_LIVES;
std::size_t GameControl_c::MapIndex = 0U;

/////////////////////////////////////////////////////////////////////////////////////////
// Implementation for GameControl_c

void GameControl_c::triggerSound()
{
    switch (StateMachine.state())
    {
    case msgGameState_e::BALL_LOST:
        PO->broadcastMessage<msgSoundEvent_e>(msgSoundEvent_e::BALL_LOST);
        break;
    case msgGameState_e::LEVEL_WON:
        PO->broadcastMessage<msgSoundEvent_e>(msgSoundEvent_e::LEVEL_WON);
        break;
    case msgGameState_e::GAME_OVER:
        PO->broadcastMessage<msgSoundEvent_e>(msgSoundEvent_e::GAME_OVER);
        break;     
    case msgGameState_e::GAME_WON:
        PO->broadcastMessage<msgSoundEvent_e>(msgSoundEvent_e::GAME_WON);
        break;       
    default:
        break;
    }
}

msgGameState_e GameControl_c::updateGameState()
{
    StateMachine.performTransition();

    // Transfer the number of lives to the HUD component
    PO->broadcastMessage<msgRemainingLives_s>({ Lives });
    PO->broadcastMessage<msgGameState_e>(StateMachine.state());

    return StateMachine.state();
}

void GameControl_c::setupStateTransitions()
{
    StateMachine.addTransition({ msgGameState_e::TILE_SCREEN,
                                 msgGameState_e::TILE_SCREEN_EXIT,
                                 [this]() { return LastKeyEvent == msgKeyEvent_e::JUMP; },
                                 [this]() { MapIndex = 0; Lives = Constants_s::INITIAL_LIVES; },
                                 statemachine::no_repeated_action
                               });
    StateMachine.addTransition({ msgGameState_e::TILE_SCREEN_EXIT,
                                 msgGameState_e::NORMAL_GAMEPLAY,
                                 statemachine::default_condition,
                                 statemachine::no_onetime_action,
                                 statemachine::no_repeated_action
                               });

    StateMachine.addTransition({ msgGameState_e::NORMAL_GAMEPLAY,
                                 msgGameState_e::BALL_LOST_WAIT,
                                 [this]() { return LastBallState == msgBallStateChange_e::BALL_LOST; },
                                 statemachine::no_onetime_action,
                                 [this]() { WaitTimer += GameClock_c::TimePeriodSec; }
                               });
    StateMachine.addTransition({ msgGameState_e::BALL_LOST_WAIT,
                                 msgGameState_e::BALL_LOST,
                                 [this]() { return WaitTimer >= Constants_s::WAIT_TIME; },
                                 [this]() { WaitTimer = 0; Lives--; },
                                 statemachine::no_repeated_action
                               });
    StateMachine.addTransition({ msgGameState_e::BALL_LOST,
                                 msgGameState_e::NORMAL_GAMEPLAY,
                                 [this]() { return Lives > 0; },
                                 statemachine::no_onetime_action,
                                 statemachine::no_repeated_action
                               });
    
    StateMachine.addTransition({ msgGameState_e::BALL_LOST,
                                 msgGameState_e::GAME_OVER,
                                 [this]() { return Lives == 0; },
                                 statemachine::no_onetime_action,
                                 statemachine::no_repeated_action
                               });
    StateMachine.addTransition({ msgGameState_e::GAME_OVER,
                                 msgGameState_e::TILE_SCREEN,
                                 statemachine::default_condition,
                                 statemachine::no_onetime_action,
                                 statemachine::no_repeated_action
                               });


    StateMachine.addTransition({ msgGameState_e::NORMAL_GAMEPLAY,
                                 msgGameState_e::LEVEL_WON_WAIT,
                                 [this]() { return LastBallState == msgBallStateChange_e::LEVEL_WON; },
                                 statemachine::no_onetime_action,
                                 [this]() { WaitTimer += GameClock_c::TimePeriodSec; }
                               });
    StateMachine.addTransition({ msgGameState_e::LEVEL_WON_WAIT,
                                 msgGameState_e::LEVEL_WON,
                                 [this]() { return WaitTimer >= Constants_s::WAIT_TIME; },
                                 [this]() { WaitTimer = 0; MapIndex++; },
                                 statemachine::no_repeated_action
                               });
    StateMachine.addTransition({ msgGameState_e::LEVEL_WON,
                                 msgGameState_e::NORMAL_GAMEPLAY,
                                 [this]() { return MapIndex + 1 < MapCount; },
                                 [this]() { Lives += Constants_s::LEVEL_WON_BONUS; },
                                 statemachine::no_repeated_action
                               });

    StateMachine.addTransition({ msgGameState_e::LEVEL_WON,
                                 msgGameState_e::GAME_WON,
                                 [this]() { return MapIndex + 1 == MapCount; },
                                 statemachine::no_onetime_action,
                                 statemachine::no_repeated_action
                               });
    StateMachine.addTransition({ msgGameState_e::GAME_WON,
                                 msgGameState_e::TILE_SCREEN,
                                 statemachine::default_condition,
                                 statemachine::no_onetime_action,
                                 statemachine::no_repeated_action
                               });
}

void GameControl_c::sendMessage(msg_t m)
{
    if (isMessageType<msgBallStateChange_e>(m))
    {
        LastBallState = msg_cast<msgBallStateChange_e>(m);
    }
    else if (isMessageType<msgKeyEvent_e>(m))
    {
        LastKeyEvent = msg_cast<msgKeyEvent_e>(m);
    }
}

GameControl_c::GameControl_c(messaging::PostOffice_c* po,
                             msgGameState_e initialState,
                             std::size_t mapCount) :
    MessageRecipient_i(po),
    StateMachine(initialState),
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
