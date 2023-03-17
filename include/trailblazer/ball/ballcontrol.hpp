#pragma once

#include <messaging/postoffice.hpp>
#include <messaging/recipient.hpp>
#include <trailblazer/game/messagetypes.hpp>

#include <rigidbody/rigidbody.hpp>
#include <trailblazer/game/clock.hpp>
#include <trailblazer/game/constants.hpp>

#include <iostream>

namespace trailblazer::ball
{

enum class BallState_e
{
    NORMAL,
    JUMPING,
    IN_AIR,
    LOST
};

class BallControl_c :
    public messaging::MessageRecipient_i,
    public rigidbody::RigidBody_c
{   
    BallState_e BallState;
    double JumpTimer;


    void moveLeft()
    {
        addForce(rigidbody::Vector3D_s(-10.F, 0.F, 0.F));
    }

    void moveRight()
    {
        addForce(rigidbody::Vector3D_s(10.F, 0.F, 0.F));
    }

    void addFriction(float rigidbody::Vector3D_s::*component, float coefficient)
    {
        // Get the direction of the force
        rigidbody::Vector3D_s v = Velocity.normalize();
        float velocityComponent = v.*component;
        constexpr float normalForce = Constants_s::BALL_MASS * Constants_s::GRAVITY;
        float frictionMagnitude = velocityComponent * normalForce * -1 * coefficient;

        rigidbody::Vector3D_s frictionForce(0.F, 0.F, 0.F);
        frictionForce.*component = frictionMagnitude;
        addForce(frictionForce);
    }

    void addDrag()
    {
        float dragCoefficient = 0.47F;
        float airDensity = 1.29F;
        constexpr float crossectionArea = Constants_s::BALL_DIAMETER * Constants_s::BALL_DIAMETER * 3.14159F;
        float dragMagnitude = -0.5F * dragCoefficient * airDensity * crossectionArea * (Velocity.Z * Velocity.Z);
        if (Velocity.Z < 0.F)
        {
            dragMagnitude *= -1;
        }
        rigidbody::Vector3D_s dragForce(0.F, 0.F, dragMagnitude);
        addForce(dragForce);
    }
        
    
    void jump()
    {
        if (BallState == BallState_e::NORMAL)
        {
            JumpTimer = 0;
            BallState = BallState_e::JUMPING;
        }
    }


    void applyConstraints()
    {
        if (Position.X < 0)
        {
            Position.X = 0;
            Velocity.X = 0;
        }
        else if (Position.X > Constants_s::MAP_WIDTH - 1)
        {
            Position.X = Constants_s::MAP_WIDTH - 1;
            Velocity.X = 0;
        }

        if (BallState != BallState_e::LOST && Position.Z <= 0)
        {
            Position.Z = 0;
            Velocity.Z = -Velocity.Z;
            addFriction(&rigidbody::Vector3D_s::Z, 5.F);
        }

        printf("Z %f v%f %d\n", Position.Z, Velocity.Z, (int)BallState);
    }

    void addForces(float delta_time)
    {
        if (BallState == BallState_e::JUMPING)
        {
            Velocity.Z = 4;

            JumpTimer += delta_time;
            if (JumpTimer >= 0.1)
            {
                BallState = BallState_e::IN_AIR;
            }
        }
        if (BallState != BallState_e::NORMAL)
        {
            addForce(rigidbody::Vector3D_s(0, 0, -(Constants_s::GRAVITY)));
            if (Velocity.Z > 0)
            {
                addDrag();
            }
        }
        else
        {
            addFriction(&rigidbody::Vector3D_s::X, .2F);
        }

    }

    void handleActualTile(map::TileType_e tt)
    {
        switch (tt)
        {
            case map::TileType_e::GAP:
                if (BallState == BallState_e::NORMAL &&
                    Velocity.Z <= 0.1F)
                {
                    printf("lost\n");
                    BallState = BallState_e::LOST;
                }
                break;
            case map::TileType_e::SPEEDUP:
                if (BallState == BallState_e::NORMAL)
                {
                    Velocity.Y += 0.1;
                }
                break;
            case map::TileType_e::SPEEDDOWN:
                if (BallState == BallState_e::NORMAL)
                {
                    Velocity.Y = 1;
                }
                break;
            case map::TileType_e::FINISH:
            case map::TileType_e::NORMAL:
                break;
        }
        
        if (BallState != BallState_e::LOST)
        {
            if (Position.Z == 0)
            {
                BallState = BallState_e::NORMAL;
            }
            else
            {
                BallState = BallState_e::IN_AIR;
            }
        }
    }

    void broadcastPosition(float delta_time)
    {
        // Calculate the horizontal speed of the
        // ball by zeroing the Z component
        rigidbody::Vector3D_s v = Velocity;
        v.Z = 0.F;
        float speed = v.magnitude();
        float dist = speed * delta_time;
        
        msgBallPositionAndDistance msg({ dist, {Position.X, Position.Y, Position.Z}});
        PO->broadcastMessage<msgBallPositionAndDistance>(msg);
    }

public:
    void updatePosition()
    {
        double dt = GameClock_c::get().elapsedTime();
        addForces(dt);
        update(dt);
        applyConstraints();
        broadcastPosition(dt);
    }

    void sendMessage(std::any m) override
    {
        if (isMessageType<msgKeyEvent>(m))
        {
            if (BallState == BallState_e::NORMAL)
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
            }
            updatePosition();
        }
        else if (isMessageType<msgActualTileType>(m))
        {
            msgActualTileType tt = std::any_cast<msgActualTileType>(m);
            handleActualTile(tt.Type);
        }
    }

    BallControl_c(messaging::PostOffice_c* po) :
        MessageRecipient_i(po),
        BallState(BallState_e::NORMAL),
        RigidBody_c(rigidbody::Vector3D_s(2, 0, 0), rigidbody::Vector3D_s(0, 1, 0), Constants_s::BALL_MASS)
    {   
        // Manage subscriptions
        PO->subscribeRecipient<msgKeyEvent>(this);
        PO->subscribeRecipient<msgActualTileType>(this);
    }

};

} // namespace trailblazer::ball