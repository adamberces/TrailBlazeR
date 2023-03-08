#pragma once

#include <string>
#include <glkit/core/ogl_headers.hpp>
#include <glkit/window/scene.hpp>


namespace glkit::window
{

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

    WindowState_e updateWindow(Scene_i*);

    GLWindow_i(int width, int height, std::string title);

    ~GLWindow_i();
};

} // namespace glkit::window
