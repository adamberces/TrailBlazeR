#pragma once

#include <string>
#include <glkit/core/ogl_headers.hpp>


namespace glkit::window
{

/////////////////////////////////////////////////////////////////////////////////////////
// Interface class represents and displays a GLFW window.
// Provides convient functions for testing keypress events.
// The child classes has to override handleKeypressEvents where the
// desired keypress events can be tested and handled
class GLWindow_i
{
    GLFWwindow* Window = NULL;

    static void resizeCallback(GLFWwindow*, int w, int h);
    void handleESC() const;

protected:
    virtual void handleKeypressEvents() = 0;
    bool isPressed(int key) const;

public:
    enum class WindowState_e
    {
        OK,
        CLOSING
    };

    WindowState_e updateWindow();
    GLWindow_i(int width, int height, std::string title);
    ~GLWindow_i();
};

} // namespace glkit::window
