
#include <memory>
#include <iostream>

#include <glkit/mesh/glcube.hpp>

static const char WINDOW_TITLE[] = "test";

class GameWindow_c
{
    GLFWwindow* Window = NULL;
    glkit::mesh::GLCube_c* cube;

    static void resizeCallback(GLFWwindow*, int w, int h)
    {
        glViewport(0, 0, w, h);
    }

    void processInput(GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            std::cout << "ESC" << std::endl;
            glfwSetWindowShouldClose(window, true);
        }
    }

public:
    enum class WindowState_e
    {
        OK,
        CLOSING
    };
    
    WindowState_e updateWindow()
    {
        processInput(Window);

        glClearColor(.2F, .2F, .4F, 1.F);
        glClear(GL_COLOR_BUFFER_BIT);

       cube->draw();

        glfwSwapBuffers(Window);
        glfwPollEvents();

        return (glfwWindowShouldClose(Window) ? 
                WindowState_e::CLOSING :
                WindowState_e::OK);
    }


    GameWindow_c()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

        Window = glfwCreateWindow(640, 480, WINDOW_TITLE, NULL, NULL);
        if (!Window)
        {
            std::cout << "Failed to initialize Window" << std::endl;
            glfwTerminate();
            throw 1;
        }

        glfwMakeContextCurrent(Window);
        glfwSetFramebufferSizeCallback(Window, resizeCallback);

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        {
            std::cout << "Failed to initialize OpenGL context" << std::endl;
            throw 1;
        }   

        cube = new glkit::mesh::GLCube_c(1.F, 1.F, 0.1F);
    }

    ~GameWindow_c()
    {
        glfwTerminate();
    }
};

class Game
{
    GameWindow_c GameWindow;

public:
    void gameLoop()
    {
        GameWindow_c::WindowState_e WindowState =
            GameWindow_c::WindowState_e::OK;

        while (WindowState == GameWindow_c::WindowState_e::OK)
        {
            WindowState = GameWindow.updateWindow();
        }
    }

    Game()
    {}
};


int main()
{
    Game g;
    g.gameLoop();
    return 0;
}