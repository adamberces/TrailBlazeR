#pragma once

#include <messaging/postoffice.hpp>
#include <messaging/recipient.hpp>
#include <trailblazer/game/messagetypes.hpp>

#include <rigidbody/rigidbody.hpp>
#include <trailblazer/game/clock.hpp>

#include <iostream>

namespace trailblazer::ball
{

enum class BallState_e
{
    NORMAL,
    JUMPING,
    FALLING,
    LOST
};


class BallControl_c : public messaging::MessageRecipient_i
{   
    BallState_e BallState;
    rigidbody::RigidBody_c BallPhysics;
    
    void moveLeft()
    {
        BallPhysics.add_force(rigidbody::Vector3D_s(-1, 0, 0));
    }

    void moveRight()
    {
        BallPhysics.add_force(rigidbody::Vector3D_s(1, 0, 0));
    }

    void jump()
    {
        BallPhysics.add_force(rigidbody::Vector3D_s(0, 0, 1));
    }

    void handleActualTile(map::TileType_e tt)
    {
        std::cout << (int)tt << std::endl;
        /*
        switch (tt)
        {
           
            case map::TileType_e::GAP:
                BallState = BallState_e::LOST;
                break;
        }*/
    }

public:
    void sendMessage(std::any m) override
    {
        if (isMessageType<msgKeyEvent>(m))
        {
            msgKeyEvent e = std::any_cast<msgKeyEvent>(m);

            switch(e)
            {
            case msgKeyEvent::JUMP:
                jump();
                break;
            case msgKeyEvent::LEFT:
                moveLeft();
                break;
            case msgKeyEvent::RIGHT:
                moveRight();
                break;
            case msgKeyEvent::NONE:
                break;
            }

            updatePosition();
        }
        else if (isMessageType<msgActualTileType>(m))
        {
            msgActualTileType tt = std::any_cast<msgActualTileType>(m);
            handleActualTile(tt.Type);
        }
    }

    void updatePosition()
    {
        double dt = GameClock_c::get().elapsedTime();
        BallPhysics.update(dt);

        rigidbody::Vector3D_s pos = BallPhysics.position();
        rigidbody::Vector3D_s v = BallPhysics.velocity();

        // Calculate the horizontal speed of the
        // ball by zeroing the Z component
        v.Z = 0.F;
        float speed = v.magnitude();

        msgBallPositionAndSpeed msg({  speed, {pos.X, pos.Y, pos.Z}});
        PO->broadcastMessage<msgBallPositionAndSpeed>(msg);
    }

    BallControl_c(messaging::PostOffice_c* po) :
        MessageRecipient_i(po),
       // BallState(BallState_e::ROLLING),
        BallPhysics(rigidbody::Vector3D_s(2.5, .375, .375), rigidbody::Vector3D_s(0, 1, 0), 1)
    {   
        // Manage subscriptions
        PO->subscribeRecipient<msgKeyEvent>(this);
        PO->subscribeRecipient<msgActualTileType>(this);
    }

};

} // namespace trailblazer::ball