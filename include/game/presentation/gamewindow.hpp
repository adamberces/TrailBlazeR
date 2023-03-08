#pragma once

#include <memory>
#include <glkit/window/glwindow.hpp>
#include <game/controls/keymessaging.hpp>

namespace trailblazer::presentation
{

class GameWindow_c : public glkit::window::GLWindow_i
{
public:
    using glkit::window::GLWindow_i::GLWindow_i;

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