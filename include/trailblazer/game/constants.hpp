#pragma once

#include <string_view>


namespace trailblazer
{

using namespace std::literals;

struct Files_s
{
    static constexpr auto AUDIO_PATH = "./assets/audio/"sv;
    static constexpr auto BACKGROUNDS_PATH = "./assets/backgrounds/"sv;
    static constexpr auto FONT_PATH = "./assets/fonts/font"sv;
};

struct Constants_s
{
    static constexpr int WINDOW_WIDTH = 1024;
    static constexpr int WINDOW_HEIGHT = 768;

    static constexpr int INITIAL_LIVES = 5;
    /// This number is added to Lives if a level is cleared
    static constexpr int LEVEL_WON_BONUS = 1;
    static constexpr float WAIT_TIME = 4.F; //sec

    /// Number of map tiles per row
    static constexpr int MAP_WIDTH = 5;
    /// Number of tiles displayed at a time on the scene
    static constexpr int MAX_DISPLAYED_TILES = 25;

    /// Ball properties
    static constexpr float BALL_DIAMETER = .25F;
    static constexpr float BALL_MASS = 2.F;
    static constexpr float BALL_COLOR_R = 1.F;
    static constexpr float BALL_COLOR_G = 0.F;
    static constexpr float BALL_COLOR_B = 0.F;

    /// Global physics constants
    static constexpr float PI = 3.14159265359F;
    
    static constexpr float FRICITON_COEFFICIENT_X = 0.2F;
    static constexpr float FRICITON_COEFFICIENT_Z = 5.F;
    static constexpr float FRICITON_COEFFICIENT_ENDLEVEL = 0.5F;
    
    static constexpr float GRAVITY = 9.81F;
    static constexpr float SPHERE_DRAG_COEFFICIENT = 0.47F;
    static constexpr float AIR_DENSITY = 1.29F;

    static constexpr float BOUNCE_VELOCITY_THRESHOLD = 1.F;
    static constexpr float FRICTION_VELOCITY_THRESHOLD = 0.001F;

    /// Ball control constants
    static constexpr float JUMP_VELOCITY = 4.F;
    static constexpr float JUMP_TIME = 0.1F;

    static constexpr float START_POSITION_X = 2.F;
    static constexpr float START_POSITION_Y = 0.F;
    static constexpr float START_POSITION_Z = 0.F;

    static constexpr float START_VELOCITY = 1.F;
    static constexpr float SPEEDUP_ADDED_VELOCITY = 0.1F;

    /// Force applied to the ball when moving left/right
    static constexpr float CONTROL_FORCE_X = 10.F;
};

} // namespace trailblazer