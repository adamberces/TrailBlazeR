#pragma once


namespace trailblazer::messaging
{

enum class GameState_e
{
    LEVEL_START,
    NORMAL,
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
    NORMAL,
    JUMPING,
    FALLING_OFF
};

} // namespace trailblazer::messaging