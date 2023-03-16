#pragma once

#include <messaging/postoffice.hpp>
#include <messaging/recipient.hpp>
#include <trailblazer/game/messagetypes.hpp>


namespace trailblazer
{

enum class GameState_e
{
    MAIN_MENU,
    LEVEL_START,
    LEVEL_RUNNING,
    LEVEL_END,
    GAME_END,
    GAME_OVER
};

enum class BallState_e
{
    NORMAL,
    JUMPING,
    FALLING,
    FALLING_OFF
};



class GameControl_c : public messaging::MessageRecipient_i
{   
    GameState_e GameState;
    BallState_e BallState = ROLLING;

    void handleActualTile(map::TileType_e tt)
    {
        switch (tt)
        {
            case map::TileType_e::GAP:

        }
    }

public:
    void sendMessage(std::any m) override
    {
        if (isMessageType<msgActualTileType>(m))
        {
            msgActualTileType tt = std::any_cast<msgActualTileType>(m);
            handleActualTile(tt);
        }
    }

    GameControl_c(messaging::PostOffice_c* po) :
        MessageRecipient_i(po)
    {   
        // Manage subscriptions
        PO->subscribeRecipient<msgActualTileType>(this);
        PO->subscribeRecipient<msgKeyEvent>(this);
    }

};

} // namespace trailblazer