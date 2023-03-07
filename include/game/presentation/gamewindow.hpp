#pragma once

#include <memory>
#include <glkit/window/glwindow.hpp>


namespace trailblazer::presentation
{

class GameWindow_c : public glkit::window::GLWindow_i
{
public:
    using glkit::window::GLWindow_i::GLWindow_i;

    enum class KeyEvent_e
    {
        NONE,
        LEFT,
        RIGHT,
        JUMP
    };

private:
    KeyEvent_e LastKeyEvent;

public:
    KeyEvent_e lastKeyEvent() const
    {
        return LastKeyEvent;
    }

    void handleKeypressEvents() override
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