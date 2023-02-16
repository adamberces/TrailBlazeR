
#include <memory>
#include <iostream>

#include <glkit/core/shaderprogram.hpp>
#include <glkit/core/vertexarray.hpp>

static const char WINDOW_TITLE[] = "TrailBlazeR";

class GameWindow_c
{
    GLFWwindow* Window = NULL;

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

    ShaderProgram_c* sp;
    ArrayBuffer_c<float>* vbo;
    ArrayBuffer_c<unsigned int>* ebo;
    VertexArrayObject_c<float>* vao;
    
    WindowState_e updateWindow()
    {
        processInput(Window);

        glClearColor(.2F, .2F, .4F, 1.F);
        glClear(GL_COLOR_BUFFER_BIT);
        sp->use();
        vao->bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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

        ShaderSourceList_s test;
        test.FragmentShaderPath = "./assets/shaders/f_uniformcolor.glsl";
        test.VertexShaderPath = "./assets/shaders/v_simple.glsl";
        sp = new ShaderProgram_c(test);

        std::vector<float> vertices = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
        };
        std::vector<unsigned int> indices = {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
        };

        vao = new VertexArrayObject_c<float>();
        vao->copyVertexData(vertices, indices);
        vao->setVertexAttribute(0, 3);
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