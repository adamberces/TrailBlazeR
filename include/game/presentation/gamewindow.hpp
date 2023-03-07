#pragma once

#include <memory>
#include <glkit/window/glwindow.hpp>


namespace trailblazer::presentation
{

class GameWindow_c : public glkit::window::GLWindow_i
{
public:
    using glkit::window::GLWindow_i::GLWindow_i;

    enum class KeyEvents_e
    {
        NONE,
        LEFT,
        RIGHT,
        JUMP
    };

private:
    KeyEvents_e LastKeyEvent;


public:
    void setBall(shared_ptr<ball::Ball_c>& ball)
    {
        Ball = ball;
    }

    void setMap(shared_ptr<map::Map_c>& map)
    {
        Map = map;
    }

    KeyEvents_e lastKeyEvent() const
    {
        return LastKeyEvent;
    }

    void initEvents() override
    {
    }

    void drawEvents() override
    {
        Map->draw();
        Ball->draw();
    }

    void keypressEvents() override
    {
        LastKeyEvent = KeyEvent_e::NONE;

        if (isPressed(GLFW_KEY_A))
        {
            LastKeyEvent = KeyEvent_e::LEFT;
        }
        else if (isPressed(GLFW_KEY_D))
        {
            LastKeyEvent = KeyEvent_e::RIGHT;
        }
        else if (isPressed(GLFW_KEY_SPACE))
        {
            LastKeyEvent = KeyEvent_e::JUMP;
        }
    }
};

} // namespace trailblazer::presentation