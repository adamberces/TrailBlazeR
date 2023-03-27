#include <trailblazer/ball/ballcontrol.hpp>


namespace trailblazer::ball
{

/////////////////////////////////////////////////////////////////////////////////////////
// Implementation for BallControl_c

void BallControl_c::updateBall()
{
    double dt = GameClock_c::get().elapsedTime();
    
    handleActualTile();
    addForces(dt);
    updatePosition(dt);
    applyMapLimits();
    
    broadcastPosition(dt);
}

/////////////////////////////////////////////////////////////////////////////////////////
// Handle the actual tile type on/above which the ball is
// and do a state transition of BallState if needed

void BallControl_c::handleActualTile()
{
    switch (LastTileType)
    {
        case map::TileType_e::GAP:
            if (BallState == BallState_e::ON_GROUND)
            {
                BallState = BallState_e::LOST;

                // Inform game control and sound control if the ball is lost
                PO->broadcastMessage<msgGameStateChange_e>(msgGameStateChange_e::BALL_LOST);
                PO->broadcastMessage<msgSoundEvent_e>(msgSoundEvent_e::BALL_LOST);
            }
            break;
            
        case map::TileType_e::SPEEDUP:
            if (BallState == BallState_e::ON_GROUND)
            {
                Velocity.Y += Constants_s::SPEEDUP_ADDED_VELOCITY;
                PO->broadcastMessage<msgSoundEvent_e>(msgSoundEvent_e::SPEEDUP);
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
                PO->broadcastMessage<msgGameStateChange_e>(msgGameStateChange_e::LEVEL_WON);
                PO->broadcastMessage<msgSoundEvent_e>(msgSoundEvent_e::LEVEL_WON);
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

void BallControl_c::addForces(float delta_time)
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

static float sgn(float f)
{
    return ( f < 0.F ? -1.F : 1.F  );
}

void BallControl_c::addFriction(float rigidbody::Vector3D_s::* component, float coefficient)
{
    // Get the direction of the force
    float velocityDirection = sgn(Velocity.*component);

    // Calculate friction force
    constexpr float normalForce = Constants_s::BALL_MASS * Constants_s::GRAVITY;
    float frictionMagnitude = velocityDirection * normalForce * -1 * coefficient;

    // Create vector object and apply the magnitude of the force to the desired component
    rigidbody::Vector3D_s frictionForce(0.F, 0.F, 0.F);
    frictionForce.*component = frictionMagnitude;
    addForce(frictionForce);
}

void BallControl_c::addDrag()
{
    // Calculate the crossection area of the sphere in compile time
    constexpr float crossectionArea =
        Constants_s::BALL_DIAMETER * Constants_s::BALL_DIAMETER * Constants_s::PI;

    // Calculate drag force using the enironmental constants
    float dragMagnitude =
        -0.5F * Constants_s::SPHERE_DRAG_COEFFICIENT *
        Constants_s::AIR_DENSITY * crossectionArea *
        (Velocity.Z * Velocity.Z) * sgn(Velocity.Z);

    // Create vector object and apply the force
    rigidbody::Vector3D_s dragForce(0.F, 0.F, dragMagnitude);
    addForce(dragForce);
}      
    

/////////////////////////////////////////////////////////////////////////////////////////
// Apply world constraints and do collision detection on the ball 
// Updates ball position and velocity for specific conditions

void BallControl_c::applyMapLimits()
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
        applyBounce();
    }
}

// Bounce back to the ball when the ground is hit, except when:
// - the level is won when we want to stop the ball ASAP
// - the ball will fall down due to a gap is under the ball
// - The Z component of velocity is already too slow to bounce back

void BallControl_c::applyBounce()
{
    bool isAllowedState =
        (BallState == BallState_e::ON_GROUND ||
         BallState == BallState_e::IN_AIR);

    if (::abs(Velocity.Z) < 0.01)
    {
        Velocity.Z == 0.F;
    }
    else if (isAllowedState && LastTileType != map::TileType_e::GAP)
    {
        Velocity.Z = -Velocity.Z;

        // Also add some friction for the Z component
        // to lose some energy everytime it hits the ground again
        // and finally stop bouncing
        addFriction(&rigidbody::Vector3D_s::Z,
            Constants_s::FRICITON_COEFFICIENT_Z);

        // Trigger Sound Control to play a sound if the ball touches the ground
        PO->broadcastMessage<msgSoundEvent_e>(msgSoundEvent_e::BOUNCE);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
// Handle keyboard input

void BallControl_c::handleKeyboardInput(msgKeyEvent_e e)
{
    // Allow keyboard input only when the ball
    // is on ground and no other special conditions
    // (eg. ball is lost or level is over) are present
    if (BallState == BallState_e::ON_GROUND)
    {
        switch(e)
        {
        case msgKeyEvent_e::JUMP:
            jump();
            break;
        case msgKeyEvent_e::LEFT:
            moveLeft();
            break;
        case msgKeyEvent_e::RIGHT:
            moveRight();
            break;
        case msgKeyEvent_e::NONE:
            break;
        }
    }

    // Call the main update function
    updateBall();
}
    
void BallControl_c::moveLeft()
{
    addForce(rigidbody::Vector3D_s(-(Constants_s::CONTROL_FORCE_X), 0.F, 0.F));
}

void BallControl_c::moveRight()
{
    addForce(rigidbody::Vector3D_s(Constants_s::CONTROL_FORCE_X, 0.F, 0.F));
}

void BallControl_c::jump()
{
    // Allow jumping only when the ball is on ground
    // If yes, do a state transition which will be handled in addForces
    if (BallState == BallState_e::ON_GROUND)
    {
        JumpTimer = 0;
        BallState = BallState_e::JUMPING;

        // Play jumping sound
        PO->broadcastMessage<msgSoundEvent_e>(msgSoundEvent_e::JUMP);
    }
}


/////////////////////////////////////////////////////////////////////////////////////////
// Messaging and constructor

void BallControl_c::sendMessage(msg_t m)
{
    if (isMessageType<msgKeyEvent_e>(m))
    {
        msgKeyEvent_e e = msg_cast<msgKeyEvent_e>(m);
        handleKeyboardInput(e);
    }
    else if (isMessageType<msgActualTileType_s>(m))
    {
        msgActualTileType_s tt = msg_cast<msgActualTileType_s>(m);
        LastTileType = tt.Type;
    }
}

void BallControl_c::broadcastPosition(float delta_time)
{
    // Calculate the horizontal speed of the
    // ball by zeroing the Z component
    rigidbody::Vector3D_s v = Velocity;
    v.Z = 0.F;
    float speed = v.magnitude();
    float dist = speed * delta_time;
    
    msgBallPositionAndDistance_s msg;
    msg.Distance = dist;
    msg.Position = { Position.X, Position.Y, Position.Z };
    msg.Position = { Position.X, Position.Y, Position.Z };
    PO->broadcastMessage<msgBallPositionAndDistance_s>(msg);
}

BallControl_c::BallControl_c(messaging::PostOffice_c* po) :
    MessageRecipient_i(po),
    RigidBody_c(rigidbody::Vector3D_s(Constants_s::START_POSITION_X,
                                        Constants_s::START_POSITION_Y,
                                        Constants_s::START_POSITION_Z),
                rigidbody::Vector3D_s(0, Constants_s::START_VELOCITY, 0),
                Constants_s::BALL_MASS),
    BallState(BallState_e::ON_GROUND),
    LastTileType(map::TileType_e::NORMAL)
{   
    // Manage subscriptions
    PO->subscribeRecipient<msgKeyEvent_e>(this);
    PO->subscribeRecipient<msgActualTileType_s>(this);
}

} // namespace trailblazer::ball