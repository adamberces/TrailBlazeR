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

/////////////////////////////////////////////////////////////////////////////////////////
// 

enum class BallState_e
{
    ON_GROUND,
    JUMPING,
    IN_AIR,
    LOST,
    LEVEL_WON
};

/////////////////////////////////////////////////////////////////////////////////////////
// Represents the ball's movement in the 3D space, inheriting from RigidBody_c
// and realizes the core game physics
//
// Inherits from MessageRecipient_i:
// Provides the msgBallPositionAndDistance message for Ball Drawer
// Receives the msgKeyEvent message from Game Window
// Receives the msgActualTileType message from Map

class BallController_c :
    public messaging::MessageRecipient_i,
    public rigidbody::RigidBody_c
{   
    BallState_e BallState;

    // The last know tile's type on/above which the ball is
    map::TileType_e LastTileType;

    // Time counter used to limit the time for the 
    // jump force is applied on the ball
    double JumpTimer;

    // Keyboard input functions
    void handleKeyboardInput(msgKeyEvent e);
    void moveLeft();
    void moveRight();
    void jump();

    // The main update function, triggered by a keyboard input
    void updateBall();

    // Update the ball state according to the actual tile type
    void handleActualTile();

    // Ball physics, calculate the new position from the actual state
    void addForces(float delta_time);
    void addFriction
        (float rigidbody::Vector3D_s::*component,
         float coefficient);
    void addDrag();

    // Apply world constraints and do collision detection
    void applyMapLimits();

    // Send the resulting new ball position
    void broadcastPosition(float delta_time);

public:
    void sendMessage(msg_t m) override;
    BallController_c(messaging::PostOffice_c* po);
};

} // namespace trailblazer::ball