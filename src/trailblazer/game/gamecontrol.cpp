#include <trailblazer/game/gamecontrol.hpp>


namespace trailblazer
{

/////////////////////////////////////////////////////////////////////////////////////////
// Definition for the static class member Lives
int GameControl_c::Lives = Constants_s::INITIAL_LIVES;


/////////////////////////////////////////////////////////////////////////////////////////
// Implementation for GameControl_c

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

    if (GameState != msgGameStateChange_e::NORMAL)
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

void GameControl_c::sendMessage(msg_t m)
{
    if (isMessageType<msgBallStateChange_e>(m))
    {
        msgBallStateChange_e s = msg_cast<msgBallStateChange_e>(m);
        
        switch(s)
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

GameControl_c::GameControl_c(messaging::PostOffice_c* po) :
    MessageRecipient_i(po),
    GameState(msgGameStateChange_e::NORMAL),
    WaitTimer(0.F)
{   
    // Manage subscriptions
    PO->subscribeRecipient<msgBallStateChange_e>(this);
}

} // namespace trailblazer
