
#include <memory>
#include <iostream>

#include <game/gfx/renderpipeline.hpp>

static const char WINDOW_TITLE[] = "test";

class GameWindow_c
{
    GLFWwindow* Window = NULL;

    trailblazer::gfx::TilePipeline_c ppl;

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

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            ppl.config().CameraConfig.Position.Z += .05;
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            ppl.config().CameraConfig.Position.Z -= .05;
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            ppl.config().CameraConfig.Position.Y -= .05;
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            ppl.config().CameraConfig.Position.Y += .05;
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

        ppl.config().CameraConfig.Direction.X = 1;
        ppl.config().CameraConfig.Direction.Y = 0;
        ppl.config().CameraConfig.Direction.Z = 0;

        ppl.config().ModelConfig.Position.X = .1;
        ppl.config().ModelConfig.Position.Y = .2;
        ppl.config().ModelConfig.Position.Z = .3;
        ppl.config().ModelConfig.Rotation.X = 1;
        ppl.config().ModelConfig.Rotation.Y = 0;
        ppl.config().ModelConfig.Rotation.Z = 0;
        ppl.config().ModelConfig.Rotation.Angle += 1;

        ppl.run();

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

        ppl.config().CameraConfig.Position.X = -3;
        ppl.config().CameraConfig.Position.Y = 0;
        ppl.config().CameraConfig.Position.Z = 0;

        ppl.config().ProjectionConfig.FOV = 45.F;
        ppl.config().ProjectionConfig.ScreenWidth = 640;
        ppl.config().ProjectionConfig.ScreenHeight = 480;
        ppl.config().ProjectionConfig.NearPlane = 0.1F;
        ppl.config().ProjectionConfig.FarPlane = 100.F;

        ppl.config().ModelConfig.Rotation.Angle = 0;

        ppl.setup();
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