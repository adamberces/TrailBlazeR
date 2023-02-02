#include <GLFW/glfw3.h>
#include <memory>
#include <iostream>


static const char WINDOW_TITLE[] = "TrailBlazeR";

class Game
{
    GameWindow w;

    GameLoop()
    {

    }

    Game()
    {}
};

class GameWindow
{
    GLFWwindow* Window = NULL;

    void resizeCallback(GLFWwindow*, int w, int h)
    {
        glViewport(0, 0, w, h);
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
        
        glfwSwapBuffers(Window);
        glfwPollEvents();

        return (glfwWindowShouldClose(Window) ? 
                WindowState_e::CLOSING :
                WindowState_e::OK);
    }


    GameWindow()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        Window = glfwCreateWindow(640, 480, WINDOW_TITLE, NULL, NULL);
        if (!Window)
        {
            std::cout << "Failed to initialize Window" << std::endl;
            glfwTerminate();
            throw 1;
        }

        glfwMakeContextCurrent(Window);
        glfwSetFramebufferSizeCallback(Window, resizeCallback);

    }

    ~GameWindow()
    {
        glfwTerminate();
    }
};



int main()
{
    Game g;

       return 0;
}