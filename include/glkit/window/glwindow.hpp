#pragma once

#include <string>
#include <glkit/core/ogl_headers.hpp>


namespace glkit::window
{

class GLWindow_i
{
    bool IsInitialized = false;
    GLFWwindow* Window = NULL;
  
    static void resizeCallback(GLFWwindow*, int w, int h);

    void handleESC() const;

protected:
    virtual void drawEvents() = 0;
    virtual void initEvents() = 0;
    virtual void keypressEvents() = 0;
    
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
