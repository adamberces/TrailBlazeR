#include <trailblazer/game/gamecontrol.hpp>


namespace trailblazer
{

/////////////////////////////////////////////////////////////////////////////////////////
// Definition for the static class member Lives
int GameControl_c::Lives = Constants_s::INITIAL_LIVES;


/////////////////////////////////////////////////////////////////////////////////////////
// Implementation for GameControl_c

void GameControl_c::resetLives()
{
    Lives = Constants_s::INITIAL_LIVES;
}

void GameControl_c::triggerSound()
{
    switch (GameState)
    {
    case msgGameStateChange_e::BALL_LOST:
        PO->broadcastMessage<msgSoundEvent_e>(msgSoundEvent_e::BALL_LOST);
        break;
    case msgGameStateChange_e::LEVEL_WON:
        PO->broadcastMessage<msgSoundEvent_e>(msgSoundEvent_e::LEVEL_WON);
        break;
    case msgGameStateChange_e::GAME_OVER:
        PO->broadcastMessage<msgSoundEvent_e>(msgSoundEvent_e::GAME_OVER);
        break;     
    case msgGameStateChange_e::GAME_WON:
        PO->broadcastMessage<msgSoundEvent_e>(msgSoundEvent_e::GAME_WON);
        break;       
    default:
        break;
    }
}

msgGameStateChange_e GameControl_c::getGameState(bool isLastMap)
{
    // Transfer the number of lives to the HUD component
    PO->broadcastMessage<msgRemainingLives_s>({ Lives });
    PO->broadcastMessage<msgGameStateChange_e>(GameState);

    if (GameState == msgGameStateChange_e::TILE_SCREEN ||
        GameState == msgGameStateChange_e::NORMAL)
    {
        return GameState;
    }
    else if (GameState == msgGameStateChange_e::GAME_START)
    {
        GameState = msgGameStateChange_e::NORMAL;
        return msgGameStateChange_e::GAME_START;
    }
    else
    {
        if (WaitTimer == 0.F)
        {
            // Decrement lives if the ball was lost
            // and see if that was the last one...
            if (GameState == msgGameStateChange_e::BALL_LOST)
            {
                if (--Lives == 0)
                {
                    GameState = msgGameStateChange_e::GAME_OVER;
                }
            }

            // If we are on the current map and the level
            // is won it means that the whole game is won
            if (GameState == msgGameStateChange_e::LEVEL_WON && isLastMap)
            {
                GameState = msgGameStateChange_e::GAME_WON;
            }

            // Play the corresponding sound effect once
            // for the game state change on state transition
            triggerSound();
        }

        // Add game cycle period to the wait counter
        WaitTimer += GameClock_c::TimePeriodSec;
        
        // When the time is up, inform the main Game class about the
        // resulting state
        if (WaitTimer >= Constants_s::WAIT_TIME)
        {
            WaitTimer = 0.F;
            return GameState;
        }
    }

    return msgGameStateChange_e::NORMAL;
}

void GameControl_c::setupStateTransitions()
{
    StateMachine.addTransition({ msgGameStateChange_e::TILE_SCREEN,
                                 msgGameStateChange_e::NORMAL,
                                 [this]() { return LastKeyEvent == msgKeyEvent_e::JUMP; }
                               });


    StateMachine.addTransition({ msgGameStateChange_e::NORMAL,
                                 msgGameStateChange_e::BALL_LOST_WAIT,
                                 [this]() { return LastBallState == msgBallStateChange_e::BALL_LOST; },
                                 statemachine::no_onetime_action,
                                 [this]() { WaitTimer += GameClock_c::TimePeriodSec; }
                               });
    StateMachine.addTransition({ msgGameStateChange_e::BALL_LOST_WAIT,
                                 msgGameStateChange_e::BALL_LOST,
                                 [this]() { return WaitTimer >= Constants_s::WAIT_TIME; },
                                 [this]() { WaitTimer = 0; Lives--; },
                                 statemachine::no_repeated_action
                               });
    StateMachine.addTransition({ msgGameStateChange_e::BALL_LOST,
                                 msgGameStateChange_e::NORMAL,
                                 [this]() { return Lives > 0; },
                                 statemachine::no_onetime_action,
                                 statemachine::no_repeated_action
                               });
    
    StateMachine.addTransition({ msgGameStateChange_e::BALL_LOST,
                                 msgGameStateChange_e::GAME_OVER,
                                 [this]() { return Lives == 0; },
                                 statemachine::no_onetime_action,
                                 statemachine::no_repeated_action
                               });
    StateMachine.addTransition({ msgGameStateChange_e::GAME_OVER,
                                 msgGameStateChange_e::TILE_SCREEN,
                                 statemachine::default_condition,
                                 [this]() { MapIndex = 0; Lives == Constants_s::INITIAL_LIVES; },
                                 statemachine::no_repeated_action
                               });


    StateMachine.addTransition({ msgGameStateChange_e::NORMAL,
                                 msgGameStateChange_e::GAME_OVER_WAIT,
                                 [this]() { LastBallState == msgBallStateChange_e::BALL_LOST; },
                                 statemachine::no_onetime_action,
                                 [this]() { WaitTimer += GameClock_c::TimePeriodSec; }
                               });
    StateMachine.addTransition({ msgGameStateChange_e::BALL_LOST_WAIT,
                                 msgGameStateChange_e::BALL_LOST,
                                 [this]() { WaitTimer = 0; Lives--; },
                                 statemachine::no_repeated_action
                               });

    StateMachine.addTransition({ msgGameStateChange_e::BALL_LOST,
                                 msgGameStateChange_e::NORMAL,
                                 [this]() { Lives > 0; }
        });

    StateMachine.addTransition({ msgGameStateChange_e::NORMAL,
                                 msgGameStateChange_e::LEVEL_WON,
                                 [this]() { LastBallState == msgBallStateChange_e::LEVEL_WON; }
                               });

    StateMachine.addTransition({ msgGameStateChange_e::TILE_SCREEN,
                                 msgGameStateChange_e::NORMAL,
                                 [this]() { LastKeyEvent == msgKeyEvent_e::JUMP; }
        });
}

void GameControl_c::sendMessage(msg_t m)
{
    if (isMessageType<msgBallStateChange_e>(m))
    {
        if (GameState != msgGameStateChange_e::TILE_SCREEN &&
            GameState != msgGameStateChange_e::GAME_START)
        {
            msgBallStateChange_e s = msg_cast<msgBallStateChange_e>(m);

            switch (s)
            {
            case msgBallStateChange_e::BALL_LOST:
                GameState = msgGameStateChange_e::BALL_LOST;
                break;
            case msgBallStateChange_e::LEVEL_WON:
                GameState = msgGameStateChange_e::LEVEL_WON;
                break;
            }
        }
    }
    else if (isMessageType<msgKeyEvent_e>(m))
    {
        if (GameState == msgGameStateChange_e::TILE_SCREEN)
        {
            msgKeyEvent_e e = msg_cast<msgKeyEvent_e>(m);
            if (e == msgKeyEvent_e::JUMP)
            {
                GameState = msgGameStateChange_e::GAME_START;
            }
        }
    }
}

GameControl_c::GameControl_c(messaging::PostOffice_c* po, msgGameStateChange_e initialState) :
    MessageRecipient_i(po),
    GameState(initialState),
    WaitTimer(0.F)
{   
    // Manage subscriptions
    PO->subscribeRecipient<msgBallStateChange_e>(this);
    PO->subscribeRecipient<msgKeyEvent_e>(this);
}

} // namespace trailblazer
