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
/// Represents the current state of the ball:
/// - moving on ground (for convience, the ground level is defined as Z = 0)
/// - the force to perform a jump is actively maintained
/// - the ball is in air (because of the remaining velocity from the jumping force, eg. bouncing)
/// - ball felling down in a gap and level will restart soon
/// - the finish line is reached by the ball and next level will start soon

enum class BallState_e
{
    ON_GROUND,
    JUMPING,
    IN_AIR,
    LOST,
    LEVEL_WON
};

/////////////////////////////////////////////////////////////////////////////////////////
/// Represents the ball's movement in the 3D space, inheriting from RigidBody_c
/// and realizes the core game physics
//
/// Inherits from MessageRecipient_i:
/// Provides the msgBallPositionAndDistance_s message for Ball Drawer
/// Receives the msgKeyEvent_e message from Game Window
/// Receives the msgActualTileType_s message from Map

class BallControl_c :
    public messaging::MessageRecipient_i,
    public rigidbody::RigidBody_c
{   
    BallState_e BallState;

    /// The last know tile's type on/above which the ball is
    map::TileType_e LastTileType;

    /// Time counter used to limit the time for the 
    /// jump force is applied on the ball
    double JumpTimer;

    /// Keyboard input functions
    void handleKeyboardInput(msgKeyEvent_e e);
    void moveLeft();
    void moveRight();
    void jump();

    /// The main update function, triggered by a keyboard input
    void updateBall();

    /// Update the ball state according to the actual tile type
    void handleActualTile();

    /// Ball physics, calculate the new position from the actual state
    void addForces(float delta_time);
    void addFriction
        (float rigidbody::Vector3D_s::* component,
         float coefficient);
    void addDrag();

    /// Apply world constraints and do collision detection
    void applyMapLimits();

    /// Send the resulting new ball position
    void broadcastPosition(float delta_time);

public:
    void sendMessage(msg_t m) override;
    explicit BallControl_c(messaging::PostOffice_c* po);
};

} // namespace trailblazer::ball