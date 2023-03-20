#pragma once

#include <messaging/postoffice.hpp>
#include <messaging/recipient.hpp>
#include <trailblazer/game/messagetypes.hpp>


namespace trailblazer
{

enum class GameState_e
{
    NORMAL,
    BALL_LOST,
    LEVEL_WON,
    GAME_OVER
};


class GameControl_c : public messaging::MessageRecipient_i
{   
    GameState_e GameState;

    int Lives;

    // Counter to measure the the short time before switching
    // or restarting scene after the ball is lost or the level is won
    float WaitTimer;

public:
    GameState_e getGameState()
    {
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

    void sendMessage(msg_t m) override
    {
        if (isMessageType<msgGameStateChange>(m))
        {
            msgGameStateChange s = msg_cast<msgGameStateChange>(m);
            
            switch(s)
            {
                case msgGameStateChange::BALL_LOST:
                    GameState = GameState_e::BALL_LOST;
                    break;
                case msgGameStateChange::LEVEL_WON:
                    GameState = GameState_e::LEVEL_WON;
                    break;
            }
        }
    }

    GameControl_c(messaging::PostOffice_c* po) :
        MessageRecipient_i(po),
        GameState(GameState_e::NORMAL),
        Lives(Constants_s::INITIAL_LIVES),
        WaitTimer(0.F)
    {   
        // Manage subscriptions
        PO->subscribeRecipient<msgGameStateChange>(this);
    }

};

} // namespace trailblazer