#pragma once

#include <glkit/functors/functor_types.hpp>


namespace trailblazer::messaging
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

enum class KeyEvent_e
{
    NONE,
    LEFT,
    RIGHT,
    JUMP
};

enum class BallEvent_e
{
    ROLLING,
    JUMPING,
    FALLING,
    FALLING_OFF
};


// Create a strong type for wrapping the Ball position
// so it will have an unique signature when dealing with 
// message types, if we may want to use another point3d_t
// in the future...

struct BallPosition_t
{
    glkit::functors::point3d_t Position;
};

} // namespace trailblazer::messaging