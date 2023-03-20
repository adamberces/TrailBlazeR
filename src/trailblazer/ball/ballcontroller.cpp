#include <trailblazer/ball/ballcontroller.hpp>


namespace trailblazer::ball
{

/////////////////////////////////////////////////////////////////////////////////////////
// Implementation for BallController_c

void BallController_c::updateBall()
{
    double dt = GameClock_c::get().elapsedTime();
    
    handleActualTile();
    addForces(dt);
    updatePosition(dt);
    applyMapLimits();
    
    broadcastPosition(dt);
}

void BallController_c::handleActualTile()
{
    switch (LastTileType)
    {
        case map::TileType_e::GAP:
            if (BallState == BallState_e::ON_GROUND)
            {
                BallState = BallState_e::LOST;

                // Inform game control if the ball is lost
                PO->broadcastMessage<msgGameStateChange>(msgGameStateChange::BALL_LOST);
            }
            break;
        case map::TileType_e::SPEEDUP:
            if (BallState == BallState_e::ON_GROUND)
            {
                Velocity.Y += Constants_s::SPEEDUP_ADDED_VELOCITY;
            }
            break;
        case map::TileType_e::SLOWDOWN:
            if (BallState == BallState_e::ON_GROUND)
            {
                Velocity.Y = Constants_s::START_VELOCITY;
            }
            break;
        case map::TileType_e::FINISH:
            if (BallState != BallState_e::LEVEL_WON)
            {
                BallState = BallState_e::LEVEL_WON;

                // Inform game control if the level is won
                PO->broadcastMessage<msgGameStateChange>(msgGameStateChange::LEVEL_WON);
            }
            break;
        case map::TileType_e::NORMAL:
            break;
    }
    

    // Do the state transition between In air vs. On ground
    // if the ball is on the ground level (Z == 0) and no 
    // other special states are present
    if (BallState != BallState_e::JUMPING &&
        BallState != BallState_e::LOST &&
        BallState != BallState_e::LEVEL_WON)
    {
        if (Position.Z == 0.F)
        {
            BallState = BallState_e::ON_GROUND;
        }
        else
        {
            BallState = BallState_e::IN_AIR;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
// Ball physics implementation, calculate the new position of the ball
// according to the actual state

void BallController_c::addForces(float delta_time)
{
    // Handle jumping, add velocity to the Z speed component
    // for a short period of time
    if (BallState == BallState_e::JUMPING)
    {
        Velocity.Z = Constants_s::JUMP_VELOCITY;

        JumpTimer += delta_time;
        if (JumpTimer >= Constants_s::JUMP_TIME)
        {
            BallState = BallState_e::IN_AIR;
        }
    }

    // If the ball is on the ground, apply friction
    if (BallState == BallState_e::ON_GROUND)
    {
        addFriction(&rigidbody::Vector3D_s::X,
            Constants_s::FRICITON_COEFFICIENT_X);
    }

    // If the ball is in the air, apply gravity and air drag
    if (BallState == BallState_e::JUMPING ||
        BallState == BallState_e::IN_AIR)
    {
        addForce(rigidbody::Vector3D_s(0, 0, -(Constants_s::GRAVITY)));

        if (Velocity.Z > 0)
        {
            addDrag();
        }
    }
    
    // If the level is won, stop the ball gradually by applying friction
    if (BallState == BallState_e::LEVEL_WON)
    {
        if (Position.Z <= 0)
        {
            Position.Z = 0;
        }

        addFriction(&rigidbody::Vector3D_s::X,
            Constants_s::FRICITON_COEFFICIENT_ENDLEVEL);
        addFriction(&rigidbody::Vector3D_s::Y,
            Constants_s::FRICITON_COEFFICIENT_ENDLEVEL);
    }

}

// This function calculates and applies friction to a given component of a Vector3D
// as we want to have a different magnitude of friction on the ball's left/right movement
// on the occasions when the ball is bouncing and it hits the ground in order to stop the
// ball's bouncing in a short term, but at the same time maintain a realistic look & feel.
//
// Another trick here is that the Y component of the ball's speed vector normally is never 
// influenced by friction, nor any other force to maintain a continous moving forward.
// Only the magnitude of the Y component is changed when moving on speedup/slowdown tiles,
// so according to Newton's first law the ball will move forward during the entire gameplay.
// The only exception from this is when the level is won, when we will stop the ball gradually
// by applying a huge friction force on the Y component as well.

void BallController_c::addFriction(float rigidbody::Vector3D_s::*component, float coefficient)
{
    // Get the direction of the force
    rigidbody::Vector3D_s v = Velocity.normalize();
    float velocityComponent = v.*component;

    // Calculate friction force
    constexpr float normalForce = Constants_s::BALL_MASS * Constants_s::GRAVITY;
    float frictionMagnitude = velocityComponent * normalForce * -1 * coefficient;

    // Create vector object and apply the magnitude of the force to the desired component
    rigidbody::Vector3D_s frictionForce(0.F, 0.F, 0.F);
    frictionForce.*component = frictionMagnitude;
    addForce(frictionForce);
}

void BallController_c::addDrag()
{
    // Calculate the crossection area of the sphere in compile time
    constexpr float crossectionArea =
        Constants_s::BALL_DIAMETER * Constants_s::BALL_DIAMETER * Constants_s::PI;

    // Calculate drag force using the enironmental constants
    float dragMagnitude =
        -0.5F * Constants_s::SPHERE_DRAG_COEFFICIENT *
        Constants_s::AIR_DENSITY * crossectionArea *
        (Velocity.Z * Velocity.Z);


    // Reverse the direction of the force, it the ball is falling
    if (Velocity.Z < 0.F)
    {
        dragMagnitude *= -1;
    }

    // Create vector object and apply the force
    rigidbody::Vector3D_s dragForce(0.F, 0.F, dragMagnitude);
    addForce(dragForce);
}      
    

/////////////////////////////////////////////////////////////////////////////////////////
// Apply world constraints and do collision detection on the ball 
// Updates ball position and velocity for specific conditions

void BallController_c::applyMapLimits()
{
    // Stop movement in the X direction on the edges of the map
    // and also zero the corresponding speed component
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

    // Stop the ball on the ground (if there's ground :-)
    if (BallState != BallState_e::LOST &&
        Position.Z <= 0)
    {
        Position.Z = 0;

        // Add bouncing to the ball when the ground is hit
        // (except when the level is won when we want to stop
        // the ball as soon as possible or the ball will fall
        // down due to a gap)
        if (BallState != BallState_e::LEVEL_WON &&
            LastTileType != map::TileType_e::GAP)
        {
            Velocity.Z = -Velocity.Z;

            // Also add some friction for the Z component
            // to lose some energy everytime it hits the ground again
            // and finally stop bouncing
            addFriction(&rigidbody::Vector3D_s::Z,
                Constants_s::FRICITON_COEFFICIENT_Z);
        }
    }
}


/////////////////////////////////////////////////////////////////////////////////////////
// Handle keyboard input

void BallController_c::handleKeyboardInput(msgKeyEvent e)
{
    // Allow keyboard input only when the ball
    // is on ground and no other special conditions
    // (eg. ball is lost or level is over) are present
    if (BallState == BallState_e::ON_GROUND)
    {
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

    // Call the main update function
    updateBall();
}
    
void BallController_c::moveLeft()
{
    addForce(rigidbody::Vector3D_s(-(Constants_s::CONTROL_FORCE_X), 0.F, 0.F));
}

void BallController_c::moveRight()
{
    addForce(rigidbody::Vector3D_s(Constants_s::CONTROL_FORCE_X, 0.F, 0.F));
}

void BallController_c::jump()
{
    // Allow jumping only when the ball is on ground
    // If yes, do a state transition which will be handled in addForces
    if (BallState == BallState_e::ON_GROUND)
    {
        JumpTimer = 0;
        BallState = BallState_e::JUMPING;
    }
}


/////////////////////////////////////////////////////////////////////////////////////////
// Messaging and constructor

void BallController_c::sendMessage(msg_t m)
{
    if (isMessageType<msgKeyEvent>(m))
    {
        msgKeyEvent e = msg_cast<msgKeyEvent>(m);
        handleKeyboardInput(e);
    }
    else if (isMessageType<msgActualTileType>(m))
    {
        msgActualTileType tt = msg_cast<msgActualTileType>(m);
        LastTileType = tt.Type;
    }
}

void BallController_c::broadcastPosition(float delta_time)
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

BallController_c::BallController_c(messaging::PostOffice_c* po) :
    MessageRecipient_i(po),
    BallState(BallState_e::IN_AIR),
    LastTileType(map::TileType_e::NORMAL),
    RigidBody_c(rigidbody::Vector3D_s(Constants_s::START_POSITION_X,
                                        Constants_s::START_POSITION_Y,
                                        Constants_s::START_POSITION_Z),
                rigidbody::Vector3D_s(0, Constants_s::START_VELOCITY, 0),
                Constants_s::BALL_MASS)
{   
    // Manage subscriptions
    PO->subscribeRecipient<msgKeyEvent>(this);
    PO->subscribeRecipient<msgActualTileType>(this);
}

} // namespace trailblazer::ball