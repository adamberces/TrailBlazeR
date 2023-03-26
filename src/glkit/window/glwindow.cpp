#include <iostream>
#include <glkit/window/glwindow.hpp>


namespace glkit::window
{

/////////////////////////////////////////////////////////////////////////////////////////
// GLWindow_i implementation

void GLWindow_i::resizeCallback(GLFWwindow*, int w, int h)
{
    glViewport(0, 0, w, h);
}

void GLWindow_i::handleESC() const 
{
    if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(Window, true);
    }
}

bool GLWindow_i::isPressed(int key) const
{
    bool ret = false;

    if (glfwGetKey(Window, key) == GLFW_PRESS)
    {
        ret = true;
    }

    return ret;
}

GLWindow_i::WindowState_e GLWindow_i::updateWindow()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    handleESC();
    handleKeypressEvents();

    glfwSwapBuffers(Window);
    glfwPollEvents();

    return (glfwWindowShouldClose(Window) ? 
            WindowState_e::CLOSING :
            WindowState_e::OK);
}


GLWindow_i::GLWindow_i(int width, int height, std::string title)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

    Window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!Window)
    {
        std::cout << "Failed to initialize Window" << std::endl;
        glfwTerminate();
        throw 1;
    }

    glfwMakeContextCurrent(Window);
    glfwSetFramebufferSizeCallback(Window, resizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        throw 1;
    } 

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);  
}

GLWindow_i::~GLWindow_i()
{
    glfwTerminate();
}

} // namespace glkit::window
