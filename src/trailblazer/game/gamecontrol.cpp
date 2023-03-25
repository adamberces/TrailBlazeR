#include <trailblazer/game/gamecontrol.hpp>


namespace trailblazer
{

/////////////////////////////////////////////////////////////////////////////////////////
// Definition for the static class member Lives
int GameControl_c::Lives = Constants_s::INITIAL_LIVES;


/////////////////////////////////////////////////////////////////////////////////////////
// Implementation for GameControl_c

GameState_e GameControl_c::getGameState()
{
    PO->broadcastMessage<msgRemainingLives_s>({ Lives });

    if (GameState == GameState_e::BALL_LOST ||
        GameState == GameState_e::LEVEL_WON)
    {
        WaitTimer += GameClock_c::get().elapsedTime();
        if (WaitTimer >= Constants_s::WAIT_TIME)
        {
            WaitTimer = 0;
            if (GameState == GameState_e::BALL_LOST)
            {
                Lives--;
                if (Lives == 0)
                {
                    GameState = GameState_e::GAME_OVER;
                }
            }
            return GameState;
        }
    }

    return GameState_e::NORMAL;
}

void GameControl_c::sendMessage(msg_t m)
{
    if (isMessageType<msgGameStateChange_e>(m))
    {
        msgGameStateChange_e s = msg_cast<msgGameStateChange_e>(m);
        
        switch(s)
        {
            case msgGameStateChange_e::BALL_LOST:
                GameState = GameState_e::BALL_LOST;
                break;
            case msgGameStateChange_e::LEVEL_WON:
                GameState = GameState_e::LEVEL_WON;
                break;
        }
    }
}

GameControl_c::GameControl_c(messaging::PostOffice_c* po) :
    MessageRecipient_i(po),
    GameState(GameState_e::NORMAL),
    WaitTimer(0.F)
{   
    // Manage subscriptions
    PO->subscribeRecipient<msgGameStateChange_e>(this);
}

} // namespace trailblazer
